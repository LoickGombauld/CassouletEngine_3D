#pragma once
#include<CassouletEngineLibrarie/System/Libs.h>

class CASSOULET_DLL FreeCamera
{
public:
    enum Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    FreeCamera(Vec3 position, Vec3 up, float yaw, float pitch);

    Mat4 GetViewMatrix() const;
    void ProcessKeyboard(Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    void SetPosition(const Vec3& position);
    void SetYaw(float yaw);
    void SetPitch(float pitch);

    const Vec3& GetPosition() const { return m_position; }
    float GetYaw() const { return m_yaw; }
    float GetPitch() const { return m_pitch; }

private:
    void updateCameraVectors();

    Vec3 m_position;
    Vec3 m_front;
    Vec3 m_up;
    Vec3 m_right;
    Vec3 m_worldUp;

    float m_yaw;
    float m_pitch;

    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;
};