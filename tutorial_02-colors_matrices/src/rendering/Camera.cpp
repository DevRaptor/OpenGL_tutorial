#include "Camera.h"

#include <iostream>

#include "modules/GameModule.h"

Camera::Camera(float fov, float near, float far)
{
	float resolution_x = GameModule::resources->GetIntParameter("resolution_x");
	float resolution_y = GameModule::resources->GetIntParameter("resolution_y");
	float ratio = resolution_x / resolution_y;

	position = glm::vec3(1, 1, 0),
	up = glm::vec3(0, 1, 0);

	projection = glm::perspective(glm::radians(fov), ratio, near, far);
	view = glm::lookAt(position, glm::vec3(0,0,0), up);
	model = glm::mat4(1.0f);
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetMVP()
{
	return projection * view * model;
}

void Camera::Update()
{
	glm::vec2 mouse_delta = GameModule::input->GetMouseDeltaPos();



	if (GameModule::input->GetKeyState(SDL_SCANCODE_LEFT))
	{
		position.x += 1.0f;
	}
	else if (GameModule::input->GetKeyState(SDL_SCANCODE_RIGHT))
	{
		position.x -= 1.0f;
	}

	if (GameModule::input->GetKeyState(SDL_SCANCODE_DOWN))
	{	
		position.y -= 1.0f;
	}
	else if (GameModule::input->GetKeyState(SDL_SCANCODE_UP))
	{
		position.y += 1.0f;
	}

	std::cout << position.x << " " << position.y << " " << position.z << "\n";


	view = glm::lookAt(position, glm::vec3(0,0,0), up);
}
