#include <CassouletEngineLibrarie/OpenGL/Camera.h>
#include <CassouletEngineLibrarie/System/GameObject.h>

void Camera::Draw()
{
	//if this is not the active camera return
	//if (scene->activeCamera != this)
	//	return;


	////set viewport perspective
	glMatrixMode(GL_PROJECTION_MATRIX);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	const GLfloat ratio = static_cast<float>(m_sizeX) / static_cast<float>(m_sizeY);
	glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
	

	glMatrixMode(GL_MODELVIEW_MATRIX);

	//clear and set background color
	glClearColor(0.1f, 0.1f,0.1f,0.1f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//set rotation
	glRotatef(-gameObject->transform.rotation.x, 1, 0, 0);
	glRotatef(-gameObject->transform.rotation.y, 0, 1, 0);
	glRotatef(-gameObject->transform.rotation.z, 0, 0, 1);

	//set position
	//we flip the x and y position because everything else is relative to the camera
	//if we want the camera to look down on a cube with a y value of 5, what we actually want to do is move everything else doww 5 on y
	//we don't do this for z because we want +1 to go forward (into your screen). OpenGL does the reverse. so we don't flip z to flip it.
	glTranslatef(-gameObject->transform.position.x, -gameObject->transform.position.y, gameObject->transform.position.z);
}

void Camera::SetWindowSize(int x,int y)
{
	m_sizeX = x;
	m_sizeY = y;
}
