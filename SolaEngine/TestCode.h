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
//
//#pragma comment(lib, "glew32.lib")
//#pragma comment(lib, "freeglut.lib")
//
//#include <stdio.h>
//#include <gl/glew.h>
//#include <gl/glut.h>
//
//
//int windowWidth = 0;
//int windowHeight = 0;
//
//const int TexWidth = 512;
//const int TexHeight = 512;
//
//bool leftMouseDown = false;
//float mouseX, mouseY;
//float cameraAngleX, cameraAngleY;
//float xRot, yRot;
//
//GLuint textureID;
//GLuint frameBufferID;
//GLuint renderBufferID;
//
//void drawCube()
//{
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glColor4f(1, 1, 1, 1);
//
//	glBegin(GL_QUADS);
//	//Front
//	glNormal3d(0, 0, 1);
//	glVertex3d(-1, -1, 1);   glTexCoord2d(0, 0);
//	glVertex3d(1, -1, 1);   glTexCoord2d(1, 0);
//	glVertex3d(1, 1, 1);    glTexCoord2d(1, 1);
//	glVertex3d(-1, 1, 1);   glTexCoord2d(0, 1);
//
//	//Back
//	glNormal3d(0, 0, -1);
//	glVertex3d(1, -1, -1); glTexCoord2d(0, 0);
//	glVertex3d(-1, -1, -1); glTexCoord2d(1, 0);
//	glVertex3d(-1, 1, -1);  glTexCoord2d(1, 1);
//	glVertex3d(1, 1, -1);   glTexCoord2d(0, 1);
//
//	//Left
//	glNormal3d(-1, 0, 0);
//	glVertex3d(-1, -1, -1); glTexCoord2d(0, 0);
//	glVertex3d(-1, -1, 1);  glTexCoord2d(1, 0);
//	glVertex3d(-1, 1, 1);   glTexCoord2d(1, 1);
//	glVertex3d(-1, 1, -1);  glTexCoord2d(0, 1);
//
//	//Right
//	glNormal3d(1, 0, 0);
//	glVertex3d(1, -1, 1);   glTexCoord2d(0, 0);
//	glVertex3d(1, -1, -1);  glTexCoord2d(1, 0);
//	glVertex3d(1, 1, -1);   glTexCoord2d(1, 1);
//	glVertex3d(1, 1, 1);    glTexCoord2d(0, 1);
//
//	//Top
//	glNormal3d(0, 1, 0);
//	glVertex3d(-1, 1, 1);   glTexCoord2d(0, 0);
//	glVertex3d(1, 1, 1);    glTexCoord2d(1, 0);
//	glVertex3d(1, 1, -1);   glTexCoord2d(1, 1);
//	glVertex3d(-1, 1, -1);  glTexCoord2d(0, 1);
//
//	//Bottom
//	glNormal3d(0, -1, 0);
//	glVertex3d(1, -1, 1);   glTexCoord2d(0, 0);
//	glVertex3d(-1, -1, 1);  glTexCoord2d(1, 0);
//	glVertex3d(-1, -1, -1); glTexCoord2d(1, 1);
//	glVertex3d(1, -1, -1);  glTexCoord2d(0, 1);
//
//	glEnd();
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//
//void ChangeSize(int w, int h)
//{
//	windowWidth = w;
//	windowHeight = h;
//
//	if (h == 0)
//		h = 1;
//}
//
//void SetupRC()
//{
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TexWidth, TexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	glGenRenderbuffers(1, &renderBufferID);
//	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, TexWidth, TexHeight);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
//	glGenFramebuffers(1, &frameBufferID);
//	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferID);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//	if (status != GL_FRAMEBUFFER_COMPLETE)
//	{
//		fprintf(stderr, "GLEW Error: %s\n", "FRAME BUFFER STATUS Error!");
//		return;
//	}
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_TEXTURE_2D);
//}
//
//void RenderScene(void)
//{
//	//������Ⱦ��������ӿں�ͶӰ����
//	glViewport(0, 0, TexWidth, TexHeight);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60.0f, (float)(TexWidth) / TexHeight, 1.0f, 100.0f);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	//��Ⱦ������
//	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
//	glClearColor(1, 1, 1, 1);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glColor3f(1, 0, 1);
//	glPushMatrix();
//	glTranslated(0, 0.0, -5);
//	glRotated(xRot, 1, 0, 0);
//	glRotated(yRot, 0, 1, 0);
//	glutSolidTeapot(1.0);
//	glPopMatrix();
//
//	//�л�������ϵͳ��֡������
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glViewport(0, 0, windowWidth, windowHeight);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60.0f, (float)(windowWidth) / windowHeight, 1.0f, 100.0f);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glClearColor(0, 0, 0, 0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glTranslated(0, 0, -5);
//	glRotated(cameraAngleY*0.5, 1, 0, 0);
//	glRotated(cameraAngleX*0.5, 0, 1, 0);
//	glColor3d(1.0, 1.0, 1.0);
//	drawCube();
//	glutSwapBuffers();
//}
////
////
////void MouseFuncCB(int button, int state, int x, int y)
////{
////	mouseX = x;
////	mouseY = y;
////
////	if (button == GLUT_LEFT_BUTTON)
////	{
////		if (state == GLUT_DOWN)
////		{
////			leftMouseDown = true;
////		}
////		else if (state == GLUT_UP)
////		{
////			leftMouseDown = false;
////		}
////	}
////
////}
////
////
////void MouseMotionFuncCB(int x, int y)
////{
////	if (leftMouseDown)
////	{
////		cameraAngleX += (x - mouseX);
////		cameraAngleY += (y - mouseY);
////
////		mouseX = x;
////		mouseY = y;
////	}
////
////	glutPostRedisplay();
////}
////
////
//void TimerFuncCB(int value)
//{
//	xRot += 2;
//	yRot += 3;
//	glutPostRedisplay();
//	glutTimerFunc(33, TimerFuncCB, 1);
//}
////
////
////int main(int argc, char* argv[])
////{
////	glutInit(&argc, argv);
////	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
////	glutInitWindowSize(800, 600);
////	glutCreateWindow("OpenGL");
////	glutReshapeFunc(ChangeSize);
////	glutDisplayFunc(RenderScene);
////	glutMouseFunc(MouseFuncCB);
////	glutMotionFunc(MouseMotionFuncCB);
////	glutTimerFunc(33, TimerFuncCB, 1);
////
////	GLenum err = glewInit();
////	if (GLEW_OK != err) {
////		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
////		return 1;
////	}
////
////	SetupRC();
////
////	glutMainLoop();
////	return 0;
////}