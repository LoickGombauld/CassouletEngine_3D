#include <CassouletEngineLibrarie/OpenGL/Mesh.h>
#include <CassouletEngineLibrarie/System/GameObject.h>
#include <CassouletEngineLibrarie/Doom/Angle.h>

// D�finition des couleurs des vertices
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
	if (indices != nullptr)
		delete indices;
	if (vertices != nullptr)
		delete vertices;
}


void Mesh::SetVertices(GLfloat* pvertices, int pverticesCount)
{
	if (vertices != nullptr)
		//remove old vertices from memory
		delete vertices;


	// Allouez de la m�moire pour les nouvelles coordonn�es UV
	this->vertices = new GLfloat[pverticesCount];

	// Copiez les coordonn�es UV dans le tableau de la classe
	for (int i = 0; i < pverticesCount; ++i) {
		this->vertices[i] = pvertices[i];
	}
	verticesCount = pverticesCount;

	hasVertices = true;

}

void Mesh::SetTexture(sf::Texture* ptexture, GLubyte* texture_coord, bool isTransparent)
{
	//set new texture and uvs
	texture = ptexture;
	indices = texture_coord;
	isTransparent = isTransparent;
}

void Mesh::Draw()
{
	//if the mesh does not have any vertices stop here
	if (!hasVertices)
		return;

	if (texture == nullptr)
	{
		texture = new sf::Texture();
		texture->create(10, 10);
	}

	//set position
	glTranslatef(gameObject->transform.position.x, gameObject->transform.position.y, -gameObject->transform.position.z);

	//set rotation
	glRotatef(gameObject->transform.rotation.x, 1, 0, 0);
	glRotatef(gameObject->transform.rotation.y, 0, 1, 0);
	glRotatef(gameObject->transform.rotation.z, 0, 0, 1);

	//set scale
	glScalef(gameObject->transform.scale.x, gameObject->transform.scale.y, gameObject->transform.scale.z);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//disable cullface if we want to draw both sides, else enable it
	if (doubleSided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);

	//enable textures and set filter mode to nearest, we want to use nearest to get a clear pixel art style
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//bind texture
	//glBindTexture(GL_TEXTURE_2D, texture->getNativeHandle());

	  // Configuration des attributs des vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	// Dessin du cube
	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_BYTE, indices);

	// D�sactivation des attributs
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Mesh::SetIndices(const GLubyte* indices, int indiceCount)
{
	// Assurez-vous que uvCount est valide
	if (indiceCount <= 0 || indiceCount % 2 != 0) {
		// G�rer l'erreur ou l'ignorer
		return;
	}

	// Lib�rez la m�moire s'il y a d�j� des coordonn�es Indices pr�c�dentes
	delete[] this->indices;

	// Allouez de la m�moire pour les nouvelles coordonn�es Indices
	this->indices = new GLubyte[indiceCount];

	// Copiez les coordonn�es Indices dans le tableau de la classe
	for (int i = 0; i < indiceCount; ++i) {
		this->indices[i] = indices[i];
	}

	// Mise � jour de uvCount
	this->indiceCount = indiceCount;
}


Mesh* Mesh::CreateMesh(GLfloat* vertices, GLubyte* indices, int countVertice, int countIndice)
{
	Mesh* mesh = new Mesh();
	mesh->SetVertices(vertices, countVertice);
	mesh->SetIndices(indices, countIndice);

	return mesh;
}

Mesh* Mesh::CreateCube()
{
	// D�finition des sommets du cube
	std::vector<GLfloat> vertices = {
			-1, -1, -1, // Face arri�re
			1, -1, -1,
			1, 1, -1,
			-1, 1, -1,
			-1, -1, 1,  // Face avant
			1, -1, 1,
			1, 1, 1,
			-1, 1, 1
	};

	// D�finition des coordonn�es de texture (UV)
	std::vector<GLubyte> indices = {
			0, 1, 2, 2, 3, 0, // Face arri�re
			1, 5, 6, 6, 2, 1, // Face droite
			4, 5, 6, 6, 7, 4, // Face avant
			0, 4, 7, 7, 3, 0, // Face gauche
			0, 1, 5, 5, 4, 0, // Face inf�rieure
			3, 2, 6, 6, 7, 3  // Face sup�rieure
	};

	return CreateMesh(vertices.data(), indices.data(), vertices.size(), indices.size());
}

Mesh* Mesh::CreateQuad() {
	std::vector<GLfloat> vertices = {
			-0.5f, -0.5f, -0.5f, // Face arri�re
			0.5f, -0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f
	};

	std::vector<GLubyte>  indices = {
		0, 1, 2, 2, 3, 0
	};

	return CreateMesh(vertices.data(), indices.data(), vertices.size(), indices.size());
}

Mesh* Mesh::CreateTriangle() {
	std:: vector<GLfloat> vertices = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

	std::vector<GLubyte>  indices = {
	0, 1, 2
	};

	return CreateMesh(vertices.data(), indices.data(), vertices.size(),indices.size());
}

Mesh* Mesh::CreateSphere(int resolution) {
	std::vector<GLfloat> vertices;
	std::vector<GLubyte> indices;


	float x, y, z, xy;
	float radius = 1.0f;
	float nx, ny, nz, lengthInv = 1.0f / radius;
	GLubyte s, t;

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
	return CreateMesh(vertices.data(),indices.data(),vertices.size(), indices.size());
}