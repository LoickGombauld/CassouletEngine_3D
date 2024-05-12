#pragma once
#include<CassouletEngineLibrarie/System/Libs.h>
#include<CassouletEngineLibrarie/Doom/WADLoader.h>

class Things;
class Player;
class ViewRender;
class Map;
class Vector2;

class CASSOULET_DLL CassouletEngine
{
public:
    CassouletEngine();
    ~CassouletEngine();

    virtual void Render();
    virtual void KeyReleasedMouseInput();
    virtual void MouseMovedInput();
    virtual void UpdateKeyStatus();
    virtual void KeyPressed();
    virtual void KeyReleased();
    virtual void Quit();
    virtual void Update();
    virtual void UpdateResize();

    virtual bool IsOver();
    virtual bool Init();

    virtual int GetRenderWidth();
    virtual int GetRenderHeight();

    virtual std::string GetWADFileName();
    virtual std::string GetAppName();
    virtual sf::RenderWindow& GetWindow();

protected:
    void LoadWAD();
    void ReadDataFromWAD();
    void ProcessMouseMovement(float xPos, float yPos);
    Vector2 MouseMoveDir() const;


    int m_iRenderWidth;
    int m_iRenderHeight;

    bool m_bIsOver;
    sf::RenderWindow m_window; // The windows we will create
    std::string m_sAppName;
    WADLoader m_WADLoader;
    std::vector<WADPalette> m_palettes;
    std::unique_ptr<Map> m_pMap;
    std::unique_ptr<Player> m_pPlayer;
    std::unique_ptr<Things> m_pThings;
    std::unique_ptr<ViewRender> m_pViewRender;
    sf::Clock GameClock;
    sf::Time m_dt;

    bool m_firstMouse;

    float m_lastX, m_lastY;
};