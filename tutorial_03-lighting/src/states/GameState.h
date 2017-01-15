#pragma once

#include <chrono>
#include <memory>
#include <vector>

#include <SDL.h>

#include "rendering/Mesh.h"
#include "rendering/Camera.h"

class Renderer;

class GameState
{
	friend class Renderer;

public:
	GameState();
	~GameState();

	void Update(std::chrono::milliseconds delta_time);

protected:
	std::vector<std::shared_ptr<Mesh>> meshes;
	std::shared_ptr<Camera> camera;
};
