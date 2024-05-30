#include <CassouletEngineLibrarie/System/CassouletEngine.h>
#include <CassouletEngineLibrarie/System/ViewRender.h>
#include <CassouletEngineLibrarie/Doom/AssetsManager.h>
#include <CassouletEngineLibrarie/Doom/Map.h>
#include <CassouletEngineLibrarie/Doom/Player.h>
#include <CassouletEngineLibrarie/Doom/Things.h>
#include <CassouletEngineLibrarie/Math/Vector2.h>
#include <CassouletEngineLibrarie/System/GameObject.h>
#include <CassouletEngineLibrarie/OpenGL/glDebug.h>
#include <CassouletEngineLibrarie/OpenGL/FreeCamera.h>



CassouletEngine::CassouletEngine() : m_sAppName("CassouletMood Engine 2 : insérer un citation stylée"), m_bIsOver(false), m_iRenderWidth(1280), m_iRenderHeight(900), m_pMap(nullptr), m_pPlayer(nullptr)
{
}
CassouletEngine::~CassouletEngine()
{
}

bool CassouletEngine::Init()
{
	sf::ContextSettings settings ;
	m_window.create(sf::VideoMode(m_iRenderWidth, m_iRenderHeight), m_sAppName, sf::Style::Default,settings);
	settings.majorVersion = 4;
	settings.minorVersion = 6;
	std::cout << "OpenGL version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	m_window.setActive(true);
	if (glewInit() != GLEW_OK)
	{
		return false;
	}
	//glEnable(GL_DEBUG_OUTPUT);
	//glDebugMessageCallback(glDebugOutput, nullptr);
	//glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	ImGui::SFML::Init(m_window);
	m_window.setFramerateLimit(144);

	// Load WAD 
	LoadWAD();
	AssetsManager::GetInstance()->Init(&m_WADLoader);

	// Delay object creation to this point so renderer is inistilized correctly
	m_pViewRender = std::unique_ptr<ViewRender>(new ViewRender());
	m_pThings = std::unique_ptr<Things>(new Things());
	m_pPlayer = std::unique_ptr<Player>(new Player(m_pViewRender.get(), 1));
	m_pMap = std::unique_ptr<Map>(new Map(m_pViewRender.get(), "E1M1", m_pPlayer.get(), m_pThings.get()));

	ReadDataFromWAD();

	m_pPlayer->Init((m_pMap->GetThings())->GetThingByID(m_pPlayer->GetID()));
	m_pMap->Init();
	m_pViewRender->GLInit(m_iRenderWidth, m_iRenderHeight);

	return true;
}

void CassouletEngine::LoadWAD()
{
	m_WADLoader.SetWADFilePath(GetWADFileName());
	m_WADLoader.LoadWADToMemory();
}

std::string CassouletEngine::GetWADFileName()
{

	return std::filesystem::path("Resources/Map/DOOM1.WAD").string();
}

void CassouletEngine::Render()
{
	m_pViewRender->Clear();
	m_pViewRender->UIRender();
	m_pViewRender->Render(m_window);
	m_pMap->Render3DTest();
	ImGui::SFML::Render(m_window);
	m_window.display();

	//m_pDisplayManager->InitFrame();
	//m_pViewRender->Render( m_iRenderWidth);
	//m_pPlayer->Render( m_iRenderWidth);
	//m_pDisplayManager->Render();
}

void CassouletEngine::KeyReleasedMouseInput()
{
	m_firstMouse = true;
}

void CassouletEngine::MouseMovedInput() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		ProcessMouseMovement(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	}
}

FreeCamera* CassouletEngine::GetCam() {return m_pViewRender->f_Cam; };

void CassouletEngine::KeyPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		Quit();
	m_pViewRender->UpdateCameraMovement(m_dt.asSeconds());
}

void CassouletEngine::UpdateKeyStatus()
{
	//m_pPlayer->UpdateInput(KeyStates,m_iRenderWidth,m_iRenderHeight );

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_pPlayer->MoveForward();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_pPlayer->MoveLeftward();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_pPlayer->RotateLeft();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_pPlayer->RotateRight();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		m_pPlayer->Fly();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		m_pPlayer->Sink();
	}

}


void CassouletEngine::KeyReleased()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		//m_bRenderAutoMap = false;
	}
}

void CassouletEngine::ProcessMouseMovement(float xPos, float yPos) {
	if (m_firstMouse) {
		m_lastX = xPos;
		m_lastY = yPos;
		m_firstMouse = false;
	}

	float xOffset = xPos - m_lastX;
	float yOffset = m_lastY - yPos; // Inverse car l'origine de l'écran est en haut à gauche
	m_lastX = xPos;
	m_lastY = yPos;

	xOffset *= m_pViewRender->m_cameraSensitivity;
	yOffset *= m_pViewRender->m_cameraSensitivity;

	//m_pViewRender->m_objCam->transform.rotation.y += xOffset * m_dt.asSeconds();
	//m_pViewRender->m_objCam->transform.rotation.x -= yOffset * m_dt.asSeconds();


	//// Limiter l'angle de tangage entre -89° et 89° pour éviter les erreurs de calcul
	//if (m_pViewRender->m_objCam->transform.rotation.x > 89.0f)
	//	m_pViewRender->m_objCam->transform.rotation.x = 89.0f;
	//if (m_pViewRender->m_objCam->transform.rotation.x < -89.0f)
	//	m_pViewRender->m_objCam->transform.rotation.x = -89.0f;
}


Vector2 CassouletEngine::MouseMoveDir() const {
	Vector2 mousePos = Vector2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	Vector2 mouseDir = Vector2(m_lastX, m_lastY);
	return mousePos - mouseDir;
}


void  CassouletEngine::Quit()
{
	m_bIsOver = true;
	ImGui::SFML::Shutdown();
}

void CassouletEngine::Update()
{
	// m_pPlayer->Think(m_pMap->GetPlayerSubSectorHeight());
	m_dt = GameClock.restart();
	m_pViewRender->Update();
	ImGui::SFML::Update(m_window, sf::seconds(1 / 144));
}

void CassouletEngine::UpdateResize()
{
	m_iRenderWidth = m_window.getSize().x;
	m_iRenderHeight = m_window.getSize().y;
	m_pViewRender->UpdateResize(m_iRenderWidth, m_iRenderHeight);
}

bool CassouletEngine::IsOver()
{
	return m_bIsOver;
}

int CassouletEngine::GetRenderWidth()
{
	return m_iRenderWidth;
}

int CassouletEngine::GetRenderHeight()
{
	return m_iRenderHeight;
}

std::string CassouletEngine::GetAppName()
{
	return m_sAppName;
}

sf::RenderWindow& CassouletEngine::GetWindow()
{
	return m_window;
}

void CassouletEngine::ReadDataFromWAD()
{
	m_WADLoader.LoadPalette(m_palettes);
	m_WADLoader.LoadMapData(m_pMap.get());
}
