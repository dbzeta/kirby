#include "stdafx.h"
#include "poppy.h"
#include "enemyManager.h"
#include "kirby.h"


poppy::poppy()
{
}


poppy::~poppy()
{
}

// �߰� ���� -> ���� ���� ������ ���� ����
HRESULT poppy::init(float x, float y, float speed, int moveRange)
{
	_imageEnemy = IMAGEMANAGER->addFrameImage("poppy_walk", "image/Enemy/middleBoss/Poppy/�ȱ�.bmp", /*492 * 1.5*/732, /*96 * 1.5*/136, 12, 2, true, 0xff00ff);

	IMAGEMANAGER->addFrameImage("poppy_walk", "image/Enemy/middleBoss/Poppy/�ȱ�.bmp", 492 * 1.5, 96 * 1.5, 12, 2, true, 0xff00ff);
	IMAGEMANAGER->findImage("poppy_walk")->setFrameX(0);

	IMAGEMANAGER->addFrameImage("poppy_dash", "image/Enemy/middleBoss/Poppy/�뽬.bmp", 287 * 1.5, 92 * 1.5, 7, 2, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("poppy_attack", "image/Enemy/middleBoss/Poppy/����.bmp", 390 * 1.5, 96 * 1.5, 10, 2, true, 0xff00ff);
	IMAGEMANAGER->addFrameImage("poppy_die", "image/Enemy/middleBoss/Poppy/����.bmp", 41 * 1.5, 48 * 1.5, 1, 2, true, 0xff00ff);

	_currentFrameX = _currentFrameY = 0;
	_x = _startX = x;
	_y = _startY = y;
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	_fSpeed = speed;
	_count = _motionCount = 0;
	_moveRange = moveRange;

	_state = ENEMY_LEFT_JUMP;

	_jumpPower = 50;
	_gravity = 150;
	_nEnemyHP = 5;
	_angle = PI / 1.6;
	_bDie = false;
	_mapGravity = 0;
	_patternPlay = 2/*RND->getFromIntTo(1, 4)*/;

	//--------------------------------------------------------------------
	_isHit = false;							// ���� �������� �ƴ��� Ȯ��.
	_bEat = false;							// Ŀ�� �������ִ� �̴Ͼ������� Ȯ��.
	_InvincibilityCount = 0;				// �°� ���� �ߺ����� ������ �ȵǴ� ������ �Ǵ� �ð����� �� ����.

	return S_OK;
}

void poppy::release()
{

}

void poppy::update()
{
	if (_bDie) return;

	_count += TIMEMANAGER->getElapsedTime();
	_motionCount += TIMEMANAGER->getElapsedTime();

	// ���� ����
	//----------------------------------------------------------------------------
	if (!_isHit)													// ���� ���¸� �������� ������ �ȵǱ⶧���� ������ ��.
	{
		if (_patternPlay == 1)
		{
			jumpMove(50, true);
		}

		if (_patternPlay == 2)
		{
			followJumpMove();
		}
	}

	// ----------------------------------------------------------------------------

	if (_isHit)														// �����ð��� �������°� Ǯ���Ե� �ڵ�.
	{
		_InvincibilityCount += TIMEMANAGER->getElapsedTime();

		if (_InvincibilityCount > 3)
		{
			_isHit = false;
		}

	}

	switch (_state)
	{
	case ENEMY_RIGHT_STOP:

		break;
	case ENEMY_RIGHT_MOVE:
		if (_currentFrameX > IMAGEMANAGER->findImage("poppy_walk")->getMaxFrameX() - 1)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameX(_currentFrameX);

			_currentFrameY = 0;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameY(_currentFrameY);
		}
		if (_count > 1)
		{
			_count = 0;

			if (_currentFrameX > IMAGEMANAGER->findImage("poppy_walk")->getMaxFrameX() - 1)
				_currentFrameX = IMAGEMANAGER->findImage("poppy_walk")->getMaxFrameX() - 1;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("poppy_walk")->setFrameX(_currentFrameX);

			_currentFrameY = 0;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameY(_currentFrameY);
		}
		break;

	case ENEMY_RIGHT_DASH:
		if (_currentFrameX > IMAGEMANAGER->findImage("poppy_dash")->getMaxFrameX() - 1)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("poppy_dash")->setFrameX(_currentFrameX);

			_currentFrameY = 0;
			IMAGEMANAGER->findImage("poppy_dash")->setFrameY(_currentFrameY);
		}
		if (_count > 0.2)
		{
			_count = 0;

			if (_currentFrameX > IMAGEMANAGER->findImage("poppy_dash")->getMaxFrameX() - 1)
				_currentFrameX = IMAGEMANAGER->findImage("poppy_dash")->getMaxFrameX() - 1;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("poppy_dash")->setFrameX(_currentFrameX);

			_currentFrameY = 0;
			IMAGEMANAGER->findImage("poppy_dash")->setFrameY(_currentFrameY);
		}

		break;
	case ENEMY_RIGHT_DIE:
		_currentFrameX = 0;
		_currentFrameY = 0;
		IMAGEMANAGER->findImage("poppy_die")->setFrameY(_currentFrameX);
		IMAGEMANAGER->findImage("poppy_die")->setFrameY(_currentFrameY);
		break;
	case ENEMY_RIGHT_HIT:

		break;
	case ENEMY_RIGHT_ATTACK:
		if (_currentFrameX > IMAGEMANAGER->findImage("poppy_attack")->getMaxFrameX() - 1)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("poppy_attack")->setFrameX(_currentFrameX);

			_currentFrameY = 0;
			IMAGEMANAGER->findImage("poppy_attack")->setFrameY(_currentFrameY);
		}
		if (_count > 0.2)
		{
			_count = 0;

			if (_currentFrameX > IMAGEMANAGER->findImage("poppy_attack")->getMaxFrameX() - 1)
				_currentFrameX = IMAGEMANAGER->findImage("poppy_attack")->getMaxFrameX() - 1;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("poppy_attack")->setFrameX(_currentFrameX);

			_currentFrameY = 0;
			IMAGEMANAGER->findImage("poppy_attack")->setFrameY(_currentFrameY);
		}
		break;

	case ENEMY_RIGHT_JUMP:
		if (_currentFrameX == 0)
		{
			_currentFrameX = 10;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameX(_currentFrameX);

			_currentFrameY = 0;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameY(_currentFrameY);
		}
		if (_count > 0.3)
		{
			_count = 0;

			if (_currentFrameX == 0) _currentFrameX = 10;
			else if (_currentFrameX == 10) _currentFrameX = 0;

			IMAGEMANAGER->findImage("poppy_walk")->setFrameX(_currentFrameX);

			_currentFrameY = 0;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameY(_currentFrameY);
		}
		break;




	case ENEMY_LEFT_STOP:

		break;
	case ENEMY_LEFT_MOVE:
		if (_currentFrameX > IMAGEMANAGER->findImage("poppy_walk")->getMaxFrameX() - 1)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameX(_currentFrameX);

			_currentFrameY = 1;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameY(_currentFrameY);
		}
		if (_count > 1)
		{
			_count = 0;

			if (_currentFrameX > IMAGEMANAGER->findImage("poppy_walk")->getMaxFrameX() - 1)
				_currentFrameX = IMAGEMANAGER->findImage("poppy_walk")->getMaxFrameX() - 1;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("poppy_walk")->setFrameX(_currentFrameX);

			_currentFrameY = 1;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameY(_currentFrameY);
		}
		break;
	case ENEMY_LEFT_DASH:

		if (_currentFrameX > IMAGEMANAGER->findImage("poppy_dash")->getMaxFrameX() - 1)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("poppy_dash")->setFrameX(_currentFrameX);

			//_currentFrameY = 1;
			//IMAGEMANAGER->findImage("poppy_dash")->setFrameY(_currentFrameY);
		}
		if (_count > 0.2)
		{
			_count = 0;

			if (_currentFrameX > IMAGEMANAGER->findImage("poppy_dash")->getMaxFrameX() - 1)
				_currentFrameX = IMAGEMANAGER->findImage("poppy_dash")->getMaxFrameX() - 1;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("poppy_dash")->setFrameX(_currentFrameX);

			//_currentFrameY = 1;
			//IMAGEMANAGER->findImage("poppy_dash")->setFrameY(_currentFrameY);
		}
		break;

	case ENEMY_LEFT_DIE:
		_currentFrameX = 0;
		_currentFrameY = 1;
		IMAGEMANAGER->findImage("poppy_die")->setFrameY(_currentFrameX);
		IMAGEMANAGER->findImage("poppy_die")->setFrameY(_currentFrameY);
		break;

	case ENEMY_LEFT_HIT:
		break;

	case ENEMY_LEFT_ATTACK:
		if (_currentFrameX > IMAGEMANAGER->findImage("poppy_attack")->getMaxFrameX() - 1)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("poppy_attack")->setFrameX(_currentFrameX);

			_currentFrameY = 1;
			IMAGEMANAGER->findImage("poppy_attack")->setFrameY(_currentFrameY);
		}
		if (_count > 0.2)
		{
			_count = 0;

			if (_currentFrameX > IMAGEMANAGER->findImage("poppy_attack")->getMaxFrameX() - 1)
				_currentFrameX = IMAGEMANAGER->findImage("poppy_attack")->getMaxFrameX() - 1;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("poppy_attack")->setFrameX(_currentFrameX);

			_currentFrameY = 1;
			IMAGEMANAGER->findImage("poppy_attack")->setFrameY(_currentFrameY);
		}
		break;

	case ENEMY_LEFT_JUMP:
		if (_currentFrameX > IMAGEMANAGER->findImage("poppy_walk")->getMaxFrameX() - 1)
		{
			_currentFrameX = 0;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameX(_currentFrameX);

			_currentFrameY = 1;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameY(_currentFrameY);
		}
		if (_count > 0.3)
		{
			_count = 0;

			if (_currentFrameX > IMAGEMANAGER->findImage("poppy_walk")->getMaxFrameX() - 1)
				_currentFrameX = IMAGEMANAGER->findImage("poppy_walk")->getMaxFrameX() - 1;
			else ++_currentFrameX;

			IMAGEMANAGER->findImage("poppy_walk")->setFrameX(_currentFrameX);

			_currentFrameY = 1;
			IMAGEMANAGER->findImage("poppy_walk")->setFrameY(_currentFrameY);
		}
		break;



	case ENEMY_UP_JUMP:
		break;

	case ENEMY_RIGHT_READY:

		break;
	case ENEMY_LEFT_READY:

		break;
	case ENEMY_LEFT_DROPJUMP:

		break;
	case ENEMY_RIGHT_DROPJUMP:

		break;
	}

	//_y += _mapGravity * TIMEMANAGER->getElapsedTime();
	_rc = RectMake(_x, _y, _imageEnemy->getFrameWidth(), _imageEnemy->getFrameHeight());
	//PixelCollision();
}

