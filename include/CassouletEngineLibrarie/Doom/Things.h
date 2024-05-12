#pragma once

#include <CassouletEngineLibrarie/Doom/DataTypes.h>
#include <CassouletEngineLibrarie/System/Libs.h>

class Things
{
public:
    Things();
    ~Things();

    void AddThing(Thing& thing);
    Thing GetThingByID(int iID);
    int GetThingsSize() const;

protected:
    std::vector<Thing> m_Things;
};