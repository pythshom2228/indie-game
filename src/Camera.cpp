
#include "camera.hpp"

void Camera::update() {

    if (IsKeyDown(KEY_UP)) {
            _camera.zoom += 0.01f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        if (_camera.zoom > 0.7f) {
            _camera.zoom -= 0.01f;
        }
    }
}

Vector2 Camera::getOffset() const { return _camera.offset; }
Vector2 Camera::getTarget() const { return _camera.target; }
float Camera::getRotation() const { return _camera.rotation; }
float Camera::getZoom()     const { return _camera.zoom; }

// Сеттеры
void Camera::setOffset(const Vector2& newOffset) { _camera.offset = newOffset; }
void Camera::setTarget(const Vector2& newTarget) { _camera.target = newTarget; }
void Camera::setRotation(float newRotation) { _camera.rotation = newRotation; }
void Camera::setZoom(float newZoom) { _camera.zoom = newZoom; }

void Camera::setOffsetX(float x) { _camera.offset.x = x; }
void Camera::setOffsetY(float y) { _camera.offset.y = y; }
void Camera::setTargetX(float x) { _camera.target.x = x; }
void Camera::setTargetY(float y) { _camera.target.y = y; }


