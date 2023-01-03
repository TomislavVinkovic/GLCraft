#include <iostream>
#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include "Shader.hpp"

//GLM
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "Application.h"
#include "Camera.h"
int main() {
    Application App(800, 600, "GLCraft", Camera(800, 600));
    App.runLoop();
    return 0;
}