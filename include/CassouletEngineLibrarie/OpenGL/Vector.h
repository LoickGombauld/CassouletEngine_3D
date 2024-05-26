#include <CassouletEngineLibrarie/System/Libs.h>

Vec3 Vec3_add(Vec3 a, Vec3 b) {
	return Vec3 ( a.x + b.x, a.y + b.y, a.z + b.z );
}

Vec3 Vec3_sub(Vec3 a, Vec3 b) {
	return Vec3 (a.x - b.x, a.y - b.y, a.z - b.z );
}

Vec3 Vec3_scale(Vec3 v, float s) {
	return Vec3 ( v.x* s, v.y* s, v.z* s );
}

	float Vector3F_length(Vec3& v) { 
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	float Vector2F_length(Vec2& v) {
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	Vec3 Vec3_normalize(Vec3& v) {
		float l = Vector3F_length(v);

		return Vec3{ v.x / l, v.y / l, v.z / l };
	}

	Vec2 Vec2_normalize(Vec2& v) {
		float l = Vector2F_length(v);

		return Vec2{ v.x / l, v.y / l };
	}

	float Vec3_dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

	Vec3 Vec3_cross(Vec3 a, Vec3 b) {
		return Vec3 (
			a.y* b.z - a.z * b.y,
				a.z* b.x - a.x * b.z,
				a.x* b.y - a.y * b.x);
	}

	double Rad2Deg(double radian)
	{
		return(radian * (180 / PI));
	};

	double Deg2Rad(double degree)
	{
		return (degree * (PI / 180));

	};
