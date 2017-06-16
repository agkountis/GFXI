#ifndef BATTLE_ARENA_APPLICATION_H_
#define BATTLE_ARENA_APPLICATION_H_
#include "application.h"

class BattleArenaApplication : public Blade::Application
{

public:
	bool Initialize(int* argc, char* argv[]) override;

	void Update() noexcept override;

	void Draw() const noexcept override;

	int Run() noexcept override;
};

#endif //BATTLE_ARENA_APPLICATION_H_
