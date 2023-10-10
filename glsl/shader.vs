#version 330 core
layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;

// uniform float delta;
out vec3 ourColor;

void main()
{
    // gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);  // 练习1 上下颠倒三角形
    // gl_Position = vec4(aPos.x + delta, aPos.y, aPos.z, 1.0);
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aPos;
}