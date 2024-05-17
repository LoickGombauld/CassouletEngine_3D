#include <CassouletEngineLibrarie/OpenGL/Mesh.h>
#include <CassouletEngineLibrarie/System/GameObject.h>
#include <CassouletEngineLibrarie/Doom/DataTypes.h>


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

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Mesh::SetMesh(std::vector<GLfloat>& vertices, std::vector<uint32_t>& uv)
{
	SetMesh(vertices.data(), uv.data(), vertices.size(), uv.size());
}


void Mesh::SetMesh(GLfloat* vertices, uint32_t* uvs, int verticesCount, int uvCount)
{

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticesCount, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * uvCount, uvs, GL_STATIC_DRAW);


	m_uvCount = uvCount;
	m_verticesCount = verticesCount;
	hasVertices = verticesCount > 0 && uvCount > 0;
}


void Mesh::SetTexture(sf::Texture* ptexture, bool isTransparent)
{
	if (m_texture != nullptr)
		delete m_texture;
	//set new texture and uvs
	m_texture = ptexture;
	m_isTransparent = isTransparent;
}

void Mesh::Draw()
{
	//if the mesh does not have any vertices stop here
	if (!hasVertices)
		return;

	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//set position
	glTranslatef(gameObject->transform.position.x, gameObject->transform.position.y, -gameObject->transform.position.z);

	//set rotation
	glRotatef(gameObject->transform.rotation.x, 1, 0, 0);
	glRotatef(gameObject->transform.rotation.y, 0, 1, 0);
	glRotatef(gameObject->transform.rotation.z, 0, 0, 1);

	//set scale
	glScalef(gameObject->transform.scale.x, gameObject->transform.scale.y, gameObject->transform.scale.z);

	//disable cullface if we want to draw both sides, else enable it
	if (doubleSided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);

	//enable textures and set filter mode to nearest, we want to use nearest to get a clear pixel art style
	//glEnable(GL_TEXTURE_2D);
	//sf::Texture::bind(texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//bind texture
	//glBindTexture(GL_TEXTURE_2D, texture->getNativeHandle());
	// Enable position and texture coordinates vertex components

	

	// Configurer les attributs de sommet
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, m_uvCount, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}


Mesh* Mesh::CreateMesh(std::vector<GLfloat>& vertices, std::vector<uint32_t>& uvs)
{
	Mesh* mesh = new Mesh();
	mesh->SetMesh(vertices, uvs);
	return mesh;
}

Mesh* Mesh::CreateCube()
{
	std::vector<GLfloat> cube =
	{
		//Top
			   -1, 1, -1, //0
				1, 1, -1  //1
			   - 1, 1,  1, //2
				1, 1,  1, //3

			   //Bottom
			   -1, -1, -1, //4
				1, -1, -1, //5
			   -1, -1,  1, //6
				1, -1,  1  //7

			   //Front
			   - 1,  1, 1, //8
				1,  1, 1, //9
			   -1, -1, 1, //10
				1, -1, 1, //11

			   //Back
			   -1,  1, -1, //12
				1,  1, -1, //13
			   -1, -1, -1, //14
				1, -1, -1, //15

			   //Left
			   -1,  1,  1, //16
			   -1,  1, -1, //17
			   -1, -1,  1, //18
			   -1, -1, -1, //19

			   //Right
			   1,  1,  1, //20
			   1,  1, -1, //21
			   1, -1,  1, //22
			   1, -1, -1  //23
	};

	std::vector<uint32_t> uv = {

		//Top
		2, 6, 7,
		2, 3, 7,

		//Bottom
		0, 4, 5,
		0, 1, 5,

		//Left
		0, 2, 6,
		0, 4, 6,

		//Right
		1, 3, 7,
		1, 5, 7,

		//Front
		0, 2, 3,
		0, 1, 3,

		//Back
		4, 6, 7,
		4, 5, 7
	};

	auto cubemesh = CreateMesh(cube, uv);
	cubemesh->doubleSided = true;
	return cubemesh;
}

Mesh* Mesh::CreateQuad() {
	std::vector<GLfloat> quad =
	{
		//Front
		-1,  1, 1, //8
		 1,  1, 1, //9
		-1, -1, 1, //10
		 1, -1, 1, //11

	};

	std::vector<uint32_t> uv = {
		//Front
		0, 2, 3,
		0, 1, 3,
	};
	return CreateMesh(quad, uv);
}

Mesh* Mesh::CreateTriangle() {
	std::vector<GLfloat> vertices = {
	-0.f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	std::vector<uint32_t>  indices = {
	0, 0,
	1, 0,
	};

	return CreateMesh(vertices, indices);
}

Mesh* Mesh::CreateSphere(int resolution) {
	std::vector<GLfloat> vertices;
	std::vector<uint32_t> indices;


	float x, y, z, xy;
	float radius = 1.0f;
	float nx, ny, nz, lengthInv = 1.0f / radius;
	uint32_t s, t;

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