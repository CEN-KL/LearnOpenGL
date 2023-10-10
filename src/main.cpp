#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utils/shader_s.hpp>
#include <unistd.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main() {
    // 查看当前路径
    // const int MAXPATH = 250;
    // char buffer[MAXPATH];
    // getcwd(buffer, MAXPATH);
    // printf("The current directory is: %s\n", buffer);


    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // 构建和编译自己定义的着色器
    // ---------------------
    Shader ourShader("/Users/ckl/VSCodeCpp/LearnOpenGL/glsl/shader.vs", "/Users/ckl/VSCodeCpp/LearnOpenGL/glsl/shader.fs");

    // 顶点输入
    // ------
    float vertices[] = {
        // 位置              // 颜色
        0.0f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -1.0f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    };

    unsigned int VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    // 使用线框模式绘制
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // 设置回默认模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // render loop
    // -----------
    float delta = 0.0;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // render
        // ------
        glClearColor(.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        if (delta < 1.0) {
            delta += 0.001;
        }
        ourShader.setFloat("delta", delta);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    // std::cout << "(" << width << ", " << height << ")" << std::endl;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}