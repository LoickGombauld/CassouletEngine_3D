#include <CassouletEngineLibrarie/Doom/Things.h>


Things::Things()
{
}

Things::~Things()
{
}

void Things::AddThing(Thing& thing)
{
    m_Things.push_back(thing);
}

Thing Things::GetThingByID(int iID)
{
    Thing thing;
    for (std::vector<Thing>::iterator itr = m_Things.begin(); itr != m_Things.end(); ++itr)
    {
        if (itr->Type == iID)
        {
            thing = (*itr);
            break;
        }
    }
    return thing;
}

int Things::GetThingsSize() const
{
    return m_Things.size();
}
