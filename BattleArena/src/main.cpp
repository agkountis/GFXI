#include "battle_arena_application.h"
#include "trace.h"


int main(int argc, char** argv)
{
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);

	BattleArenaApplication application;

	if (!application.Initialize(&argc, argv))
	{
		BLADE_TRACE("Application Terminating! Exit code 1");
		return 1;
	}

	BLADE_TRACE("Application Initialized!") // console and vs output printout

	BLADE_TRACE("Running Application!")
	int res = application.Run();

	_CrtDumpMemoryLeaks();

	BLADE_TRACE("Application Terimating! Exit code 0")
	return res;
}
