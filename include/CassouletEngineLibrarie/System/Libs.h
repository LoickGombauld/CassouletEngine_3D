#pragma once
#ifndef CASSOULET_LIB_HPP
#define CASSOULET_LIB_HPP

//EnTT
#include <entt/entt.hpp>

// ImGui
#include <imgui.h>
#include <imgui-SFML.h>

//OpenGl
#define GLEW_STATIC
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// SFML
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>



//C++ standard headers
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <list>
#include <utility>
#include <array>
#include <stdexcept>
#include <map>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <cstdint>
#include <fstream>
#include <math.h>
#include <filesystem>

//Cassoulet DLL
#include <CassouletEngineLibrarie/System/Export.hpp>

#define PI 3.14159265358979f

// Constants
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float FOV = 45.0f;

#endif