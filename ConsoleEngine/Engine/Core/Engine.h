#pragma once

#include "Core.h"

// 앞으로 사용할 Level 클래스를 미리 선언합니다.
class Level;

/// @class Engine
/// @brief 콘솔 기반 게임 루프를 관리하는 엔진 클래스.
/// 
/// 고해상도 타이머를 이용해 delta time과 FPS를 계산하고,
/// 입력 처리, 업데이트, 렌더링 루프를 수행합니다.
/// 하나의 레벨(Level)을 등록하여 BeginPlay / Tick / Render를 호출하고,
/// 키 입력 상태를 조회할 수 있는 함수 (GetKey, GetKeyDown, GetKeyUp)를 제공합니다.
class Engine_API Engine
{
	/// @brief 단일 키의 상태를 표현하는 구조체.
	struct KeyState
	{
		/// @brief 이번 프레임에 키가 눌려 있는지 여부입니다.
		bool isKeyDown = false;

		/// @brief 직전 프레임에 키가 눌려 있었는지 여부입니다.
		bool previousKeyDown = false;
	};

public:
	/// @brief 엔진을 초기화합니다.
	Engine();

	/// @brief 엔진이 종료될 떄 정리 작업을 수행합니다.
	~Engine();

	/// @brief 메인 게임 루프를 실행합니다.
	void Run();

	/// @brief 레벨을 엔진에 등록합니다. 기존 레벨이 있을 경우 삭제됩니다.
	/// @param newLevel 엔진이 관리할 레벨 포인터입니다.
	void AddLevel(Level* newLevel);

	/// @brief 키가 눌려 있는지 확인합니다. (매 프레임)
	/// @param[In] keyCode 가상 키 코드(0~255)입니다.
	/// @return 키가 눌려 있으면 true, 아니면 false를 반환합니다.
	bool GetKey(int keyCode);

	/// @brief 이번 프레임에 키가 새로 눌렸는지 확인합니다.
	/// @param[In] keyCode 가상 키 코드(0~255)입니다.
	/// @return 직전 프레임에는 눌려 있지 않았고 이번 프레임에 눌렸다면 true, 아니면 false를 반환합니다.
	bool GetKeyDown(int keyCode);

	/// @brief 이번 프레임에 키가 떼어졌는지 확인합니다.
	/// @param[In] keyCode 가상 키 코드(0~255)입니다.
	/// @return 직전 프레임에는 눌려 있었고 이번 프레임에 떼어졌다면 true, 아니면 false를 반환합니다.
	bool GetKeyUp(int keyCode);

	/// @brief 게임 루프를 종료하도록 플레그를 설정합니다.
	void Quit();

private:
	/// @brief 입력 처리를 관리합니다.
	///
	/// Win32 GetAsyncKeyState를 사용해 모든 가상 키(0~255)의
	/// 현재 눌림 상태를 keyStates 배열에 기록합니다.
	void ProcessInput();

	/// @brief 레벨과 관련된 초기화 처리(BeginPlay)를 수행합니다.
	///
	/// 등록된 레벨이 있을 경우 Level::BeginPlay를 호출하여,
	/// 아직 BeginPlay가 호출되지 않은 Actor들의 초기화가
	/// 한 번 이상 수행되도록 합니다.
	/// 이 함수 자체는 Run 루프에서 반복 호출되므로
	/// 새로 추가된 Actor 역시 BeginPlay 호출을 보장합니다.
	void BeginPlay();

	/// @brief 매 프레임마다 게임 상태 업데이트합니다.
	/// @param[In] deltaTime 이전 프레임 이후 경과 시간(초 단위)
	void Tick(float deltaTime = 0.0f);

	/// @brief 화면/콘솔 출력 등 렌더링 처리합니다.
	///
	/// 등록된 레벨이 있을 경우 Level::Render를 호출합니다.
	void Render();

	/// @brief 엔진 종료 플래그입니다. true가 되면 루프 종료됩니다.
	bool isQuit = false;

	/// @brief 모든 키의 상태를 저장하는 배열입니다. (0~255 가상 키 코드)
	KeyState keyStates[256];

	/// @brief 현재 엔진이 관리하는 메인 레벨입니다.
	Level* mainLevel = nullptr;
};