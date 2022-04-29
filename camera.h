#ifndef CAMARA_H
#define CAMARA_H

#include <vector>

#include "renderer.h"

#include "vendor/stb_image/stb_image.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  0.6f;
const float SENSITIVITY =  0.8f;
const float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    glm::mat4 ViewMatrix;
    glm::mat4 SkyViewMatrix;

    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // euler Angles
    float Yaw;
    float Pitch;
    GLfloat roll;

    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(glm::vec3 position/* = glm::vec3(0.0f, 0.0f, 3.0f)*/, glm::vec3 front/* = glm::vec3(0.0f, 0.0f, -1.0f)*/, glm::vec3 up/* = glm::vec3(0.0f, 1.0f, 0.0f)*/, float yaw = YAW, float pitch = PITCH);
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();
    glm::mat4 GetSkyViewMatrix();

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void move(const float& dt, const int direction);
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(const double &dt, double xoffset, double yoffset, GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

    const glm::vec3 getPosition() const;
    void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);
    void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();

    //void updateCameraVectors();
};
#endif // CAMARA_H
