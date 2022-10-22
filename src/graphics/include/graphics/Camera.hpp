#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace fenton
{

namespace graphics
{

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  10.0f;
const float SENSITIVITY =  0.001f;
const float ZOOM        =  45.0f;

class Camera
{
    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
        float Yaw;
        float Pitch;
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        Camera
        (
            glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f),
            float yaw = YAW,
            float pitch = PITCH
        )
        :   Front(glm::vec3(0.0f,0.0f,-1.0f)),
            MovementSpeed(SPEED),
            MouseSensitivity(SENSITIVITY),
            Zoom(ZOOM)
        {
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
            updateCameraVectors();
        }

        glm::mat4 getViewMatrix() const
        {
            return glm::lookAt(Position,Position + Front,Up);
        }

        void ProcessKeyboard(CameraMovement direction,float deltaTime)
        {
            float velocity = MovementSpeed * deltaTime * 100;
            switch(direction)
            {
                case FORWARD:
                    Position += Front * velocity;
                    break;
                case BACKWARD:
                    Position -= Front * velocity;
                    break;
                case LEFT:
                    Position -= Right * velocity;
                    break;
                case RIGHT:
                    Position += Right * velocity;
                    break;
            }
        }

        void ProcessMouseMovement(float xOffset,float yOffset,bool constrainPitch = true)
        {
            Yaw += xOffset * MouseSensitivity;
            Pitch += yOffset * MouseSensitivity;

            if(constrainPitch)
            {
                if(Pitch > 89.0f) Pitch = 89.0f;
                if(Pitch < -89.0f) Pitch = -89.0f;
            }

            updateCameraVectors();
        }

        void ProcessMouseScroll(float yOffset)
        {
            Zoom += yOffset * SENSITIVITY;
            if(Zoom < 1.0f) Zoom = 1.0f;
            if(Zoom > 60.0f) Zoom = 60.0f;
        }
    private:
        void updateCameraVectors()
        {
            glm::vec3 front;
            front.x = std::cos(glm::radians(Yaw)) * std::cos(glm::radians(Pitch));
            front.y = std::sin(glm::radians(Pitch));
            front.z = std::sin(glm::radians(Yaw)) * std::cos(glm::radians(Pitch));
            Front = glm::normalize(front);
            Right = glm::normalize(glm::cross(Front,WorldUp));
            Up = glm::normalize(glm::cross(Right,Front));
        }
};

} // namespace graphics

} // namespace fenton
