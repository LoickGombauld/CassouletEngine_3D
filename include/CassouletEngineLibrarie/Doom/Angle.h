#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>


class CASSOULET_DLL Angle
{
public:
    Angle();
    Angle(float angle);
    ~Angle();

    Angle operator=(const float& rhs);
    Angle operator+(const Angle& rhs);
    Angle operator-(const Angle& rhs);
    Angle operator-();
    Angle& operator+=(const float& rhs);
    Angle& operator-=(const float& rhs);

    bool operator<(const Angle& rhs);
    bool operator<(const float& rhs);
    bool operator<=(const Angle& rhs);
    bool operator<=(const float& rhs);
    bool operator>(const Angle& rhs);
    bool operator>(const float& rhs);
    bool operator>=(const Angle& rhs);
    bool operator>=(const float& rhs);

    float GetValue();
    float GetCosValue();
    float GetSinValue();
    float GetTanValue();
    float GetSignedValue();
protected:
    float m_Angle;

    void Normalize360();
};