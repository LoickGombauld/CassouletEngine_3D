#include <CassouletEngineLibrarie/OpenGL/Mesh.h>
#include <CassouletEngineLibrarie/System/GameObject.h>
#include <CassouletEngineLibrarie/System/GameManager.h>
#include <CassouletEngineLibrarie/OpenGL/FreeCamera.h>
#include <CassouletEngineLibrarie/System/ViewRender.h>

glm::vec3 get_random_color(const void* seed) {
	srand((uintptr_t)seed);
	return glm::normalize(glm::vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX));
}

Mesh::Mesh(std::vector<MeshVertex>& vertices, std::vector<GLuint>& indices)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	shaderID = ViewRender::shaderProgram;
	m_cam = ViewRender::camera;
	SetMesh(vertices, indices);
}

Mesh::Mesh() : VAO(0), VBO(0), EBO(0), m_texture(nullptr), isTransparent(false), m_meshColor(glm::vec3(1.0f, 1.0f, 1.0f))
{

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	shaderID = ViewRender::shaderProgram;
	m_cam = ViewRender::camera;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Mesh::CalculateNormals() {
	// Initialise toutes les normales à zéro
	for (auto& vertex : m_vertices) {
		vertex.Normal = glm::vec3(0.0f);
	}

	// Calcule les normales des triangles
	for (size_t i = 0; i < m_indices.size(); i += 3) {
		GLuint idx0 = m_indices[i];
		GLuint idx1 = m_indices[i + 1];
		GLuint idx2 = m_indices[i + 2];

		glm::vec3 v0 = m_vertices[idx0].Position;
		glm::vec3 v1 = m_vertices[idx1].Position;
		glm::vec3 v2 = m_vertices[idx2].Position;

		glm::vec3 edge1 = v1 - v0;
		glm::vec3 edge2 = v2 - v0;
		glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

		m_vertices[idx0].Normal += normal;
		m_vertices[idx1].Normal += normal;
		m_vertices[idx2].Normal += normal;
	}

	// Normalise les normales des vertices
	for (auto& vertex : m_vertices) {
		vertex.Normal = glm::normalize(vertex.Normal);
	}

	// Initialise toutes les normales à zéro
	for (auto& vertex : m_vertices) {
		vertex.Normal = glm::vec3(0.0f);
	}

	// Calcule les normales des triangles
	for (size_t i = 0; i < m_indices.size(); i += 3) {
		GLuint idx0 = m_indices[i];
		GLuint idx1 = m_indices[i + 1];
		GLuint idx2 = m_indices[i + 2];

		glm::vec3 v0 = m_vertices[idx0].Position;
		glm::vec3 v1 = m_vertices[idx1].Position;
		glm::vec3 v2 = m_vertices[idx2].Position;

		glm::vec3 edge1 = v1 - v0;
		glm::vec3 edge2 = v2 - v0;

		// Vérifie si les vecteurs des arêtes ne sont pas nuls
		if (glm::length(edge1) > 0.0f && glm::length(edge2) > 0.0f) {
			glm::vec3 normal = glm::cross(edge1, edge2);

			// Vérifie si la normale est valide (non nulle)
			if (glm::length(normal) > 0.0f) {
				normal = glm::normalize(normal);
				m_vertices[idx0].Normal += normal;
				m_vertices[idx1].Normal += normal;
				m_vertices[idx2].Normal += normal;
			}
		}
	}

	// Normalise les normales des vertices
	for (auto& vertex : m_vertices) {
		if (glm::length(vertex.Normal) > 0.0f) {
			vertex.Normal = glm::normalize(vertex.Normal);
		}
		else {
			vertex.Normal = glm::vec3(0.0f, 1.0f, 0.0f); // Par défaut, une normale vers le haut
		}
	}
}


void Mesh::SetMesh(std::vector<MeshVertex>& vertices, std::vector<GLuint>& indices)
{
	this->m_vertices.clear();
	this->m_indices.clear();
	this->m_vertices = vertices;
	this->m_indices = indices;

	// Calcul des normales
	CalculateNormals();

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(MeshVertex), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Normal));

	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, TexCoords));

	// vertex colors
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Color));

	glBindVertexArray(0);

	hasVertices = m_vertices.size() > 0 && indices.size() > 0;
}

void Mesh::SetCam(FreeCamera* pcam)
{
	m_cam = pcam;
}

void Mesh::AddVertex(MeshVertex& vertices)
{
	m_vertices.push_back(vertices);
}


void Mesh::SetTexture(sf::Texture* ptexture, bool isTransparent)
{
	if (m_texture != nullptr)
		delete m_texture;
	//set new texture
	m_texture = ptexture;
	isTransparent = isTransparent;
}

