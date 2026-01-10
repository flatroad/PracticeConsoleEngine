#pragma once

#include "Actors/Actor.h"

// 테스트용 엑터.
// 매 프레임 Tick에서 FPS를 출력합니다.
class TestActor : public Actor
{
public:
	virtual void Tick(float deltaTime) override;
};