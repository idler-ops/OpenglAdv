#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightDirectional
{
public:
	LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	LightDirectional(bool giveDirection, glm::vec3 _position, glm::vec3 _direction, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	void UpdateDirection();
	~LightDirectional();
	glm::vec3 position;		//����ƽ�й�Դ��û�����壬��Ҫ���ڵ��Դ�;۹�Դ
	glm::vec3 angles;		//��תŷ����
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);	//��ת��Ĺ�������
	glm::vec3 color;
};