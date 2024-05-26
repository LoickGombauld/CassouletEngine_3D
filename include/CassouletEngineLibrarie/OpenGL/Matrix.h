#pragma once

#include <CassouletEngineLibrarie/OpenGL/Vector.h>

Mat4 mat4_identity() {

	float array[16];
	array[0] = 1.0f; array[4] = 0.0f; array[8] = 0.0f; array[12] = 0.0f;
	array[1] = 0.0f; array[5] = 1.0f; array[9] = 0.0f; array[13] = 0.0f;
	array[2] = 0.0f; array[6] = 0.0f; array[10] = 1.0f; array[14] = 0.0f;
	array[3] = 0.0f; array[7] = 0.0f; array[11] = 0.0f; array[15] = 1.0f;
	return Mat4(array);
}

Mat4 calcLookAtMatrix(Vec3 eye, Vec3 center, Vec3 up) {

	Vec3 f = Vec3(center.x - eye.x, center.y - eye.y, center.z - eye.z);
	float lenF = sqrt(f.x * f.x + f.y * f.y + f.z * f.z);
	f.x /= lenF;
	f.y /= lenF;
	f.z /= lenF;

	Vec3 s = Vec3(
		f.y * up.z - f.z * up.y,
		f.z * up.x - f.x * up.z,
		f.x * up.y - f.y * up.x
	);
	float lenS = sqrt(s.x * s.x + s.y * s.y + s.z * s.z);
	s.x /= lenS;
	s.y /= lenS;
	s.z /= lenS;

	Vec3 u = Vec3(
		s.y * f.z - s.z * f.y,
		s.z * f.x - s.x * f.z,
		s.x * f.y - s.y * f.x
	);

	float* result;
	result[0] = s.x;
	result[1] = u.x;
	result[2] = -f.x;
	result[3] = 0.0f;

	result[4] = s.y;
	result[5] = u.y;
	result[6] = -f.y;
	result[7] = 0.0f;

	result[8] = s.z;
	result[9] = u.z;
	result[10] = -f.z;
	result[11] = 0.0f;

	result[12] = -s.x * eye.x - s.y * eye.y - s.z * eye.z;
	result[13] = -u.x * eye.x - u.y * eye.y - u.z * eye.z;
	result[14] = f.x * eye.x + f.y * eye.y + f.z * eye.z;
	result[15] = 1.0f;

	return Mat4(result);
}

Mat4 mat4_mul(Mat4 m1, Mat4 m2) {
	float array[16];
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++) {
			array[x * y] = m1.array[x * y] * m2.array[x * y];
		}

	}
	return Mat4(array);
}

Mat4 mat4_translate(Vec3 translation) {
	Mat4 mat = mat4_identity();

	mat.array[12] = translation.x;
	mat.array[13] = translation.y;
	mat.array[14] = translation.z;

	return mat;
}

Mat4 mat4_scale(Vec3 scale) {
	float array[16]{
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
	};
	array[0] = scale.x;
	array[5] = scale.y;
	array[10] = scale.z;
	array[15] = 1.f;
	return Mat4(array);
}

Mat4 mat4_rotate(Vec3 axis, float angle) {
	float c = cosf(angle);
	float s = sinf(angle);
	float t = 1.f - c;

	Vec3 axis_normalized = Vec3_normalize(axis);
	float  x = axis_normalized.x, y = axis_normalized.y, z = axis_normalized.z;

	float array[16]{
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
	};

	array[0] = t * x * x + c;
	array[1] = t * x * y - s * z;
	array[2] = t * x * z + s * y;
	array[3] = 0.0f;
	array[4] = t * x * y + s * z;
	array[5] = t * y * y + c;
	array[6] = t * y * z - s * x;
	array[7] = 0.0f;
	array[8] = t * x * z - s * y;
	array[9] = t * y * z + s * x;
	array[10] = t * z * z + c;
	array[11] = 0.0f;
	array[12] = 0.0f;
	array[13] = 0.0f;
	array[14] = 0.0f;
	array[15] = 1.0f;

	return Mat4(array);
};

Mat4 mat4_ortho(float left, float right, float bottom, float top, float nearp,
	float farp) {
	float array[16]{
		0,0,0,0,
		0,0,0,0,
		0,0,0,0
	};
	array[0] = 2.f / (right - left);
	array[5] = 2.f / (top - bottom);
	array[10] = -2.f / (farp - nearp);
	array[12] = -(right + left) / (right - left);
	array[13] = -(top + bottom) / (top - bottom);
	array[14] = -(farp + nearp) / (farp - nearp);
	array[15] = 1.f;

	return Mat4(array);
}

Mat4 mat4_perspective(float fov, float aspect_ratio, float p_near, float p_far) {
	float array[16]{
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
	};

	float tan_half_fov = tanf(fov / 2.0f);
	float range_inv = 1.0f / (p_near - p_far);

	array[0] = 1.0f / (aspect_ratio * tan_half_fov);
	array[5] = 1.0f / tan_half_fov;
	array[10] = (p_near + p_far) * range_inv;
	array[11] = -1.0f;
	array[15] = 2.0f * p_near * p_far * range_inv;
	array[14] = 0.0f;

	return  Mat4(array);
}