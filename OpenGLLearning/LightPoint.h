#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightPoint
{
public:
	LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();
	glm::vec3 position;		//����ƽ�й�Դ��û�����壬��Ҫ���ڵ��Դ�;۹�Դ
	glm::vec3 angles;		//��תŷ����
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);	//��ת��Ĺ�������
	glm::vec3 color;

	//˥��ϵ��������ĸ�еģ������һ���1����һ���������
	float constant;
	float linear;
	float quadratic;
};