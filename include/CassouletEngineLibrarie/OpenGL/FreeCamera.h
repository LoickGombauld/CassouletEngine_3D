#pragma once
#include<CassouletEngineLibrarie/System/Libs.h>

class CASSOULET_DLL FreeCamera
{
public:
    void SetTarget(const glm::vec3& target);
    void SetUp(const glm::vec3& up);
    void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
    glm::vec3 GetTarget();
    glm::vec3 GetUp();
    void SetShaderUniforms(GLuint shaderProgram);
    void InitCamera(int width,int height);
    void Rotate(float angle, const glm::vec3& axis);
    void RotateAroundTarget(float angle, const glm::vec3& axis);
    void UpdateRotation();
    void Clear();

    void MoveForward(float distance);
    void MoveBackward(float distance);
    void MoveLeft(float distance);
    void MoveRight(float distance);

    void SetProjectionSize(int width, int height);
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    glm::vec3 position;
    glm::vec3 rotation;
    float cameraSensitivity = 25;
    float speed = 100;
private:

    glm::vec3 target;
    glm::vec3 up;
    glm::mat4 projection;
    sf::Color backgroundColor = sf::Color::Cyan;
};