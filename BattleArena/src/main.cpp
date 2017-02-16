#include "battle_arena_application.h"

int main(int argc, char** argv)
{
	BattleArenaApplication application;

	if (!application.Initialize(&argc, argv))
	{
		return 1;
	}

	application.Run();

	return 0;
}
