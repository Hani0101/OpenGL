#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Callbacks.h"
#include<string>
#include<iostream>

const int NUM_WINDOWS = 10; // Change this to the desired number of windows

int main(int argc, char** argv) {
    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();

    // Create an array to hold pointers to GLFW windows
    GLFWwindow* windows[NUM_WINDOWS];

    // Create multiple GLFW windows
    for (int i = 0; i < NUM_WINDOWS; ++i) {
        windows[i] = glfwCreateWindow(1200, 800, ("OpenGL Window " + std::to_string(i)).c_str(), nullptr, nullptr);
        if (!windows[i]) {
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(windows[i]);
    }

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Main loop
    while (true) {
        // Loop through each window
        for (int i = 0; i < NUM_WINDOWS; ++i) {
            // Set the context to the current window
            glfwMakeContextCurrent(windows[i]);

            // Render or do other operations for each window here

            // Swap buffers and poll events
            glfwSwapBuffers(windows[i]);
            glfwPollEvents();

            // Check if window should close
            if (glfwWindowShouldClose(windows[i])) {
                // Close the window
                glfwDestroyWindow(windows[i]);
                windows[i] = nullptr;
            }
        }

        // Check if all windows are closed
        bool allClosed = true;
        for (int i = 0; i < NUM_WINDOWS; ++i) {
            if (windows[i] != nullptr) {
                allClosed = false;
                break;
            }
        }
        if (allClosed) break; // Exit the loop if all windows are closed
    }

    glfwTerminate();
    return 0;
}
