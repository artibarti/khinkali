#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace khinkali
{
    class GLCamera 
    {
        public:
            GLCamera();
            GLCamera(int width, int height);
            glm::mat4 getModelViewProjectionMatrix();
            void initMatrices();

            glm::vec3 getCamPosition();
            glm::vec3 getForward();
            glm::vec3 getRight();
            float getCamSpeed();
            float getYaw();
            float getPitch();

            glm::vec2 lookAtPosition;

            GLdouble getMouseX();
            GLdouble getMouseY();

            void setMouseX(GLdouble x);
            void setMouseY(GLdouble y);
            void setYaw(float yaw_);
            void setPitch(float pitch_);
            void setCamPosition(glm::vec3 pos);

            void moveForward();
            void moveBack();
            void moveRight();
            void moveLeft();

            void turn(GLdouble dx, GLdouble dy);

        private:
            glm::vec3 forward;
            glm::vec3 right;
            glm::vec3 cam_pos;
            glm::mat4 rotation;

            float yaw, pitch;
            float speed;

            glm::vec3 lookAt;

            GLdouble mouseX = -1;
            GLdouble mouseY = -1;

            glm::mat4 modelMatrix;
            glm::mat4 viewMatrix;
            glm::mat4 projectionMatrix;
            glm::mat4 viewProjectionMatrix;
            glm::mat4 modelViewProjectionMatrix;

            int scene_width, scene_height;
    };
    
    GLCamera::GLCamera() {}

    GLCamera::GLCamera(int width, int height)
    {
        cam_pos = glm::vec3(0.0f, 0.0f, 2.0f);

        yaw = 0.0;
        pitch = 0.0;
        speed = 0.01f;

        scene_width = width;
        scene_height = height;

        initMatrices();
    }

    void GLCamera::initMatrices()
    {
        glm::mat4 rotation = 
            glm::rotate(yaw, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(pitch, glm::vec3(1.0f, 0.0f, 0.0f));

        glm::vec4 forward_ = glm::vec4(0.0, 0.0, -1.0, 1.0);
        glm::vec4 right_ = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        forward = glm::vec3(rotation * forward_);
	    right = glm::vec3(rotation * right_);

    	modelMatrix = glm::rotate(glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        viewMatrix = glm::lookAt(cam_pos, cam_pos + forward, glm::vec3(0.0f, 1.0f, 0.0f));
        projectionMatrix = glm::perspective(glm::radians(65.0f), GLfloat(scene_width)/GLfloat(scene_height), 0.001f, 1000.0f);
        modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
    }

    glm::mat4 GLCamera::getModelViewProjectionMatrix()
    {
        return modelViewProjectionMatrix;
    }

    glm::vec3 GLCamera::getCamPosition()
    {
        return cam_pos;
    }
    
    glm::vec3 GLCamera::getForward()
    {
        return forward;
    }
    
    glm::vec3 GLCamera::getRight()
    {
        return right;
    }

    float GLCamera::getCamSpeed()
    {
        return speed;
    }

    float GLCamera::getYaw()
    {
        return yaw;
    }
    
    float GLCamera::getPitch()
    {
        return pitch;
    }

    GLdouble GLCamera::getMouseX()
    {
        return mouseX;
    }

    GLdouble GLCamera::getMouseY()
    {
        return mouseY;
    }

    void GLCamera::setMouseX(GLdouble x)
    {
        mouseX = x;
    }

    void GLCamera::setMouseY(GLdouble y)
    {
        mouseY = y;
    }

    void GLCamera::setYaw(float yaw_)
    {
        yaw = yaw_;
    }

    void GLCamera::setPitch(float pitch_)
    {
        pitch = pitch_;
    }
    
    void GLCamera::setCamPosition(glm::vec3 pos)
    {
        cam_pos = pos;
    }

    void GLCamera::moveForward()
    {
        cam_pos += forward * speed;
        initMatrices();
    }

    void GLCamera::moveBack()
    {
        cam_pos -= forward * speed;
        initMatrices();
    }

    void GLCamera::moveRight()
    {
        cam_pos += right * speed;
        initMatrices();
    }

    void GLCamera::moveLeft()
    {
        cam_pos -= right * speed;
        initMatrices();
    }

    void GLCamera::turn(GLdouble dx, GLdouble dy)
    {
        pitch = glm::clamp<GLfloat>(pitch - dy * speed, glm::radians(-89.0f), glm::radians(179.0f));
        yaw = yaw - dx * speed;
        initMatrices();
    }

}

#endif