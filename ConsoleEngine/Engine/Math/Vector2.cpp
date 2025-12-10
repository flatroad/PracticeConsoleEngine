#include "Vector2.h"
#include <cstdio>

// 정적 멤버 초기화.
Vector2 Vector2::Zero = Vector2(0, 0);
Vector2 Vector2::One = Vector2(1, 1);
Vector2 Vector2::Up = Vector2(0, 1);
Vector2 Vector2::Right = Vector2(1, 0);

// 생성자: 멤버 이니셜 라이저로 x, y 설정.
Vector2::Vector2(int x, int y)
	: x(x), y(y)
{
}

// 소멸자: value 버퍼가 있으면 해제.
Vector2::~Vector2()
{
	if (value != nullptr)
	{
		delete[] value;
		value = nullptr;
	}
}

// 두 벡터를 더한 결과 반환.
Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

// 두 벡터의 차이 반환.
Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

// "(x, y)" 형태으ㅢ 문자열로 만들어 내부 버퍼에 저장 후 포인터 반환.
const char* Vector2::ToString()
{
	// 이전에 할당된 버퍼가 있으면 정리.
	if (value != nullptr)
	{
		delete[] value;
	}

	// 간단히 64바이트 정도만 할당.
	const int BUFFER_SIZE = 64;
	value = new char[BUFFER_SIZE];

	// "(%d, %d)" 형태로 출력.
	sprintf_s(value, BUFFER_SIZE, "(%d, %d)", x, y);

	return (value);
}
