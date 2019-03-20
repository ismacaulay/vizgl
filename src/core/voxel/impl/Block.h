#pragma once
#include <glm/glm.hpp>

class Block
{
public:
    explicit Block();
    ~Block() = default;

    bool isActive() const;
    void setActive(bool active);

    const glm::vec3& size() const;
    void setSize(const glm::vec3& size);

    glm::vec3 getVertex(unsigned int vertex, const glm::vec3& offset) const;

private:
    bool isActive_;
    glm::vec3 size_;
};
