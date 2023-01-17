#include "Context.h"

Context::Context(const Camera& camera, unsigned int w, unsigned int h, const std::string& title) : Context(camera) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    scr_width = w;
    scr_height = h;

    this->window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);

    if(window == NULL)
        reportCrash("Failed to create GLFW window");

    glfwMakeContextCurrent(window);
    initCallbacks();

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        reportCrash("Failed to init GLAD");

    //ENABLANJE INPUT FEATUREA OPENGL-A
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Context::adjustDeltaTime(){
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Context::reportCrash(const std::string&) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
}

void Context::handleKeyboardInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        state.player.getCamera().ProcessKeyboard(Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        state.player.getCamera().ProcessKeyboard(Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        state.player.getCamera().ProcessKeyboard(Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        state.player.getCamera().ProcessKeyboard(Movement::RIGHT, deltaTime);
}

void Context::handleKeyboardInterrupt(GLFWwindow *window, int key, int scancode, int action, int mods) {
    //TOGGLE ZA WIREFRAME MOD
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        GLint polygonMode[2];
        glGetIntegerv(GL_POLYGON_MODE, polygonMode);
        if(*polygonMode == GL_LINE)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else if(*polygonMode == GL_FILL)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    //TOGGLE ZA INVENTORY SLOT
    if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        state.player.setSelectedSlot(0);
    }
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        state.player.setSelectedSlot(1);
    }
    else if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        state.player.setSelectedSlot(2);
    }
    else if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        state.player.setSelectedSlot(3);
    }
    else if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        state.player.setSelectedSlot(4);
    }
    else if(glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) {
        state.player.setSelectedSlot(5);
    }
    else if(glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        state.player.setSelectedSlot(6);
    }
    else if(glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS) {
        state.player.setSelectedSlot(7);
    }
    else if(glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
        state.player.setSelectedSlot(8);
    }
    else if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
        state.player.setSelectedSlot(9);
    }
}

void Context::handleMouseMovement(GLFWwindow *window, double xPos, double yPos) {
    float xPosf = static_cast<float>(xPos);
    float yPosf = static_cast<float>(yPos);
    if(firstMouse) {
        lastX = xPosf;
        lastY = yPosf;
        firstMouse = false;
    }

    float xOffset = xPosf - lastX;
    float yOffset = lastY - yPosf;

    lastX = xPosf;
    lastY = yPosf;

    state.player.getCamera().ProcessMouseMovement(xOffset, yOffset);
}

void Context::handleMouseZoom(GLFWwindow *window, double xOffset, double yOffset) {
    state.player.getCamera().ProcessMouseScroll(static_cast<float>(yOffset));
}

void Context::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0,0,scr_width, scr_height);
}

void Context::initCallbacks() {
    glfwSetWindowUserPointer(window, this);

    //initanje svake funkcije na ovu instancu prozora
    auto framebuffer_func = [](GLFWwindow* w, int width, int height) {
        static_cast<Context*>(glfwGetWindowUserPointer(w))->framebuffer_size_callback(w, width, height);
    };

    auto interrupt_func = [](GLFWwindow* w, int key, int scancode, int action, int mods) {
        static_cast<Context*>(glfwGetWindowUserPointer(w))->handleKeyboardInterrupt(
                w, key, scancode, action, mods
        );
    };

    auto mousemove_func = [](GLFWwindow* w, double xPos, double yPos) {
        static_cast<Context*>(glfwGetWindowUserPointer(w))->handleMouseMovement(
                w, xPos, yPos
        );
    };

    auto mousezoom_func = [](GLFWwindow* w, double xOffset, double yOffset) {
        static_cast<Context*>(glfwGetWindowUserPointer(w))->handleMouseZoom(
                w, xOffset, yOffset
        );
    };

    auto mouseclick_func = [](GLFWwindow* w, int button, int action, int mods) {
        static_cast<Context*>(glfwGetWindowUserPointer(w))->handleMouseClick(
                w, button, action, mods
        );
    };

    //assignanje tih funkcija na instancu prozora preko opengl-a
    glfwSetFramebufferSizeCallback(window, framebuffer_func);
    glfwSetKeyCallback(window, interrupt_func);
    glfwSetCursorPosCallback(window, mousemove_func);
    glfwSetScrollCallback(window, mousezoom_func);
    glfwSetMouseButtonCallback(window, mouseclick_func);
}

void Context::handleMouseClick(GLFWwindow *window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        //zasad samo cast ray
        //std::cout << "Left click!" << std::endl;
        state.world.castRay(state.player.getCamera(), button);
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        //zasad samo cast ray
        //std::cout << "Right click!" << std::endl;
        state.world.castRay(state.player.getCamera(), button);
    }
}
