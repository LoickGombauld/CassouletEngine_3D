#include <CassouletEngineLibrarie/System/ViewRender.h>
#include <CassouletEngineLibrarie/System/Test.h>
#include <CassouletEngineLibrarie/System/Imguicpp.h>
#include <CassouletEngineLibrarie/System/GameObject.h>
#include <CassouletEngineLibrarie/System/GameManager.h>
#include <CassouletEngineLibrarie/Doom/Map.h>
#include <CassouletEngineLibrarie/OpenGL/FreeCamera.h>
#include <CassouletEngineLibrarie/OpenGL/Mesh.h>
#include <CassouletEngineLibrarie/System/CassouletEngine.h>
#include <CassouletEngineLibrarie/Math/Vector2.h>

const char* vertSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aColor;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
    Color = aColor;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

const char* fragSrc = R"(
#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;

uniform sampler2D texture1;

void main()
{
    vec3 ambient = 0.1 * texture(texture1, TexCoords).rgb;
    vec3 diffuse = max(dot(Normal, vec3(0.0, 0.0, 1.0)), 0.0) * texture(texture1, TexCoords).rgb;
    vec3 result = (ambient + diffuse) * Color;
    FragColor = vec4(result, 1.0);
}
)";

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


static GLuint LoadShader(const char* shaderSrc, GLenum shaderType) {

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
		return 0;
	}

	return shader;
}

static GLuint CreateShaderProgram(const char* vertexSrc, const char* fragmentSrc) {
	GLuint vertexShader = LoadShader(vertexSrc, GL_VERTEX_SHADER);
	GLuint fragmentShader = LoadShader(fragmentSrc, GL_FRAGMENT_SHADER);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		throw std::runtime_error("Program linking failed: " + std::string(infoLog));
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

ViewRender::ViewRender() : f_Cam(new FreeCamera())
{
	m_shaderProgram = CreateShaderProgram(vertSrc,fragSrc);
	m_objtest = new GameObject();
	m_objtest2 = new GameObject();
	m_mesh = GameManager::Instance().addComponent<Mesh>(m_objtest->id, Mesh::CreateCube());
	m_mesh2 = GameManager::Instance().addComponent<Mesh>(m_objtest2->id, Mesh::CreateCube());
	m_mesh->shaderID = m_shaderProgram;
	m_mesh->SetCam(f_Cam.get());
	m_objtest2->transform.position = Vector3(25, 0, 0);
	t = new Test();
}

ViewRender::~ViewRender(){
	glDeleteProgram(m_shaderProgram);
	delete(m_objtest);
	delete(m_objtest2);
	delete(m_mesh);
	delete(m_mesh2);
	delete(t);
	f_Cam.reset();
}

void ViewRender::GLInit(int width, int height)
{
	if (f_Cam)
	{
		f_Cam->SetProjectionSize(width, height);
	}
	f_Cam->InitCamera(width, height);
	m_screenWidth = width;
	m_screenHeight = height;
}

void ViewRender::UpdateCameraMovement(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		f_Cam->Rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		f_Cam->Rotate(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		f_Cam->Rotate(1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		f_Cam->Rotate(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		f_Cam->MoveForward(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		f_Cam->MoveBackward(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		f_Cam->MoveLeft(-dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		f_Cam->MoveRight(dt);
	}
}

void ViewRender::UpdateCameraRotation() {

		static sf::Vector2i lastMousePosition = sf::Mouse::getPosition();
		sf::Vector2i currentMousePosition = sf::Mouse::getPosition();

		sf::Vector2i delta = currentMousePosition - lastMousePosition;
		float sensitivity = 0.5f;  // Sensibilité de la rotation

		f_Cam->Rotate(-delta.x * sensitivity, glm::vec3(0.0f, 1.0f, 0.0f));  // Rotation autour de l'axe Y
		f_Cam->Rotate(-delta.y * sensitivity, glm::vec3(1.0f, 0.0f, 0.0f));  // Rotation autour de l'axe X

		lastMousePosition = currentMousePosition;
}

void ViewRender::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ViewRender::UIRender() {

	IMGUICPP::DrawVector3Windowf(m_objtest->transform.position, "Cube 1 Position");
	IMGUICPP::DrawVector3Windowf(m_objtest2->transform.position, "Cube 2 Position");
	IMGUICPP::DrawVector3Windowf(m_boxScale, "Cube Scale");
	ImGui::End();

	m_objtest->transform.scale = Vector3(m_boxScale.x, m_boxScale.y, m_boxScale.z);
}

void ViewRender::Render(sf::RenderWindow& window)
{
	//t->render3D(window);
	//GameManager::Instance().DrawAllGameObjects();
	m_objtest->Draw();
	//m_objtest2->Draw();
}


static bool checkShader(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		std::cout << "Error compiling shader:" << buffer << std::endl;
		return false;
	}
	return true;
}

void ViewRender::Update()
{
}

void ViewRender::UpdateResize(int width, int height)
{
	m_screenWidth = width;
	m_screenHeight = height;
	f_Cam->SetProjectionSize(width, height);
	glViewport(0, 0, width, height);
}