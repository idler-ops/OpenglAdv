//����Ļ�ռ��з����Ե����ֵ�任���������ֵ������Ƭ����ɫ�����£����仰˵����͸��ͶӰ��Ϊ����ͶӰ����
#version 330 core
struct Material {
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;		//���տ��Ե�����ɫֵ

in vec2 TexCoord;		//��Ӧ��ͼ�е�uv����
in vec3 FragPos;		//��ǰ������
in vec3 Normal;			//������

//Phong Model��������ǿ�ȷ�Ϊambient�������⣬�뵥��ι�����Ĺ�Դ�޹أ���diffuse�������䣩��Specular��������գ���ע��ÿ�����ֵ���Сֵ��Ϊ0���������ձ��˵Ĺ���ǿ�ȣ�
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
