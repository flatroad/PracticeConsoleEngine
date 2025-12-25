#pragma once

#include "Core/Core.h"
#include "Math/Vector2.h"

// 게임 세계에 존재하는 모든 객체의 공통 기반 클래스.
// 위치를 가지고 있고, 엔진이 호출하는 이벤트 함수(생성/업데이트/렌더)를 제공합니다.
class Engine_API Actor
{
public:
	// 기본 생성자
	Actor();

	// 소멸자
	virtual ~Actor();

	// 객체 생애주기(Lifetime)에 1번만 호출됨 (초기화 목적)
	virtual void BeginPlay();

	// 프레임마다 호출 (반복성 작업/지속성이 필요한 작업).
	virtual void Tick(float deltaTime);

	// 그리기 함수.
	virtual void Render();

	// BeginPlay 가 호출된 적이 있는지 확인.
	inline bool HasBeganPlay() const { return (hasBeganPlay); }
private:
	// 개체의 위치.
	Vector2 position;

	// 콘솔에 그릴 문자 값.
	char image = ' ';

	// BeginPlay 호출 여부.
	bool hasBeganPlay = false;
};