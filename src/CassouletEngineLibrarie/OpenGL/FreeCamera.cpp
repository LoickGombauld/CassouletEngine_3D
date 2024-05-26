#include <CassouletEngineLibrarie/OpenGL/FreeCamera.h>
#include <CassouletEngineLibrarie/OpenGL/Matrix.h>

FreeCamera::FreeCamera(Vec3 position, Vec3 up, float yaw, float pitch)
    : m_position(position), m_worldUp(up), m_yaw(yaw), m_pitch(pitch),
      m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM) {
    updateCameraVectors();
}

Mat4 FreeCamera::GetViewMatrix() const {
    return Mat4(calcLookAtMatrix(
       Vec3(m_position.x, m_position.y, m_position.z),
       Vec3(m_position.x + m_front.x, m_position.y + m_front.y, m_position.z + m_front.z), Vec3(m_up.x, m_up.y, m_up.z)));
}

void FreeCamera::ProcessKeyboard(Movement direction, float deltaTime) {
    float velocity = m_movementSpeed * deltaTime;
    if (direction == FORWARD)
        m_position += m_front * velocity;
    if (direction == BACKWARD)
        m_position -= m_front * velocity;
    if (direction == LEFT)
        m_position -= m_right * velocity;
    if (direction == RIGHT)
        m_position += m_right * velocity;
    if (direction == UP)
        m_position += m_up * velocity;
    if (direction == DOWN)
        m_position -= m_up * velocity;
}

void FreeCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch) {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    updateCameraVectors();
}

void FreeCamera::ProcessMouseScroll(float yoffset) {
    if (m_zoom >= 1.0f && m_zoom <= 45.0f)
        m_zoom -= yoffset;
    if (m_zoom <= 1.0f)
        m_zoom = 1.0f;
    if (m_zoom >= 45.0f)
        m_zoom = 45.0f;
}

void FreeCamera::SetPosition(const Vec3& position) {
    m_position = position;
    updateCameraVectors();
}

void FreeCamera::SetYaw(float yaw) {
    m_yaw = yaw;
    updateCameraVectors();
}

void FreeCamera::SetPitch(float pitch) {
    m_pitch = pitch;
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;
    updateCameraVectors();
}

void FreeCamera::updateCameraVectors() {
    Vec3 front;
    front.x = cos(Deg2Rad(m_yaw)) * cos(Deg2Rad(m_pitch));
    front.y = sin(Deg2Rad(m_pitch));
    front.z = sin(Deg2Rad(m_yaw)) * cos(Deg2Rad(m_pitch));
    m_front = Vec3_normalize(front);

    m_right = Vec3_normalize(Vec3_cross(m_front, m_worldUp));
    m_up = Vec3_normalize(Vec3_cross(m_right, m_front));
}