#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>
#include <CassouletEngineLibrarie/Doom/DataTypes.h>
#include <CassouletEngineLibrarie/Doom/Angle.h>
#include <CassouletEngineLibrarie/Doom/Things.h>
#include <CassouletEngineLibrarie/Doom/Map.h>
#include <CassouletEngineLibrarie/System/ViewRender.h>

class CASSOULET_DLL Player
{
public:
    Player(ViewRender* pViewRenderer, int iID);
    ~Player();

    void Init(Thing thing);
    void SetXPosition(int XPosition);
    void SetYPosition(int YPosition);
    void SetZPosition(int ZPosition);
    void SetAngle(int Angle);
    void MoveForward();
    void MoveLeftward();
    void RotateLeft();
    void RotateRight();
    void Fly();
    void Sink();
    void Think(int iSubSectorHieght);
    void Render();

    int GetID();
    int GetXPosition();
    int GetYPosition();
    int GetZPosition();
    int GetFOV();

    bool ClipVertexesInFOV(Vertex& V1, Vertex& V2, Angle& V1Angle, Angle& V2Angle, Angle& V1AngleFromPlayer, Angle& V2AngleFromPlayer);

    // Calulate the distance between the player an the vertex.
    float DistanceToPoint(Vertex& V);

    Angle AngleToVertex(Vertex& vertex);
    Angle GetAngle();

protected:
    int m_iPlayerID;
    int m_XPosition;
    int m_YPosition;
    int m_ZPosition;
    int m_EyeLevel;
    int m_FOV;
    int m_iRotationSpeed;
    int m_iMoveSpeed;

    Angle m_Angle;
    Angle m_HalfFOV;
    ViewRender* m_pViewRender;
};
