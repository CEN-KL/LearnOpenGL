#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

struct Material {
    sampler2D diffuse;   // 环境光颜色在几乎所有情况下都等于漫反射颜色，所以我们不需要将它们分开储存
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction; // 此处表示聚光所指的方向
    float cutOff; // （内圆锥）聚光半径的切光角，落在这个角度之外的物体都不会被这个聚光所照亮。
    float outerCutOff; // （外圆锥）切光角

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // 衰减系数计算
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{   
    // 聚光强度计算
    vec3 lightDir = normalize(light.position - FragPos);
    float cos_theta = dot(lightDir, -light.direction);
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((cos_theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // 冯氏光照模型
    // 环境光照
    // ------
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // 漫反射光照
    // --------
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // 镜面光照
    vec3 viewDir = normalize(FragPos - viewPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // 衰减计算
    // 光源距离
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    ambient *= attenuation;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    // 最终输出
    // ------
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}