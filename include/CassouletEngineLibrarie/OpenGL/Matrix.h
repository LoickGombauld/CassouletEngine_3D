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

	Vec3 axis_normalized = vec3_normalize(axis);
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
