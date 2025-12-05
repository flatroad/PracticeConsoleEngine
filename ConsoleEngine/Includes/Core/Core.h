/// @file Core.h
/// @brief Engine DLL을 위한 기본 매크로와 공용 정의를 제공합니다.
/// 
/// 이 헤더는 DLL export/import 매크로(Engine_API)를 정의합니다.
/// Engine 프로젝트에서는 dllexport, Game 프로젝트에서는 dllimport로 동작합니다.
#pragma once

#ifdef BuildEngineDLL
	#define Engine_API __declspec(dllexport)
#else
	#define Engine_API __declspec(dllimport)
#endif!