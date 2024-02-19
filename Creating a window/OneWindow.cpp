#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "Callbacks.h"
#include "Utilities.h"
int main(int argc, char** argv) {
	glfwSetErrorCallback(glfw_error_callback);
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	GLFWwindow* window = glfwCreateWindow(1200, 800, extract_version(argv[0]), nullptr, nullptr);// extract_version(argv[0]) used to extract the name of our program, full explanation in the utility header
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetWindowCloseCallback(window, glfw_window_clone_callback);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}