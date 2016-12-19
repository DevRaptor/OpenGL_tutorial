#include "GameState.h"

#include <iostream>

#include "utility/Log.h"

GameState::GameState()
{
	mesh = std::make_shared<Mesh>();

	camera = std::make_shared<Camera>(45.0f, 0.1f, 100.0f);

}

GameState::~GameState()
{
	Logger::Log("Close GameState \n");
}

void GameState::Update(std::chrono::milliseconds delta_time)
{
	camera->Update();

	/*
	//sample timer
	static std::chrono::high_resolution_clock::time_point timer = std::chrono::high_resolution_clock::now();
	if (std::chrono::high_resolution_clock::now() > timer)
	{
		timer = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
	}
	*/
}
