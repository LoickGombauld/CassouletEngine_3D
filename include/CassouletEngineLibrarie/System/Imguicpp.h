#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>


class CASSOULET_DLL IMGUICPP {
public:
    static void DrawVector4Windowf(float& x, float& y, float& z, float& w, const std::string& title) {
       

        ImGui::Begin(title.c_str());
        ImGui::SetWindowSize(ImVec2(300, 100));

        ImGui::InputFloat("X", &x);
        ImGui::InputFloat("Y", &y);
        ImGui::InputFloat("Z", &z);
        ImGui::InputFloat("W", &w);

        ImGui::End();
    }

    static void DrawVector4Windowi(int& x, int& y, int& z, int& w, const std::string& title) {
        
        
        ImGui::Begin(title.c_str());
        ImGui::SetWindowSize(ImVec2(300, 100));

        ImGui::InputInt("X", &x);
        ImGui::InputInt("Y", &y);
        ImGui::InputInt("Z", &z);
        ImGui::InputInt("W", &w);

        ImGui::End();
    }



    static void DrawVector3Windowf(float& x, float& y, float& z, const std::string& title) {
        ImGui::Begin(title.c_str());
        ImGui::SetWindowSize(ImVec2(300, 100));

        ImGui::InputFloat("X", &x);
        ImGui::InputFloat("Y", &y);
        ImGui::InputFloat("Z", &z);

        ImGui::End();
    }

    static void DrawVector3Windowi(int& x, int& y, int& z, const std::string& title) {
        ImGui::Begin(title.c_str());
        ImGui::SetWindowSize(ImVec2(300, 100));

        ImGui::InputInt("X", &x);
        ImGui::InputInt("Y", &y);
        ImGui::InputInt("Z", &z);

        ImGui::End();
    }

    static void DrawVector3Windowf(glm::vec3& vec, const std::string& title)
    {
        DrawVector3Windowf(vec.x, vec.y, vec.z, title);
    }

    static void DrawVector2Windowf(float& x, float& y, const std::string& title) {

        ImGui::Begin(title.c_str());
        ImGui::SetWindowSize(ImVec2(300, 100)); 

        ImGui::InputFloat("X", &x);
        ImGui::InputFloat("Y", &y);

        ImGui::End();
    }

    static void DrawVector2Windowi(int& x, int& y, const std::string& title) {

        ImGui::Begin(title.c_str());
        ImGui::SetWindowSize(ImVec2(300, 100));

        ImGui::InputInt("X", &x);
        ImGui::InputInt("Y", &y);

        ImGui::End();
    }

    static void DrawVector2Windowf(glm::vec3& vec, const std::string& title) {
        DrawVector2Windowf(vec.x, vec.y, title);
    }

    static void DrawVector2Windowf(glm::vec2& vec, const std::string& title) {
        DrawVector2Windowf(vec.x, vec.y, title);
    }


    static void DrawVector4Windowf(float& x, float& y, float& z, float& w) {

        ImGui::InputFloat("X", &x);
        ImGui::InputFloat("Y", &y);
        ImGui::InputFloat("Z", &z);
        ImGui::InputFloat("W", &w);

        ImGui::End();
    }

    static void DrawVector4Windowi(int& x, int& y, int& z, int& w) {
       

        ImGui::InputInt("X", &x);
        ImGui::InputInt("Y", &y);
        ImGui::InputInt("Z", &z);
        ImGui::InputInt("W", &w);

        ImGui::End();
    }

    static void DrawVector4Windowf(glm::vec4& vec) {
        ImGui::SetWindowSize(ImVec2(300, 100));
        DrawVector4Windowf(vec.x, vec.y, vec.z, vec.w);
    }

    static void DrawVector3Windowf(float& x, float& y, float& z) {
        
        ImGui::InputFloat("X", &x);
        ImGui::InputFloat("Y", &y);
        ImGui::InputFloat("Z", &z);

        ImGui::End();
    }

    static void DrawVector3Windowi(int& x, int& y, int& z) {

        ImGui::InputInt("X", &x);
        ImGui::InputInt("Y", &y);
        ImGui::InputInt("Z", &z);

    }

    static void DrawVector3Windowf(glm::vec3& vec) {
        ImGui::SetWindowSize(ImVec2(300, 100));
        DrawVector3Windowf(vec.x, vec.y, vec.z);
    }

    static void DrawVector2Windowf(float& x, float& y) {

        ImGui::InputFloat("X", &x);
        ImGui::InputFloat("Y", &y);
    }

    static void DrawVector2Windowi(int& x, int& y) {
        
        ImGui::InputInt("X", &x);
        ImGui::InputInt("Y", &y);

    }

    static void DrawVector2Windowf(glm::vec2& vec) {
        ImGui::SetWindowSize(ImVec2(300, 100));
        DrawVector2Windowf(vec.x, vec.y);
    }
};