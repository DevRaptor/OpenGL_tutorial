#include "GameState.h"

#include <iostream>

#include "utility/Log.h"

GameState::GameState()
{

}

GameState::~GameState()
{
	Logger::Log("Close GameState \n");
}

void GameState::Update(std::chrono::milliseconds delta_time)
{
	/*
	//sample timer
	static std::chrono::high_resolution_clock::time_point timer = std::chrono::high_resolution_clock::now();
	if (std::chrono::high_resolution_clock::now() > timer)
	{
		timer = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
	}
	*/
}
