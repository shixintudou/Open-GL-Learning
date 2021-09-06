#ifndef BASE_WINDOW_H
#define BASE_WINDOW_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include"shader.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


float deltatime = 0.0f;
float lastframe = 0.0f;
float yaws = -90.0f;
float pitchs = 0.0f;
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
bool firstmouse = true;
float lastx = 960;
float lasty = 540;

int window_base()
{
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] =
    {
     glm::vec3(0.0f,  0.0f,  0.0f),
     glm::vec3(2.0f,  5.0f, -15.0f),
     glm::vec3(-1.5f, -2.2f, -2.5f),
     glm::vec3(-3.8f, -2.0f, -12.3f),
     glm::vec3(2.4f, -0.4f, -3.5f),
     glm::vec3(-1.7f,  3.0f, -7.5f),
     glm::vec3(1.3f, -2.0f, -2.5f),
     glm::vec3(1.5f,  2.0f, -2.5f),
     glm::vec3(1.5f,  0.2f, -1.5f),
     glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    unsigned int indices[] =
    {
        0, 1, 3, // 第一个三角形
        1, 2, 3,  // 第二个三角形
        //0, 3, 4
    };

    //mat4 model = mat4(1.0f);//模型矩阵，使平面绕x轴旋转
    //model = rotate(model, radians(-55.0f), vec3(1.0f, 0.0f, 0.0f));

    mat4 view = mat4(1.0f);// 观察矩阵
    view = translate(view, vec3(0.0f, 0.0f, -3.0f));

    mat4 projection = mat4(1.0f);//投影矩阵
    projection = perspective(radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

    mat4 trans = mat4(1.0f);

    vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);//摄像机位置
    vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
    vec3 cameraDirection = normalize(cameraPos - cameraTarget);
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    vec3 cameraRight = normalize(cross(up, cameraDirection));
    vec3 cameraUp = cross(cameraDirection, cameraRight);


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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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

    //将变换矩阵传给uniform
    unsigned int transformloc = glGetUniformLocation(myshader.ID, "transform");
    unsigned int viewloc = glGetUniformLocation(myshader.ID, "view");
    glUniformMatrix4fv(viewloc, 1, GL_FALSE, value_ptr(view));
    unsigned int projectionloc = glGetUniformLocation(myshader.ID, "projection");
    glUniformMatrix4fv(projectionloc, 1, GL_FALSE, value_ptr(projection));

    glEnable(GL_DEPTH_TEST);//启用深度测试

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while (!glfwWindowShouldClose(window))
    {
        glfwSetCursorPosCallback(window, mouse_callback);

        float currentframe = glfwGetTime();
        deltatime = currentframe - lastframe;
        lastframe = currentframe;

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        float cameraSpeed = 5.0f; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront * deltatime;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront * deltatime;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltatime;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltatime;
        //trans = rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        glUniformMatrix4fv(transformloc, 1, GL_FALSE, value_ptr(trans));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex2);
        glBindVertexArray(VAO);
        view = lookAt(cameraPos, cameraPos + cameraFront, up);
        glUniformMatrix4fv(glGetUniformLocation(myshader.ID, "view"), 1, GL_FALSE, value_ptr(view));
        for (int i = 0; i < 10; i++)
        {
            mat4 model = mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            model = rotate(model, (float)glfwGetTime(), vec3(0.0f, 1.0f, 1.0f));
            int modeloc = glGetUniformLocation(myshader.ID, "model");
            glUniformMatrix4fv(modeloc, 1, GL_FALSE, value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //glBindTexture(GL_TEXTURE_2D, texture);       
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstmouse)
    {
        lastx = xpos;
        lasty = ypos;
        firstmouse = false;
    }
    float xoffset = xpos - lastx;
    float yoffset = ypos - lasty;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaws += xoffset;
    pitchs += yoffset;
    if (pitchs > 89.0f)
        pitchs = 89.0f;
    if (pitchs < -89.0f)
        pitchs = -89.0f;
    vec3 front;
    front.x = cos(glm::radians(yaws)) * cos(glm::radians(pitchs));
    front.y = -sin(glm::radians(pitchs));
    front.z = sin(glm::radians(yaws)) * cos(glm::radians(pitchs));
    cameraFront = glm::normalize(front);
    pitchs = 0.0f;
    yaws = -90.0f;
}


#endif
