#pragma once
#include<CassouletEngineLibrarie/System/Libs.h>

class Mesh;

class CASSOULET_DLL FreeCamera
{
public:

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetTarget(const glm::vec3& target);
    void SetUp(const glm::vec3& up);
    void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
    glm::vec3 GetPosition();
    glm::vec3 GetTarget();
    glm::vec3 GetUp();
    void SetShaderUniforms(GLuint shaderProgram);
    void InitCamera(int width,int height);
    void Rotate(float angle, const glm::vec3& axis);
    void RotateAroundTarget(float angle, const glm::vec3& axis);

    glm::vec3 GetRotation() const;

    void MoveForward(float distance);
    void MoveBackward(float distance);
    void MoveLeft(float distance);
    void MoveRight(float distance);

    void SetProjectionSize(int width, int height);
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    glm::vec3 m_position;
    float m_speed = 10;
private:

    void UpdateCameraVectors();

    sf::Color backgroundColor = sf::Color::Cyan;
    glm::vec3 m_target;
    glm::vec3 m_up;
    glm::vec3 m_rotation;
    glm::mat4 m_projection;
};