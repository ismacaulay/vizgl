#pragma once
#include <glm/glm.hpp>

class Block
{
public:
    explicit Block();
    ~Block() = default;

    bool isActive() const;
    void setActive(bool active);

    glm::vec3 getVertex(unsigned int vertex, const glm::vec3& offset) const;

private:
    bool isActive_;
};
