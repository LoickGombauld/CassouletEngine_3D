#include <CassouletEngineLibrarie/System/Libs.h>


	float Vector3F_length(Vec3& v) { 
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	float Vector2F_length(Vec2& v) {
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	Vec3 vec3_normalize(Vec3& v) {
		float l = Vector3F_length(v);

		return Vec3{ v.x / l, v.y / l, v.z / l };
	}

	Vec2 vec2_normalize(Vec2& v) {
		float l = Vector2F_length(v);

		return Vec2{ v.x / l, v.y / l };
	}

