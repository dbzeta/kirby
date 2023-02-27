#include "stdafx.h"
#include "kirby.h"
#include "fireKirby.h"
#include "beamKirby.h"
#include "mapManager.h"
#include "enemyManager.h"

kirby::kirby()
{
}


kirby::~kirby()
{
}

HRESULT kirby::init()
{


	_cx = 100.0f;
	_cy = WINSIZEY - 150.0f;
	_startCx = _startCy = 0.0f;

	_dir = DIRECTION_STOP;
	_preState = RIGHT_STOP;
	_state = RIGHT_STOP;

	_count = 0;

	_isDashReady = false;
	_isPixelCollision = _isRectCollision = _isPixelCollisionUp = false;
	_isGameEnd = false;

	_isRight = true;
	_isFull = false;
	_isPushButton = false;
	_isAttack = false;

	_isOnTheDoor = false;

	_hp = 6;
	_life = 3;
	_mode = MODE_NORMAL;

	_currentKirby = new kirbyBase;
	_currentKirby->setKirbyMemoryLink(this);
	_currentKirby->init();


	_rc = RectMakeCenter(_cx, _cy, _currentKirby->getImage()->getFrameWidth(), _currentKirby ->getImage()->getFrameHeight());

	return S_OK;
}

void kirby::release()
{
	_currentKirby->release();
	SAFE_DELETE(_currentKirby);
}

void kirby::update()
{
	float elapsedTime = TIMEMANAGER->getElapsedTime();
	_currentKirby->update();

	checkState();
	keyControl();

	if (!_isPixelCollision) 
		_cy += 200 * elapsedTime;
	checkPixelCollision();
	checkRectCollision();


	int collisionRight = _cx + _currentKirby->getImage()->getFrameWidth() / 2 - 5;
	int collisionBottom = _cy + _currentKirby->getImage()->getFrameHeight() / 2 - 5;

	_collisionRC = { collisionRight - 50, collisionBottom - 45, collisionRight, collisionBottom };
	_rc = RectMakeCenter(_cx, _cy, _currentKirby->getImage()->getFrameWidth(), _currentKirby ->getImage()->getFrameHeight());


}

void kirby::render()
{

	_currentKirby->render(_mm->getFocus());
}

