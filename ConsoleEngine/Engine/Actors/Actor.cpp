#include "Actor.h"

// 기본 생성자.
Actor::Actor()
{
}

// 소멸자.
Actor::~Actor()
{
}

// 객체 생애주기(Lifetime)에 1번만 호출됨(초기화 목적).
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// 프레임마다 호출 (반복성 작업/지속성이 필요한 작업).
void Actor::Tick(float deltaTime)
{
	// 기본 Actor는 특별히 할 일이 없음.
}

// 그리기 함수.
void Actor::Render()
{
	// 나중에 콘솔 그리기 로직을 구현 예정.
}
