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
#include "whiteboard_renderer.h"

whiteboard_renderer* wb;

void updateMinimalContext (GLFWwindow* window, NVGcontext* vg) {
    int winWidth, winHeight;
    int fbWidth, fbHeight;

    glfwSetKeyCallback(window, [](GLFWwindow * w, int key, int scancode, int action, int mods) {
       if (action == GLFW_RELEASE || action == GLFW_REPEAT) {
           if (key == GLFW_KEY_RIGHT) {
               wb->forward();
           } else if (key == GLFW_KEY_LEFT) {
               wb->backward();
           }
       }
    });

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

void minimalWhiteboardContext (int width, int height, whiteboard_renderer* wbToUse) {
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW.";
        return;
    }

    wb = wbToUse;

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
    glfwSwapInterval(10);

    NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

    wb->init(vg);

    updateMinimalContext(window, vg);
}

#endif //WHITEBOARD_MINIMALWHITEBOARDCONTEXT_H
