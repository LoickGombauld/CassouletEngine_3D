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

const char* vertSrc =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec2 texCoord;\n"
"out vec2 TexCoord; \n"

"uniform mat4 model; \n"
"uniform mat4 view; \n"
"uniform mat4 projection; \n"

"void main() {\n"
"gl_Position = projection * view * model * vec4(position, 1.0);"
"TexCoord = texCoord;"
" }\n";

const char* fragSrc =
"#version 330 core\n"
"in vec2 TexCoord; \n"
"out vec4 color; \n"
"uniform sampler2D ourTexture; \n"
"void main() {\n"
"color = texture(ourTexture, TexCoord); \n"
"}\n";

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
	m_mesh = GameManager::Instance().addComponent<Mesh>(m_objtest->id, Mesh::CreateQuad());
	m_mesh2 = GameManager::Instance().addComponent<Mesh>(m_objtest2->id, Mesh::CreateCube());
	m_objtest2->transform.position = Vector3(25, 0, 0);
	t = new Test();
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
		f_Cam->RotateAroundTarget(-1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		f_Cam->RotateAroundTarget(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		f_Cam->RotateAroundTarget(-1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		f_Cam->RotateAroundTarget(1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		f_Cam->MoveForward(0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		f_Cam->MoveBackward(0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		f_Cam->MoveLeft(0.1f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		f_Cam->MoveRight(0.1f);
	}
}

void  ViewRender::RenderMesh(const Mesh* mesh, Mat4& transformation,
	Vec4& color) {
}


void ViewRender::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ViewRender::UIRender() {

	ImGui::Begin("f_Cam Speed");
	ImGui::InputFloat("speed", &m_cameraspeed);
	glm::vec3 _campos = f_Cam->GetPosition();
	IMGUICPP::DrawVector3Windowf(_campos, "f_Cam Postion");
	//IMGUICPP::DrawVector3Windowf(m_objCam->transform.rotation, "f_Cam Rotation");

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
	//m_objtest->Draw();
	//m_objtest2->Draw();

 f_Cam->Draw(*m_mesh,m_shaderProgram);
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