void Mesh::Draw(GLuint shaderProgram, glm::mat4 view, glm::mat4 projection, glm::mat4 model) {
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::SetObjectColor(const glm::vec3& color)
{
	m_meshColor = color;
}

void Mesh::Draw()
{
	glEnable(GL_DEPTH_TEST);
	// if texture is loaded then bind
	if (m_texture) {
		sf::Texture::bind(m_texture);
	}

	if (!hasVertices)
		return;

	glm::mat4 model = gameObject->transform.GetModelMatrix();
	glUseProgram(shaderID);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	GLint colorLoc = glGetUniformLocation(shaderID, "meshColor");
	if (colorLoc == -1) {
		std::cerr << "Warning: meshColor uniform not found in shader." << std::endl;
	}
	glUniform3fv(colorLoc, 1, glm::value_ptr(m_meshColor));;
	m_cam->SetShaderUniforms(shaderID);

	if (doubleSided) {
		glDisable(GL_CULL_FACE);
	}
	else {
		glEnable(GL_CULL_FACE);
	}

	if (isTransparent) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else {
		glDisable(GL_BLEND);
	}
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	sf::Texture::bind(nullptr);
}

Mesh* Mesh::CreateCube() {
	Mesh* cube = new Mesh();

	std::vector<MeshVertex> vertices = {
		// Positions          // Normals           // Texture Coords
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f,  1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // Rouge
		{{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f,  1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // Vert
		{{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f,  1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // Bleu
		{{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f,  1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}}, // Jaune
		{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // Rouge
		{{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // Vert
		{{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // Bleu
		{{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}}  // Jaune

	};

	std::vector<GLuint> indices = {
		0, 1, 3, 1, 2, 3,   // Front face
		4, 5, 7, 5, 6, 7,   // Back face
		0, 1, 5, 0, 4, 5,   // Bottom face
		2, 3, 7, 2, 6, 7,   // Top face
		0, 3, 7, 0, 4, 7,   // Left face
		1, 2, 6, 1, 5, 6    // Right face
	};

	cube->SetMesh(vertices, indices);
	return cube;
}

Mesh* Mesh::CreateQuad() {
	Mesh* quad = new Mesh();

	std::vector<MeshVertex> vertices = {
		// Positions          // Normals           // Texture Coords
		{{-0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},{1.0f, 0.0f, 0.0f}},
		{{ 0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f},{0.0f, 1.0f, 0.0f}},
		{{ 0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f},{0.0f, 0.0f, 1.0f}},
		{{-0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f},{1.0f, 1.0f, 0.0f}},
	};

	std::vector<GLuint> indices = {
		0, 1, 2,  // First Triangle
		0, 2, 3   // Second Triangle
	};

	quad->SetMesh(vertices, indices);
	return quad;
}

Mesh* Mesh::CreateTriangle() {
	Mesh* triangle = new Mesh();

	std::vector<MeshVertex> vertices = {
		// Positions          // Normals           // Texture Coords
		{{-0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
		{{ 0.5f, -0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
		{{ 0.0f,  0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}},
	};

	std::vector<GLuint> indices = {
		0, 1, 2  // Single Triangle
	};

	triangle->SetMesh(vertices, indices);
	return triangle;
}

Mesh* Mesh::CreateSphere(float radius, unsigned int sectorCount, unsigned int stackCount)
{

	Mesh* sphere = new Mesh();

	std::vector<MeshVertex> vertices;
	std::vector<GLuint> indices;

	float x, y, z, xy;  // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;  // normal
	float s, t;  // texture coordinate

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	// Generate vertices
	for (unsigned int i = 0; i <= stackCount; ++i) {
		stackAngle = PI / 2 - i * stackStep;  // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);  // r * cos(u)
		z = radius * sinf(stackAngle);  // r * sin(u)

		// Add (sectorCount+1) vertices per stack
		for (unsigned int j = 0; j <= sectorCount; ++j) {
			sectorAngle = j * sectorStep;  // starting from 0 to 2pi

			// Vertex position (x, y, z)
			x = xy * cosf(sectorAngle);  // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);  // r * cos(u) * sin(v)
			vertices.push_back({
				glm::vec3(x, y, z),
				glm::vec3(x * lengthInv, y * lengthInv, z * lengthInv),
				glm::vec2((float)j / sectorCount, (float)i / stackCount)
				});
		}
	}

	// Generate indices
	for (unsigned int i = 0; i < stackCount; ++i) {
		unsigned int k1 = i * (sectorCount + 1);  // beginning of current stack
		unsigned int k2 = k1 + sectorCount + 1;  // beginning of next stack

		for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
			// 2 triangles per sector excluding first and last stacks
			if (i != 0) {
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (i != (stackCount - 1)) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	sphere->SetMesh(vertices, indices);
	return sphere;
}