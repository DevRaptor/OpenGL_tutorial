#include <iostream>

#include "utility/Log.h"
#include "GameEngine.h"

#undef main

int main(int argc, char* argv[])
{
	GameEngine engine;

	while (!engine.IsExit())
	{
		engine.Update();
	}

	return 0;
}