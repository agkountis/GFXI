#include "battle_arena_application.h"
#include "trace.h"

int main(int argc, char** argv)
{
	BattleArenaApplication application;
	

	if (!application.Initialize(&argc, argv))
	{
		return 1;
	}
	BLADE_TRACE_VSOUT("APP INITIALIZED.."); // viusal studio output printout
	BLADE_TRACE_CON("APP INITIALIZED.."); // console output printout
	BLADE_TRACE("CONSOLE AND VS PRINTOUT.."); // console and vs output printout
	application.Run();

	return 0;
}
