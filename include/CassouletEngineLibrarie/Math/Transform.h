#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>

//responsible for keeping track of a game objects position, scale and rotation in the game world
class CASSOULET_DLL Transform
{
public:
    Transform() : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f),modelMatrix(glm::mat4(1.0f)) {};

    glm::vec3 position;
    glm::vec3 rotation; // en degrés
    glm::vec3 scale;
    glm::mat4 modelMatrix;

    glm::mat4 GetModelMatrix() const {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, scale);
        return model;
    }

    void SetTransform(const glm::mat4& matrix) {
        modelMatrix = matrix;
        DecomposeModelMatrix();
    }

    void SetTransform(const glm::vec3& newPosition, const glm::vec3& newRotation, const glm::vec3& newScale) 
    {
        position = newPosition;
        rotation = newRotation;
        scale = newScale;
        UpdateModelMatrix();
    }

private:
    void UpdateModelMatrix() {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    }

    void DecomposeModelMatrix() {
        // Decompose the model matrix to position, rotation, and scale
        // This requires extracting the components from the model matrix
        // Assuming column-major order as used by glm

        position = glm::vec3(modelMatrix[3]);

        glm::vec3 scaleVec;
        scaleVec.x = glm::length(glm::vec3(modelMatrix[0]));
        scaleVec.y = glm::length(glm::vec3(modelMatrix[1]));
        scaleVec.z = glm::length(glm::vec3(modelMatrix[2]));
        scale = scaleVec;

        glm::mat4 rotationMatrix = modelMatrix;
        rotationMatrix[3] = glm::vec4(0, 0, 0, 1);
        rotationMatrix[0] /= scaleVec.x;
        rotationMatrix[1] /= scaleVec.y;
        rotationMatrix[2] /= scaleVec.z;

        rotation.x = glm::degrees(atan2(rotationMatrix[1][2], rotationMatrix[2][2]));
        rotation.y = glm::degrees(atan2(-rotationMatrix[0][2], sqrt(pow(rotationMatrix[1][2], 2) + pow(rotationMatrix[2][2], 2))));
        rotation.z = glm::degrees(atan2(rotationMatrix[0][1], rotationMatrix[0][0]));
    }
};