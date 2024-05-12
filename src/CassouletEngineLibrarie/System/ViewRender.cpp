#include <CassouletEngineLibrarie/System/ViewRender.h>
#include <CassouletEngineLibrarie/System/Test.h>
#include <CassouletEngineLibrarie/System/Imguicpp.h>
#include <CassouletEngineLibrarie/System/GameObject.h>
#include <CassouletEngineLibrarie/System/GameManager.h>
#include <CassouletEngineLibrarie/Doom/Map.h>
#include <CassouletEngineLibrarie/OpenGL/Camera.h>
#include <CassouletEngineLibrarie/OpenGL/Mesh.h>
#include <CassouletEngineLibrarie/OpenGL/Matrix.h>
#include <CassouletEngineLibrarie/System/CassouletEngine.h>
#include <CassouletEngineLibrarie/Math/Vector2.h>



static std::string model_location, view_location, projection_location;
static std::string  color_location, use_texture_location, texture_index_location;

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

static bool init_shader(std::shared_ptr<sf::Shader>& shader);
static void init_projection(std::shared_ptr<sf::Shader>& shader, int width, int height);
void init_projection(int left, int width, int height, int top, int znear, int zfar);

ViewRender::ViewRender()
{
	if (init_shader(m_shader)) { std::cout << "Shader init !" << std::endl; }
	else
		std::cout << "Shader not init" << std::endl;
	m_objCam = new GameObject();
	m_objtest = new GameObject();
	m_cam = GameManager::Instance().addComponent<Camera>(m_objCam->id);
	m_mesh = GameManager::Instance().addComponent<Mesh>(m_objtest->id, Mesh::CreateCube());
	t = new Test();
}

void ViewRender::GLInit(int width, int height)
{
	m_cam->SetWindowSize(width, height);


	//enable blend and set blend function so we can have transparent textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//enable depth test by deafult and set depth function
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	m_screenWidth = width;
	m_screenHeight = height;
}

void ViewRender::UpdateCameraMovement(float dt) {
	//move up and down relative to the world
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		m_objCam->transform.position += Vector3::Up() * m_cameraspeed *dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		m_objCam->transform.position += Vector3::Down() * m_cameraspeed *dt;

	//move foward, back, left and right relative to self
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_objCam->transform.position += m_objCam->transform.Forward() * m_cameraspeed *dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_objCam->transform.position += m_objCam->transform.Back() * m_cameraspeed *dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_objCam->transform.position += m_objCam->transform.Left() * m_cameraspeed *dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_objCam->transform.position += m_objCam->transform.Right() * m_cameraspeed *dt;
}

void ViewRender::UpdateResize(int width, int height)
{
	m_screenWidth = width;
	m_screenHeight = height;
	m_cam->SetWindowSize(width, height);
}

void ViewRender::SetView() {
	//glViewport(m_view.x,m_view.y,m_screenWidth, m_screenHeight);

}

void ViewRender::DrawMesh(Mesh* mesh, Mat4& transformation, Vec4& color)
{
	m_shader->setUniform("color", color);
	m_shader->setUniform("model", transformation);
	mesh->Draw();
}

void ViewRender::DrawPoints(std::vector<Vec2>& points, float size, Vec4& color)
{
	glBegin(GL_POINTS);
	for (Vec2 vec : points)
	{
		glVertex2f(vec.x, vec.y);
	}
	glEnd();
}

void ViewRender::DrawLine(Vec2& p0, Vec2& p1, float width, Vec4& color)
{
	float x = p1.x - p0.x, y = p0.y - p1.y;
	float length = std::sqrt(x * x + y * y);
	float angle = std::atan2(y, x) * 180.f / static_cast<float>(PI);

	sf::Transform transform = sf::Transform::Identity;
	transform.translate((p0.x + p1.x) / 2.f, (p0.y + p1.y) / 2.f);
	transform.rotate(angle);
	transform.scale(length, width);

	glPushMatrix();
	glMultMatrixf(transform.getMatrix());

	glBegin(GL_QUADS);
	glColor4f(color.x, color.y, color.z, color.w);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glPopMatrix();
}

