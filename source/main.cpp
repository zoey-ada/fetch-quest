#include "engine.hpp"

int main()
{
	auto game = std::make_shared<Engine>();
	// logInfo("starting game");
	game->initialize();
	// logWarning("running game", "state");
	auto ret = game->run();
	// logError("ending game");
	game->deinitialize();

	return ret;
}

#ifdef _WIN32
	#include <Windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, PSTR, int)
{
	return main();
}
#endif