void kirby::keyControl()
{

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_em->addEnemy(_cx + 200, _cy, 4.0f, 200, 2, true);
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_mode = MODE_FIRE;
		changeMode(_mode);
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_mode = MODE_BEAM;
		changeMode(_mode);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_mode = MODE_NORMAL;
		changeMode(_mode);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && !_isAttack && (_state != LEFT_EATING) &&

		(_state != RIGHT_EATING))
	{
		_isRight = false;
		_isPushButton = true;
		if (_state == LEFT_FLY ||
			_state == RIGHT_FLY)
		{
			_dir = DIRECTION_LEFT;
			_state = LEFT_FLY;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_FLY_UP ||
			_state == RIGHT_FLY_UP)
		{
			_dir = DIRECTION_LEFT;
			_state = LEFT_FLY_UP;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_FLY_DOWN ||
			_state == RIGHT_FLY_DOWN)
		{
			_dir = DIRECTION_LEFT;
			_state = LEFT_FLY_DOWN;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_STOP ||
			_state == RIGHT_STOP ||
			_state == RIGHT_MOVE)
		{

			if (_isDashReady) _state = LEFT_DASH;
			else _state = LEFT_MOVE;
			_isDashReady = true;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_SIT ||
			_state == RIGHT_SIT)
		{
			_state = LEFT_SIT;
			_currentKirby->setMotion();
		}
		else if (_state == RIGHT_DASH)
		{
			_state = LEFT_DASH;
			_currentKirby->setMotion();
		}
		else if (_state == RIGHT_JUMP_UP)
		{
			_state = LEFT_JUMP_UP;
			_currentKirby->setMotion();
		}
		else if (_state == RIGHT_JUMP_TURN)
		{
			_state = LEFT_JUMP_TURN;
			_currentKirby->setMotion();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_isPushButton = false;
		if (_state == LEFT_MOVE ||
			_state == LEFT_DASH)
		{
			_state = LEFT_STOP;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_FLY_UP ||
			_state == LEFT_FLY_DOWN ||
			_state == LEFT_FLY)
		{
			_dir = DIRECTION_STOP;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && !_isAttack && (_state != LEFT_EATING) &&

		(_state != RIGHT_EATING))
	{
		_isRight = true;
		_isPushButton = true;

		if (_state == LEFT_FLY ||
			_state == RIGHT_FLY)
		{
			_dir = DIRECTION_RIGHT;
			_state = RIGHT_FLY;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_FLY_UP ||
			_state == RIGHT_FLY_UP)
		{
			_dir = DIRECTION_RIGHT;
			_state = RIGHT_FLY_UP;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_FLY_DOWN ||
			_state == RIGHT_FLY_DOWN)
		{
			_dir = DIRECTION_RIGHT;
			_state = RIGHT_FLY_DOWN;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_STOP ||
			_state == RIGHT_STOP ||
			_state == LEFT_MOVE)
		{
			if (_isDashReady) _state = RIGHT_DASH;
			else _state = RIGHT_MOVE;
			_isDashReady = true;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_SIT ||
			_state == RIGHT_SIT)
		{
			_state = RIGHT_SIT;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_DASH)
		{
			_state = RIGHT_DASH;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_JUMP_UP)
		{
			_state = RIGHT_JUMP_UP;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_JUMP_TURN)
		{
			_state = RIGHT_JUMP_TURN;
			_currentKirby->setMotion();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_isPushButton = false;
		if (_state == RIGHT_MOVE ||
			_state == RIGHT_DASH)
		{
			_state = RIGHT_STOP;
			_currentKirby->setMotion();
		}
		else if (_state == RIGHT_FLY_UP ||
			_state == RIGHT_FLY_DOWN ||
			_state == RIGHT_FLY)
		{
			_dir = DIRECTION_STOP;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		// 문이 있는 위치 일 때 ( 노란색 픽셀 충돌 ) && 내가 STOP일때 (날때는 검사 안하게)
		if (checkDoorPixel() && (_state == LEFT_STOP || _state == RIGHT_STOP))
		{
			// 석호한테 rect값을 준 후 사용 가능한 문 인지 확인. 
			_isOnTheDoor = _mm->getDoorCheck(&_rc);
		}

		// 이게 사용가능한 문 일때
		if (_isOnTheDoor)
		{
			if (_state == LEFT_STOP) _state = LEFT_OPEN_DOOR;
			else if (_state == RIGHT_STOP) _state = RIGHT_OPEN_DOOR;

			_currentKirby->setMotion();
		}

		// 사용 가능한 문 이 아니면
		else
		{
			// FLY_EAT 상태 후 UP으로 바뀐다.
			if ((_state == RIGHT_STOP ||
				_state == RIGHT_MOVE ||
				_state == RIGHT_DASH) &&
				!_isFull)
			{
				SOUNDMANAGER->play("fly", atof(DATABASE->getElementData("effectVolume").c_str()));
				_state = RIGHT_FLY_EAT;
				_currentKirby->setMotion();
			}
			// 위 방향키를 누르면 FLY_UP이 되어 Y좌표가 작아진다.
			else if (_state == RIGHT_FLY ||
				_state == RIGHT_FLY_DOWN)
			{
				SOUNDMANAGER->play("fly", atof(DATABASE->getElementData("effectVolume").c_str()));
				_state = RIGHT_FLY_UP;
				_currentKirby->setMotion();
			}

			// FLY_EAT 상태 후 UP으로 바뀐다.
			if ((_state == LEFT_STOP ||
				_state == LEFT_MOVE ||
				_state == LEFT_DASH) &&
				!_isFull)
			{
				SOUNDMANAGER->play("fly", atof(DATABASE->getElementData("effectVolume").c_str()));
				_state = LEFT_FLY_EAT;
				_currentKirby->setMotion();
			}
			// 위 방향키를 누르면 FLY_UP이 되어 Y좌표가 작아진다.
			else if (_state == LEFT_FLY ||
				_state == LEFT_FLY_DOWN)
			{
				SOUNDMANAGER->play("fly", atof(DATABASE->getElementData("effectVolume").c_str()));
				_state = LEFT_FLY_UP;
				_currentKirby->setMotion();
			}

		}

	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		// UP이 아닐땐 DOWN
		if (_state == RIGHT_FLY_UP)
		{
			_state = RIGHT_FLY_DOWN;
			_currentKirby->setMotion();
		}
		if (_state == LEFT_FLY_UP)
		{
			_state = LEFT_FLY_DOWN;
			_currentKirby->setMotion();
		}


	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{

		if (_state == RIGHT_STOP ||
			_state == RIGHT_MOVE)
		{
			_state = RIGHT_SIT;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_STOP ||
			_state == LEFT_MOVE)
		{
			_state = LEFT_SIT;
			_currentKirby->setMotion();
		}

		if (_isFull) _isFull = false;

	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_state == RIGHT_SIT)
		{
			_state = RIGHT_STOP;
			_currentKirby->setMotion();
		}
		if (_state == LEFT_SIT)
		{
			_state = LEFT_STOP;
			_currentKirby->setMotion();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// 노말 모드 아닐 때
		if (_mode != MODE_NORMAL)
		{
			if (_state == RIGHT_FLY ||
				_state == RIGHT_FLY_UP ||
				_state == RIGHT_FLY_DOWN)
			{
				_state = RIGHT_FALL;
				_currentKirby->setMotion();
			}
			else if (_state == LEFT_FLY ||
				_state == LEFT_FLY_UP ||
				_state == LEFT_FLY_DOWN)
			{
				_state = LEFT_FALL;
				_currentKirby->setMotion();
			}
			else attack();
		}
		// 노말 모드 였을 때
		else
		{
			// 적을 안 먹었을 때
			if (!_isFull)
			{
				// 처음 삼키기 했을 때
				if (_state == RIGHT_STOP ||
					_state == RIGHT_MOVE ||
					_state == RIGHT_DASH)
				{
					_state = RIGHT_EAT;
					_currentKirby->setMotion();
				}
				// 앉아있을떄 -> KICK
				else if (_state == RIGHT_SIT)
				{
					_state = RIGHT_KICK;
					_currentKirby->setMotion();
				}
				// FLY 상태였다면 FALL
				else if (_state == RIGHT_FLY ||
					_state == RIGHT_FLY_UP ||
					_state == RIGHT_FLY_DOWN)
				{
					_dir = DIRECTION_STOP;
					_state = RIGHT_FALL;
					_currentKirby->setMotion();
				}
			}
			// 적을 먹은 상태일때
			else if (_isFull)
			{
				attack();
			}

			// 적을 안 먹었을 때
			if (!_isFull)
			{
				// 처음 삼키기 했을 때
				if (_state == LEFT_STOP ||
					_state == LEFT_MOVE ||
					_state == LEFT_DASH)
				{
					_state = LEFT_EAT;
					_currentKirby->setMotion();
				}
				else if (_state == LEFT_SIT)
				{
					_state = LEFT_KICK;
					_currentKirby->setMotion();
				}
				// FLY 상태였다면 FALL
				else if (_state == LEFT_FLY ||
					_state == LEFT_FLY_UP ||
					_state == LEFT_FLY_DOWN)
				{
					_dir = DIRECTION_STOP;
					_state = LEFT_FALL;
					_currentKirby->setMotion();
				}
			}
			// 적을 먹었을 때
			else if (_isFull)
			{
				attack();
			}
		}

	}
	if (KEYMANAGER->isOnceKeyUp('X'))
	{
		// 노말 모드
		if (_mode == MODE_NORMAL)
		{
			if (_state == RIGHT_EAT || _state == RIGHT_EATING)
			{
				SOUNDMANAGER->stop("eat");
				_count = 0;
				_state = RIGHT_STOP;
				_currentKirby->setMotion();
			}
			else if (_state == LEFT_EAT || _state == LEFT_EATING)
			{
				SOUNDMANAGER->stop("eat");
				_count = 0;
				_state = LEFT_STOP;
				_currentKirby->setMotion();
			}
		}
		// 불커비
		else if (_mode == MODE_FIRE)
		{
			if (_state == LEFT_ATTACK)
			{
				_state = LEFT_STOP;
				_isAttack = false;
				_currentKirby->setMotion();
			}
			else if (_state == RIGHT_ATTACK)
			{
				_state = RIGHT_STOP;
				_isAttack = false;
				_currentKirby->setMotion();
			}
		}
		// 빔커비
		else if (_mode == MODE_BEAM)
		{

		}

	}


	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		// 처음 눌렀을때는 JUMP (RIGHT)
		if ((_state == RIGHT_STOP ||
			_state == RIGHT_MOVE ||
			_state == RIGHT_DASH) &&
			_isPixelCollision)
		{
			SOUNDMANAGER->stop("eat");
			_startCy = _cy;
			_state = RIGHT_JUMP_UP;
			_currentKirby->setMotion();
		}
		// 두번 눌렀을때는 FLY (LEFT)
		else if (_state == RIGHT_JUMP_UP ||
			_state == RIGHT_JUMP_TURN)
		{
			SOUNDMANAGER->play("fly", atof(DATABASE->getElementData("effectVolume").c_str()));
			_state = RIGHT_FLY_EAT;
			_currentKirby->setMotion();
		}
		else if (_state == RIGHT_FLY_DOWN ||
			_state == RIGHT_FLY_UP ||
			_state == RIGHT_FLY)
		{
			SOUNDMANAGER->play("fly", atof(DATABASE->getElementData("effectVolume").c_str()));
			_state = RIGHT_FLY_UP;
			_currentKirby->setMotion();
		}

		// 처음 눌렀을때는 JUMP (RIGHT)
		if ((_state == LEFT_STOP ||
			_state == LEFT_MOVE ||
			_state == LEFT_DASH) &&
			_isPixelCollision)
		{
			SOUNDMANAGER->play("jump", atof(DATABASE->getElementData("effectVolume").c_str()));
			_startCy = _cy;
			_state = LEFT_JUMP_UP;
			_currentKirby->setMotion();
		}
		// 두번 눌렀을때는 FLY (LEFT)
		else if (_state == LEFT_JUMP_UP ||
			_state == LEFT_JUMP_TURN)
		{
			SOUNDMANAGER->play("fly", atof(DATABASE->getElementData("effectVolume").c_str()));

			_state = LEFT_FLY_EAT;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_FLY_DOWN ||
			_state == LEFT_FLY_UP ||
			_state == LEFT_FLY)
		{
			SOUNDMANAGER->play("fly", atof(DATABASE->getElementData("effectVolume").c_str()));

			_state = LEFT_FLY_UP;
			_currentKirby->setMotion();
		}

	}
	if (KEYMANAGER->isOnceKeyUp('Z'))
	{
		if (_state == RIGHT_JUMP_UP)
		{
			_state = RIGHT_JUMP_TURN;
			_currentKirby->setMotion();
		}
		else if (_state == RIGHT_FLY_UP)
		{
			_state = RIGHT_FLY_DOWN;
			_currentKirby->setMotion();
		}
		if (_state == LEFT_JUMP_UP)
		{
			_state = LEFT_JUMP_TURN;
			_currentKirby->setMotion();
		}
		else if (_state == LEFT_FLY_UP)
		{
			_state = LEFT_FLY_DOWN;
			_currentKirby->setMotion();
		}
	}


}

void kirby::checkState()
{
	animation* motion = _currentKirby->getMotion();

	float elapsedTime = TIMEMANAGER->getElapsedTime();

	switch (_state)
	{
		// 킥을 하면 약 1.5?초 유지 후 돌아온다.
	case LEFT_KICK:
		if (_cx - _currentKirby->getImage()->getFrameWidth() / 2 > 0) _cx -= 250 * elapsedTime;
		_count++;
		if (_count > 25)
		{
			_state = LEFT_STOP;
			_currentKirby->setMotion();
			_count = 0;
		}
		break;

	case RIGHT_KICK:
		_cx += 250 * elapsedTime;
		_count++;
		if (_count > 25)
		{
			_state = RIGHT_STOP;
			_currentKirby->setMotion();
			_count = 0;
		}
		break;

	case LEFT_EAT:
		_count++;
		_isRight = false;
		// 계속 삼키키
		if (_count > 20)
		{
			_state = LEFT_EATING;
			_currentKirby->setMotion();
		}
		break;
	case RIGHT_EAT:
		_count++;
		_isRight = true;
		// 계속 삼키키
		if (_count > 20)
		{
			_state = RIGHT_EATING;
			_currentKirby->setMotion();
		}
		break;

	case LEFT_THROW:
		if (!_currentKirby->getMotion()->isPlay())
		{
			_state = LEFT_STOP;
			_isFull = false;
			_currentKirby->setMotion();
		}break;
	case RIGHT_THROW:
		if (!_currentKirby->getMotion()->isPlay())
		{
			_state = RIGHT_STOP;
			_isFull = false;
			_currentKirby->setMotion();
		}break;

	case LEFT_FALL:
		if (!motion->isPlay())
		{
			_state = LEFT_STOP;
			_currentKirby->setMotion();
		}
		break;
	case RIGHT_FALL:
		if (!motion->isPlay())
		{
			_state = RIGHT_STOP;
			_currentKirby->setMotion();
		}
		break;

	case LEFT_FLY_EAT:
		if (!motion->isPlay())
		{
			_state = LEFT_FLY_DOWN;
			_currentKirby->setMotion();
		}
		break;
	case RIGHT_FLY_EAT:
		if (!motion->isPlay())
		{
			_state = RIGHT_FLY_DOWN;
			_currentKirby->setMotion();
		}
		break;
	case LEFT_STOP:	case RIGHT_STOP: case LEFT_LOW_STOP_UP: case RIGHT_LOW_STOP_UP:
	case LEFT_LOW_STOP_DOWN:
	case RIGHT_LOW_STOP_DOWN:
	case LEFT_HIGH_STOP_UP:
	case RIGHT_HIGH_STOP_UP:
	case LEFT_HIGH_STOP_DOWN:
	case RIGHT_HIGH_STOP_DOWN:
	case LEFT_SIT:
	case RIGHT_SIT:
	case LEFT_LOW_SIT_DOWN:
	case RIGHT_LOW_SIT_DOWN:
	case LEFT_LOW_SIT_UP:
	case RIGHT_LOW_SIT_UP:
	case LEFT_HIGH_SIT_DOWN:
	case RIGHT_HIGH_SIT_DOWN:
	case LEFT_HIGH_SIT_UP:
	case RIGHT_HIGH_SIT_UP:
		break;
	case LEFT_MOVE: case LEFT_LOW_MOVE: case LEFT_HIGH_MOVE:
		if (_cx - _currentKirby->getImage()->getFrameWidth() / 2 > 0) _cx -= 200 * elapsedTime;
		break;
	case RIGHT_MOVE: case RIGHT_LOW_MOVE: case RIGHT_HIGH_MOVE:
		_cx += 200 * elapsedTime;
		break;
	case LEFT_DASH:
		if (_cx - _currentKirby->getImage()->getFrameWidth() / 2 > 0) _cx -= 400 * elapsedTime;
		break;
	case RIGHT_DASH:
		_cx += 400 * elapsedTime;
		break;
	case LEFT_FLY_UP: case RIGHT_FLY_UP:
		if (_cy - _currentKirby->getImage()->getFrameHeight() / 2 > 0) _cy -= 450 *

			elapsedTime;
		break;
	case LEFT_FLY_DOWN:
		if (_isPixelCollision)
		{
			_state = LEFT_FLY;
			_currentKirby->setMotion();
		}
		break;
	case RIGHT_FLY_DOWN:
		if (_isPixelCollision)
		{
			_state = RIGHT_FLY;
			_currentKirby->setMotion();
		}

		break;
	case LEFT_FLY:
		break;
	case RIGHT_FLY:
		break;
	case LEFT_JUMP_UP:
		if (_cy > 0) _cy -= 600 * elapsedTime;
		if (_startCy - _cy > _currentKirby->getImage()->getFrameHeight() * 2 ||

			_isPixelCollisionUp)
		{
			_state = LEFT_JUMP_TURN;
			_currentKirby->setMotion();
		}break;
	case RIGHT_JUMP_UP:
		if (_cy > 0) _cy -= 600 * elapsedTime;
		if (_startCy - _cy > _currentKirby->getImage()->getFrameHeight() * 2 ||

			_isPixelCollisionUp)
		{
			_state = RIGHT_JUMP_TURN;
			_currentKirby->setMotion();
		}break;
	case LEFT_JUMP_TURN:
		if (_isPixelCollision)
		{
			_state = LEFT_JUMP_DOWN;
			_currentKirby->setMotion();
		}
		break;
	case RIGHT_JUMP_TURN:
		if (_isPixelCollision)
		{
			_state = RIGHT_JUMP_DOWN;
			_currentKirby->setMotion();
		}
		break;
	case LEFT_JUMP_DOWN:
		if (!_currentKirby->getMotion()->isPlay())
		{
			_isPixelCollisionUp = false;
			_state = LEFT_STOP;
			_currentKirby->setMotion();
		}break;
	case RIGHT_JUMP_DOWN:
		if (!_currentKirby->getMotion()->isPlay())
		{
			_isPixelCollisionUp = false;
			_state = RIGHT_STOP;
			_currentKirby->setMotion();
		}break;
	case LEFT_EATING:
		eat();
		break;
	case RIGHT_EATING:
		eat();
		break;
	case LEFT_OPEN_DOOR:
		if (!_currentKirby->getMotion()->isPlay())
		{
			_state = LEFT_STOP;
			_currentKirby->setMotion();
			_isOnTheDoor = false;
		}break;
	case RIGHT_OPEN_DOOR:
		if (!_currentKirby->getMotion()->isPlay())
		{
			_state = RIGHT_STOP;
			_currentKirby->setMotion();
			_isOnTheDoor = false;
		}break;
	case LEFT_ATTACK:
		break;
	case RIGHT_ATTACK:
		break;
	case LEFT_RETURN:
		break;
	case RIGHT_RETURN:
		break;
	case LEFT_CRASH:
		_cx += 250 * elapsedTime;
		if (!_currentKirby->getMotion()->isPlay())
		{
			if (_mode != MODE_NORMAL)
			{
				_mode = MODE_NORMAL;
				changeMode(_mode);
			}
			_state = LEFT_STOP;
			_currentKirby->setMotion();
		}
		break;
	case RIGHT_CRASH:
		if (_cx - _currentKirby->getImage()->getFrameWidth() / 2 > 0) _cx -= 250 * elapsedTime;
		if (!_currentKirby->getMotion()->isPlay())
		{
			if (_mode != MODE_NORMAL)
			{
				_mode = MODE_NORMAL;
				changeMode(_mode);
			}
			_state = RIGHT_STOP;
			_currentKirby->setMotion();
		}
		break;
	default:
		break;
	}

	static int count = 0;

	if (_isDashReady)
	{
		count++;
		int aa = 0;

		if (count > 10)
		{
			_isDashReady = false;
			count = 0;
		}
	}
	else count = 0;

	switch (_dir)
	{
	case DIRECTION_STOP:
		break;
	case DIRECTION_LEFT:
		//if(_cx - _currentKirby->getImage()->getFrameWidth() / 2 > 0 ) _cx -= 200 * 

		elapsedTime;
		break;
	case DIRECTION_RIGHT:
		//_cx += 200 * elapsedTime;
		break;
	case DIRECTION_UP:
		break;
	case DIRECTION_DOWN:
		break;
	default:
		break;
	}

	// EATING 이 아닐때는 렉트 초기화를 해준다.
	if (_state != LEFT_EATING && _state != RIGHT_EATING)
	{
		_eatRc = RectMake(0, 0, 0, 0);
	}

	// JUMP일때 방향 제어
	if ((_state == LEFT_JUMP_UP || _state == LEFT_JUMP_TURN || _state == LEFT_JUMP_DOWN ||
		_state == RIGHT_JUMP_UP || _state == RIGHT_JUMP_TURN || _state ==

		RIGHT_JUMP_DOWN ||
		_state == LEFT_FLY_UP || _state == LEFT_FLY || _state == LEFT_FLY_DOWN ||
		_state == RIGHT_FLY_UP || _state == RIGHT_FLY || _state == RIGHT_FLY_DOWN) &&
		_isPushButton)
	{
		float elapsedTime = TIMEMANAGER->getElapsedTime();
		if (_isRight) _cx += 200 * elapsedTime;
		else if (!_isRight && _cx - _currentKirby->getImage()->getFrameWidth() / 2 > 0) _cx -=

			200 * elapsedTime;
	}


}

void kirby::checkPixelCollision()
{

	image* map = _mm->getPixalCrushImage();
	int width = _currentKirby->getImage()->getFrameWidth();
	int height = _currentKirby->getImage()->getFrameHeight();
	bool collision = false;

	_isPixelCollision = false;

	// 땅 충돌 ( 날때는 하지말래요 )
	//위
	collision = false;
	for (int probeY = _cy; probeY>_cy - (height - 20) / 2; --probeY)
	{
		for (int probeX = _cx - (width - 30) / 2; probeX < _cx + (width - 30) / 2; ++probeX)
		{
			COLORREF color = GetPixel(map->getMemDC(), probeX, probeY);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{
				_cy = probeY + (height - 20) / 2;
				collision = true;
				_isPixelCollision = true;
				_isPixelCollisionUp = true;
				break;
			}
		}
		if (collision)
			break;
	}

	//아래
	collision = false;
	for (int probeY = _cy; probeY<_cy + (height - 20) / 2; ++probeY)
	{
		for (int probeX = _cx - (width - 30) / 2; probeX < _cx + (width - 30) / 2; ++probeX)
		{
			COLORREF color = GetPixel(map->getMemDC(), probeX, probeY);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{
				_cy = probeY - (height - 22) / 2;
				collision = true;
				_isPixelCollision = true;
				break;
			}
		}
		if (collision)
			break;
	}



	//// 벽 충돌
	//왼
	collision = false;
	for (int probeX = _cx; probeX > _cx - (width - 25) / 2; --probeX)
	{
		for (int probeY = _cy - (height - 22) / 2; probeY<_cy + (height - 22) / 2; ++probeY)
		{
			COLORREF color = GetPixel(map->getMemDC(), probeX, probeY);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)
			{
				_cx = probeX + (width - 20) / 2;
				collision = true;
				break;
			}
		}
		if (collision)
			break;
	}
	collision = false;
	//오
	for (int probeX = _cx; probeX < _cx + (width - 25) / 2; ++probeX)
	{
		for (int probeY = _cy - (height - 22) / 2; probeY<_cy + (height - 22) / 2; ++probeY)
		{
			COLORREF color = GetPixel(map->getMemDC(), probeX, probeY);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 0 && b == 255)
			{
				_cx = probeX - (width - 20) / 2;
				collision = true;
				break;
			}
		}
		if (collision)
			break;
	}

}

bool kirby::checkDoorPixel()
{

	// 여기가 문이에요?
	COLORREF color = GetPixel(_mm->getPixalCrushImage()->getMemDC(), _cx, _cy);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	// 문 : 노란색
	if (r == 255 && g == 255 && b == 0) return true;
	else return false;

}


void kirby::checkRectCollision()
{

	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_em->getVEnemy()[i]->getRC(), &_rc))
		{
			if (_em->getVEnemy()[i]->getHit()) continue;
			if (_em->getVEnemy()[i]->getDie()) continue;

			// 충돌 했을때는 충돌처리 안해줘요! ( 무적 시간 !! )
			if (_state != LEFT_CRASH && _state != RIGHT_CRASH) _isRectCollision = true;
			else _isRectCollision = false;

			// 킥이 아니면 충돌 state로 바꿔준다.
			if (_state != LEFT_KICK && _state != RIGHT_KICK && _state != LEFT_EATING

				&& _state != RIGHT_EATING)
			{
				if (_em->getVEnemy()[i]->getRC().left < _rc.left) _state =

					LEFT_CRASH;
				else _state = RIGHT_CRASH;
				_currentKirby->setMotion();
				_em->getVEnemy()[i]->hitDamage(1);
			}
			else if (_state == LEFT_KICK || _state == RIGHT_KICK)
			{
				_em->getVEnemy()[i]->hitDamage(1);
			}
		}
		else _isRectCollision = false;

	}

	// 충돌 처리
	if (_isRectCollision)
	{
		// 충돌 state면 setMotion 해준후 hp 감소
		if (_state == LEFT_CRASH || _state == RIGHT_CRASH)
		{
			SOUNDMANAGER->play("damage", atof(DATABASE->getElementData("effectVolume").c_str()));
			_currentKirby->setMotion();
			_hp--;
		}
		// 충돌 아닌데 충돌처리가 났다( kick & attack ... )
		else _isRectCollision = false;

	}
	if (_hp <= 0)
	{
		_life--;
		_hp = 6;
	}
	if (_life < 0)
	{
		_isGameEnd = true;
	}



}

