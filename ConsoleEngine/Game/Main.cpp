#include <io.h> // _setmode, _fileno.
#include <fcntl.h> // _O_U16TEXT.
#include <iostream> // std::wcout.
#include <Engine.h>

// 프로그램의 진입점.
int wmain(int argc, wchar_t* argv[])
{
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

	// 엔진 객체 생성.
	Engine engine;

	// 메인 게임 루프 실행.
	engine.Run();

	std::wcout << L"엔진 종료\n";

	return (0);
}