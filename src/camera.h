#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
    Camera();

    void set_position(const glm::vec3& pos);
    void translate(const glm::vec3& delta);
    void turn_x(float delta);
    void turn_y(float delta);

    glm::mat4 get_view();
    glm::vec3 get_front_direction();
    glm::vec3 get_right_direction();

private:
    void calculate();

    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 front_direction{0.0f, 0.0f, -1.0f};
    glm::vec3 up_direction{0.0f, 1.0f, 0.0f};
    float pitch{0.0f};
    float yaw{90.0f};

};