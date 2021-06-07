
// ʹ��Blinn-Phong model
// Ҫ����һ��shadowֵ����Ƭ������Ӱ��ʱΪ1.0������Ӱ��ʱΪ0.0
// ֮��diffuse��specular����ɫ����ԣ�1.0 - �����ӰԪ�أ�
// ����Ҫ�Թ�ռ�������͸�ӳ��������������ȷ�Χ��-1��1��Ϊ�˱Ƚϣ���Ҫ�任��0-1
// ���ֵ�洢��rֵ������һ������ȡ�����texture�й�ռ�xy�����µ���ǳ���ֵ
// �����ǰ�����ȣ�zֵ�������ֵҪ����ǰ������Ӱ��

#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

struct Material {
	vec3 ambient;
//	vec3 diffuse;
	sampler2D diffuse;
//	vec3 specular;
	sampler2D specular;
	float shininess;
};

struct LightDirectional {
	vec3 pos;
	vec3 color;
	vec3 dirToLight;	//��֤���ǵ�λ����
};
uniform LightDirectional lightD;	//ƽ�й�Դ
uniform Material material;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 viewPos;
uniform bool shadows;

vec3 lightColor = vec3(0.4);

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Calculate bias (based on depth map resolution and slope)
    // �����Ϊ���texture�����ز�������б���ϲ����Ĳ��ó��ֵ���Ӱ����
	// ��б���¶Ƚϴ󣨼������뷨�ߵ��ڻ���С��ʱ�������ֵ�����Է��������ж�Ϊ�ڵ�
	vec3 normal = normalize(fs_in.Normal);
//	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	vec3 lightDir = normalize(lightD.dirToLight);
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // Check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

	// �����������ʱ���ܻ�������һ�����⣺�������ͼ���ƣ���Ӱ����������ƣ��������帡������
	// һ�ֽ���������������������ʱ�޳�����

	// ������Ӱ�еľ��
	// ���Ƭ�λ�������ͼ��ͬһ�����ֵ���в������⼸��Ƭ�α�õ�����ͬһ����Ӱ����ͻ������ݱ�
	// �������ͼ�ж�β�����ÿһ�β������������궼���в�ͬ��ÿ������������������Ҳ���ܲ�����Ӱ�С����еĴ��������ƽ�����õ������Ӱ
    // PCF����������
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

//����specular�����ַ�ʽ��Phong model �� Blinn-Phong model
float CalcSpecIntensity(vec3 lightPos, vec3 lightDir, vec3 uNormal, vec3 dirToCamera) {

	// Phong model ���㷴������ӽ�֮��Ƕȵ�cos
//	vec3 R = normalize(reflect(-lightDir, uNormal));	// ��������������Ϊ����������������
//	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess);
//	float specIntensity = pow(max(dot(R, dirToCamera), 0), 64.0);
	// Blinn-Phong model ������������ӽǵĽ�ƽ�����뷨��֮��Ƕȵ�cos
	vec3 halfwayDir = normalize(dirToCamera + lightDir);
//	float specIntensity = pow(max(dot(uNormal, halfwayDir), 0.0), shininess);
	float specIntensity = pow(max(dot(uNormal, halfwayDir), 0.0), 64.0);
	
	return specIntensity;
}

//��װƽ�й�Դ
vec3 CalcLightDirectional(LightDirectional light, vec3 uNormal, vec3 dirToCamera) {
	// diffuse		max(dot(L, N), 0)
	float diffuseIntensity = max(dot(light.dirToLight, uNormal), 0);
	vec3 diffColor = diffuseIntensity * lightColor * texture(material.diffuse, fs_in.TexCoords).rgb;

	// specular		pow(max(dot(R, Cam), 0), shininess)
	float specIntensity = CalcSpecIntensity(light.pos, light.dirToLight, uNormal, dirToCamera);
//	vec3 specColor = specIntensity * light.color * texture(material.specular, fs_in.TexCoords).rgb;
	vec3 specColor = specIntensity * lightColor * texture(material.diffuse, fs_in.TexCoords).rgb;

	float shadow = shadows ? ShadowCalculation(fs_in.FragPosLightSpace) : 0.0;                      
    shadow = min(shadow, 0.75); // reduce shadow strength a little: allow some diffuse/specular light in shadowed regions

	vec3 result = (diffColor + specColor) * (1.0 - shadow);
	return result;
}

void main()
{
	vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 color = texture(material.diffuse, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    // Ambient
    vec3 ambient = 0.2 * color;
    vec3 directionalLight = CalcLightDirectional(lightD, normal, viewDir);

	// Calculate shadow
    float shadow = shadows ? ShadowCalculation(fs_in.FragPosLightSpace) : 0.0;                      
    shadow = min(shadow, 0.75);
	// reduce shadow strength a little: allow some diffuse/specular light in shadowed regions
	vec3 lighting = ambient * color + directionalLight;
    
    FragColor = vec4(lighting, 1.0f);
}
