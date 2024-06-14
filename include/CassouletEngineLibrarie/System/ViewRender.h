#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>

class Map;
class Mesh;
class GameObject;
class FreeCamera;
class Camera;
class Vector2;

class CASSOULET_DLL ViewRender {

public:
	ViewRender();
	~ViewRender();

	void GLInit(int width, int height);
	void UpdateCameraMovement(float dt);
	void Clear();
	void Update();
	void UpdateResize(int width, int height);
	void Render(sf::RenderWindow& window);
	void UIRender();

	static GLuint shaderProgram;
	static GLuint model_location;
	static GLuint view_location;
	static GLuint projection_location;
	static GLuint color_location;
	static FreeCamera* camera;

private:
	std::shared_ptr<FreeCamera> f_Cam = std::make_shared<FreeCamera>();
	Map* m_map;
	int m_screenWidth;
	int m_screenHeight;
	float fps;

	GameObject* m_objtest;
	GameObject* m_objtest2;
};