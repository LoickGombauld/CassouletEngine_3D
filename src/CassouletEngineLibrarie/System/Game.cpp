#include <CassouletEngineLibrarie/System/Game.h>
#include <CassouletEngineLibrarie/System/CassouletEngine.h>
#include <CassouletEngineLibrarie/OpenGL/FreeCamera.h>

Game::Game() 
{
}

Game::~Game()
{
}

bool Game::Init()
{
    m_pCassouletEngine = std::unique_ptr<CassouletEngine>(new CassouletEngine());

    if (!m_pCassouletEngine || !m_pCassouletEngine->Init())
    {
       std::cout << m_pCassouletEngine->GetAppName() << " failed to initialize!" <<std::endl;
        return false;
    }
    return true;
}

void Game::ProcessInput()
{
    sf::Event event;
    while (m_pCassouletEngine->GetWindow().pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(m_pCassouletEngine->GetWindow(), event);
        switch (event.type)
        {
        case sf::Event::Closed:
            m_pCassouletEngine->Quit();
            break;

        case sf::Event::KeyPressed:
            m_pCassouletEngine->KeyPressed();
            break;
        case sf::Event::MouseMoved:
           m_pCassouletEngine->GetCam()->ProcessMouseMovement(event.mouseMove.x, event.mouseMove.y);
            break;
            
        case sf::Event::MouseWheelScrolled:
            m_pCassouletEngine->GetCam()->ProcessMouseScroll(event.mouseWheelScroll.delta);
            break;
        case sf::Event::KeyReleased:
            m_pCassouletEngine->KeyReleased();
            break;
        case sf::Event::Resized:
            m_pCassouletEngine->UpdateResize();
            break;
        case sf::Event::MouseButtonReleased:
            m_pCassouletEngine->KeyReleasedMouseInput();
        }
    }

    m_pCassouletEngine->UpdateKeyStatus();
}

void Game::Render()
{
    //Game objects to draw themselves
    m_pCassouletEngine->Render();
}

void Game::Update()
{
    m_pCassouletEngine->Update();
}

bool Game::IsOver()
{
    return m_pCassouletEngine->IsOver();
}


