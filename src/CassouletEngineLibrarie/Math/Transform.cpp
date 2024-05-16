
#include <CassouletEngineLibrarie/Math/Transform.h>

void Transform::Translate(Vector3 translation)
{
	position += translation;
}

Vector3 Transform::RotateTransform(Vector3 axis, float angle) {

	// Normalisation de l'axe de rotation
	float length = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	float x = axis.x / length;
	float y = axis.y / length;
	float z = axis.z / length;

	// Calcul des composantes de l'angle
	float c = std::cos(angle);
	float s = std::sin(angle);
	float t = 1.0f - c;

	// Calcul des nouvelles coordonnées du vecteur après rotation
	Vector3 result;
	result.x = (t * x * x + c) * rotation.x + (t * x * y - s * z) * rotation.y + (t * x * z + s * y) * rotation.z;
	result.y = (t * x * y + s * z) * rotation.x + (t * y * y + c) * rotation.y + (t * y * z - s * x) * rotation.z;
	result.z = (t * x * z - s * y) * rotation.x + (t * y * z + s * x) * rotation.y + (t * z * z + c) * rotation.z;

	return result;
}

Vector3 Transform::Up()
{
	return Vector3(0, 1, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}
Vector3 Transform::Down()
{
	return Vector3(0, -1, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}
Vector3 Transform::Right()
{
	return Vector3(1, 0, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}
Vector3 Transform::Left()
{
	return Vector3(-1, 0, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}
Vector3 Transform::Forward()
{
	return Vector3(0, 0, 1).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}
Vector3 Transform::Back()
{
	return Vector3(0, 0, -1).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}

