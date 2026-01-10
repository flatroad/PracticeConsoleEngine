#include <iostream>
#include "TestActor.h"

// 매 프레임 호출되는 Tick 함수.
// 기본 Actor::Tick을 먼저 호출하고, 그 다음 FPS를 콘솔에 출력합니다.
void TestActor::Tick(float deltaTime)
{
	// (필요 시) 기반 클래스 로직 호출.
	Actor::Tick(deltaTime);

	if (deltaTime <= 0.0f)
	{
		return;
	}

#pragma region testDay2
	//const float fps = 1.0f / deltaTime;

	//std::wcout << L"TestActor::Tick. FPS: " << fps << L"\n";
#pragma endregion
}
