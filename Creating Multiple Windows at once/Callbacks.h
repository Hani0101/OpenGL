#pragma once
#pragma once
#include<cstdio>
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Erro: %s\n", description);
	throw("glfw.error");
}

static void glfw_window_clone_callback(GLFWwindow* window)
{
	printf("window closed\n");
}

