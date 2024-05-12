#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>

class Map;
class Test;
class Mesh;
class GameObject;
class Camera;
class Vector2;

class CASSOULET_DLL ViewRender {

public:
	ViewRender();

	void SetView();

	void GLInit(int width, int height);
	void UpdateCameraMovement(float dt);
	void DrawMesh(Mesh* mesh, Mat4& transformation, Vec4& color);
	void Clear();

	void Update();
	void UpdateResize(int width, int height);
	void Render(sf::RenderWindow& window);
	void UIRender();
	void DrawPoints(std::vector<Vec2>& points, float size, Vec4& color);
	void DrawLine(Vec2& p0, Vec2& p1, float width, Vec4& color);
	void DrawLine(int16_t p0x, int16_t p0y, int16_t p1x, int16_t& p1y, float width, Vec4& color);
	void DrawQuad(Vec2& center, Vec2& size, float angle, Vec4& color);
	GameObject* m_objCam;
	float m_cameraSensitivity = 100.f;

private:
	float m_cameraspeed = 50.f;
	Map* m_map;
	int m_screenWidth;
	int m_screenHeight;
	float fps;
	Vec2 m_view;;
	Vec3 m_boxScale = Vec3(1, 1, 1);
	GameObject* m_objtest;
	Camera* m_cam;
	Mesh* m_mesh;
	Test* t;
	std::shared_ptr<sf::Shader>	m_shader;
};