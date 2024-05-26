#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>

class Map;
class Test;
class Mesh;
class GameObject;
class FreeCamera;
class Camera;
class Vector2;

class CASSOULET_DLL ViewRender {

public:
	ViewRender();

	void GLInit(int width, int height);
	void UpdateCameraMovement(float dt);
	void Clear();
	void Setview(Mat4& view);
	void SetProjection(Mat4& projection);
	void Update();
	void UpdateResize(int width, int height);
	void Render(sf::RenderWindow& window);
	void UIRender();
	void RenderMesh(const Mesh* mesh, Mat4& transformation, Vec4& color);
	FreeCamera* f_Cam;
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
	GameObject* m_objtest2;
	Camera* m_cam;
	Mesh* m_mesh;
	Mesh* m_mesh2;
	Test* t;
};