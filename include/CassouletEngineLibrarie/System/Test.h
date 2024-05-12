#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>


class CASSOULET_DLL Test {
public :
	Test() {};

	void DrawCube();
	void loop(sf::RenderWindow& Pwindow);
	void render3D(sf::RenderWindow& window);
	void sopecialKeys();

private:
	double rotate_y = 0;
	double rotate_x = 0;
 };

