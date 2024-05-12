#include <CassouletEngineLibrarie/System/Test.h>

void Test::DrawCube() {
	// Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);

	glColor3f(0.5f, 0, 0);
	//Multi-colored side - FRONT
	glBegin(GL_POLYGON);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5); // P1 is red
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.5, 0.5, -0.5); // P2 is green
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-0.5, 0.5, -0.5); // P3 is blue
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(-0.5, -0.5, -0.5); // P4 is purple

	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
}

void Test::loop(sf::RenderWindow& Pwindow)
{
	while (Pwindow.isOpen())
	{
		sf::Event event;
		while (Pwindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Pwindow.close();
		}
		sopecialKeys();
		// Logique de rendu
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawCube();

		Pwindow.display();

		// Ajouter une pause pour laisser le temps au système de traiter les événements
		sf::sleep(sf::milliseconds(10));
	}
}

void Test::render3D(sf::RenderWindow& window) {
	// Activation du contexte OpenGL
	window.setActive();
	

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

	// Définition des sommets du cube
	GLfloat vertices[] = {
			-0.5f, -0.5f, -0.5f, // Face arrière
			0.5f, -0.5f, -0.5f,
			0.5f, 0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,
			-0.5f, -0.5f, 0.5f,  // Face avant
			0.5f, -0.5f, 0.5f,
			0.5f, 0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f
	};

	GLubyte indices[] = {
			0, 1, 2, 2, 3, 0, // Face arrière
			1, 5, 6, 6, 2, 1, // Face droite
			4, 5, 6, 6, 7, 4, // Face avant
			0, 4, 7, 7, 3, 0, // Face gauche
			0, 1, 5, 5, 4, 0, // Face inférieure
			3, 2, 6, 6, 7, 3  // Face supérieure
	};


	// Chargement des shaders
	//sf::Shader shader;
	//if (!shader.loadFromMemory(
	//	"#version 330 core\n"
	//	"in vec3 position;\n"
	//	"in vec3 color;\n"
	//	"out vec3 fragColor;\n"
	//	"uniform mat4 projection;\n"
	//	"uniform mat4 view;\n"
	//	"void main()\n"
	//	"{\n"
	//	"    gl_Position = projection * view * vec4(position, 1.0);\n"
	//	"    fragColor = color;\n"
	//	"}\n",

	//	"#version 330 core\n"
	//	"in vec3 fragColor;\n"
	//	"out vec4 outColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	"    outColor = vec4(fragColor, 1.0);\n"
	//	"}\n"
	//)) {
	//	std::cerr << "Failed to load shader!" << std::endl;
	//	return;
	//}


	// Activation du shader
	//shader.setUniform("projection", mat4_ortho(0.f, window.getSize().x, window.getSize().y, 0.f, -1.f, 1.f));
	//  shader.setUniform("view", sf::gl::getModelViewMatrix());

	  // Configuration des attributs des vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	// Dessin du cube
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	// Désactivation des attributs
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

}

void Test::sopecialKeys()
{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			rotate_y += 5;

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			rotate_y -= 5;

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			rotate_x += 5;

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			rotate_x -= 5;
}
