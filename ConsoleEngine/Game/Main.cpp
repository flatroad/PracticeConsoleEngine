#include <io.h> // _setmode, _fileno.
#include <fcntl.h> // _O_U16TEXT.
#include <iostream> // std::wcout.
#include <string>
#include <Windows.h>
#include <crtdbg.h> // 메모리 누수 확인.

#include "Core/Engine.h"
#include "Math/Vector2.h"
#include "Levels/DemoLevel.h"

// ANSI 문자열(현 시스템 코드페이지 기준)을 std::wstring으로 변환.
std::wstring AnsiToWide(const char* str)
{
	if (str == nullptr)
	{
		return (L"");
	}

	// MultiByteToWideChar: ANSI(멀티바이트) -> UTF-16
	// 먼저 필요한 wide 문자 개수(널포함)를 얻는다.
	const int length = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
	if (length <= 0)
	{
		return (L"");
	}

	// Length에는 널 문자까지 포함된 길이가 들어있다.
	// std::wstring result는 널이 보장되어 있어서 Length에서 널은 생략해야한다.
	std::wstring result;
	result.resize(length - 1); // 실제 문자열 길이만큼 공간 확보 (널은 제외).
	
	// &result[0] 는 쓰기 가능한 버퍼.
	MultiByteToWideChar(CP_ACP, 0, str, -1, &result[0], length);

	return (result);
}

// 프로그램의 진입점.
int wmain(int argc, wchar_t* argv[])
{
	// 메모리 누수 체크를 위한 CRT Debug 플래그 설정.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 콘솔의 표준 출력/에러를 UTF-16 텍스트 모드로 변경.
	if (_setmode(_fileno(stdout), _O_U16TEXT) == -1)
	{
		return (1);
	}
	if (_setmode(_fileno(stderr), _O_U16TEXT) == -1)
	{
		return (1);
	}

	std::wcout << L"콘솔 엔진 시작\n";

#pragma region Test_day2
	//// Vector2 테스트.
	//Vector2 a(10, 20);
	//Vector2 b(20, 30);
	//Vector2 c = a + b;

	//// ANSI -> Wide 변환 후 출력.
	//std::wstring cText = AnsiToWide(c.ToString());
	//std::wcout << L"a(10, 20) + b(20, 30) = " << cText << L"\n";
#pragma endregion

	// 엔진 객체 생성 및 레벨 등록.
	Engine engine;
	engine.AddLevel(new DemoLevel());

	// 메인 게임 루프 실행.
	engine.Run();

	std::wcout << L"엔진 종료\n";

	return (0);
}