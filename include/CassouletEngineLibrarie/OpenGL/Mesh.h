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

struct VertexHasher {
	std::size_t operator()(const glm::vec3& vertex) const {
		return std::hash<float>()(vertex.x) ^ std::hash<float>()(vertex.y) ^ std::hash<float>()(vertex.z);
	}
};

// Structure pour repr?senter un segment unique
struct Segment {
	glm::vec3 start;
	glm::vec3 end;

	bool operator==(const Segment& other) const {
		return (start == other.start && end == other.end) ||
			(start == other.end && end == other.start);
	}
};

// Fonction de hachage pour la structure Segment
struct SegmentHasher {
	std::size_t operator()(const Segment& segment) const {
		auto hash1 = std::hash<float>()(segment.start.x) ^ std::hash<float>()(segment.start.y) ^ std::hash<float>()(segment.start.z);
		auto hash2 = std::hash<float>()(segment.end.x) ^ std::hash<float>()(segment.end.y) ^ std::hash<float>()(segment.end.z);
		return hash1 ^ hash2;
	}
};

class CASSOULET_DLL Mesh : public Component
{
public:
	// mesh data
	//true if we want to draw both sides of the mesh

	Mesh(std::vector<MeshVertex>& vertices, std::vector<GLuint>& indices);
	Mesh();

	Mesh::~Mesh();

	static Mesh* CreateCube();
	static Mesh* CreateQuad();
	static Mesh* CreateTriangle();
	static Mesh* CreateSphere(float radius = 1.0f, unsigned int sectorCount = 36, unsigned int stackCount = 18);

	void CalculateNormals();

	void SetMesh(std::vector<MeshVertex>& vertices, std::vector<GLuint>& indices);
	void SetCam(FreeCamera* pcam);
	void AddVertex(MeshVertex& vertices);
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
