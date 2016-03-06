#ifndef WHITEBOARD_MINIMALWHITEBOARDCONTEXT_H
#define WHITEBOARD_MINIMALWHITEBOARDCONTEXT_H

#include <iostream>
#ifdef __APPLE__
#	define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include "nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"
#include "whiteboard.h"

void updateMinimalContext (GLFWwindow* window, NVGcontext* vg, whiteboard* wb) {
    int winWidth, winHeight;
    int fbWidth, fbHeight;

    while (!glfwWindowShouldClose(window)) {
        glfwGetWindowSize(window, &winWidth, &winHeight);
        glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
        float pxRatio = (float)fbWidth / (float)winWidth;

        // Update and render
        glViewport(0, 0, fbWidth, fbHeight);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

        nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

        wb->draw(vg, winWidth, winHeight);

        nvgEndFrame(vg);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    nvgDeleteGL3(vg);
    glfwTerminate();
}

void minimalWhiteboardContext (int width, int height, whiteboard* wb) {
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW.";
        return;
    }

#ifndef _WIN32 // don't require this on win32, and works with more cards
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

    GLFWwindow* window = glfwCreateWindow(width, height, "Whiteboard", NULL, NULL);

    if (!window) {
        glfwTerminate();
        std::cout << "couldn't create window" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);

    NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

    wb->init(vg);

    updateMinimalContext(window, vg, wb);
}

#endif //WHITEBOARD_MINIMALWHITEBOARDCONTEXT_H