void kirby::changeMode(MODE mode)
{
	SOUNDMANAGER->play("change", atof(DATABASE->getElementData("effectVolume").c_str()));
	
	float cx, cy;
	cx = _cx - _mm->getFocus().left;
	cy = _cy - _mm->getFocus().top;
	EFFECTMANAGER->play("CHANGE", cx, cy);

	switch (mode)
	{
	case MODE_NORMAL:
		_currentKirby = new kirbyBase;
		_currentKirby->setKirbyMemoryLink(this);
		_currentKirby->init();
		break;
	case MODE_FIRE:
		_currentKirby = new fireKirby;
		_currentKirby->setKirbyMemoryLink(this);
		_currentKirby->init();
		break;
	case MODE_CUPID:
		break;
	case MODE_BEAM:
		_currentKirby = new beamKirby;
		_currentKirby->setKirbyMemoryLink(this);
		_currentKirby->init();
		break;
	default:
		break;
	}



}

void kirby::eat()
{

	//노말아니면 실행안되게
	if (_mode != MODE_NORMAL)
	{
		return;
	}
	_timer += TIMEMANAGER->getElapsedTime();
	//노말아니면 실행안되게
	if (_timer > 0.3)
	{
		SOUNDMANAGER->setPosition("eat", 1000);
		_timer = 0;
	}
	if (_isFull)
	{
		if (_isRight) _state = RIGHT_STOP;
		else _state = LEFT_STOP;
		_currentKirby->setMotion();
	}

	//오른쪽이면
	if (_isRight && (_state == RIGHT_EAT || _state == RIGHT_EATING))
	{
		_eatRc = RectMake(_cx, _cy - (_currentKirby->getImage()->getFrameHeight() / 2) + 10,

			80, _currentKirby->getImage()->getFrameHeight() - 20);
	}

	//왼쪽이면
	else if (!_isRight && (_state == LEFT_EAT || _state == LEFT_EATING))
	{
		_eatRc = RectMake(_cx - 80, _cy - (_currentKirby->getImage()->getFrameHeight() / 2) +

			10, 80, _currentKirby->getImage()->getFrameHeight() - 20);
	}


	RECT temp, temp2;

	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{

		if (IntersectRect(&temp, &_eatRc, &_em->getVEnemy()[i]->getRC()))
		{
			if (_em->getVEnemy()[i]->getDie()) continue;
			if (_em->getVEnemy()[i]->getHit()) continue;
			if (!_em->getVEnemy()[i]->getEat()) continue;

			float elapsedTime = TIMEMANAGER->getElapsedTime();

			// 적이 오른쪽에 있으면
			if (_em->getVEnemy()[i]->getRC().left > _rc.left)
			{
				_em->getVEnemy()[i]->setX(_em->getVEnemy()[i]->getRC().left -

					4);
			}
			// 적이 왼쪽에 있으면
			else
			{
				_em->getVEnemy()[i]->setX(_em->getVEnemy()[i]->getRC().left +

					4);
			}

			// 적이랑 나랑 충돌하면 적에게 데미지
			if (IntersectRect(&temp2, &_rc, &_em->getVEnemy()[i]->getRC()))
			{
				// 제거하라 제거하라
				_em->getVEnemy()[i]->hitDamage(2);
				_isFull = true;
			}
		}
	}


	//충돌한 적 있으면 빨아들이고 빵빵한 상태
	//_isFull = true;
	//뚱뚱이 서있는 모션으로 바꾸기
}

