#include <CassouletEngineLibrarie/OpenGL/FreeCamera.h>
#include <CassouletEngineLibrarie/OpenGL/Mesh.h>


void FreeCamera::SetPosition(const glm::vec3& position) {
    this->m_position = position;
}


void FreeCamera::SetTarget(const glm::vec3& target) {
    this->m_target = target;
}

void FreeCamera::SetUp(const glm::vec3& up) {
    this->m_up = up;
}

void FreeCamera::InitCamera(int width, int height){
    m_position = glm::vec3(0.0f, 0.0f, 3.0f);
    m_target = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
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
    return m_target;
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
    glm::vec3 direction = m_target - m_position;
    direction = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * glm::vec4(direction, 0.0f);
    m_target = m_position + direction;
}

void FreeCamera::RotateAroundTarget(float angle, const glm::vec3& axis) {
    glm::vec3 direction = m_position - m_target;
    direction = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * glm::vec4(direction, 0.0f);
    m_position = m_target + direction;
}

void FreeCamera::MoveForward(float distance) {
    glm::vec3 direction = glm::normalize(m_target - m_position);
   m_position += direction * distance;
   m_target += direction * distance;
}

void FreeCamera::MoveBackward(float distance) {
    glm::vec3 direction = glm::normalize(m_target - m_position);
    m_position -= direction * distance;
    m_target -= direction * distance;
}

void FreeCamera::MoveLeft(float distance) {
    glm::vec3 direction = glm::normalize(m_target - m_position);
    glm::vec3 left = glm::normalize(glm::cross(m_up, direction));
    m_position -= left * distance;
    m_target -= left * distance;
}

void FreeCamera::MoveRight(float distance) {
    glm::vec3 direction = glm::normalize(m_target - m_position);
    glm::vec3 right = glm::normalize(glm::cross(direction, m_up));
    m_position += right * distance;
    m_target += right * distance;
}

void FreeCamera::Draw(Mesh& mesh,GLuint shaderProgram) {
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);	
    glm::mat4 view = GetViewMatrix();
    glm::mat4 projection = GetProjectionMatrix();

   glUseProgram(shaderProgram);

    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    mesh.Draw();
}

glm::mat4 FreeCamera::GetViewMatrix() const {
   return glm::lookAt(m_position, m_target, m_up);
}

glm::mat4 FreeCamera::GetProjectionMatrix() const {
    return m_projection;
}