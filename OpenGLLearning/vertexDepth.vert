//仅仅将顶点变换到光线视角空间

#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main() {
	gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0f);
}