void ViewRender::DrawLine(int16_t p0x, int16_t p0y, int16_t p1x, int16_t& p1y, float width, Vec4& color)
{
	float x = p1x - p0x, y = p0y - p1y;
	float length = std::sqrt(x * x + y * y);
	float angle = std::atan2(y, x) * 180.f / static_cast<float>(PI);

	sf::Transform transform = sf::Transform::Identity;
	transform.translate((p0x + p1x) / 2.f, (p0y + p1y) / 2.f);
	transform.rotate(angle);
	transform.scale(length, width);

	glPushMatrix();
	glMultMatrixf(transform.getMatrix());

	glBegin(GL_QUADS);
	glColor4f(color.x, color.y, color.z, color.w);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glPopMatrix();
}

void ViewRender::DrawQuad(Vec2& center, Vec2& size, float angle, Vec4& color)
{
	// Calculer les coordonnées du coin supérieur gauche à partir du centre et de la taille
	sf::Vector2f halfSize = size / 2.f;
	sf::Vector2f topLeft = center - halfSize;

	// Appliquer la rotation au centre
	sf::Transform transform;
	transform.rotate(angle, center);

	// Calculer les coordonnées des coins du quad après rotation
	sf::Vector2f topRight = transform.transformPoint(topLeft + sf::Vector2f(size.x, 0));
	sf::Vector2f bottomLeft = transform.transformPoint(topLeft + sf::Vector2f(0, size.y));
	sf::Vector2f bottomRight = transform.transformPoint(topLeft + size);

	// Dessiner le quad en utilisant des triangles
	glBegin(GL_TRIANGLES);
	glColor4f(color.x, color.y, color.z, color.w);
	// Premier triangle (top-left, top-right, bottom-left)
	glVertex2f(topLeft.x, topLeft.y);
	glVertex2f(topRight.x, topRight.y);
	glVertex2f(bottomLeft.x, bottomLeft.y);
	// Deuxième triangle (top-right, bottom-left, bottom-right)
	glVertex2f(topRight.x, topRight.y);
	glVertex2f(bottomLeft.x, bottomLeft.y);
	glVertex2f(bottomRight.x, bottomRight.y);
	glEnd();
}

void ViewRender::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ViewRender::UIRender() {
	Vec3 campos = Vec3(m_objCam->transform.position.x, m_objCam->transform.position.y, m_objCam->transform.position.z);
	IMGUICPP::DrawVector3Windowf(campos, "Camera Postion");
	Vec3 camrot = Vec3(m_objCam->transform.rotation.x, m_objCam->transform.rotation.y, m_objCam->transform.rotation.z);
	IMGUICPP::DrawVector3Windowf(camrot, "Camera Rotation");
	IMGUICPP::DrawVector3Windowf(m_boxScale, "Cube Scale");
	ImGui::Begin("Camera Speed");
	ImGui::InputFloat("speed", &m_cameraspeed);
	ImGui::End();

	m_objCam->transform.position = Vector3(campos.x, campos.y, campos.z);
	m_objCam->transform.rotation = Vector3(camrot.x, camrot.y, camrot.z);
	m_objtest->transform.scale = Vector3(m_boxScale.x, m_boxScale.y, m_boxScale.z);
}

void ViewRender::Render(sf::RenderWindow& window)
{

	//t->render3D(window);


	m_objCam->Draw();
	m_objtest->Draw();
}

static bool init_shader(std::shared_ptr<sf::Shader>& shader)
{

	shader = std::make_shared<sf::Shader>();

	projection_location = "projection";
	model_location = "model";
	view_location = "view";
	color_location = "color";
	use_texture_location = "useTexture";
	texture_index_location = "texIdx";

	if (!shader->loadFromMemory(vertSrc, fragSrc))
	{
		return false;
	}
	if (!shader->isAvailable() || !shader->isGeometryAvailable())
	{
		return false;
	}

	return true;
}


void ViewRender::Update()
{
	SetView();
	//std::cout << "View : " << glGet(GL_VIEWPORT) << << std::endl ;
}

void init_projection(std::shared_ptr<sf::Shader>& shader, int width, int height)
{
	//Mat4 projection = mat4_ortho(0.f, width, height, 0.f, -1.f, 1.f);
	//shader->setUniform("projection", projection);
	glOrtho(-100.0f, width, -height, 100.0f, -100.0f, 100.0f);
}

void init_projection(int left, int width, int height, int top, int znear, int zfar)
{
	//Mat4 projection = mat4_ortho(0.f, width, height, 0.f, -1.f, 1.f);
	//shader->setUniform("projection", projection);
	glFrustum(left, width, -height, top, -znear, zfar);
}