#include "Mesh.h"

#include <SOIL.h>

#include "utility/Log.h"

Mesh::Mesh(const std::string& model_name, glm::vec3 pos)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	
	if (!LoadOBJ(model_name, vertices, uvs, normals))
		return;


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);
	
	vertex_amount = vertices.size();

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vbo_uv);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);

	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);

	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);


	//texture
	int width, height, channels;
	unsigned char *img = SOIL_load_image("Data/textures/texture.png",
		&width,
		&height,
		&channels,
		SOIL_LOAD_RGB);

	/* check for an error during the load process */
	if (!img) {
		Logger::Log(SOIL_last_result(), "\n");
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

		texture = 0;
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

	SetPosition(pos);
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

void Mesh::SetPosition(glm::vec3 pos)
{
	position = pos;
}

glm::mat4 Mesh::GetTransform()
{
	return glm::translate(glm::mat4(1.0f), position);
}

bool Mesh::LoadOBJ(const std::string& file_name,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals)
{
	Logger::Log("Loading OBJ file ", file_name, "\n");

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE* file = fopen(file_name.c_str(), "r");
	if (file == NULL) {
		Logger::Log("Impossible to open the file ! Are you in the right path?\n");
		getchar();
		return false;
	}

	while (true) 
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				Logger::Log("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}
	fclose(file);
	return true;
}