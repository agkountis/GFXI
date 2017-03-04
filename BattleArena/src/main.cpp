#include "battle_arena_application.h"

#ifdef _DEBUG 

/* MEMORY LEAKS DETECTION */
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

struct AtExit
{
  ~AtExit()
  {
    _CrtDumpMemoryLeaks();
  }
} doAtExit;

/* ENDS - MEMORY LEAKS DETECTION */
#endif

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
