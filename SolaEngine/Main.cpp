#include "TestCode.h"

#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

//for stack
#include "core\render\SLMatrixStack.h"
SLMatrixStack* stack2d = new SLMatrixStack();
SLMatrixStack* stack3d = new SLMatrixStack();
//=========

#include "events/TouchEvent.h"
#include "core\misc\SLFileUtils.h"
#include <vector>
#include "Launcher.h"
#include "core/SLScene.h"
#include "managers/SLSceneManager.h"
#include "core\3D\SLNode3d.h"
#include "managers\SLCameraManager.h"

bool _isPress;
SLPoint _pressPoint;

void SetupRC()
{
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glEnable(GL_TEXTURE_2D);//�ǵÿ���֧��2d����
	GLint max;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);//��ȡ֧�����������
	printf("���֧��������%d\r\n", max);
	printf("Mat4�Ŀ��ǣ���ת�ǵ���Ȳ��ǽǶȣ�ogl���ǽǶ�\r\n");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Launcher::getInstance()->startUp();
	testCodeInit();
}

void OnMouse(int key, int isUp, int x, int y)
{
	printf("isUp is %d,x is %d,y is %d \r\n", isUp, x, y);

	SLPoint p;
	p.x = (float)x;
	//fix by hy:for unknow bug.
	//p.y = ((float)y)*1.02f;
	p.y = (float)y;
	SLPoint wp = Launcher::getInstance()->screen2wp(&p);
	printf("wp.x is %f,wp.y is %f \r\n", wp.x, wp.y);

	TouchEvent* event = TouchEvent::getInstance();
	if (isUp == 0){
		_isPress = true;
		event->dispathEvent(TouchEvent::EVENT_ON_TOUCH_BEGIN, &p);
	}
	else{
		_isPress = false;
		event->dispathEvent(TouchEvent::EVENT_ON_TOUCH_END, &p);
	}
}

void OnMouseMove(int x, int y){
	//printf("OnMouseMove,x is %d,y is %d \r\n", x, y);

	SLPoint p;
	p.x = (float)x;
	p.y = (float)y;
	SLPoint wp = Launcher::getInstance()->screen2wp(&p);
	_pressPoint = p;
	//TouchEvent* be = TouchEvent::getInstance();
	//be->dispathEvent(TouchEvent::EVENT_ON_TOUCH_MOVE, &wp);
	printf("wp.x is %f,wp.y is %f \r\n", p.x, p.y);
}

void ShutdownRC(void)
{
}

void ChangeSize(int w, int h)
{
	//renderSunEarthChangeSize(w,h);if (true){return;}
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);

	SLSize winSize;
	winSize.w = (float)w;
	winSize.h = (float)h;
	Launcher::getInstance()->setWinSize(winSize);

	stack3d->changeSize3d(10);
	stack2d->changeSize(10);
}

//#include "extends\freetype\SLFreetype.h"
void RenderScene(void)
{
	//renderSunEarth();if (true){ return; }
	Launcher::getInstance()->calculateDeltaTime();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	TouchEvent* be = TouchEvent::getInstance();
	if (_isPress){
		be->dispathEvent(TouchEvent::EVENT_ON_TOUCH_MOVE, &_pressPoint);
	}
	be->dispathEvent(TouchEvent::EVENT_ON_NODE_UPDATED, &_pressPoint);
	SLSceneManager* sMgr = SLSceneManager::getInstance();
	
	//draw 3d
	glEnable(GL_DEPTH_TEST);
	SLCameraManager::getInstance()->getMainCamera()->renderScene(*stack3d->modelViewMatrix, *stack3d->transformPipeline);
	glDisable(GL_DEPTH_TEST);
	//=====
	
	//draw 2d
	glEnable(GL_BLEND);
	SLScene* rScene = sMgr->getRunningScene();
	rScene->draw(*stack2d->modelViewMatrix, *stack2d->transformPipeline);
	glDisable(GL_BLEND);
	//=====

	glutSwapBuffers();
	glutPostRedisplay();
}

//#include "extends\freetype\SLFreetype.h"

int main(int argc, char *argv[])
{
	//testmain(argc, argv);
	//if (true)return 0;

	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(Launcher::DISPLAY_WIDTH, Launcher::DISPLAY_HEIGHT);
	glutCreateWindow(Launcher::APPLICATION_TITLE);
	glutReshapeFunc(ChangeSize);
	//glutSpecialFunc(OnKey);
	glutMouseFunc(OnMouse);
	glutMotionFunc(OnMouseMove);
	glutDisplayFunc(RenderScene);

	//glutCreateMenu(ProcessMenu);
	//glutAddMenuEntry("GL_NEAREST", 0);
	//glutAddMenuEntry("GL_LINEAR", 1);
	//glutAddMenuEntry("GL_NEAREST_MIPMAP_NEAREST", 2);
	//glutAddMenuEntry("GL_NEAREST_MIPMAP_LINEAR", 3);
	//glutAddMenuEntry("GL_LINEAR_MIPMAP_NEAREST", 4);
	//glutAddMenuEntry("GL_LINEAR_MIPMAP_LINEAR", 5);

	//glutAttachMenu(GLUT_RIGHT_BUTTON);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	SetupRC();
	glutMainLoop();
	ShutdownRC();

	return 0;
}



