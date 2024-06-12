#pragma once
#include <CassouletEngineLibrarie/OpenGL/Vector.h>

glm::mat4 glm_translate(const glm::vec3& translation) {
    // Crée une matrice d'identité
    glm::mat4 mat = glm::mat4(1.0f);

    // Applique la translation
    mat = glm::translate(mat, translation);

    return mat;
}

glm::mat4 glm_scale(const glm::vec3& scale) {
    // Crée une matrice d'identité
    glm::mat4 mat = glm::mat4(1.0f);

    // Applique le scaling
    mat = glm::scale(mat, scale);

    return mat;
}

glm::mat4 glm_rotate(const glm::vec3& axis, float angle) {
    // Crée une matrice d'identité
    glm::mat4 mat = glm::mat4(1.0f);

    // Applique la rotation
    mat = glm::rotate(mat, angle, axis);
    return mat;
}

glm::mat4 glm_mat4_mul(const glm::mat4& m1, const glm::mat4& m2) {
    return m1 * m2;
}