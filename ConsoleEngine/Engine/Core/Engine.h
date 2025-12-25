#pragma once

#include "Core.h"

// 앞으로 사용할 Level 클래스를 미리 선언합니다.
class Level;

/// @class Engine
/// @brief 콘솔 기반 게임 루프를 관리하는 엔진 클래스.
/// 
/// 고해상도 타이머를 이용해 delta time과 FPS를 계산하고,
/// 입력 처리, 업데이트, 렌더링 루프를 수행합니다.
class Engine_API Engine
{
public:
	/// @brief 엔진을 초기화합니다.
	Engine();

	/// @brief 엔진이 종료될 떄 정리 작업을 수행합니다.
	~Engine();

	/// @brief 메인 게임 루프를 실행합니다.
	void Run();

	/// @brief 레벨을 엔진에 등록합니다. 기존 레벨이 있을 경우 삭제됩니다.
	void AddLevel(Level* newLevel);

	/// @brief 게임 루프를 종료하도록 플레그를 설정합니다.
	void Quit();

private:
	/// @brief 입력 처리를 관리합니다.
	void ProcessInput();

	/// @brief 레벨과 관련된 초기화 처리(BeginPlay)를 수행합니다.
	void BeginPlay();

	/// @brief 매 프레임마다 게임 상태 업데이트합니다.
	/// @param[In] deltaTime 이전 프레임 이후 경과 시간(초 단위)
	void Tick(float deltaTime = 0.0f);

	/// @brief 화면/콘솔 출력 등 렌더링 처리합니다.
	void Render();

	/// @brief 엔진 종료 플래그입니다. true가 되면 루프 종료됩니다.
	bool isQuit = false;

	/// @brief 현재 엔진이 관리하는 메인 레벨입니다.
	Level* mainLevel = nullptr;
};