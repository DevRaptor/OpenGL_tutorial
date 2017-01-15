#include "Renderer.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "modules/GameModule.h"
#include "utility/Log.h"
#include "utility/FileUtility.h"

Renderer::Renderer()
{
	int resolution_x = GameModule::resources->GetIntParameter("resolution_x");
	int resolution_y = GameModule::resources->GetIntParameter("resolution_y");

	window = SDL_CreateWindow(GameModule::resources->GetStringParameter("game_title").c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		resolution_x, resolution_y, SDL_WINDOW_OPENGL);

	if (window == NULL)
	{
		Logger::Log("Could not create window: ", SDL_GetError(), "\n");
		std::exit(EXIT_FAILURE);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	context = SDL_GL_CreateContext(window);

	glewExperimental = true;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, resolution_x, resolution_y);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);

	shader_program = std::make_shared<ShaderProgram>("data/shaders/color.vert", "data/shaders/color.frag");

	shader_program->UseProgram();

	mvp_uniform = glGetUniformLocation(shader_program->GetProgram(), "mvp");

}

Renderer::~Renderer()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void Renderer::Render(std::shared_ptr<GameState> game_state)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader_program->UseProgram();

	mvp = game_state->camera->GetMVP();
	glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(mvp));

	if(game_state->mesh)
		game_state->mesh->Draw();
	
	SDL_GL_SwapWindow(window);
}
