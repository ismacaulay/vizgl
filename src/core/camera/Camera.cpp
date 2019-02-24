#include "Camera.h"
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/quaternion.hpp>

namespace
{
const glm::vec3 INITIAL_TARGET = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 INITAL_POSITION = glm::vec3(20.0f, 20.0f, 20.0f);
const glm::vec3 UP = glm::vec3(0.0f, 1.0f,  0.0f);
}

Camera::Camera(double fov, double width, double height, double near, double far)
    : fov_(fov)
    , width_(width)
    , height_(height)
    , near_(near)
    , far_(far)

    , view_(glm::mat4(1.0f))
    , proj_(glm::perspective(glm::radians(fov), width/height, near, far))

    , target_(INITIAL_TARGET)
    , position_(INITAL_POSITION)

    , sphericalDelta_()
    , panDelta_()
    , scale_(1.0)
{
    update();
}

void Camera::updateAspectRatio(int width, int height)
{
    width_ = width;
    height_ = height;
    double aspectRatio = static_cast<double>(width) / static_cast<double>(height);
    proj_ = glm::perspective(glm::radians(fov_), aspectRatio, near_, far_);
}

void Camera::rotate(const glm::vec2& delta, double speed)
{
    auto calculateRotationAngle = [](double delta, double speed, double size) {
        return ((2 * M_PI * delta) / size) * speed;
    };
    double leftRotation = calculateRotationAngle(delta.x, speed, width_);
    sphericalDelta_.y -= leftRotation;

    double upRotation = calculateRotationAngle(delta.y, speed, height_);
    sphericalDelta_.z -= upRotation;
}

void Camera::zoom(double delta, double scale)
{
    if (delta > 0) {
        scale_ /= scale;
    } else if (delta < 0) {
        scale_ *= scale;
    }
}

void Camera::pan(const glm::vec2& delta)
{
    auto calculatePanDistance = [](double delta, double distance, double fov, double size) {
        double targetDistance = distance * tan(((fov / 2) * M_PI) / 180.0);
        return (2 * delta * targetDistance) / size;
    };

    glm::vec3 offset = position_ - target_;

    double panLeftDistance = calculatePanDistance(delta.x, glm::length(offset), fov_, height_);
    glm::vec3 panX = glm::vec3(view_[0][0], view_[1][0], view_[2][0]);
    panDelta_ += panX * static_cast<float>(-panLeftDistance);

    double panUpDistance = calculatePanDistance(delta.y, glm::length(offset), fov_, height_);
    glm::vec3 panY = glm::vec3(view_[0][1], view_[1][1], view_[2][1]);
    panDelta_ += panY * static_cast<float>(panUpDistance);
}

void Camera::update()
{
    auto applyQuaternion = [](const glm::vec3& v, const glm::quat& q) {
        return (q * v) * glm::inverse(q);
    };
    glm::quat quaternion = glm::angleAxis(0.0f, glm::vec3(0.0, 1.0, 0.0));
    glm::vec3 updateOffset = position_ - target_;
    updateOffset = applyQuaternion(updateOffset, quaternion);

    auto sphericalFromVector = [](const glm::vec3& v) {
        double r = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        double t = 0.0;
        double p = 0.0;
        if (r != 0.0) {
            t = atan2(v.x, v.z);
            p = acos(std::clamp(v.y/r, -1.0, 1.0));
        }
        return glm::vec3(r, t, p);
    };
    glm::vec3 updateSpherical = sphericalFromVector(updateOffset);
    updateSpherical.x = std::max(0.0, updateSpherical.x * scale_);
    updateSpherical.y += sphericalDelta_.y;
    updateSpherical.z = std::max(0.000001f, std::min(static_cast<float>(M_PI) - 0.000001f, updateSpherical.z + sphericalDelta_.z));

    target_ += panDelta_;

    auto vectorFromSpherical = [](const glm::vec3& s) {
        double sinPhiRadius = sin(s.z) * s.x;
		double x = sinPhiRadius * sin(s.y);
		double y = cos(s.z) * s.x;
		double z = sinPhiRadius * cos(s.y);
		return glm::vec3(x, y, z);
    };
    updateOffset = vectorFromSpherical(updateSpherical);
    updateOffset = applyQuaternion(updateOffset, glm::inverse(quaternion));

    position_ = target_ + updateOffset;
    view_ = glm::lookAt(position_, target_, UP);

    sphericalDelta_ = glm::vec3();
    scale_ = 1.0;
    panDelta_ = glm::vec3();
}

const glm::mat4& Camera::view()
{
    return view_;
}

const glm::mat4& Camera::projection()
{
    return proj_;
}
