#pragma once

#include "Core/Core.h"
#include "Core/RTTI.h"
#include "Math/Vector2.h"

/// @class Actor
/// @brief 게임 오브젝트의 기본 클래스.
///
/// 위치(Vector2)와 문자 이미지(char)를 가지며,
/// 엔진과 레벨로부터 BeginPlay / Tick / Render 호출을 전달받아
/// 게임 내에서 실제 동작을 수행하는 역할을 합니다.
class Engine_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	/// @brief Actor를 생성합니다. 기본 위치는 (0, 0), 이미지는 공백 문자입니다.
	Actor();

	/// @brief Actor 소멸될 때 정리 작업을 수행합니다.
	virtual ~Actor();

	/// @brief Actor가 게임에 참여하기 전에 수행해야 하는 초기화 함수입니다.
	///
	/// 같은 Actor에 대해 초기화 로직은 한 번만 동작하도록 합니다.
	virtual void BeginPlay();

	/// @brief 매 프레임마다 호출되는 업데이트 함수입니다.
	/// @param[In] deltaTime 이전 프레임 이후 경과 시간(초 단위)입니다.
	virtual void Tick(float deltaTime);

	/// @brief 매 프레임마다 렌더링을 수행합니다.
	virtual void Render();

	/// @brief BeginPlay가 이미 호출되었는지 여부를 반환합니다.
	/// @retrun BeginPlay가 한 번 이상 호출되었으면 true를 반환합니다.
	inline bool HasBeganPlay() const { return (hasBeganPlay); }

private:
	/// @brief Actor의 위치입니다.
	Vector2 position;

	/// @brief 콘솔에서 Actor를 표현할 문자입니다.
	char image = ' ';

	/// @brief BeginPlay가 호출되었는지 여부입니다.
	bool hasBeganPlay = false;
};