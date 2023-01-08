#pragma once

#include "glm.hpp"
#include "Camera.h"
#include <cmath>

class Ray {
    private:
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        glm::vec3 origin;
        glm::vec3 direction;
        glm::vec3 end;
    public:
        Ray(const glm::vec3 origin, const glm::vec3 direction);
        void step(float scale, const Camera& camera);
        const glm::vec3& getEnd() const;
        float getLength() const;

};
