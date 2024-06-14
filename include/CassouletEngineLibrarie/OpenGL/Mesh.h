#pragma once
#include <CassouletEngineLibrarie/System/Component.h>
#include <CassouletEngineLibrarie/Doom/DataTypes.h>
class FreeCamera;


struct MeshVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Color;
};

class CASSOULET_DLL Mesh : public Component
{
public:
	// mesh data
	//true if we want to draw both sides of the mesh

	Mesh();

	Mesh::~Mesh();

	static Mesh* CreateCube();
	static Mesh* CreateMap(std::vector<Seg>& segs, std::vector<Sector>& sectors, std::vector<Vertex>& vertices, std::vector<Subsector>& subsectors);
	static Mesh* CreateQuad();
	static Mesh* CreateTriangle();
	static Mesh* CreateSphere(float radius = 1.0f, unsigned int sectorCount = 36, unsigned int stackCount = 18);

	void SetMesh(std::vector<MeshVertex>& vertices, std::vector<GLuint>& indices);
	void SetCam(FreeCamera* pcam);

	void Draw();
	void Draw(GLuint shaderProgram, glm::mat4 view, glm::mat4 projection, glm::mat4 model);
	void SetObjectColor(const glm::vec3& color);
	void SetTexture(sf::Texture* ptexture, bool isTransparent);
	bool doubleSided;
	bool isTransparent;

	const std::string GetName() { return "Mesh"; };
	GLuint shaderID;
private:
	glm::vec3 m_meshColor;
	GLuint VAO, VBO, EBO;
	std::vector<MeshVertex> m_vertices;
	std::vector<GLuint> m_indices;
	sf::Texture* m_texture = nullptr;
	//is the texture transparent somewhere
	FreeCamera* m_cam;
	//true of the mesh has vertices
	bool hasVertices;
};
