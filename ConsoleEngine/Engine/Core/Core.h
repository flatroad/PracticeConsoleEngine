/// @file Core.h
/// @brief Engine DLL을 위한 기본 매크로와 공용 정의를 제공합니다.
/// 
/// 이 헤더는 DLL export/import 매크로(Engine_API)를 정의합니다.
/// Engine 프로젝트에서는 dllexport, Game 프로젝트에서는 dllimport로 동작합니다.

#pragma once

// dll 외부로 템플릿 내볼낼 때 발생하는 경고 비활성화.
#pragma warning(disable : 4251)

// 지역 변수의 주소를 반환할 때 발생하는 경고 비활성화.
#pragma warning(disable : 4172)

// CRT 디버그를 위한 매크로/헤더 설정.
// 메모리 누수 추적에 사용.
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


// Engine Dll export / import 매크로.
// BuildEngineDll가 정의된 경우 (Engine 프로젝트 빌드 시) dllexport로
// 그렇지 않은 경우 (Game 등에서 사용할 때) dllimport로 동작합니다.
#ifdef BuildEngineDLL
	#define Engine_API __declspec(dllexport)
#else
	#define Engine_API __declspec(dllimport)
#endif