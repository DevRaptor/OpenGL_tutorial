#include "Mesh.h"

#include <vector>
#include <cstddef> //for NULL

#include <SOIL.h>

#include "utility/Log.h"


/*
//cube
GLfloat vertices[] = {
-1.0f,-1.0f,-1.0f,
-1.0f,-1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,
1.0f, 1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f,-1.0f,
1.0f,-1.0f, 1.0f,
-1.0f,-1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f, 1.0f,-1.0f,
1.0f,-1.0f, 1.0f,
-1.0f,-1.0f, 1.0f,
-1.0f,-1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f,-1.0f, 1.0f,
1.0f,-1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f,-1.0f,
1.0f,-1.0f,-1.0f,
1.0f, 1.0f, 1.0f,
1.0f,-1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f,-1.0f,
-1.0f, 1.0f,-1.0f,
1.0f, 1.0f, 1.0f,
-1.0f, 1.0f,-1.0f,
-1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,
1.0f,-1.0f, 1.0f
};
*/

/*
//triangle
GLfloat vertices[] = {
-1.0f, -1.0f, 0.0f,
1.0f, -1.0f, 0.0f,
0.0f,  1.0f, 0.0f,
};
*/

Mesh::Mesh()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);

	GLfloat vertices[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	vertex_amount = sizeof(vertices) / sizeof(GLfloat);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);


	static const GLfloat uv_buffer_data[] = {
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		0.335973f, 1.0f - 0.335903f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
	};

	GLfloat normals[] = {
		0.000000, 0.000000, -1.000000,
		-1.000000, -0.000000, -0.000000,
		-0.000000, -0.000000, 1.000000,
		-0.000001, 0.000000, 1.000000,
		1.000000, -0.000000, 0.000000,
		1.000000, 0.000000, 0.000001,
		0.000000, 1.000000, -0.000000,
		-0.000000, -1.000000, 0.000000
	};

	glGenBuffers(1, &vbo_uv);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);

	glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer_data), uv_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);




	//texture
	int width, height, channels;
	unsigned char *img = SOIL_load_image("Data/texture.png",
		&width,
		&height,
		&channels,
		SOIL_LOAD_RGB);

	/* check for an error during the load process */
	if (!img) {
		Logger::Log(SOIL_last_result(),"\n");
	}
	else
	{
		Logger::Log("SOIL loading succesfull\n");

		// Reverse Y axis
		std::vector<unsigned char> img_y_rev(width * height * channels, 0);
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				for (int k = 0; k < channels; ++k) {
					img_y_rev[(height - i - 1)*width * 3 + j * 3 + k]
						= img[i * width * 3 + j * 3 + k];
				}
			}
		}

		GLuint texture = 0;
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, &img_y_rev[0]);

		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(img);
	}
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo_vertex);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::Draw()
{
	glBindVertexArray(vao);

	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawArrays(GL_TRIANGLES, 0, vertex_amount);

	glBindVertexArray(0);
}
