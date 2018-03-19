#include "managers\SLTextureManager.h"
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

void testCodeInit(){
}

void testCode(){
	SLTextureManager* tMgr = SLTextureManager::getInstance();
	SLTexture* t = tMgr->addTexture("c:\\1.png");
	t->use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLE_STRIP);
	glColor4f(1, 0, 0, 0.5);
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);

	glTexCoord2f(1, 0);
	glVertex2f(0.5, 0);

	glTexCoord2f(0, 1);
	glVertex2f(0, 0.5);

	glTexCoord2f(1, 1);
	glVertex2f(0.5, 0.5);

	glEnd();
	//glutPostRedisplay();
}


//̫������ ԭ��gl����=========
#define GL_PI 3.1415f    
GLfloat fMoonRot = 0.0f;
//������ת�Ƕ� 
GLfloat fEarthRot = 0.0f;
//������ת�Ƕ� 
GLfloat angle = 0.0f;
void renderSunEarthChangeSize(int w, int h){
	GLfloat fAspect;
	if (h == 0)   h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  //͸��ͶӰ   
	gluPerspective(60.0f, fAspect, 1.0f, 400.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void renderSunEarth(){
	glEnable(GL_DEPTH_TEST); //������Ȳ���  
	glEnable(GL_CULL_FACE);  //����ѡ��  
	glFrontFace(GL_CCW);  //͸�ӹ���
	glUseProgram(0);

	//����������������ת�Ƕ�   
	GLfloat lightPos[] = { -50.0f, 50.0f, 100.0f, 1.0f };
	//���ģʽ   
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);  glPushMatrix();
	//��̫��   
	glTranslatef(0.0f, 0.0f, -150.0f);
	//̫����ɫΪ��ɫ 
	glColor3ub(255, 0, 0);
	//�رչ���   
	glDisable(GL_LIGHTING);
	//��һ��ʵ����   
	glutSolidSphere(15.0f, 15, 15);
	//�򿪹���   
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	//������   
	glRotatef(fEarthRot, cos(angle + (GL_PI) / 2), sin(angle + GL_PI / 2), 0.0f);
	//  
	glColor3ub(0, 0, 255);
	//��x,y,z�����ƶ��ķ���   
	glTranslatef(50.0f*cos(angle), 100.0f*sin(angle), 0.0f);

	//���Ƶ����С   
	glutSolidSphere(15.0f, 15, 15);
	glColor3ub(0, 255, 0);
	//������   
	//��ĳ��������תһ���Ƕȣ�angle��x,y,z��  
	glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);
	//������ת�Ƕ�����  
	fMoonRot += 0.1f;
	//����������С   
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();
	//���ӵ������ת�Ƕ�  
	fEarthRot += 0.1f;
	//ˢ�»�ͼ   
	//glutSwapBuffers();
	glDisable(GL_DEPTH_TEST); //������Ȳ���  
	glDisable(GL_CULL_FACE);  //����ѡ��  
	glutSwapBuffers();
	glutPostRedisplay();
}
//=========