#include "Engine.h"
#include <iostream>
#include <Windows.h> // 고해상도 타이머, 키 입력 처리를 위한 Windows API

Engine::Engine()
{
	// TODO: 엔진 초기화 코드 추가 (예: 콘솔 설정, 리소스 로드).
}

Engine::~Engine()
{
	// TODO: 엔진 종료 시 리소스 해제 코드 추가.
}

void Engine::Run()
{
	// 고해상도 타이머 정보.
	LARGE_INTEGER frequency; // 초당 카운터 횟수.
	LARGE_INTEGER previousTime; // 이전 프레임 시간.
	LARGE_INTEGER currentTime; // 현재 시간.

	// 타이머 주파수 얻기 (1초에 카운터가 몇 번 증가하는지).
	QueryPerformanceFrequency(&frequency);
	
	// 시작 시점 시간 저장.
	QueryPerformanceCounter(&previousTime);

	// 60 FPS 목표 -> 한 프레임 시간이 약 1/60초.
	const float targetFrameTime = 1.0f / 60.0f;

	// 누적 시간(프레임이 충분히 지났는지 확인용).
	float accumulatedTime = 0.0f;

	// 메인 게임 루프.
	while (!this->isQuit)
	{
		// 현재 시간 가져오기.
		QueryPerformanceCounter(&currentTime);

		// 지난 프레임 이후 경과 시간(초 단위) 계산.
		// (current - previous) / frequency.
		const LONGLONG tickDelta = currentTime.QuadPart - previousTime.QuadPart;
		const float deltaTime = static_cast<float>(tickDelta) / static_cast<float>(frequency.QuadPart);

		// 이전 시간 갱신.
		previousTime = currentTime;

		// 누적 시간 갱신.
		accumulatedTime = accumulatedTime + deltaTime;

		// 입력 처리.
		this->ProcessInput();

		// 목표 프레임 시간 이상 경과했을 때만 업데이트/랜더링.
		if (accumulatedTime >= targetFrameTime)
		{
			// Update, Render 처리.
			Update(accumulatedTime);
			Render();

			// 누적 시간 초기화.
			accumulatedTime = 0.0f;
		}
	}
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	// GetAsyncKeyState(VK_ESCPAE)가 0x800 비트가 켜져 있으면
	// 현재 ESC 키가 눌린 상태라고 판단.
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		// isQuit = true; Run 루프 종료.
		Quit();
	}
}

void Engine::Update(float deltaTime)
{
	// deltaTime: 지난 프레임(또는 누적) 시간(초)
	if (deltaTime <= 0.0f)
	{
		return;
	}

	const float fps = 1.0f / deltaTime;

	std::wcout << L"DeltaTime: " << deltaTime << L", FPS: " << fps << L"\n";
}

void Engine::Render()
{
	// TODO: 나중에 렌더링(지금은 콘솔 출력 정도) 구현.
}
