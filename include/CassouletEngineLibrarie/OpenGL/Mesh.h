#pragma once
#include <CassouletEngineLibrarie/System/Component.h>

class CASSOULET_DLL Mesh  : public Component
{
public:
	// mesh data
	//true if we want to draw both sides of the mesh

	Mesh();

	Mesh::~Mesh();

	
	static Mesh* CreateMesh(std::vector<GLfloat>& vertices, std::vector<uint32_t>& uvs);

	static Mesh* CreateCube();
	static Mesh* CreateQuad();
	static Mesh* CreateTriangle();
	static Mesh* CreateSphere(int subdivisions);

	void SetMesh(std::vector<GLfloat>& vertices, std::vector<uint32_t>& uv);

	void SetMesh(GLfloat* vertices, uint32_t* uvs, int verticesCount, int uvsCount);

	void Draw();
	void SetTexture(sf::Texture* ptexture, bool isTransparent);
	bool doubleSided;

	const std::string GetName() { return "Mesh"; };
private:
	sf::Texture* m_texture = nullptr;
	//is the texture transparent somewhere
	bool m_isTransparent;

	//mesh vertices
	int m_uvCount = 0;
	//amount of vertices
	int m_verticesCount;
	//true of the mesh has vertices
	bool hasVertices;
	bool first_loop = true;
	GLuint vao, vbo, ebo;
};
