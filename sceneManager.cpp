#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"


DWORD CALLBACK loadingThread(LPVOID prc)
{
	//교체 대기 중인 씬 초기화
	sceneManager::_readyScene->init();

	sceneManager::_currentScene = sceneManager::_readyScene;

	sceneManager::_loadingScene->release();
	sceneManager::_loadingScene = NULL;
	sceneManager::_readyScene = NULL;

	//반환형이 DWORD 형이라 정수로 반환
	return 0;
}

gameNode* sceneManager::_currentScene = NULL;
gameNode* sceneManager::_loadingScene = NULL;
gameNode* sceneManager::_readyScene = NULL;

sceneManager::sceneManager()
{
}


sceneManager::~sceneManager()
{
}

HRESULT sceneManager::init()
{
	_currentScene = _loadingScene = _readyScene = NULL;
	_fadeIn = _fadeOut = false;
	_alpha = 255;

	_fadeIn_cbFunction = _fadeOut_cbFunction = NULL;
	_fadeOut_cbFunctionParameter = _fadeIn_cbFunctionParameter = NULL;
	_obj = NULL;

	return S_OK;
}

void sceneManager::release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	//맵 안을 돌아서
	for (; miSceneList != _mSceneList.end();)
	{
		//씬이 존재한다면
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();

			SAFE_DELETE(miSceneList->second);

			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update();

	if (_fadeIn)
	{
		_alpha -= _speed;
		if (_alpha <= 0)
		{
			_alpha = 0;
			_fadeIn = false;
			if (_obj == NULL)
			{
				if (_fadeIn_cbFunction != NULL) _fadeIn_cbFunction();
				_fadeIn_cbFunction = NULL;
			}
			else
			{
				_fadeIn_cbFunctionParameter(_obj);
				_fadeIn_cbFunctionParameter = NULL;
				_obj = NULL;
			}
		}
	}
	if (_fadeOut)
	{
		_alpha += _speed;
		if (_alpha >= 255)
		{
			_alpha = 255;
			_fadeOut = false;
			if (_obj == NULL)
			{
				if (_fadeOut_cbFunction != NULL) _fadeOut_cbFunction();
				_fadeOut_cbFunction = NULL;
			}
			else
			{
				_fadeOut_cbFunctionParameter(_obj);
				_fadeOut_cbFunctionParameter = NULL;
				_obj = NULL;
			}
		}
	}
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render();

	if (_fadeIn || _fadeOut)
	{
		IMAGEMANAGER->findImage("fade")->alphaRender(_currentScene->getMemDC(), _alpha);
	}
}

//씬 추가
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	//씬이 없다면 널값 반환
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

//로딩 씬 추가
gameNode* sceneManager::addLoadingScene(string loadingSceneName, gameNode* scene)
{
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	//이터레이터로 바꾸고자 하는 씬을 찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	//없다면 FAIL
	if (find == _mSceneList.end()) return E_FAIL;
	//바꾸려는 씬이 현재씬이면 S_OK
	if (find->second == _currentScene) return S_OK;

	//씬 바꾸는게 성공하면
	if (SUCCEEDED(find->second->init()))
	{
		if (_currentScene) _currentScene->release();
		//교체될 씬을 현재씬에 넣어준다
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(string sceneName, string loadingSceneName)
{
	//이터레이터로 바꾸고자 하는 씬을 찾는다
	mapSceneIter find = _mSceneList.find(sceneName);

	//없다면 FAIL
	if (find == _mSceneList.end()) return E_FAIL;
	//바꾸려는 씬이 현재씬이면 S_OK
	if (find->second == _currentScene) return S_OK;
	//
	mapSceneIter findLoading = _mLoadingSceneList.find(loadingSceneName);

	if (find == _mLoadingSceneList.end()) return changeScene(loadingSceneName);

	//씬 바꾸는게 성공하면
	if (SUCCEEDED(find->second->init()))
	{
		if (_currentScene) _currentScene->release();

		_loadingScene = findLoading->second;

		_readyScene = find->second;
		
		CloseHandle(CreateThread(NULL, 0, loadingThread, NULL, 0, &_loadThreadID));
	}

	return E_FAIL;
}

void sceneManager::fadeIn(CALLBACK_FUNCTION cbFunction,int speed)
{
	if (_fadeIn || _fadeOut) return;
	_fadeIn_cbFunction = cbFunction;
	_fadeIn_cbFunctionParameter = NULL;
	_obj = NULL;
	_fadeIn = true;
	_alpha = 255;
	_speed = speed;
}

void sceneManager::fadeOut(CALLBACK_FUNCTION cbFunction, int speed)
{
	if (_fadeIn || _fadeOut) return;
	_fadeOut_cbFunction = cbFunction;
	_fadeOut_cbFunctionParameter = NULL;
	_obj = NULL;
	_fadeOut = true;
	_alpha = 0;
	_speed = speed;
}

void sceneManager::fadeIn(CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj, int speed)
{
	if (_fadeIn || _fadeOut) return;
	_fadeIn_cbFunction = NULL;
	_fadeIn_cbFunctionParameter = cbFunction;
	_obj = obj;
	_fadeIn = true;
	_alpha = 255;
	_speed = speed;
}

void sceneManager::fadeOut(CALLBACK_FUNCTION_PARAMETER cbFunction, void * obj, int speed)
{
	if (_fadeIn || _fadeOut) return;
	_fadeOut_cbFunction = NULL;
	_fadeOut_cbFunctionParameter = cbFunction;
	_obj = obj;
	_fadeOut = true;
	_alpha = 0;
	_speed = speed;
}
