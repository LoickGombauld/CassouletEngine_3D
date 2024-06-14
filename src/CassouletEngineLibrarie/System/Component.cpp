#include <CassouletEngineLibrarie/System/Component.h>
#include <CassouletEngineLibrarie/System/GameObject.h>

void Component::V_Update()
{
	if (enabled)
		Update();
}

void Component::V_Draw()
{
	if (enabled)
		Draw();
}

