#include "Ray.h"

Ray::Ray(const glm::vec3 origin, const glm::vec3 direction)
    : origin(origin), direction(direction), end(origin){}

void Ray::step(float scale, const Camera& camera) {
//    float yaw = glm::radians(camera.Yaw);
//    float pitch = glm::radians(camera.Pitch);
//    float x = glm::cos(yaw) * scale;
//    float y = glm::tan(pitch) * scale;
//    float z = glm::sin(yaw) * scale;

//    float x = direction.x * scale;
//    float y = direction.x * scale;
//    float z = direction.x * scale;

    end+=direction*scale;
}

const glm::vec3 &Ray::getEnd() const {
    return end;
}

float Ray::getLength() const {
    return glm::distance(origin, end);
}
