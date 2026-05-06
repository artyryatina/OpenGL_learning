#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "shader_utils.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glClearColor(0.9, 0.9, 0.9,  1.0);

    std::string vertexShaderName = "res/shaders/triangle.vert";
    std::string fragmentShaderName = "res/shaders/triangle.frag";
    GLuint shaderProgram = createProgram(
        vertexShaderName,
        fragmentShaderName);

    float vertices[] = {  // float* vertices
        /* координати */  -0.5f, -0.5f,  /* тестурні координати */  0.0f, 0.0f,  //  0
        /* координати */   0.5f, -0.5f,  /* тестурні координати */  1.0f, 0.0f, // 1
        /* координати */   0.5f, 0.5f,   /* тестурні координати */  1.0f, 1.0f, // 2
        /* координати */  -0.5f, 0.5f,   /* тестурні координати */  0.0f, 1.0f, // 3
    };

    unsigned int indices[] = {
        0, 1, 2, // перший трикутник
        0, 2, 3, // другий трикутник
    };

    GLuint VBO, indexBuffer; // data - ідентифікатор для даних - місток CPU та GPU
    GLuint VAO; // vertex array object

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &indexBuffer);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind = activate
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint posAttribLocation = glGetAttribLocation(shaderProgram, "aPos");
    glVertexAttribPointer(
        posAttribLocation,  // location - 0 знайдена командою glGetAttribLocation
        2,                  // 2 компоненти: x, y
        GL_FLOAT,           // тип даних
        GL_FALSE,           // не нормалізувати
        4 * sizeof(float),  // stride: 4 float-а на вершину
        (void*)0            // offset: починаємо з 0
        );
    glEnableVertexAttribArray(posAttribLocation);

    GLuint  textureCoordsAttribLocation = glGetAttribLocation(shaderProgram, "aUV");
    glVertexAttribPointer(
         textureCoordsAttribLocation,  // location - 0 знайдена командою glGetAttribLocation
        2,                          // 2 компоненти: u, v
        GL_FLOAT,                   // тип даних
        GL_FALSE,                   // не нормалізувати
        4 * sizeof(float),          // stride: 4 float-а на вершину
        (void*)(2 * sizeof(float))  // offset: починаємо з 2
        );
    glEnableVertexAttribArray( textureCoordsAttribLocation);

    glBindVertexArray(0); // деактивувати VAO

    unsigned int textureHouse = loadTexture("res/textures/house.jpg");
    unsigned int textureGirl = loadTexture("res/textures/girl.jpg");
    unsigned int textureField = loadTexture("res/textures/field.jpg");
    unsigned int textureGhost= loadTexture("res/textures/ghost.jpg");

    GLint textureHouse_loc = glGetUniformLocation(shaderProgram, "uTextureHouse");
    GLint textureGirl_loc = glGetUniformLocation(shaderProgram, "uTextureGirl");
    GLint textureField_loc = glGetUniformLocation(shaderProgram, "uTextureField");
    GLint textureGhost_loc = glGetUniformLocation(shaderProgram, "uTextureGhost");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureHouse);
        glUniform1i(textureHouse_loc, 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textureGirl);
        glUniform1i(textureGirl_loc, 1);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textureField);
        glUniform1i(textureField_loc, 2);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, textureGhost);
        glUniform1i(textureGhost_loc, 3);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    glDeleteTextures(1, &textureHouse);
    glDeleteTextures(1, &textureGirl);
    glDeleteTextures(1, &textureField);
    glDeleteTextures(1, &textureGhost);

    glfwTerminate();
    return 0;
}
