#pragma once

#include <memory>

#define GLEW_STATIC //needed to static link GLEW
#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include "states/GameState.h"

#include "rendering/Mesh.h"
#include "rendering/ShaderProgram.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Render(std::shared_ptr<GameState> game_state);

protected:
	SDL_Window* window;
};