void poppy::render()
{

}

void poppy::draw(RECT rcFocus)
{
	if (_bDie) return;						// �������´� �׸��� �ʴ´�.
	/*int x, y;
	RECT rc = RectMake(_x, _y, IMAGEMANAGER->findImage("poppy_walk")->getFrameWidth(), IMAGEMANAGER->findImage("poppy_walk")->getFrameHeight());
	if (!IntersectRect(&RectMake(0, 0, 0, 0), &rc, &rcFocus)) return;

	x = rc.left - rcFocus.left;
	y = rc.top - rcFocus.top;*/

	switch (_state)
	{
	case ENEMY_RIGHT_STOP: case ENEMY_LEFT_STOP:
	case ENEMY_RIGHT_MOVE: case ENEMY_LEFT_MOVE:
	case ENEMY_UP_JUMP:
	case ENEMY_RIGHT_JUMP: case ENEMY_LEFT_JUMP:
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		IMAGEMANAGER->findImage("poppy_walk")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;

	case ENEMY_RIGHT_DASH: case ENEMY_LEFT_DASH:
		IMAGEMANAGER->findImage("poppy_dash")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;

	case ENEMY_RIGHT_DIE: case ENEMY_LEFT_DIE:
		IMAGEMANAGER->findImage("poppy_die")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;

	case ENEMY_RIGHT_HIT: case ENEMY_LEFT_HIT:
		break;

	case ENEMY_RIGHT_ATTACK: case ENEMY_LEFT_ATTACK:
		IMAGEMANAGER->findImage("poppy_attack")->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
		break;


	case ENEMY_RIGHT_READY: case ENEMY_LEFT_READY:
		break;

	case ENEMY_LEFT_DROPJUMP: case ENEMY_RIGHT_DROPJUMP:
		break;
	}

	char str[128];
	//Ŀ�� ��ǥ
	sprintf_s(str, "%d", _em->getKirby()->getRect().left);
	TextOut(getMemDC(), WINSIZEX - 100, 20, str, strlen(str));
	sprintf_s(str, "%d", _em->getKirby()->getRect().top);
	TextOut(getMemDC(), WINSIZEX - 100, 40, str, strlen(str));
	//�� ��ǥ
	sprintf_s(str, "%d", _rc.left);
	TextOut(getMemDC(), WINSIZEX - 100, 60, str, strlen(str));
	sprintf_s(str, "%d", _rc.top);
	TextOut(getMemDC(), WINSIZEX - 100, 80, str, strlen(str));
	//�� ����
	sprintf_s(str, "%d", _state);
	TextOut(getMemDC(), WINSIZEX - 100, 100, str, strlen(str));

}

