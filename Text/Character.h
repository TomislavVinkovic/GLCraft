#pragma once

#include <iostream>

class Character {
public:
    Character(int id, double xTextureCoord, double yTextureCoord, double xTexSize, double yTexSize,
              double xOffset, double yOffset, double xAdvance)
            : id(id), xTextureCoord(xTextureCoord), yTextureCoord(yTextureCoord), xOffset(xOffset),
              yOffset(yOffset), sizeX(xTextureCoord + xOffset), sizeY(yTextureCoord + yOffset), xMaxTextureCoord(xTexSize + xTextureCoord),
              yMaxTextureCoord(yTexSize + yTextureCoord), xAdvance(xAdvance) {}

    int getId() const {
        return id;
    }

    double getxTextureCoord() const {
        return xTextureCoord;
    }

    double getyTextureCoord() const {
        return yTextureCoord;
    }

    double getXMaxTextureCoord() const {
        return xMaxTextureCoord;
    }

    double getYMaxTextureCoord() const {
        return yMaxTextureCoord;
    }

    double getxOffset() const {
        return xOffset;
    }

    double getyOffset() const {
        return yOffset;
    }

    double getSizeX() const {
        return sizeX;
    }

    double getSizeY() const {
        return sizeY;
    }

    double getxAdvance() const {
        return xAdvance;
    }

private:
    int id;
    double xTextureCoord;
    double yTextureCoord;
    double xMaxTextureCoord;
    double yMaxTextureCoord;
    double xOffset;
    double yOffset;
    double sizeX;
    double sizeY;
    double xAdvance;
};

