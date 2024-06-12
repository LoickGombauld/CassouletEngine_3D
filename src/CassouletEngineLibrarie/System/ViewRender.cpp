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
	glUseProgram(shaderProgram);
	

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

GLuint ViewRender::shaderProgram;
GLuint ViewRender:: model_location;
GLuint ViewRender:: view_location;
GLuint ViewRender:: projection_location;
GLuint ViewRender:: color_location;
FreeCamera* ViewRender::camera;

ViewRender::ViewRender()
{
	camera = f_Cam.get();
	shaderProgram = CreateShaderProgram(vertSrc, fragSrc);
	projection_location = glGetUniformLocation(shaderProgram, "projection");
	model_location = glGetUniformLocation(shaderProgram, "model");
	view_location = glGetUniformLocation(shaderProgram, "view");
	color_location = glGetUniformLocation(shaderProgram, "Color");
	m_objtest = new GameObject();
	m_objtest2 = new GameObject();

	m_objtest2->transform.position = glm::vec3(25, 0, 0);
	t = new Test();
}

ViewRender::~ViewRender() {
	glDeleteProgram(shaderProgram);
	delete(m_objtest);
	delete(m_objtest2);
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

void ViewRender::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ViewRender::UIRender() {

	IMGUICPP::DrawVector3Windowf(f_Cam->position, "f_Cam Postion");
	IMGUICPP::DrawVector2Windowf(f_Cam->rotation, "f_Cam Rotation");
	ImGui::Begin("f_Cam Speed");
	ImGui::DragFloat("speed", &f_Cam->speed);
	ImGui::End();

	IMGUICPP::DrawVector3Windowf(m_objtest->transform.position, "Cube 1 Position");
	IMGUICPP::DrawVector3Windowf(m_objtest2->transform.position, "Cube 2 Position");
	ImGui::End();
}

void ViewRender::Render(sf::RenderWindow& window)
{
	//t->render3D(window);
	//GameManager::Instance().DrawAllGameObjects();
	//m_objtest->Draw();
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