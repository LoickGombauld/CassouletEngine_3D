#include <CassouletEngineLibrarie/OpenGL/FreeCamera.h>
#include <CassouletEngineLibrarie/System/Imguicpp.h>



void FreeCamera::SetTarget(const glm::vec3& target) {
    this->target = target;
}

void FreeCamera::SetUp(const glm::vec3& up) {
    this->up = up;
}


void FreeCamera::RotateAroundTarget(float angle, const glm::vec3& axis) {
    glm::vec3 direction = position - target;
    direction = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * glm::vec4(direction, 0.0f);
   position = target + direction;
}

void FreeCamera::UpdateRotation()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    direction.y = sin(glm::radians(rotation.x));
    direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    direction = glm::normalize(direction);

    // Recalculer le vecteur 'right' et 'up' pour éviter les erreurs de rotation sur l'axe Z
    glm::vec3 right = glm::normalize(glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, direction));

    target = position + direction;
}

void FreeCamera::InitCamera(int width, int height){
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    target = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    rotation = glm::vec3(0,-90,0);
    SetProjectionSize(width ,height);
}

void FreeCamera::SetProjectionSize(int width, int height) {
    SetProjection(80.0f, width / static_cast<float>(height), 0.1f, 100.0f);
}


void FreeCamera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane) {
   projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

glm::vec3 FreeCamera::GetTarget()
{
    return target;
}

glm::vec3 FreeCamera::GetUp()
{
    return up;
}

void FreeCamera::Rotate(float angle, const glm::vec3& axis) {
    if (axis == glm::vec3(1.0f, 0.0f, 0.0f)) {
        rotation.x += angle;
    }
    else if (axis == glm::vec3(0.0f, 1.0f, 0.0f)) {
        rotation.y += angle;
    }
    else if (axis == glm::vec3(0.0f, 0.0f, 1.0f)) {
        rotation.z += angle;
    }
}

void FreeCamera::MoveForward(float delta) {
    glm::vec3 direction = glm::normalize(target - position);
   position += direction * delta * speed;
   target += direction * delta * speed;
}

void FreeCamera::MoveBackward(float delta) {
    glm::vec3 direction = glm::normalize(target - position);
    position -= direction * delta * speed;
    target -= direction * delta * speed;
}

void FreeCamera::MoveLeft(float delta) {
    glm::vec3 direction = glm::normalize(target - position);
    glm::vec3 left = glm::normalize(glm::cross(up, direction));
    position -= left * delta * speed;
    target -= left * delta * speed;
}

void FreeCamera::MoveRight(float delta) {
    glm::vec3 direction = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(direction, up));
    position += right * delta * speed;
    target += right * delta * speed;
}

void FreeCamera::SetShaderUniforms(GLuint shaderProgram) {

    UpdateRotation();
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);	
    glm::mat4 view = GetViewMatrix();
    glm::mat4 projection = GetProjectionMatrix();

   glUseProgram(shaderProgram);

   glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
   glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

   // Ajout de la gestion de la couleur de la caméra
   glm::vec4 cameraColor = glm::vec4(1.0, 1.0, 1.0, 1.0); // Couleur par défaut, vous pouvez la modifier selon vos besoins
   glUniform4fv(glGetUniformLocation(shaderProgram, "Color"), 1, glm::value_ptr(cameraColor));
}



glm::mat4 FreeCamera::GetViewMatrix() const {
   return glm::lookAt(position, target, up);
}

glm::mat4 FreeCamera::GetProjectionMatrix() const {
    return projection;
}