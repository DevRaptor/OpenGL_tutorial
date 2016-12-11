#pragma once

#include <chrono>
#include <memory>
#include <vector>

#include <SDL.h>


class Renderer;

class GameState
{
	friend class Renderer;

public:
	GameState();
	~GameState();

	void Update(std::chrono::milliseconds delta_time);
};
