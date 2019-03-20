#include "Block.h"

#include <stdio.h>

Block::Block()
    : isActive_(false)
    , value_(0.0f)
    , size_(1.0f, 1.0f, 1.0f)
{
}

bool Block::isActive() const
{
    return isActive_;
}

void Block::setActive(bool active)
{
    isActive_ = active;
}

float Block::value() const
{
    return value_;
}

void Block::setValue(float value)
{
    value_ = value;
}

const glm::vec3& Block::size() const
{
    return size_;
}

void Block::setSize(const glm::vec3& size)
{
    size_ = size;
}


glm::vec3 Block::getVertex(unsigned int vertex, const glm::vec3& offset) const
{
    glm::vec3 point;
    switch(vertex)
    {
        case 0:
        {
            point = glm::vec3(0, 0, 0);
            break;
        }
        case 1:
        {
            point = glm::vec3(size_.x, 0, 0);
            break;
        }
        case 2:
        {
            point = glm::vec3(size_.x, size_.y, 0);
            break;
        }
        case 3:
        {
            point = glm::vec3(0, size_.y, 0);
            break;
        }
        case 4:
        {
            point = glm::vec3(0, 0, size_.z);
            break;
        }
        case 5:
        {
            point = glm::vec3(size_.x, 0, size_.z);
            break;
        }
        case 6:
        {
            point = glm::vec3(size_.x, size_.y, size_.z);
            break;
        }
        case 7:
        {
            point = glm::vec3(0, size_.y, size_.z);
            break;
        }
        default:
        {
            printf("[Block] Unknown vertex number: %d\n", vertex);
        }
    }

    return offset + point;
}
