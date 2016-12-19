#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
public:
	Camera(float fov, float near, float far);
	~Camera();

	glm::mat4 GetMVP();
	void Update();

private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;
};
