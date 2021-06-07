
// 使用Blinn-Phong model
// 要计算一个shadow值，当片段在阴影中时为1.0，在阴影外时为0.0
// 之后，diffuse和specular的颜色会乘以（1.0 - 这个阴影元素）
// 首先要对光空间坐标做透视除法，而做完后深度范围在-1到1，为了比较，需要变换到0-1
// 深度值存储在r值，故下一步就是取出深度texture中光空间xy坐标下的最浅深度值
// 如果当前点的深度（z值）比这个值要大，则当前点在阴影中

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
	vec3 dirToLight;	//保证它是单位向量
};
uniform LightDirectional lightD;	//平行光源
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
    // 解决因为深度texture按像素采样而在斜面上产生的不该出现的阴影条纹
	// 当斜面坡度较大（即光线与法线的内积较小）时，将深度值上移以防被错误判定为遮挡
	vec3 normal = normalize(fs_in.Normal);
//	vec3 lightDir = normalize(lightPos - fs_in.FragPos);
	vec3 lightDir = normalize(lightD.dirToLight);
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // Check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

	// 解决上述问题时可能会引发另一个问题：由于深度图后移，阴影可能整体后移，就像物体浮起来了
	// 一种解决方法是在生成深度纹理时剔除正面

	// 减轻阴影中的锯齿
	// 多个片段会从深度贴图的同一个深度值进行采样，这几个片段便得到的是同一个阴影，这就会产生锯齿边
	// 从深度贴图中多次采样，每一次采样的纹理坐标都稍有不同。每个独立的样本可能在也可能不在阴影中。所有的次生结果求平均，得到柔和阴影
    // PCF（不完整）
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

//计算specular，两种方式：Phong model 和 Blinn-Phong model
float CalcSpecIntensity(vec3 lightPos, vec3 lightDir, vec3 uNormal, vec3 dirToCamera) {

	// Phong model 计算反射光与视角之间角度的cos
//	vec3 R = normalize(reflect(-lightDir, uNormal));	// 反射向量，参数为入射向量、法向量
//	float specIntensity = pow(max(dot(R, dirToCamera), 0), material.shininess);
//	float specIntensity = pow(max(dot(R, dirToCamera), 0), 64.0);
	// Blinn-Phong model 计算入射光与视角的角平分线与法线之间角度的cos
	vec3 halfwayDir = normalize(dirToCamera + lightDir);
//	float specIntensity = pow(max(dot(uNormal, halfwayDir), 0.0), shininess);
	float specIntensity = pow(max(dot(uNormal, halfwayDir), 0.0), 64.0);
	
	return specIntensity;
}

//封装平行光源
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
