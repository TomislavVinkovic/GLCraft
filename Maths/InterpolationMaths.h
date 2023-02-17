#pragma once

//this class is static
struct InterpolationMaths {
    InterpolationMaths() = delete;
    ~InterpolationMaths() = delete;
    static float smoothStep(float edge0, float edge1, float x);
    static float bilinearInterpolation(float bottomLeft, float topLeft, float bottomRight,
                                       float topRight, float xMin, float xMax, float zMin,
                                       float zMax, float x, float z);

    static float smoothInterpolation(float bottomLeft, float topLeft, float bottomRight,
                                     float topRight, float xMin, float xMax, float zMin,
                                     float zMax, float x, float z);
};