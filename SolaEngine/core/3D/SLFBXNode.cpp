/**
	create by hy 20171213
	*/
#include "SLFBXNode.h"

void SLFBXNode::load()
{
	//bones[0].SetBone(nullptr, 4.5f);
	//bones[1].SetBone(&bones[0], 4.5f);

	///** �󶨵������ϵ�Ƥ���������� */
	//modelPoints[0].SetVertex(Vec4(-1.0f, 0.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	0, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1);
	//modelPoints[1].SetVertex(Vec4(1.0f, 0.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	0, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1);
	//modelPoints[2].SetVertex(Vec4(1.0f, 3.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 2);
	//modelPoints[3].SetVertex(Vec4(-1.0f, 3.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 2);

	//modelPoints[4].SetVertex(Vec4(-1.0f, 3.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);
	//modelPoints[5].SetVertex(Vec4(1.0f, 3.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);
	//modelPoints[6].SetVertex(Vec4(1.0f, 6.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);
	//modelPoints[7].SetVertex(Vec4(-1.0f, 6.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);

	//modelPoints[8].SetVertex(Vec4(-1.0f, 6.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2);
	//modelPoints[9].SetVertex(Vec4(1.0f, 6.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2);
	//modelPoints[10].SetVertex(Vec4(1.0f, 9.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	1, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1);
	//modelPoints[11].SetVertex(Vec4(-1.0f, 9.0f, 0.0f), Vec4(0.0f, 0.0f, 1.0),
	//	1, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0, 0.0f, 0.0f, 1.0f, 1);

}

void SLFBXNode::onDraw(GLMatrixStack &mvStack, GLGeometryTransform &transformPipeline)
{
	updateBones();

	//glUseProgram(0);
	//Mat4 mat;
	///** ��Ⱦ�����еĶ��㣬������Ƥ�� */
	//for (int j = 0; j < MAX_MESHES; j++)
	//{
	//	glBegin(GL_QUADS);

	//	for (int i = 0; i < MAX_MESH_POINTS; i++)
	//	{
	//		///��ö���ָ��
	//		auto thisVertex = &modelPoints[i + j * MAX_MESH_POINTS];

	//		///����Ȩֵ���㶥��
	//		Vec4 pos = Vec4(0.0, 0.0, 0.0, 0.0);
	//		Vec4 normal = Vec4(0.0, 0.0, 0.0);

	//		for (int i2 = 0; i2 < thisVertex->numBones; i2++)
	//		{
	//			mat = bones[thisVertex->boneIndex[i2]].worldTransform;

	//			///��Ȩ�����Զ���λ�úͷ��ߵ�Ӱ��
	//			pos += (mat*thisVertex->pos * thisVertex->weights[i2]);
	//			normal += (mat*thisVertex->normal *thisVertex->weights[i2]);
	//		}

	//		///��Ⱦ�ö���
	//		glColor4f(thisVertex->r, thisVertex->g, thisVertex->b, thisVertex->a);
	//		glNormal3f(normal.x, normal.y, normal.z);
	//		glVertex3f(pos.x, pos.y, pos.z);
	//	}

	//	glEnd();
	//}
}

void SLFBXNode::updateBones()
{
	/** ���ڱ�����ת��ƽ�ƾ��� */
	//Mat4 transpose, rotTemp1, rotTemp2, tempRelative;

	///** ѭ�����¹��� */
	//for (int i = 0; i < MAX_BONES; i++)
	//{
	//	///����Ƿ��Ǹ�����
	//	if (bones[i].parent == nullptr)
	//	{
	//		/** ���ñ任���� */
	//		bones[i].localTransform.translate(0,0,0);
	//		bones[i].worldTransform = this->getNtwTransform();

	//		/** ��ֵ��Ϊ����ʾ���� */
	//		displayBones[i] = bones[i].localTransform;
	//	}
	//	else
	//	{
	//		auto parent = &bones[bones[i].parent->index];
	//		auto thisBone = &bones[i];

	//		thisBone->localTransform.setIdentity();

	//		/** �ƶ��ù�������������(�Ƹ�����ת) */

	//		thisBone->localTransform.translate(0, parent->length * i, 0);

	//		/** ���������ת */
	//		//rotTemp1.Rotate(xRotation, 0, 1, 0);
	//		//rotTemp2.Rotate(yRotation, 0, 0, 1);

	//		/** ������Ա任���󣬲���ת */
	//		tempRelative = thisBone->localTransform;
	//		//tempRelative.inverseTranslate();

	//		/** ����任��Ϊ����ʾ���� */
	//		displayBones[i] = parent->worldTransform * thisBone->localTransform;
	//			//*(rotTemp1 * rotTemp2);

	//		/** ������Ա任���� */
	//	//	bones[i].relative = bones[i].relative * (rotTemp1 * rotTemp2) * tempRelative;

	//		/** ������Ա任���� */
	//		thisBone->worldTransform = parent->worldTransform * thisBone->localTransform;
	//	}
	//}
}