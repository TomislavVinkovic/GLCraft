#pragma once

#include "glad/glad.h"
#include "Player.h"
#include "Camera.h"
#include<GLFW/glfw3.h>
#include <string>
#include<iostream>

#include "Movement.h"
#include "State.h"

struct Context {
    State state;

    //MOUSE STATE
    //this boolean will trigger whenever a user first
    //enters the window with their mouse
    bool firstMouse = true;
    float lastX = (float)scr_width/(float)2, lastY = (float)scr_height/(float)2;

    Context(const Camera& cam) : state(cam){};
    Context(const Camera& cam, unsigned int w, unsigned int h, const std::string& title);

    unsigned int scr_width;
    unsigned int scr_height;
    float FOV = 45;

    float deltaTime = 0.f;
    float lastFrame = 0.f;

    GLFWwindow* window;

    void adjustDeltaTime();

    void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void handleKeyboardInput(GLFWwindow* window); //continuous input
    void handleKeyboardInterrupt(GLFWwindow* window, int key, int scancode, int action, int mods);
    void handleMouseMovement(GLFWwindow* window, double xPos, double YPos);
    void handleMouseZoom(GLFWwindow* window, double xOffset, double yOffset);
    void handleMouseClick(GLFWwindow* window, int button, int action, int mods);


    private:
        void initCallbacks();
        void reportCrash(const std::string&);
};
