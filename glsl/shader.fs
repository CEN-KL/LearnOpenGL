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
    // vec3 position;
    vec3 direction; // 使用定向光（平行光）
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{
    // 冯氏光照模型
    // 环境光照
    // ------
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // 漫反射光照
    // --------
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    // 镜面光照
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    // 最终输出
    // ------
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

}