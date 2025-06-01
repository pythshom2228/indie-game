#pragma once

#include "raylib.h"

class Camera {

    void update();

    Vector2 getOffset() const;
    Vector2 getTarget() const;
    float getRotation() const;
    float getZoom() const;

    // Сеттеры
    void setOffset(const Vector2& newOffset);
    void setTarget(const Vector2& newTarget);
    void setRotation(float newRotation);
    void setZoom(float newZoom);

    void setOffsetX(float x);
    void setOffsetY(float y);
    void setTargetX(float x);
    void setTargetY(float y);

    Camera2D _camera;    
};
