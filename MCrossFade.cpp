#include "MCrossFade.h"

MCrossFade::MCrossFade()
{
	// set active to false
	m_active = false;
}


MCrossFade::~MCrossFade()
{
}

void MCrossFade::Activate()
{
	// set active to true
	m_active = true;
	// set frame and time to 0
	m_frame = 0;
	m_elapsedTime = 0;
	// Total frames to 30
	m_totalFrames = 30;
}


void MCrossFade::Update(float dt)
{
	// if active is false do nothing
	if (m_active == false)
		return;

	float frameTime = 1.0f / 30.0f;  // 30 frames per second

	// Add time from last loop to elapsed time
	m_elapsedTime += dt;

	// if elapsed time is grater than fram time add 1to frame
	if (m_elapsedTime > frameTime) {
		m_frame++;
		// if frame is equal to total frames then reset
		if (m_frame >= m_totalFrames) {
			m_frame = 0;
			m_active = false;
		}
		// elapsed time equals itself minus frametime
		m_elapsedTime -= frameTime;
	}
}

void MCrossFade::SetOrthographicProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();


	glGetIntegerv(GL_VIEWPORT, m_viewport);
	int w = m_viewport[2];
	int h = m_viewport[3];

	
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);
	glTranslatef(0, (float) -h, 0);
	glMatrixMode(GL_MODELVIEW);
}

void MCrossFade::RestorePerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void MCrossFade::Render(float red, float green, float blue)
{

	if (m_active == false)
		return;

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	SetOrthographicProjection();
	glLoadIdentity();

	float w = (float) m_viewport[2];
	float h = (float) m_viewport[3];


	// Have the alpha start at 0.5 and go to 0
	float alpha =  0.5f - 0.5f * (float) m_frame / (float) m_totalFrames;

	// Render full screen quad
	glColor4f(red, green, blue, alpha);
	glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(0, h, 0);
		glVertex3f(w, h, 0);
		glVertex3f(w, 0, 0);
	glEnd();

	 

	RestorePerspectiveProjection();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}
