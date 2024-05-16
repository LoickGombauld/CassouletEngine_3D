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

using Vec2 = sf::Glsl::Vec2;
using Vec3 = sf::Glsl::Vec3;
using Vec4 = sf::Glsl::Vec4;

using Mat4 = sf::Glsl::Mat4;

#endif