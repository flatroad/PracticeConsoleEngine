#pragma once

#include <vector>

#include "Core/Core.h"
#include "Core/RTTI.h"
#include "Actors/Actor.h"

/// @class level
/// @brief 하나의 게임 레벨(씬)을 표현하는 클래스.
/// 
/// 여러 Actor를 소유하고,
/// 레벨의 BeginPlay / Tick / Render 시점에
/// 각 Actor의 BeginPlay / Tick / Render를 호출하는 역할을 합니다.
class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)

public:
	/// @brief 빈 레벨을 생성합니다.
	Level();

	/// @brief 레벨이 소멸될 때 Actor들을 정리합니다.
	virtual ~Level();

	/// 레벨은 전달 받은 Actor 포인터를 보관하고,
	/// @brief 레벨에 Actor를 추가합니다.
	/// 
	/// 레벨 소멸 시 delete를 통해 메모리를 정리합니다.
	/// @param actor 레벨에 추가할 Actor 포인터입니다.
	void AddActor(Actor* actor);

	/// @brief 레벨에 포함된 Actor들의 BeginPlay가 한 번 이상 호출되도록 합니다.
	///
	/// 엔진에서 매 프레임 호출될 수 있으며,
	/// 아직 BeginPlay가 호출되지 않은 Actor에 대해서만 Actor::BeginPlay를 호출합니다.
	virtual void BeginPlay();

	/// @brief 매 프레임마다 레벨의 Actor들을 업데이트합니다.
	///
	/// Tick 안에서는 내부적으로 BeginPlay를 다시 호출하여,
	/// 새로 추가된 Actor에 대해서도 BeginPlay가 한 번 이상 수행되도록 보장합니다.
	/// 모든 레벨이 소유한 Actor의 Tick을 호출합니다.
	/// @param[In] deltaTime 이전 프레임 이후 경과 시간(초 단위)입니다.
	virtual void Tick(float deltaTime);

	/// @brief 매 프레임마다 레벨의 Actor들을 렌더링합니다.
	virtual void Render();

protected:
	/// @brief 이 레벨이 소유하고 있는 Actor 목록입니다.
	std::vector<Actor*> actors;

};