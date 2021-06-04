#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include"shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //const char* vertexShaderSource = "#version 330 core\n"
    //    "layout (location = 0) in vec3 aPos;\n"
    //    "layout( location= 1) in vec3 acolor;\n"
    //    "out vec3 ourcolor;\n"
    //    "void main()\n"
    //    "{\n"
    //    "gl_Position = vec4(aPos, 1.0);\n"
    //    "ourcolor = acolor;\n"
    //    "}\0";//GLSL顶点着色器源码
    //const char* fragmebtShaderSource = "#version 330 core\n"
    //    "out vec4 fragcolor;\n"

    //    "in vec3 ourcolor;\n"

    //    "void main()\n"
    //    "{\n"
    //    " fragcolor = vec4(ourcolor,1.0);\n"
    //    "}\0";//片段着色器源码

    /*float vertices[] = 
    {
     -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f
    };*/
    //float vertices[] = {
    //0.5f, 0.5f, 0.0f,   // 右上角
    //0.5f, -0.5f, 0.0f,  // 右下角
    //-0.5f, -0.5f, 0.0f, // 左下角
    //-0.5f, 0.5f, 0.0f,   // 左上角
    //0.6f,0.8f,0.0f
    //};
    //float vertices[] = {
    //    // 位置              // 颜色
    //     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    //    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
    //     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
    //};
    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    unsigned int indices[] = 
    {
        0, 1, 3, // 第一个三角形
        1, 2, 3,  // 第二个三角形
        //0, 3, 4
    };

    

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Fail to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Fail to init glad\n");
        return -1;
    }
    glViewport(0, 0, 1920, 1080);


    Shader myshader = Shader("vertexshader.glsl", "fragmentshader.glsl");
    //int location = glGetUniformLocation(myshader.ID, "pi");
    
    //unsigned int vertexshader;//创建顶点着色器对象
    //vertexshader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
    //glCompileShader(vertexshader);

    //unsigned int fragmentshader;
    //fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentshader, 1, &fragmebtShaderSource, NULL);
    //glCompileShader(fragmentshader);

    //int success;
    //char info[512];
    //glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(vertexshader, 512, NULL, info);
    //    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
    //}

    //unsigned int shaderprogram;
    //shaderprogram = glCreateProgram();
    //glAttachShader(shaderprogram, vertexshader);
    //glAttachShader(shaderprogram, fragmentshader);
    //glLinkProgram(shaderprogram);
    //glUseProgram(shaderprogram);
    //glDeleteShader(vertexshader);
    //glDeleteShader(fragmentshader);

    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);//顶点数组对象
    unsigned int VBO;//创建顶点输入缓冲对象
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);//读取图像
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);//绑定并载入纹理
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    //第二个纹理
    int wid = 0, hei = 0, nr = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* dat = stbi_load("a.png", &wid, &hei, &nr, 0);
    unsigned int tex2;
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &tex2);   
    glBindTexture(GL_TEXTURE_2D, tex2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, wid, hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, dat);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);//设置纹理参数
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(data);
    stbi_image_free(dat);
    myshader.use();
    myshader.setInt("mytexture", 0);
    myshader.setInt("mytexture1", 1);

    float i = 0.0f;
    myshader.setFloat("tp", i);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue / 2.0f)) + 0.5f;
        int vertexcolorlocation = glGetUniformLocation(shaderprogram, "ourcolor");
        glUniform4f(vertexcolorlocation, 0.0f, greenValue, 0.0f, 0.0f);*/
        /*glUniform3f(location, 0.3f, 0.0f, 0.0f);
        myshader.use();
        glBindVertexArray(VAO);*/
        myshader.use();
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && i < 1.0)
        {
            i += 0.1;
            myshader.setFloat("tp", i);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && i > 0)
        {
            i -= 0.1;
            myshader.setFloat("tp", i);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex2);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 9);
        //glBindTexture(GL_TEXTURE_2D, texture);       
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //getchar();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderprogram);
    glfwTerminate();
    return 0;
}