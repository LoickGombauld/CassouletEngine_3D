#pragma once
#include <CassouletEngineLibrarie/System/Component.h>

class CASSOULET_DLL Camera : public Component {
private:
	sf::RenderWindow* m_ptrwindow;
	//is called on the first draw call
	void Draw();
	int m_sizeX;
	int m_sizeY;

public:
	//background color
	sf::Color backgroundColor = sf::Color::Cyan;
	//field of view
	int fov = 90;
	//distance from the camera the game will begin to render
	float nearClip = 0.1;
	//how far from the camera the game will render
	float farClip = 100.0f;

	void SetWindowSize(int sizeX,int sizeY);

	const std::string GetName() { return "Camera"; };
};