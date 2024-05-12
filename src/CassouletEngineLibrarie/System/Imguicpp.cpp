#include <CassouletEngineLibrarie/Math/Vector3.h>
#include <CassouletEngineLibrarie/Math/Vector2.h>
#include <CassouletEngineLibrarie/System/Imguicpp.h>


void IMGUICPP::DrawVector3Windowf(Vector3& vec, const std::string& title)
{
	DrawVector3Windowf(vec.x, vec.y, vec.z, title);
}

void IMGUICPP::DrawVector2Windowf(Vector2& vec, const std::string& title)
{
	DrawVector2Windowf(vec.x, vec.y, title);
}
