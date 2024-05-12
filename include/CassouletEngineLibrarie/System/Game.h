#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>
class CassouletEngine;

class CASSOULET_DLL Game
{
public:
    Game();
    virtual ~Game();

    void ProcessInput(); // Read user input
    void Render(); // Draw on the screen
    void Update(); // Update the world

    bool IsOver(); // Check if game is over
    bool Init(); // Initialize our objects

protected:

    std::unique_ptr<CassouletEngine> m_pCassouletEngine; // This is an object that knows more details about game internal
};