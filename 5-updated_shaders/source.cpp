#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Callbacks.h"
#include "Utilities.h"
#include "Vertex.h"
#include <vector>
#include "MeshLoader.h"
#include "Draw.h"
#include"Version.h"
#include "Input.h"
#include "ShaderLoader.h"
#include"QuerryAttribs.h"
#include<iostream>
#include<random>
using namespace std;
int main(int argc, char** argv)
{
	glfwSetErrorCallback(glfw_error_callback);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, extract_prog_name(argv[0]), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	printGLinfo();

	glfwSetWindowCloseCallback(window, glfw_window_close_callback);
	glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
	glClearColor(.6f, .1f, .6f, 0.f);

	const char* vertshader =
		"#version 430 \n"
		"layout(location = 0) in vec3 vertPos; \n"
		"layout(location = 1) in vec3 vertColor; \n"
		"layout(location = 0) out vec4 fragColor;\n"
		"void main(){ \n"
		"  fragColor = vec4(vertColor, 1.0); \n"
		"  gl_Position = vec4(vertPos, 1.0); \n"
		"}";
	const char* fragshader =
		"#version 430 \n"
		"layout(location = 0) in vec4 fragColor; \n"
		"out vec4 color;\n"
		"void main() { \n"
		"  color = fragColor; \n"
		"}";
	unsigned int mainShader = LoadShader(vertshader, fragshader);
	glClearColor(.2f, .2f, .0f, 0.f);//new
	vector<DrawDetails> ourDrawDetails;
	{
		// CREATE ARRAY TO DISPLAY (Position)
		const float posData[] = {
			-0.8f, -0.8f, 0.0f,
			 0.8f, -0.8f, 0.0f,
			 0.0f, 0.8f, 0.0f,
		};
		// CREATE ARRAY TO DISPLAY (Color)
		const float colorData[] = {
			1.0f, 0.0f, 0.0f,
			0.8f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
		};
		const GLuint elems[] = { 0,1,2 };
		ourDrawDetails.push_back(UploadMesh(posData, colorData, sizeof(posData)/sizeof(posData[0]),
			elems, sizeof(elems) / sizeof(elems[0])));
	}
	//default_random_engine generator;
	//uniform_real_distribution<float> distribution(0.f, 1.f);
	QueryAttribs(ourDrawDetails.back().vao);
	while (!glfwWindowShouldClose(window))
	{
		// HANDLE KEYPRESS
		ProcessInput(window);
		glClear(GL_COLOR_BUFFER_BIT);
		// RENDER OUR OBJECT
		glUseProgram(mainShader);

		//float c1 = distribution(generator);
		//float c2 = distribution(generator);
		//float c3 = distribution(generator);
		//uint32_t var = glGetUniformLocation(mainShader, "ucolor");
		//glUniform3f(var, c1, c2, c3);

		Draw(ourDrawDetails);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// UNLOAD DATA FROM GRAPHICS CARD
	UnloadMesh(ourDrawDetails);

	glfwTerminate();
	return 0;
}