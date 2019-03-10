#include "Block.h"

#include <stdio.h>

Block::Block()
    : isActive_(false)
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

glm::vec3 Block::getVertex(unsigned int vertex, const glm::vec3& offset) const
{
    switch(vertex)
    {
        case 0:
        {
            return glm::vec3(0, 0, 0) + offset;
            break;
        }
        case 1:
        {
            return glm::vec3(1, 0, 0) + offset;
            break;
        }
        case 2:
        {
            return glm::vec3(1, 1, 0) + offset;
            break;
        }
        case 3:
        {
            return glm::vec3(0, 1, 0) + offset;
            break;
        }
        case 4:
        {
            return glm::vec3(0, 0, 1) + offset;
            break;
        }
        case 5:
        {
            return glm::vec3(1, 0, 1) + offset;
            break;
        }
        case 6:
        {
            return glm::vec3(1, 1, 1) + offset;
            break;
        }
        case 7:
        {
            return glm::vec3(0, 1, 1) + offset;
            break;
        }
    }

    printf("[Block] Unknown vertex number: %d\n", vertex);
    return glm::vec3();
}
