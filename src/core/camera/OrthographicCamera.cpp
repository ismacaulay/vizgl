#include "OrthographicCamera.h"
#include <cmath>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/quaternion.hpp>


namespace
{
const glm::vec3 INITIAL_TARGET = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 INITAL_POSITION = glm::vec3(0.0f, 0.0f, 3.0f);
const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
}

OrthographicCamera::OrthographicCamera()
    : width_(800.0)
    , height_(600.0)
    , left_(-1.0)
    , right_(1.0)
    , bottom_(-1.0)
    , top_(1.0)
    , near_(0.1)
    , far_(2000.0)
    , zoom_(1.0)

    , view_(glm::mat4(1.0f))
    , proj_(glm::ortho(left_, right_, bottom_, top_, near_, far_))

    , target_(INITIAL_TARGET)
    , position_(INITAL_POSITION)

    , sphericalDelta_()
    , panDelta_()
    , scale_(1.0)
{
    updateMatrix();
    update();
}

void OrthographicCamera::updateAspectRatio(int width, int height)
{
    width_ = width;
    height_ = height;
    updateMatrix();
}

void OrthographicCamera::rotate(const glm::vec2& delta, double speed)
{
    auto calculateRotationAngle = [](double delta, double speed, double size) {
        return ((2 * M_PI * delta) / size) * speed;
    };
    double leftRotation = calculateRotationAngle(delta.x, speed, width_);
    sphericalDelta_.y -= leftRotation;

    double upRotation = calculateRotationAngle(delta.y, speed, height_);
    sphericalDelta_.z -= upRotation;
}

void OrthographicCamera::zoom(double delta, double scale)
{
    if (delta > 0) {
        zoom_ = std::max(0.0, std::min(std::numeric_limits<double>::max(), zoom_ * scale));
    } else if (delta < 0) {
        zoom_ = std::max(0.0, std::min(std::numeric_limits<double>::max(), zoom_ / scale));
    }
    updateMatrix();
}

void OrthographicCamera::pan(const glm::vec2& delta)
{
    double panLeftDistance = delta.x * ( right_ - left_ ) / zoom_ / width_;
    glm::vec3 panX = glm::vec3(view_[0][0], view_[1][0], view_[2][0]);
    panDelta_ += panX * static_cast<float>(-panLeftDistance);

    double panUpDistance = delta.y * ( top_ - bottom_ ) / zoom_ / height_;
    glm::vec3 panY = glm::vec3(view_[0][1], view_[1][1], view_[2][1]);
    panDelta_ += panY * static_cast<float>(panUpDistance);
}

void OrthographicCamera::update()
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

const glm::mat4& OrthographicCamera::view() const
{
    return view_;
}

const glm::mat4& OrthographicCamera::projection() const
{
    return proj_;
}

void OrthographicCamera::updateMatrix() {
    double dx = ( right_ - left_ ) / ( 2 * zoom_ );
    double dy = ( top_ - bottom_ ) / ( 2 * zoom_ );
    double cx = ( right_ + left_ ) / 2;
    double cy = ( top_ + bottom_ ) / 2;

    double left = cx - dx;
    double right = cx + dx;
    double top = cy + dy;
    double bottom = cy - dy;
    double ratio = width_/height_;

    proj_ = glm::ortho(ratio * left, ratio * right, bottom, top, near_, far_);
}
