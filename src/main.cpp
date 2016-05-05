// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "controls.hpp"

std::vector<glm::vec3> getCube(glm::vec3 offset) {
	std::vector<glm::vec3> re;
	GLfloat g_vertex_buffer_data[] = {
		-0.125f,-0.125f,-0.125f,
		-0.125f,-0.125f, 0.125f,
		-0.125f, 0.125f, 0.125f,
		 0.125f, 0.125f,-0.125f,
		-0.125f,-0.125f,-0.125f,
		-0.125f, 0.125f,-0.125f,
		 0.125f,-0.125f, 0.125f,
		-0.125f,-0.125f,-0.125f,
		 0.125f,-0.125f,-0.125f,
		 0.125f, 0.125f,-0.125f,
		 0.125f,-0.125f,-0.125f,
		-0.125f,-0.125f,-0.125f,
		-0.125f,-0.125f,-0.125f,
		-0.125f, 0.125f, 0.125f,
		-0.125f, 0.125f,-0.125f,
		 0.125f,-0.125f, 0.125f,
		-0.125f,-0.125f, 0.125f,
		-0.125f,-0.125f,-0.125f,
		-0.125f, 0.125f, 0.125f,
		-0.125f,-0.125f, 0.125f,
		 0.125f,-0.125f, 0.125f,
		 0.125f, 0.125f, 0.125f,
		 0.125f,-0.125f,-0.125f,
		 0.125f, 0.125f,-0.125f,
		 0.125f,-0.125f,-0.125f,
		 0.125f, 0.125f, 0.125f,
		 0.125f,-0.125f, 0.125f,
		 0.125f, 0.125f, 0.125f,
		 0.125f, 0.125f,-0.125f,
		-0.125f, 0.125f,-0.125f,
		 0.125f, 0.125f, 0.125f,
		-0.125f, 0.125f,-0.125f,
		-0.125f, 0.125f, 0.125f,
		 0.125f, 0.125f, 0.125f,
		-0.125f, 0.125f, 0.125f,
		 0.125f,-0.125f, 0.125f
	};
	for (int i = 0; i < 12*3*3; i += 3) {
			re.push_back(glm::vec3(g_vertex_buffer_data[i], g_vertex_buffer_data[i+1], g_vertex_buffer_data[i+2]));
	}
	for (int i = 0; i < re.size(); i++) {
		re[i] += offset;
	}

	return re;
}

std::vector<glm::vec3> getColorForCube(glm::vec3 color) {
	std::vector<glm::vec3> re (36, color);
	return re;
}

std::vector<glm::vec3> swapCubes(std::vector<glm::vec3> v, int i, int j) {
	int fst = i * 36;
	int snd = j * 36;
	for (int k = 0; k < 36; k++) {
		glm::vec3 tmp = v[fst+k];
		v[fst+k] = v[snd+k];
		v[snd+k] = tmp;
	}

	return v;
}

int main(int argc, char* argv[])
{
	if(!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "OpenGL Sample", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE); // ????????????????????????????????????????????????


	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("shaders/vertex.glsl", "shaders/fragment.glsl");

	// Get a handle for our buffers
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	GLuint colorID = glGetAttribLocation(programID, "a_color");

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> colors;

	std::vector<glm::vec3> tmp = getCube(glm::vec3(0.0, 0.0, 0.0));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.875, 0.0, 0.0));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.0, 0.875, 0.0));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.0, 0.0, 0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(-0.875, 0.0, 0.0));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.0, -0.875, 0.0));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.0, 0.0, -0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.875, 0.875, 0.0));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.0, 0.875, 0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.875, 0.0, 0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(-0.875, -0.875, 0.0));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.0, -0.875, -0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(-0.875, 0.0, -0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.875, -0.875, 0.0));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(-0.875, 0.875, 0.0));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.0, 0.875, -0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.0, -0.875, 0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.875, 0.0, -0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(-0.875, 0.0, 0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.875, 0.875, 0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(-0.875, -0.875, -0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.875, 0.875, -0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.875, -0.875, 0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(0.875, -0.875, -0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(-0.875, 0.875, 0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(-0.875, 0.875, -0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());
	tmp = getCube(glm::vec3(-0.875, -0.875, 0.875));
	vertices.insert(vertices.end(), tmp.begin(), tmp.end());

	std::vector<glm::vec3> tmpColor = getColorForCube(glm::vec3(1.0, 0.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 0.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 1.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 0.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 1.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 0.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 1.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 0.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 1.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 0.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 1.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 0.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 1.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 0.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 1.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 0.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 1.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 0.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 1.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 0.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 1.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 0.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 1.0, 0.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 0.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 1.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(1.0, 0.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());
	tmpColor = getColorForCube(glm::vec3(0.0, 1.0, 1.0));
	colors.insert(colors.end(), tmpColor.begin(), tmpColor.end());

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Use our shader
    glUseProgram(programID);

		computeMatricesFromInputs();
		glm::mat4 Projection = getProjectionMatrix();
		glm::mat4 View       = getViewMatrix();
		glm::mat4 Model      = glm::mat4(1.0f);
		glm::mat4 MVP        = Projection * View * Model;

		glm::vec3 cameraPos = getPosition();
		for (int i = 0; i < 27; i++) {
			for (int j = i+1; j < 27; j++) {
				if (glm::distance(cameraPos, vertices[i*36]) < glm::distance(cameraPos, vertices[j*36])) {
					vertices = swapCubes(vertices, i, j);
					colors = swapCubes(colors, i, j);
				}
			}
		}

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);

		// attribute buffer : vertices
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			vertexPosition_modelspaceID, 	// The attribute we want to configure
			3,                  					// size
			GL_FLOAT,           					// type
			GL_FALSE,           					// normalized?
			0,														// stride
			(void*)0            					// array buffer offset
		);

		// attribute buffer : colors
		glEnableVertexAttribArray(colorID);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			colorID, 	// The attribute we want to configure
			3,                  					// size
			GL_FLOAT,           					// type
			GL_FALSE,           					// normalized?
			0,														// stride
			(void*)0            					// array buffer offset
		);

		// Draw the triangles
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glDisableVertexAttribArray(vertexPosition_modelspaceID);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
