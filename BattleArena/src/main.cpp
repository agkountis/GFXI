#include "battle_arena_application.h"

int main(int argc, char** argv)
{
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);


	BattleArenaApplication app;

	if (!app.Initialize(&argc, argv))
	{
		return 1;
	}

	int res = app.Run();

	_CrtDumpMemoryLeaks();

	return res;
}
