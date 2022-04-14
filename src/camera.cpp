#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera()
{
    calculate();
}

void Camera::set_position(const glm::vec3& pos)
{
    position = pos;
}

void Camera::translate(const glm::vec3& delta)
{
    position += delta;
}

void Camera::turn_x(float delta)
{
    yaw += delta;
    if (yaw > 360)
    {
        yaw -= 360;
    }
    else if (yaw < 0)
    {
        yaw += 360;
    }

    calculate();
}

void Camera::turn_y(float delta)
{
    pitch += delta;
    if (pitch > 360)
    {
        pitch -= 360;
    }
    else if (pitch < 0)
    {
        pitch += 360;
    }

    calculate();
}

glm::mat4 Camera::get_view()
{
    printf("dir %f %f %f\n", front_direction.x, front_direction.y, front_direction.z);
    return glm::lookAt(position, position + front_direction, up_direction);
}

glm::vec3 Camera::get_front_direction()
{
    return front_direction;
}

glm::vec3 Camera::get_right_direction()
{
    return glm::normalize(glm::cross(front_direction, up_direction));
}

void Camera::calculate()
{
    front_direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front_direction.y = sin(glm::radians(pitch));
    front_direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}