void poppy::jumpMove(float moveSpeed, bool loop)
{
	if (_state == ENEMY_RIGHT_JUMP)
		_x += moveSpeed * TIMEMANAGER->getElapsedTime();
	else _x -= moveSpeed * TIMEMANAGER->getElapsedTime();

	_y -= _jumpPower * TIMEMANAGER->getElapsedTime();
	_jumpPower -= _gravity * TIMEMANAGER->getElapsedTime();

	if (_y > _startY)
	{
		_y = _startY;
		_jumpPower = 100;
		_gravity = 300;

		/*if (loop)
		{
		if (_state == ENEMY_RIGHT_JUMP)
		_state = ENEMY_LEFT_JUMP;
		else
		_state = ENEMY_RIGHT_JUMP;
		}
		else return;*/
	}
}

void poppy::followJumpMove()
{
	//üũ 
	//�þ�(y��)�ȿ� ������ �� or �ƴ� ��
	//�¿� ��� ��ġ�ߴ���

	//����
	//Ŀ���� �������� �̵�

	//Ŀ�� �þ�(_y) �ȿ� ������ �� //�� ������ �ʿ��Ѱ�
	//if (_em->getKirby()->getRect().bottom >= _rc.top)
	//{
	if (_rc.left >= _em->getKirby()->getRect().left)
	{
		_state = ENEMY_LEFT_JUMP;
		//jumpMove(50, false);

		if (_rc.left <= _em->getKirby()->getRect().left)
		{
			_state = ENEMY_RIGHT_JUMP;
		}
	}

	//else if (_x < _em->getKirby()->getRect().left)
	//{

	//}
	//}
}