void kirby::attack()
{
	// NORMAL모드에서 뚱뚱한 커비라면
	if (_mode == MODE_NORMAL)
	{
		if (_isRight && _isFull)
		{
			_state = RIGHT_THROW;
			_currentKirby->setMotion();
			_isFull = false;
		}
		else if (!_isRight && _isFull)
		{
			_state = LEFT_THROW;
			_currentKirby->setMotion();
			_isFull = false;
		}
	}
	// 다른 모드면 ( 다른 모드일땐 뚱뚱이 상태가 없어요 )
	else
	{
		if (_isRight)
		{
			_state = RIGHT_ATTACK;
			_currentKirby->setMotion();
			_isFull = false;
			_isAttack = true;
		}
		else if (!_isRight)
		{
			_state = LEFT_ATTACK;
			_currentKirby->setMotion();
			_isFull = false;
			_isAttack = true;
		}
	}
}



void kirby::hitDamage(int damage, RECT enemyRect)
{

	// damage가 현재 남은 hp 이상이면
	if (_hp - damage <= 0)
	{
		_life--;
		_hp = 6;
	}
	else _hp -= damage;

	if (_life <= 0) _isGameEnd = true;

	// 적이 오른쪽에 있었다.
	if (enemyRect.left > _rc.left) _state = RIGHT_CRASH;
	else _state = LEFT_CRASH;

	_currentKirby->setMotion();

}