#include "Level.h"

// 기본 생성자.
Level::Level()
{
}

// 소멸자: 레벨이 소유한 Actor들을 해제합니다.
Level::~Level()
{
	for (Actor* actor : actors)
	{
		delete actor;
	}
	actors.clear();
}

// 레벨에 Actor를 추가합니다.
void Level::AddActor(Actor* actor)
{
	if (actor == nullptr)
	{
		return;
	}

	actors.push_back(actor);
}

// 레벨이 시작될 때 한 번만 호출되는 함수입니다.
void Level::BeginPlay()
{
	for (Actor* actor : actors)
	{
		if (actor != nullptr && !actor->HasBeganPlay())
		{
			actor->BeginPlay();
		}
	}
}

// 매 프레임마다 호출되는 함수입니다.
void Level::Tick(float deltaTime)
{
	for (Actor* actor : actors)
	{
		if (actor == nullptr)
		{
			continue;
		}

		// 아직 BeginPlay를 안 한 Actor가 있다면 여기서라도 보장.
		if (!actor->HasBeganPlay())
		{
			actor->BeginPlay();
		}

		actor->Tick(deltaTime);
	}
}

// 매 프레임 렌더링 시 호출되는 함수입니다.
void Level::Render()
{
	for (Actor* actor : actors)
	{
		if (actor != nullptr)
		{
			actor->Render();
		}
	}
}