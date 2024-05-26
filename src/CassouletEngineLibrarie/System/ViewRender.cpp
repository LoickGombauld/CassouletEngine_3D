#include <CassouletEngineLibrarie/System/ViewRender.h>
#include <CassouletEngineLibrarie/System/Test.h>
#include <CassouletEngineLibrarie/System/Imguicpp.h>
#include <CassouletEngineLibrarie/System/GameObject.h>
#include <CassouletEngineLibrarie/System/GameManager.h>
#include <CassouletEngineLibrarie/Doom/Map.h>
#include <CassouletEngineLibrarie/OpenGL/Camera.h>
#include <CassouletEngineLibrarie/OpenGL/FreeCamera.h>
#include <CassouletEngineLibrarie/OpenGL/Mesh.h>
#include <CassouletEngineLibrarie/System/CassouletEngine.h>
#include <CassouletEngineLibrarie/Math/Vector2.h>

static bool checkShader(GLuint shader);
static bool compileShaders();

static GLuint vertexShader;
static GLuint fragmentShader;
static GLuint shaderProgram;

static GLuint program;
static GLuint model_location, view_location, projection_location;
static GLuint color_location;

const char* vertSrc =
"#version 330 core\n"
"layout(location = 0) in vec2 pos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main() {\n"
"  gl_Position = projection * view * model * vec4(pos, 0.0, 1.0);\n"
"}\n";

const char* fragSrc =
"#version 330 core\n"
"out vec4 fragColor;\n"
"uniform vec4 color;\n"
"void main() {\n"
"  fragColor = color;\n"
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

ViewRender::ViewRender() : f_Cam(new FreeCamera(Vec3(0.0f, 0.0f, 3.0f), Vec3(0.0f, 1.0f, 0.0f), YAW, PITCH))
{

	if (compileShaders())
	{
		std::cout << "Shader init !" << std::endl;
	}
	else
		std::cout << "Shader not init" << std::endl;
	m_objCam = new GameObject();
	m_objtest = new GameObject();
	m_objtest2 = new GameObject();
	m_cam = GameManager::Instance().addComponent<Camera>(m_objCam->id);
	m_mesh = GameManager::Instance().addComponent<Mesh>(m_objtest->id, Mesh::CreateQuad());
	m_mesh2 = GameManager::Instance().addComponent<Mesh>(m_objtest2->id, Mesh::CreateCube());
	m_objtest2->transform.position = Vector3(25, 0, 0);
	t = new Test();
}

void ViewRender::GLInit(int width, int height)
{

	if (m_cam != nullptr)
	{
		m_cam->SetWindowSize(width, height);
	}

	//enable blend and set blend function so we can have transparent textures
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	////enable depth test by default and set depth function
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);

	m_screenWidth = width;
	m_screenHeight = height;
}

void ViewRender::UpdateCameraMovement(float dt) {
	////move up and down relative to the world
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	//	m_objCam->transform.position += Vector3::Up() * m_cameraspeed * dt;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
	//	m_objCam->transform.position += Vector3::Down() * m_cameraspeed * dt;

	//move foward, back, left and right relative to self
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//	m_objCam->transform.position += m_objCam->transform.Forward() * m_cameraspeed * dt;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//	m_objCam->transform.position += m_objCam->transform.Back() * m_cameraspeed * dt;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//	m_objCam->transform.position += m_objCam->transform.Left() * m_cameraspeed * dt;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//	m_objCam->transform.position += m_objCam->transform.Right() * m_cameraspeed * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		f_Cam->ProcessKeyboard(FreeCamera::UP, 0.1f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		f_Cam->ProcessKeyboard(FreeCamera::DOWN, 0.1f);

	//move foward, back, left and right relative to self
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		f_Cam->ProcessKeyboard(FreeCamera::FORWARD, 0.1f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		f_Cam->ProcessKeyboard(FreeCamera::BACKWARD, 0.1f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		f_Cam->ProcessKeyboard(FreeCamera::LEFT, 0.1f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		f_Cam->ProcessKeyboard(FreeCamera::RIGHT, 0.1f);
	f_Cam->GetPosition();
}

void  ViewRender::Setview(Mat4& view) {
	glUniformMatrix4fv(view_location, 1, GL_FALSE, view.array);
}

void  ViewRender::SetProjection(Mat4& projection) {
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, projection.array);
}

void  ViewRender::RenderMesh(const Mesh* mesh, Mat4& transformation,
	Vec4& color) {
	glUniform4f(color_location,color.x,color.y,color.z,color.w);
	glUniformMatrix4fv(model_location, 1, GL_FALSE, transformation.array);

	glBindVertexArray(mesh->VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->IBO);
	glDrawElements(GL_TRIANGLES, mesh->m_indicesCount, GL_UNSIGNED_INT, NULL);
}


void ViewRender::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ViewRender::UIRender() {

	ImGui::Begin("Camera Speed"); 
	Vec3 a = f_Cam->GetPosition();
	IMGUICPP::DrawVector3Windowf(a, "Camera Postion");
	f_Cam->SetPosition(a);
	IMGUICPP::DrawVector3Windowf(m_objCam->transform.rotation, "Camera Rotation");

	IMGUICPP::DrawVector3Windowf(m_objtest->transform.position, "Cube 1 Position");
	IMGUICPP::DrawVector3Windowf(m_objtest2->transform.position, "Cube 2 Position");
	IMGUICPP::DrawVector3Windowf(m_boxScale, "Cube Scale");
	ImGui::InputFloat("speed", &m_cameraspeed);
	ImGui::End();

	m_objtest->transform.scale = Vector3(m_boxScale.x, m_boxScale.y, m_boxScale.z);
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


static bool compileShaders()
{
	// compile the vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	if (!checkShader(vertexShader))
		return false;

	// compile the fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	if (!checkShader(fragmentShader))
		return false;

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindFragDataLocation(shaderProgram, 0, "outColor");

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	return true;
}



void ViewRender::Update()
{
}

void ViewRender::UpdateResize(int width, int height)
{
	m_screenWidth = width;
	m_screenHeight = height;
	m_cam->SetWindowSize(width, height);
	glViewport(0, 0, width, height);
}