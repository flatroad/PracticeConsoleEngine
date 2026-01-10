#include "Engine.h"
#include <iostream>
#include <Windows.h> // 고해상도 타이머, 키 입력 처리를 위한 Windows API
#include "Levels/level.h" // Level 클래스 사용을 위한 include;

Engine::Engine()
{
	// TODO: 엔진 초기화 코드 추가 (예: 콘솔 설정, 리소스 로드).
}

Engine::~Engine()
{
	// mainLevel로 등록된 레벨이 있으면 정리합니다.
	if (mainLevel != nullptr)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
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
		ProcessInput();

		// 목표 프레임 시간 이상 경과했을 때만 업데이트/랜더링.
		if (accumulatedTime >= targetFrameTime)
		{
			// 레벨 관련 초기화.
			BeginPlay();
			// Tick, Render 처리.
			Tick(accumulatedTime);
			Render();

			// 한 프레임 처리가 끝난 뒤,
			// 이번 프레임 상태를 "이전 프레임 상태"로 복사합니다.
			for (int key = 0; key < 256; ++key)
			{
				keyStates[key].previousKeyDown = keyStates[key].isKeyDown;
			}

			// 누적 시간 초기화.
			accumulatedTime = 0.0f;
		}
	}
}

void Engine::AddLevel(Level* newLevel)
{
	// 기존에 등록된 레벨이 있으면 정리합니다.
	if (mainLevel != nullptr)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	mainLevel = newLevel;
}

bool Engine::GetKey(int keyCode)
{
	if (keyCode < 0 || keyCode >= 256)
	{
		return (false);
	}

	return (keyStates[keyCode].isKeyDown);
}

bool Engine::GetKeyDown(int keyCode)
{
	if (keyCode < 0 || keyCode >= 256)
	{
		return (false);
	}

	const KeyState& state = keyStates[keyCode];
	return (!state.previousKeyDown && state.isKeyDown);
}

bool Engine::GetKeyUp(int keyCode)
{
	if (keyCode < 0 || keyCode >= 256)
	{
		return (false);
	}

	const KeyState state = keyStates[keyCode];
	return (state.previousKeyDown && !state.isKeyDown);
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	// 모든 가상 키(0~255)에 대해 현재 눌림 상태를 갱신합니다.
	for (int key = 0; key < 256; ++key)
	{
		// GetAsyncKeyState가 0x8000 비트가 켜져 있으면 현재 눌려 있는 상태.
		keyStates[key].isKeyDown =
			(GetAsyncKeyState(key) && 0x8000) != 0;
	}
}

void Engine::BeginPlay()
{
	// mainLevel이 등록되어 있으면 레벨의 BeginPlay를 호출합니다.
	if (mainLevel != nullptr)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	// deltaTime: 지난 프레임(또는 누적) 시간(초)
	if (deltaTime <= 0.0f)
	{
		return;
	}

#pragma region testDay2
	//const float fps = 1.0f / deltaTime;

	//std::wcout << L"DeltaTime: " << deltaTime << L", FPS: " << fps << L"\n";
#pragma endregion

	// 등록된 레벨이 있다면 레벨의 Tick을 호출합니다.
	if (mainLevel != nullptr)
	{
		mainLevel->Tick(deltaTime);
	}

#pragma region testDay3
	if (GetKeyDown('A'))
	{
		std::wcout << L"[Engine] A KeyDown\n";
	}
	if (GetKey('A'))
	{
		std::wcout << L"[Engine] A GetKey\n";
	}
	if (GetKeyUp('A'))
	{
		std::wcout << L"[Engine] A GetKeyUp\n";
	}
#pragma endregion

	// ESC 키를 한 번 눌렀을 때 게임 종료.
	if (GetKeyDown(VK_ESCAPE))
	{
		Quit();
	}
}

void Engine::Render()
{
	// 등록된 레벨이 있다면 레벨의 Render를 호출합니다.
	if (mainLevel != nullptr)
	{
		mainLevel->Render();
	}
}
