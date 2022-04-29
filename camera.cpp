#include "camera.h"

//Camara::Camara()
//{

//}

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float yaw, float pitch) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Front = front;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    this->ViewMatrix = glm::lookAt(Position, Position + Front, Up);
    this->updateCameraVectors();
    return this->ViewMatrix;
}

glm::mat4 Camera::GetSkyViewMatrix()
{
    this->SkyViewMatrix = glm::lookAt(Position, Position + Front, Up);
    this->updateCameraVectors();
    return this->SkyViewMatrix;
}

void Camera::move(const float &dt, const int direction)
{
    //Update position vector
    switch (direction)
    {
    case 0:
        this->Position += this->Front * this->MovementSpeed * dt;
        break;
    case BACKWARD:
        this->Position -= this->Front * this->MovementSpeed * dt;
        break;
    case LEFT:
        this->Position -= this->Right * this->MovementSpeed * dt;
        break;
    case RIGHT:
        this->Position += this->Right * this->MovementSpeed * dt;
        break;
    default:
        break;
    }
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(const double& dt, double xoffset, double yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    this->Pitch += static_cast<GLfloat>(yoffset) * this->MouseSensitivity * dt;
    this->Yaw += static_cast<GLfloat>(xoffset) * this->MouseSensitivity * dt;


    //Yaw   += xoffset;
    //Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        else if (Pitch < -89.0f)
            Pitch = -89.0f;
        if (this->Yaw > 360.f || this->Yaw < -360.f)
            this->Yaw = 0.f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

const glm::vec3 Camera::getPosition() const
{
    return this->Position;
}

void Camera::updateMouseInput(const float &dt, const double &offsetX, const double &offsetY)
{

}

void Camera::updateInput(const float &dt, const int direction, const double &offsetX, const double &offsetY)
{
    this->move(dt, direction);
    this->updateMouseInput(dt, offsetX, offsetY);
}

void Camera::updateCameraVectors()
{
    this->Front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front.y = sin(glm::radians(this->Pitch));
    this->Front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));

    this->Front = glm::normalize(this->Front);
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
    this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}

