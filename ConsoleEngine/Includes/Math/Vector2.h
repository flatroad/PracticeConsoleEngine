#pragma once

#include "Core/Core.h"

/// @class Vector2
/// @brief 2D 정수 좌표를 표현하는 벡터 클래스.
/// 
/// 위치, 이동, 방향 등을 표현하기 위해 사용되는 기본 수학 타입입니다.
/// (x, y) 좌표와 더하기/빼기 연산, 문자열 변환 기능을 제공합니다.
class Engine_API Vector2
{
public:
	/// @brief (x, y) 좌표로 벡터를 초기화 합니다.
	/// @param x X 좌표
	/// @param y Y 좌표
	Vector2(int x = 0, int y = 0);

	/// @brief 내부에서 할당한 문자열 버퍼를 정리합니다.
	~Vector2();

	/// @brief 두 벡터를 더한 결과를 반환합니다.
	Vector2 operator+(const Vector2& other) const;

	/// @brief 두 벡터의 차이를 반환합니다.
	Vector2 operator-(const Vector2& other) const;

	/// @brief "(x, y)" 형태의 문자열을 반환합니다.
	/// @return 내부 버퍼 포인터(호출 측에서 해제하면 안 됨)
	const char* ToString();

	/// @brief (0, 0) 벡터
	static Vector2 Zero;

	/// @brief (1, 1) 벡터
	static Vector2 One;

	/// @brief 위쪽 방향 (0, 1) 벡터
	static Vector2 Up;

	/// @brief 오른쪽 방향 (1, 0) 벡터
	static Vector2 Right;

private:
	/// @brief X 좌표
	int x = 0;

	/// @brief Y 좌표
	int y = 0;

	/// @brief ToString 에서 사용하는 내부 문자열 버퍼입니다.
	char* value = nullptr;
};