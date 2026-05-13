#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"
#include "shader_utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    auto width = 1280;
    auto height = 720;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
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

    glfwSwapInterval(1);  // синхронізує рендер-цикл з частотою екрану
    glClearColor(0.9, 0.9, 0.9,  1.0);

    std::string vertexShaderName = "res/shaders/triangle.vert";
    std::string fragmentShaderName = "res/shaders/triangle.frag";
    GLuint shaderProgram = createProgram(
        vertexShaderName,
        fragmentShaderName);

    float vertices[] = {
        // -------- Передня грань (червона) --------
        0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 0.0f,

       // -------- Задня грань (зелена) --------
        0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,

       // -------- Ліва грань (синя) --------
        0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,

       // -------- Права грань (жовта) --------
        1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,   1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 0.0f,

       // -------- Нижня грань (бірюзова) --------
        0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,   0.0f, 1.0f, 1.0f,

       // -------- Верхня грань (фіолетова) --------
        0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f,   1.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {  // wrong indices
        2, 1, 0,  3, 2, 0,       // передня
        4, 5, 6,  6, 7, 4,       // задня
        8, 9,10, 10,11, 8,       // ліва
       12,13,14, 14,15,12,       // права
       16,17,18, 18,19,16,       // нижня
       20,21,22, 22,23,20        // верхня
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
        3,                  // 3 компоненти: x, y, z
        GL_FLOAT,           // тип даних
        GL_FALSE,           // не нормалізувати
        6 * sizeof(float),  // stride: 6 float-а на вершину
        (void*)0            // offset: починаємо з 0
    );
    glEnableVertexAttribArray(posAttribLocation);

    GLuint  colorAttribLocation = glGetAttribLocation(shaderProgram, "aColor");
    glVertexAttribPointer(
         colorAttribLocation,  // location - 0 знайдена командою glGetAttribLocation
        3,                          // 3 компоненти: r, g, b,
        GL_FLOAT,                   // тип даних
        GL_FALSE,                   // не нормалізувати
        6 * sizeof(float),          // stride: 6 float-а на вершину
        (void*)(3 * sizeof(float))  // offset: починаємо з 3
    );
    glEnableVertexAttribArray( colorAttribLocation);

    glBindVertexArray(0); // деактивувати VAO

    GLint model_loc = glGetUniformLocation(shaderProgram, "uModel");
    GLint view_loc = glGetUniformLocation(shaderProgram, "uView");
    GLint proj_loc = glGetUniformLocation(shaderProgram, "uProjection");

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 1.5f, -4.0f), // позиція камери
        glm::vec3(0.0f, 0.0f, 0.0f), // куди дивимось
        glm::vec3(0.0f, 1.0f, 0.0f) // вектор вгору
    );

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)width / (float)height,
        0.1f,
        100.0f
    );

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT);
    // glFrontFace(GL_CCW); // GL_CW.
    // glFrontFace(GL_CW); // GL_CW.

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
