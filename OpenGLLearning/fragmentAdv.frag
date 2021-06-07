//将屏幕空间中非线性的深度值变换至线性深度值的完整片段着色器如下（换句话说，从透视投影变为正交投影）：
#version 330 core
struct Material {
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;		//最终可以调整颜色值

in vec2 TexCoord;		//对应贴图中的uv坐标
in vec3 FragPos;		//当前点坐标
in vec3 Normal;			//法向量

//Phong Model：将光照强度分为ambient（环境光，与单独喂进来的光源无关）、diffuse（漫反射）、Specular（镜面光照），注意每个部分的最小值都为0（不能吸收别人的光照强度）
uniform vec3 ambientColor;
uniform vec3 lightDirUniform;
uniform vec3 cameraPos;

out vec4 FragColor;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth) {
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main() {
	float depth = LinearizeDepth(gl_FragCoord.z) / far;
	FragColor = vec4(vec3(depth), 1.0);
}
