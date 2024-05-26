#pragma once
#include <CassouletEngineLibrarie/System/Component.h>

class CASSOULET_DLL Mesh  : public Component
{
public:
	// mesh data
	//true if we want to draw both sides of the mesh

	Mesh();

	Mesh::~Mesh();

	
	static Mesh* CreateMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& uvs);

	static Mesh* CreateCube();
	static Mesh* CreateQuad();
	static Mesh* CreateTriangle();
	static Mesh* CreateSphere(int subdivisions);

	void SetMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& uv);

	void SetMesh(GLfloat* vertices, GLuint* indices, int verticesCount, int indicesCount);

	void Draw();
	void SetTexture(sf::Texture* ptexture, bool isTransparent);
	bool doubleSided;

	const std::string GetName() { return "Mesh"; };
	GLuint VAO, VBO, IBO;
	//amount of indices
	int m_indicesCount = 0;
	//amount of vertices
	int m_verticesCount;
private:
	sf::Texture* m_texture = nullptr;
	//is the texture transparent somewhere
	bool m_isTransparent;

	//true of the mesh has vertices
	bool hasVertices;
	bool first_loop = true;
	GLuint* m_indices;
	GLfloat* m_vertices;
};
