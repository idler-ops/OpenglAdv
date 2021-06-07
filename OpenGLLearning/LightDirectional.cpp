/*
LightDirectional��
ƽ�й�Դ����Դλ�������壬ֻ��Ҫע�ⷽ�򣨳�ʼ��ʱ��������ת��ȷ��������ɫ����˥��
*/

#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position),
	angles(_angles),
	color(_color)
{
	UpdateDirection();
}

LightDirectional::LightDirectional(bool giveDirection, glm::vec3 _position, glm::vec3 _direction, glm::vec3 _color) :
	position(_position),
	direction(_direction),
	color(_color)
{
	direction = glm::normalize(direction);
}

void LightDirectional::UpdateDirection() {
	direction = glm::vec3(0.0f, 0.0f, 1.0f);	// pointing to z (forward)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;	//shader����Ҫ֪�����Ǵ�ԭ������ķ��򣨷�����
}

LightDirectional::~LightDirectional() {}