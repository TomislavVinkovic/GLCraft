#pragma once

#include <array>
#include "glm.hpp"
#include "ABAB.h"

struct Plane {
    float distanceToPoint(const glm::vec3 &point) const;

    float distanceToOrigin;
    glm::vec3 normal;
};

class ViewFrustum {
public:
    void update(const glm::mat4 &projViewMatrix) noexcept;

    bool isBoxInFrustum(const ABAB &box) const noexcept;

private:
    std::array<Plane, 6> m_planes;
};
