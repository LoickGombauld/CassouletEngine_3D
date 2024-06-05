#pragma once
#include <CassouletEngineLibrarie/System/Component.h>

class FreeCamera;

struct MeshVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class CASSOULET_DLL Mesh : public Component
{
public:
	// mesh data
	//true if we want to draw both sides of the mesh

	Mesh();

	Mesh::~Mesh();

	static Mesh* CreateCube();
	static Mesh* CreateQuad();
	static Mesh* CreateTriangle();
	static Mesh* CreateSphere(float radius = 1.0f, unsigned int sectorCount = 36, unsigned int stackCount = 18);

	void SetMesh(std::vector<MeshVertex>& vertices, std::vector<GLuint>& indices);
	void SetCam(FreeCamera* pcam);

	void Draw();
	void SetTexture(sf::Texture* ptexture, bool isTransparent);
	bool doubleSided;

	const std::string GetName() { return "Mesh"; };
	GLuint shaderID;
private:
	GLuint VAO, VBO, EBO;
	std::vector<MeshVertex> m_vertices;
	std::vector<GLuint> m_indices;
	sf::Texture* m_texture = nullptr;
	//is the texture transparent somewhere
	bool m_isTransparent;
	FreeCamera* m_cam;
	//true of the mesh has vertices
	bool hasVertices;
	bool first_loop = true;
};
