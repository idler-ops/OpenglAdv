////首先靠自己直接复原一下画出箱子的过程
//
//#define GLEW_STATIC
//
//#include <stdio.h>
//#include <iostream>
//#include <cmath>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include "Shader.h"
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "Camera.h"
//#include "Material.h"
//#include "LightDirectional.h"
//#include "LightPoint.h"
//#include "LightSpot.h"
//#include "Mesh.h"
//#include "Model.h"
//
//
//#pragma region Model Data
//
//const unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;
//
//bool shadows = true;
//
////10个立方体距离原立方体的位移距离。这里只改变position
//glm::vec3 cubePositions[] = {
//  glm::vec3(0.0f,  0.0f,  0.0f),
//  glm::vec3(2.0f,  5.0f, -15.0f),
//  glm::vec3(-1.5f, -2.2f, -2.5f),
//  glm::vec3(-3.8f, -2.0f, -12.3f),
//  glm::vec3(2.4f, -0.4f, -3.5f),
//  glm::vec3(-1.7f,  3.0f, -7.5f),
//  glm::vec3(1.3f, -2.0f, -2.5f),
//  glm::vec3(1.5f,  2.0f, -2.5f),
//  glm::vec3(1.5f,  0.2f, -1.5f),
//  glm::vec3(-1.3f,  1.0f, -1.5f)
//};
//
//float quadVertices[] = {
//	// positions        // texture Coords
//	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//};
//
//float cubeVertices[] = {
//	// back face
//	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//	 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//	 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
//	 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//	-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
//	// front face
//	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//	 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
//	 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//	 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//	-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
//	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//	// left face
//	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//	-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
//	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//	-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//	// right face
//	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//	 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
//	 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//	 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//	 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
//	// bottom face
//	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//	 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
//	 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//	 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//	-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//	// top face
//	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//	 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//	 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
//	 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//	-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
//};
//
//float planeVertices[] = {
//	// positions            // normals         // texcoords
//	 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
//	-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
//	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
//
//	 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
//	-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
//	 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 10.0f
//};
//
////下面的用于EBO，暂时不用
//unsigned int indices[] =
//{
//	0, 1, 2,
//	2, 3, 0
//};
//#pragma endregion
//
//#pragma region Camera Declare
////初始化相机对象
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//#pragma endregion
//
//#pragma region Light Declare
//LightDirectional light(
//	glm::vec3(1.0f, 1.0f, -1.0f),
//	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0.0f),
//	glm::vec3(1.0f, 1.0f, 1.0f));
//
//LightPoint lightP0(
//	glm::vec3(10.0f, 0.0f, 0.0f),								//坐标 
//	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0.0f),	//角度
//	glm::vec3(1.0f, 0.0f, 0.0f));								//颜色
//
//LightSpot lightS(
//	glm::vec3(0.0f, 8.0f, 0.0f),
//	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0.0f),		//这个方向是向下
//	glm::vec3(1.0f, 1.0f, 1.0f));
//#pragma endregion
//
//#pragma region Input Declare
//bool firstMouse = true;		//用于mouse callback
//float lastX, lastY;			//记录mouse位置变化
//
//void processInput(GLFWwindow *window) {		//记录发生的按键事件，以便后续处理
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.speedZ = 10.0f;
//	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.speedZ = -10.0f;
//	else
//		camera.speedZ = 0.0f;
//
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.speedX = -10.0f;
//	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.speedX = 10.0f;
//	else
//		camera.speedX = 0.0f;
//
//	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	//下沉
//		camera.speedY = -10.0f;
//	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
//		camera.speedY = 10.0f;
//	else
//		camera.speedY = 0.0f;
//}
//
//void mouse_callback(GLFWwindow *window, double xPos, double yPos) {		//捕捉鼠标移动
//	if (firstMouse == true) {
//		lastX = xPos;
//		lastY = yPos;
//		firstMouse = false;
//	}
//	float deltaX = xPos - lastX;
//	float deltaY = yPos - lastY;
//	lastX = xPos;
//	lastY = yPos;
//	camera.ProcessMouseMovement(deltaX, deltaY);
//}
//#pragma endregion
//
//unsigned int loadImageToGUP(const char *fileName, GLint internalFormat, GLenum format, int textureSlot) {
//	//将图片读入Texture buffer并绑定到TEXTURE_2D
//	unsigned int TexBuffer;
//	glGenTextures(1, &TexBuffer);
//	glActiveTexture(GL_TEXTURE0 + textureSlot);		//bind前要先移动槽位，使得不同的buffer不会抢占同一个槽位，之后可以通过槽位序号找到想要的Texture(这里注意，使用的是0号槽(TEXTURE0))
//	glBindTexture(GL_TEXTURE_2D, TexBuffer);
//
//	//通过stb加载图片
//	int width, height, nrChannel;
//	stbi_set_flip_vertically_on_load(true);		//加载的图片y轴正负方向通常与opengl相反，因此可以通过这一步在加载图片时自动反转y坐标
//	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannel, 0);
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else {
//		printf("Load image failed.\n");
//	}
//	stbi_image_free(data);
//
//	return TexBuffer;
//}
//
//int main(int argc, char *argv[]) {
//
//	std::string exePath = argv[0];
//
//#pragma region Open A Window
//	//glfw库相关初始化配置
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	//mac用，前向相容性
//
//	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lighting", nullptr, nullptr);	//窗口的col、row、title
//	if (window == nullptr) {
//		printf("Open GLFW window failed.");
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);	//设为主窗口
//
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);	//不显示鼠标位置
//	glfwSetCursorPosCallback(window, mouse_callback);
//
//	//Init GLEW
//	glewExperimental = true;
//	if (glewInit() != GLEW_OK) {
//		printf("Init GLEW failed.");
//		glfwTerminate();
//		return -1;
//	}
//	glViewport(0, 0, 800, 600);		//控制可绘制区域
//	glEnable(GL_DEPTH_TEST);		//开启使用z-buffer保存深度信息
////	glDepthFunc(GL_ALWAYS);			//深度测试永远通过，则永远只渲染出深度最大的内容
//
//	//下面开启面剔除功能，背面不会被画出
//	//glEnable(GL_CULL_FACE);
//	//glCullFace(GL_BACK);
//
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//框线模式，只画出框线
//#pragma endregion
//
//#pragma region Init Shader
//	//读取shader程序码
//	Shader *myShader = new Shader("vertexShadow.vert", "fragmentShadow.frag");
//	myShader->test();
//
//	Shader *depthShader = new Shader("vertexDepth.vert", "fragmentDepth.frag");
//	depthShader->test();
//
//	Shader *debugDepthQuad = new Shader("vertexDepthDebugQuad.vert", "fragmentDepthDebugQuad.frag");
//	debugDepthQuad->test();
//
//#pragma endregion
//
//#pragma region Init VAO，VBO，EBO and load data
//	unsigned int cubeVAO;
//	glGenVertexArrays(1, &cubeVAO);	//参数1：返回的VAO个数，参数2：用来接收VAO序号，接收多个时参数2应为数组
//	glBindVertexArray(cubeVAO);
//	unsigned int cubeVBO;
//	glGenBuffers(1, &cubeVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);		//这一步是将VBO放入VAO中的attribute pointer（槽位）
//	glEnableVertexAttribArray(1);	//激活0号槽位
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
//	//（为方便记忆，固定VAO的0号槽放坐标信息，1号槽放颜色信息，2号槽放纹理信息，3号放法向量信息）
//	glBindVertexArray(0);
//
//	unsigned int planeVAO;
//	glGenVertexArrays(1, &planeVAO);
//	glBindVertexArray(planeVAO);
//	unsigned int planeVBO;
//	glGenBuffers(1, &planeVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
//	glBindVertexArray(0);
//	
//	// render a 1*1 XY quad in NDC
//	unsigned int quadVAO;
//	glGenVertexArrays(1, &quadVAO);
//	glBindVertexArray(quadVAO);
//	unsigned int quadVBO;
//	glGenBuffers(1, &quadVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
//	glBindVertexArray(0);
//#pragma endregion
//
//#pragma region configure depth map FBO and create depth texture
//	GLuint depthMapFBO;		//它是从光的透视图里渲染的深度纹理，后续将使用它计算阴影。
//	glGenFramebuffers(1, &depthMapFBO);
//	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;	//深度贴图的分辨率
//
//	GLuint depthMap;
//	glGenTextures(1, &depthMap);
//	glBindTexture(GL_TEXTURE_2D, depthMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//	//只关心深度值，因此把纹理格式指定为GL_DEPTH_COMPONENT
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//把生成的深度纹理作为帧缓冲的深度缓冲
//	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
//	//调用glDrawBuffer和glReadBuffer把读和绘制缓冲设置为GL_NONE，从而不使用任何颜色数据进行渲染
//	glDrawBuffer(GL_NONE);
//	glReadBuffer(GL_NONE);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	debugDepthQuad->use();
//	debugDepthQuad->SetUniform1i("depthMap", 0);
//	glm::vec3 lightPos(-2.0f, 4.0f, -1.0f);
//#pragma endregion
//
//#pragma region Init and load textures
//	//事实上，TEXTURE_2D包括多个槽，可以同时将几个texture buffer的内容绑定上，让GPU在之后的shader中可以读取
//
//	unsigned int woodTexture;
//	woodTexture = loadImageToGUP("wood.png", GL_RGB, GL_RGB, 0);
//
//#pragma endregion
//
//	while (!glfwWindowShouldClose(window)) {
//		
//		processInput(window);
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);					//参数为RGB+不透明度，范围为0-1
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//在渲染下一帧前将前一帧的颜色信息和z-buffer（深度信息）清空
//
//		// 1. render depth of scene to texture (from light's perspective)
//		GLfloat near_plane = 1.0f, far_plane = 7.5f;
//		glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
//		glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		glm::mat4 lightSpaceMatrix = lightProjection * lightView;
//
//		depthShader->use();
//		depthShader->SetUniform4fv("lightSpaceMatrix", lightSpaceMatrix);
//
//		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
//		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//		glClear(GL_DEPTH_BUFFER_BIT);
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, woodTexture);
//
//		//render scene
//		glm::mat4 model = glm::mat4(1.0f);
//		depthShader->SetUniform4fv("model", model);
//		glBindVertexArray(planeVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
//		model = glm::scale(model, glm::vec3(0.5f));
//		depthShader->SetUniform4fv("model", model);
//		glBindVertexArray(cubeVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
//		model = glm::scale(model, glm::vec3(0.5f));
//		depthShader->SetUniform4fv("model", model);
//		glBindVertexArray(cubeVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
//		model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
//		model = glm::scale(model, glm::vec3(0.25));
//		depthShader->SetUniform4fv("model", model);
//		glBindVertexArray(cubeVAO);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		debugDepthQuad->use();
//		debugDepthQuad->SetUniform1f("near_plane", near_plane);
//		debugDepthQuad->SetUniform1f("far_plane", far_plane);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, depthMap);
//		
//		//render quad
//		//这里将生成的深度贴图贴在一张正方向面上展示
//		glBindVertexArray(quadVAO);
//		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);		//交换两个颜色暂存区块（每个像素都存在两个颜色暂存区块）
//		//当只往单个buffer写入时，图像结果可能会闪烁。为了克服问题，轮流使用双buffer去渲染。
//		glfwPollEvents();				//获取用户的按键（操作）
//		//在这下面添加自定义处理方法是错误的，应当在上面添加，在下一次循环的开头处理上一次循环中获得的命令，尽量避免延迟导致的错误
//
//		camera.UpdateCameraPosition();	//通过按下W、S键移动相机（通常放在渲染循环的最后，在下一次循环中处理）
//	}
//	glfwTerminate();		//离开时不要忘记删除所配置的资源
//	return 0;
//}
