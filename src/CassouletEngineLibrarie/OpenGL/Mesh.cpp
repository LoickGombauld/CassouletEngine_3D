#include <CassouletEngineLibrarie/OpenGL/Mesh.h>
#include <CassouletEngineLibrarie/System/GameObject.h>
#include <CassouletEngineLibrarie/Doom/DataTypes.h>


#define POSITION 0
#define COLOR 1


// Définition des couleurs des vertices
static const GLfloat colors[] = {
	1.0f, 0.0f, 0.0f, // Rouge
	0.0f, 1.0f, 0.0f, // Vert
	0.0f, 0.0f, 1.0f, // Bleu
	1.0f, 1.0f, 0.0f, // Jaune
	1.0f, 0.0f, 0.0f, // Rouge
	0.0f, 1.0f, 0.0f, // Vert
	0.0f, 0.0f, 1.0f, // Bleu
	1.0f, 1.0f, 0.0f  // Jaune
};

Mesh::Mesh() : VAO(0), VBO(0), EBO(0), m_texture(nullptr), m_isTransparent(false), m_indicesCount(0) {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::SetMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& uv)
{
	SetMesh(vertices.data(), uv.data(), vertices.size(), uv.size());
}

void Mesh::SetMesh(GLfloat* vertices, GLuint* indices, int verticesCount, int indicesCount)
{
	this->m_vertices = vertices;
	this->m_indices = indices;
	this->m_verticesCount = verticesCount;
	this->m_indicesCount = indicesCount;

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	hasVertices = verticesCount > 0 && indicesCount > 0;
}


void Mesh::SetTexture(sf::Texture* ptexture, bool isTransparent)
{
	if (m_texture != nullptr)
		delete m_texture;
	//set new texture
	m_texture = ptexture;
	m_isTransparent = isTransparent;
}

void Mesh::Draw()
{
	//if texutre is load then bind
	if (m_texture) {
		sf::Texture::bind(m_texture);
	}

	//if the mesh does not have any vertices stop here
	if (!hasVertices)
		return;

	//// Apply some transformations
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();


	////set position
	//glTranslatef(gameObject->transform.position.x, gameObject->transform.position.y, -gameObject->transform.position.z);

	////set rotation
	//glRotatef(gameObject->transform.rotation.x, 1, 0, 0);
	//glRotatef(gameObject->transform.rotation.y, 0, 1, 0);
	//glRotatef(gameObject->transform.rotation.z, 0, 0, 1);

	////set scale
	//glScalef(gameObject->transform.scale.x, gameObject->transform.scale.y, gameObject->transform.scale.z);

	//disable cullface if we want to draw both sides, else enable it
	if (doubleSided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);

	if (m_isTransparent) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else {
		glDisable(GL_BLEND);
	}

	// Configurer les attributs de sommet
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}


Mesh* Mesh::CreateMesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices)
{
	Mesh* mesh = new Mesh();
	mesh->SetMesh(vertices, indices);
	return mesh;
}
Mesh* Mesh::CreateCube() {
	Mesh* cube = new Mesh();

	GLfloat vertices[] = {
		// Positions       // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 3,  1, 2, 3,  // Front face
		4, 5, 7,  5, 6, 7,  // Back face
		0, 1, 5,  0, 4, 5,  // Bottom face
		2, 3, 7,  2, 6, 7,  // Top face
		0, 3, 7,  0, 4, 7,  // Left face
		1, 2, 6,  1, 5, 6   // Right face
	};

	cube->SetMesh(vertices, indices, sizeof(vertices) / sizeof(GLfloat), sizeof(indices) / sizeof(GLuint));

	return cube;
}

Mesh* Mesh::CreateQuad() {
	Mesh* quad = new Mesh();

	GLfloat vertices[] = {
		// Positions       // Texture Coords
		0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
	   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
	   -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	quad->SetMesh(vertices, indices, sizeof(vertices) / sizeof(GLfloat), sizeof(indices) / sizeof(GLuint));

	return quad;
}

Mesh* Mesh::CreateTriangle() {
	GLfloat vertices[] = { 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,-0.5f, 0.0f, 0.0f, 1.0f };
	GLuint elements[] = { 0, 1, 2 };
	Mesh* mesh = new Mesh();
	mesh->SetMesh(vertices, elements, 15, 3);
	return mesh;
}

Mesh* Mesh::CreateSphere(int resolution) {
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;


	float x, y, z, xy;
	float radius = 1.0f;
	float nx, ny, nz, lengthInv = 1.0f / radius;
	GLuint s, t;

	int sectorCount = resolution;
	int stackCount = resolution;

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;
	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;
		xy = radius * cosf(stackAngle);
		z = radius * sinf(stackAngle);

		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;

			x = xy * cosf(sectorAngle);
			y = xy * sinf(sectorAngle);
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			indices.push_back(nx);
			indices.push_back(ny);
			indices.push_back(nz);

			s = j / sectorCount;
			t = i / stackCount;
			indices.push_back(s);
			indices.push_back(t);
		}
	}
	return CreateMesh(vertices, indices);
}