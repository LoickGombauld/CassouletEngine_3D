#include <CassouletEngineLibrarie/OpenGL/FreeCamera.h>
#include <CassouletEngineLibrarie/OpenGL/Mesh.h>
#include <CassouletEngineLibrarie/System/Imguicpp.h>


void FreeCamera::SetPosition(const glm::vec3& position) {
    this->m_position = position;
}

void FreeCamera::SetRotation(const glm::vec3& rotation) {
    this->m_rotation = rotation;
}


void FreeCamera::SetTarget(const glm::vec3& target) {
    this->m_target = target;
}

void FreeCamera::SetUp(const glm::vec3& up) {
    this->m_up = up;
}


void FreeCamera::RotateAroundTarget(float angle, const glm::vec3& axis) {
    glm::vec3 direction = m_position - m_target;
    direction = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * glm::vec4(direction, 0.0f);
   m_position = m_target + direction;
}

void FreeCamera::InitCamera(int width, int height){
    m_position = glm::vec3(0.0f, 0.0f, 3.0f);
    m_target = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    m_rotation = glm::vec3(0,-90,0);
    SetProjectionSize(width ,height);
}

void FreeCamera::SetProjectionSize(int width, int height) {
    SetProjection(45.0f, width / static_cast<float>(height), 0.1f, 100.0f);
}


void FreeCamera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane) {
   m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

glm::vec3 FreeCamera::GetPosition()
{
    return m_position;
}

glm::vec3 FreeCamera::GetRotation() const
{
    return m_rotation;
}

glm::vec3 FreeCamera::GetTarget()
{
    return m_target;
}

glm::vec3 FreeCamera::GetUp()
{
    return m_up;
}


void FreeCamera::Rotate(float angle, const glm::vec3& axis) {
    if (axis == glm::vec3(1.0f, 0.0f, 0.0f)) {
        m_rotation.x += angle;
    }
    else if (axis == glm::vec3(0.0f, 1.0f, 0.0f)) {
        m_rotation.y += angle;
    }
    else if (axis == glm::vec3(0.0f, 0.0f, 1.0f)) {
        m_rotation.z += angle;
    }
}

void FreeCamera::MoveForward(float delta) {
    glm::vec3 direction = glm::normalize(m_target - m_position);
   m_position += direction * delta * m_speed;
   m_target += direction * delta * m_speed;
}

void FreeCamera::MoveBackward(float delta) {
    glm::vec3 direction = glm::normalize(m_target - m_position);
    m_position -= direction * delta * m_speed;
    m_target -= direction * delta * m_speed;
}

void FreeCamera::MoveLeft(float delta) {
    glm::vec3 direction = glm::normalize(m_target - m_position);
    glm::vec3 left = glm::normalize(glm::cross(m_up, direction));
    m_position -= left * delta * m_speed;
    m_target -= left * delta * m_speed;
}

void FreeCamera::MoveRight(float delta) {
    glm::vec3 direction = glm::normalize(m_target - m_position);
    glm::vec3 right = glm::normalize(glm::cross(direction, m_up));
    m_position += right * delta * m_speed;
    m_target += right * delta * m_speed;
}

void FreeCamera::SetShaderUniforms(GLuint shaderProgram) {

    IMGUICPP::DrawVector3Windowf(m_position, "f_Cam Postion");
    IMGUICPP::DrawVector3Windowf(m_rotation, "f_Cam Rotation");
    ImGui::Begin("f_Cam Speed");
    ImGui::DragFloat("speed", &m_speed);
    ImGui::End();
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
    direction.y = sin(glm::radians(m_rotation.x));
    direction.z = sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
    direction = glm::normalize(direction);
    m_target = m_position + direction;
    glm::vec3 right = glm::normalize(glm::cross(direction, m_up));
    m_up = glm::normalize(glm::cross(right, direction));
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);	
    glm::mat4 view = GetViewMatrix();
    glm::mat4 projection = GetProjectionMatrix();

   glUseProgram(shaderProgram);

   glUseProgram(shaderProgram);
   glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
   glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}


glm::mat4 FreeCamera::GetViewMatrix() const {
   return glm::lookAt(m_position, m_target, m_up);
}

glm::mat4 FreeCamera::GetProjectionMatrix() const {
    return m_projection;
}