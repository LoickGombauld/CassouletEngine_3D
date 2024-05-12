#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>
#include <CassouletEngineLibrarie/System/Component.h>

class CASSOULET_DLL Mesh  : public Component
{
public:
	// mesh data
	//true if we want to draw both sides of the mesh

	Mesh();

	Mesh::~Mesh();

	static Mesh* CreateMesh(GLfloat* vertices, GLubyte* indices, int countVertice, int countUV);
	static Mesh* CreateMesh(std::array<GLfloat,180>& mesh,int countVertice);

	static Mesh* CreateCube();
	static Mesh* CreateQuad();
	static Mesh* CreateTriangle();
	static Mesh* CreateSphere(int subdivisions);
	void SetIndices(const GLubyte* uv, int uvCount);
	void SetMesh(std::array<GLfloat, 180>& mesh);

	void Draw();
	void SetVertices(GLfloat* pvertices,int pverticesCount);
	void SetTexture(sf::Texture* ptexture, GLubyte* texture_coord, bool isTransparent);
	bool doubleSided;

	const std::string GetName() { return "Mesh"; };
private:
	sf::RenderWindow* window;
	sf::Texture* texture = nullptr;
	GLubyte* indices = nullptr;
	int indiceCount = 0;
	GLfloat* vertices = nullptr;
	//is the texture transparent somewhere
	bool isTransparent;

	//mesh vertices
	//amount of vertices
	int verticesCount;
	//true of the mesh has vertices
	bool hasVertices;

	std::array<GLfloat, 180> m_mesh ;
};
