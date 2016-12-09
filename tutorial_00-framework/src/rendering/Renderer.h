#pragma once

#include <memory>

#define GLEW_STATIC //needed to static link GLEW
#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include "GameState.h"


class Renderer
{
public:
	Renderer(int resolution_x, int resolution_y);
	~Renderer();

	void Render(std::shared_ptr<GameState> game_state);

protected:
	SDL_Window* window;
};