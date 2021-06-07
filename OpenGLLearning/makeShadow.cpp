//���ȿ��Լ�ֱ�Ӹ�ԭһ�»������ӵĹ���

#define GLEW_STATIC

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"


#pragma region Model Data

const unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;

//10�����������ԭ�������λ�ƾ��롣����ֻ�ı�position
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

float quadVertices[] = {
	// positions        // texture Coords
	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};

float cubeVertices[] = {
	// back face
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
	 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
	// front face
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
	 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
	 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
	-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	// left face
	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	// right face
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
	// bottom face
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
	 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	// top face
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
	 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
};

float planeVertices[] = {
	// positions            // normals         // texcoords
	 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
	-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

	 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
	 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 10.0f
};

//���������EBO����ʱ����
unsigned int indices[] =
{
	0, 1, 2,
	2, 3, 0
};
#pragma endregion

#pragma region Camera Declare
//��ʼ���������
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
#pragma endregion

#pragma region Light Declare
LightDirectional lightD(
	true,
	glm::vec3(-2.0f, 4.0f, -1.0f),
	glm::vec3(-2.0f, 4.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f));

LightDirectional light(
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0.0f),
	glm::vec3(1.0f, 1.0f, 1.0f));

LightPoint lightP0(
	glm::vec3(10.0f, 0.0f, 0.0f),								//���� 
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),	//�Ƕ�
	glm::vec3(1.0f, 0.0f, 0.0f));								//��ɫ

LightSpot lightS(
	glm::vec3(0.0f, 8.0f, 0.0f),
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0.0f),		//�������������
	glm::vec3(1.0f, 1.0f, 1.0f));
#pragma endregion

#pragma region Input Declare
bool shadows = true;
bool spacePressed = false;
bool firstMouse = true;		//����mouse callback
float lastX, lastY;			//��¼mouseλ�ñ仯

void processInput(GLFWwindow *window) {		//��¼�����İ����¼����Ա��������
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.speedZ = 10.0f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.speedZ = -10.0f;
	else
		camera.speedZ = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.speedX = -10.0f;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.speedX = 10.0f;
	else
		camera.speedX = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	//�³�
		camera.speedY = -10.0f;
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.speedY = 10.0f;
	else
		camera.speedY = 0.0f;

	if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && !spacePressed) {
		spacePressed = true;
//		shadows = !shadows;
		shadows = false;
	}
	else {
		spacePressed = false;
		shadows = true;
	}
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {		//��׽����ƶ�
	if (firstMouse == true) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float deltaX = xPos - lastX;
	float deltaY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;
	camera.ProcessMouseMovement(deltaX, deltaY);
}
#pragma endregion

unsigned int loadImageToGUP(const char *fileName, GLint internalFormat, GLenum format, int textureSlot) {
	//��ͼƬ����Texture buffer���󶨵�TEXTURE_2D
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);		//bindǰҪ���ƶ���λ��ʹ�ò�ͬ��buffer������ռͬһ����λ��֮�����ͨ����λ����ҵ���Ҫ��Texture(����ע�⣬ʹ�õ���0�Ų�(TEXTURE0))
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	//ͨ��stb����ͼƬ
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);		//���ص�ͼƬy����������ͨ����opengl�෴����˿���ͨ����һ���ڼ���ͼƬʱ�Զ���תy����
	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("Load image failed.\n");
	}
	stbi_image_free(data);

	return TexBuffer;
}

