#ifndef __SLFBXNode_h__
#define __SLFBXNode_h__

#include <vector>
#include <math.h>
#include <math3d.h>
#include "SLNode3d.h"
#include "SLBone.h"

using namespace std;
#define MAX_BONES                2   /**������*/
#define MAX_MESHES              3   /**��������������ͼԪ��(������ͼ���Ƥ��)*/
#define MAX_MESH_POINTS    4   /**һ�����񶥵��������ı���*/

class SLFBXNode :public SLNode3d
{
public:
	void load();
	virtual void onDraw(GLMatrixStack &mvStack, GLGeometryTransform &transformPipeline);

	Vec4 trans;                       /**< ����ƽ�ƹ���ģ�� */
	SLBone bones[MAX_BONES];            /**< ��������ṹ */
	Mat4 displayBones[MAX_BONES];     /**< ���ڻ��ƹ��� */
	//SLBoneVertex modelPoints[MAX_MESHES * MAX_MESH_POINTS]; /**< ģ�Ͷ������ݣ���Ƥ������ */

	void updateBones();
};

#endif