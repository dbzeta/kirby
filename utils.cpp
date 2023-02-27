#include "stdafx.h"
#include "utils.h"

namespace BLUE_UTIL
{
	//거리
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//각도
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (y2 > y1)
		{

			angle = PI2 - angle;

			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}
	void RGBEllipse(image* img, int left, int top, int right, int bottom, COLORREF color)
	{
		HBRUSH hbr = CreateSolidBrush(color);
		HBRUSH holdbr = (HBRUSH)SelectObject(img->getMemDC(), hbr);
		HPEN hp = CreatePen(PS_SOLID, 0, color);
		HPEN holdp = (HPEN)SelectObject(img->getMemDC(), hp);
		Ellipse(img->getMemDC(), left, top, right, bottom);
		SelectObject(img->getMemDC(), holdbr);
		SelectObject(img->getMemDC(), holdp);
	}

	void RGBEllipseMake(image* img, int x, int y, int width, int height, COLORREF color)
	{
		HBRUSH hbr = CreateSolidBrush(color);
		HBRUSH holdbr = (HBRUSH)SelectObject(img->getMemDC(), hbr);
		HPEN hp = CreatePen(PS_SOLID, 0, color);
		HPEN holdp = (HPEN)SelectObject(img->getMemDC(), hp);
		Ellipse(img->getMemDC(), x, y, x + width, y + height);
		SelectObject(img->getMemDC(), holdbr);
		SelectObject(img->getMemDC(), holdp);
	}

	void RGBEllipseMakeCenter(image* img, int x, int y, int width, int height, COLORREF color)
	{
		HBRUSH hbr = CreateSolidBrush(color);
		HBRUSH holdbr = (HBRUSH)SelectObject(img->getMemDC(), hbr);
		HPEN hp = CreatePen(PS_SOLID, 0, color);
		HPEN holdp = (HPEN)SelectObject(img->getMemDC(), hp);
		Ellipse(img->getMemDC(), x - width / 2, y - height / 2, x + width / 2, y + height / 2);
		SelectObject(img->getMemDC(), holdbr);
		SelectObject(img->getMemDC(), holdp);
	}

	void RGBRectangle(image* img, int left, int top, int right, int bottom, COLORREF color)
	{
		HBRUSH hbr = CreateSolidBrush(color);
		HBRUSH holdbr = (HBRUSH)SelectObject(img->getMemDC(), hbr);
		HPEN hp = CreatePen(PS_SOLID, 0, color);
		HPEN holdp = (HPEN)SelectObject(img->getMemDC(), hp);
		Rectangle(img->getMemDC(), left, top, right, bottom);
		SelectObject(img->getMemDC(), holdbr);
		SelectObject(img->getMemDC(), holdp);
	}

	void RGBRectangleMake(image* img, int x, int y, int width, int height, COLORREF color)
	{
		HBRUSH hbr = CreateSolidBrush(color);
		HBRUSH holdbr = (HBRUSH)SelectObject(img->getMemDC(), hbr);
		HPEN hp = CreatePen(PS_SOLID, 0, color);
		HPEN holdp = (HPEN)SelectObject(img->getMemDC(), hp);
		Rectangle(img->getMemDC(), x, y, x + width, y + height);
		SelectObject(img->getMemDC(), holdbr);
		SelectObject(img->getMemDC(), holdp);
	}

	void RGBRectangleMakeCenter(image* img, int x, int y, int width, int height, COLORREF color)
	{
		HBRUSH hbr = CreateSolidBrush(color);
		HBRUSH holdbr = (HBRUSH)SelectObject(img->getMemDC(), hbr);
		HPEN hp = CreatePen(PS_SOLID, 0, color);
		HPEN holdp = (HPEN)SelectObject(img->getMemDC(), hp);
		Rectangle(img->getMemDC(), x - width / 2, y - height / 2, x + width / 2, y + height / 2);
		SelectObject(img->getMemDC(), holdbr);
		SelectObject(img->getMemDC(), holdp);
	}

	void RGBSetPixcel(image* img, int x, int y, COLORREF color)
	{
		SetPixel(img->getMemDC(), x, y, color);
	}
	
}