int main(int argc, char *argv[]) {

	std::string exePath = argv[0];

#pragma region Open A Window
	//glfw����س�ʼ������
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	//mac�ã�ǰ��������

	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lighting", nullptr, nullptr);	//���ڵ�col��row��title
	if (window == nullptr) {
		printf("Open GLFW window failed.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);	//��Ϊ������

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//����ʾ���λ��
	glfwSetCursorPosCallback(window, mouse_callback);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("Init GLEW failed.");
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);		//���ƿɻ�������
	glEnable(GL_DEPTH_TEST);		//����ʹ��z-buffer���������Ϣ
//	glDepthFunc(GL_ALWAYS);			//��Ȳ�����Զͨ��������Զֻ��Ⱦ�������������

	//���濪�����޳����ܣ����治�ᱻ����
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//����ģʽ��ֻ��������
#pragma endregion

#pragma region Init Shader
	//��ȡshader������
	Shader *myShader = new Shader("vertexShadow.vert", "fragmentShadow.frag");
	myShader->test();

	Shader *depthShader = new Shader("vertexDepth.vert", "fragmentDepth.frag");
	depthShader->test();

	Shader *debugDepthQuad = new Shader("vertexDepthDebugQuad.vert", "fragmentDepthDebugQuad.frag");
	debugDepthQuad->test();

	//newly added
	myShader->use();
	myShader->SetUniform1i("diffuseTexture", 0);
	myShader->SetUniform1i("shadowMap", 1);

#pragma endregion

#pragma region Init VAO��VBO��EBO and load data
	unsigned int cubeVAO;
	glGenVertexArrays(1, &cubeVAO);	//����1�����ص�VAO����������2����������VAO��ţ����ն��ʱ����2ӦΪ����
	glBindVertexArray(cubeVAO);
	unsigned int cubeVBO;
	glGenBuffers(1, &cubeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);		//��һ���ǽ�VBO����VAO�е�attribute pointer����λ��
	glEnableVertexAttribArray(1);	//����0�Ų�λ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	//��Ϊ������䣬�̶�VAO��0�Ų۷�������Ϣ��1�Ų۷���ɫ��Ϣ��2�Ų۷�������Ϣ��3�ŷŷ�������Ϣ��
	glBindVertexArray(0);

	unsigned int planeVAO;
	glGenVertexArrays(1, &planeVAO);
	glBindVertexArray(planeVAO);
	unsigned int planeVBO;
	glGenBuffers(1, &planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glBindVertexArray(0);

	// render a 1*1 XY quad in NDC
	unsigned int quadVAO;
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
	unsigned int quadVBO;
	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glBindVertexArray(0);
#pragma endregion

#pragma region configure depth map FBO and create depth texture

	//configure depth map FBO
	GLuint depthMapFBO;		//֡������󣬺�����ʹ����������Ӱ��
	glGenFramebuffers(1, &depthMapFBO);
	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;	//�����ͼ�ķֱ���
	
	GLuint depthMap;		//2D�����Ǵӹ���ӽ����ɵ���Ȼ��壬�ṩ��������֡����ʹ��
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	// ֻ�������ֵ����˰������ʽָ��ΪGL_DEPTH_COMPONENT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	
	// newly added
	// �ⲿ���ǽ����г��������ͼ�����������������Ϊ1.0���������������꽫��Զ������Ӱ֮��
	// ������������ͼ0��1���귶Χ����������������ܻ᷵��һ��1.0�����ֵ����ӰֵΪ0.0
	// ����һ����ȹ��Զƽ�滹Ҫԭ������ͶӰ��z�������1.0����������£�GL_CLAMP_TO_BORDER���Ʒ�ʽ��������
	// ���������Fragment Shader�н��
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// �����ɵ����������Ϊ֡�������Ȼ���
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	// ����glDrawBuffer��glReadBuffer�Ѷ��ͻ��ƻ�������ΪGL_NONE���Ӷ���ʹ���κ���ɫ���ݽ�����Ⱦ
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	//debugDepthQuad->use();
	//debugDepthQuad->SetUniform1i("depthMap", 0);

#pragma endregion

#pragma region Init and load textures
	//��ʵ�ϣ�TEXTURE_2D��������ۣ�����ͬʱ������texture buffer�����ݰ��ϣ���GPU��֮���shader�п��Զ�ȡ

	unsigned int woodTexture;
	woodTexture = loadImageToGUP("wood.png", GL_RGB, GL_RGB, 0);

#pragma endregion

	glm::mat4 viewMat, projMat, model;

	while (!glfwWindowShouldClose(window)) {

		processInput(window);
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);					//����ΪRGB+��͸���ȣ���ΧΪ0-1
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//����Ⱦ��һ֡ǰ��ǰһ֡����ɫ��Ϣ��z-buffer�������Ϣ�����

		// Change light position over time
		//lightD.position.x = sin(glfwGetTime()) * 3.0f;
		//lightD.position.z = cos(glfwGetTime()) * 2.0f;
		//lightD.position.y = 5.0 + cos(glfwGetTime()) * 1.0f;

		// 1. �ӹ���ӽ���Ⱦ�����ͼ
		GLfloat near_plane = 1.0f, far_plane = 7.5f;
		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		//Ϊÿ���������ú��ʵ�ͶӰ����ͼ���󣻽�Ϊ��Դʹ������ͶӰ����͸��ͼ��û���κα���
		//lightProjection = glm::perspective(45.0f, (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);
		//Note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene.
		glm::mat4 lightView = glm::lookAt(lightD.position, lightD.position - lightD.direction, glm::vec3(0.0f, 1.0f, 0.0f));
		//�ӹ�Դ��λ�ÿ��򳡾�����
		glm::mat4 lightSpaceMatrix = lightProjection * lightView;
		//��������Ϊ�����ṩ��һ����ռ�ı任��������ÿ������ռ�����任����Դ�����������Ǹ��ռ䣻������������Ⱦ�����ͼ����Ҫ��

		depthShader->use();
		depthShader->SetUniform4fv("lightSpaceMatrix", lightSpaceMatrix);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTexture);

		// render scene with depthShader

		// Floor
		model = glm::mat4(1.0f);
		depthShader->SetUniform4fv("model", model);
		glBindVertexArray(planeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Cubes
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
		//model = glm::scale(model, glm::vec3(0.5f));
		depthShader->SetUniform4fv("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
		//model = glm::scale(model, glm::vec3(0.5f));
		depthShader->SetUniform4fv("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
		model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		model = glm::scale(model, glm::vec3(0.5));
		depthShader->SetUniform4fv("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		//�������Ȼ��屻���£��õ��˹����ӽ��µ����ͼ
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// 2. ������Ⱦ����
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		myShader->use();
		viewMat = camera.GetViewMatrix();
		projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projMat));
		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(viewMat));
		// Set light uniforms
		glUniform3fv(glGetUniformLocation(myShader->ID, "lightD.dirToLight"), 1, &lightD.direction[0]);
		glUniform3fv(glGetUniformLocation(myShader->ID, "lightD.pos"), 1, &lightD.position[0]);
		glUniform3fv(glGetUniformLocation(myShader->ID, "viewPos"), 1, &camera.Position[0]);
		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
		// Enable/Disable shadows by pressing 'SPACE'
		glUniform1i(glGetUniformLocation(myShader->ID, "shadows"), shadows);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTexture);
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		// render scene with myShader
		
		// Floor
		model = glm::mat4(1.0f);
		myShader->SetUniform4fv("model", model);
		glBindVertexArray(planeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Cubes
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
		// model = glm::scale(model, glm::vec3(0.5f));
		myShader->SetUniform4fv("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
		// model = glm::scale(model, glm::vec3(0.5f));
		myShader->SetUniform4fv("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
		model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
		model = glm::scale(model, glm::vec3(0.5));
		myShader->SetUniform4fv("model", model);
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// 3. DEBUG: visualize depth map by rendering it to plane
		debugDepthQuad->use();
		glUniform1f(glGetUniformLocation(debugDepthQuad->ID, "near_plane"), near_plane);
		glUniform1f(glGetUniformLocation(debugDepthQuad->ID, "far_plane"), far_plane);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		////render quad
		//glBindVertexArray(quadVAO);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		//glBindVertexArray(0);

		glfwPollEvents();				//��ȡ�û��İ�����������
		//������������Զ��崦�����Ǵ���ģ�Ӧ����������ӣ�����һ��ѭ���Ŀ�ͷ������һ��ѭ���л�õ�������������ӳٵ��µĴ���
		camera.UpdateCameraPosition();	//ͨ������W��S���ƶ������ͨ��������Ⱦѭ�����������һ��ѭ���д���

		glfwSwapBuffers(window);		//����������ɫ�ݴ����飨ÿ�����ض�����������ɫ�ݴ����飩
		//��ֻ������bufferд��ʱ��ͼ�������ܻ���˸��Ϊ�˿˷����⣬����ʹ��˫bufferȥ��Ⱦ��
	}
	glfwTerminate();		//�뿪ʱ��Ҫ����ɾ�������õ���Դ
	return 0;
}
