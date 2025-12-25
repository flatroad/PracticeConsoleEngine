#pragma once

#include <vector>

#include "Core/Core.h"
#include "Actors/Actor.h"

// 하나의 게임 레벨(씬)을 표현하는 클래스.
// 레벨은 여러 Actor들을 보관하고, BeginPlay/Tick/Render를 순서대로 호출합니다.
class Engine_API Level
{
public:
	// 생성자.
	Level();

	// 소멸자.
	virtual ~Level();

	// 레벨에 Actor를 추가합니다. (소유권은 Level이 가짐).
	void AddActor(Actor* actor);

	// 레벨이 시작될 때 한 번만 호출되는 함수입니다.
	// 아직 BeginPlay가 호출되지 않은 Actor들에 대해 BeginPlay를 호출합니다.
	virtual void BeginPlay();

	// 매 프레임마다 호출되는 함수입니다.
	// 필요하다면 BeginPlay가 아직 안 된 Actor에 대해 BeginPlay를 먼저 보장합니다.
	virtual void Tick(float deltaTime);

	// 매 프레임 렌더링 시 호출되는 함수입니다.
	virtual void Render();

protected:
	// 이 레벨에 포함된 Actor 목록.
	std::vector<Actor*> actors;

};