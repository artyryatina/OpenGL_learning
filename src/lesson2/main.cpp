#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../utils/shader_utils.h"

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
        // позиція     // колір
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,  1.0f,    // червоний
         0.5f, -0.5f,   1.0f, 1.0f, 0.0f,  1.0f,    // жовтий
         0.5f,  0.5f,   0.0f, 1.0f, 0.0f,  1.0f,    // зелений

         0.5f,  0.5f,   0.0f, 1.0f, 0.0f,  1.0f,    // зелений
        -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,  1.0f,     // синій
        -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,  1.0f,    // червоний
    };

    GLuint VAO; // vertex array object
    GLuint VBO; // data - ідентифікатор для даних - місток CPU та GPU

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind = activate

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLuint posAttribLocation = glGetAttribLocation(shaderProgram, "aPos");
    glVertexAttribPointer(
        posAttribLocation,  // location - 0
        2,                  // 2 компоненти: x, y
        GL_FLOAT,           // тип даних
        GL_FALSE,           // не нормалізувати
        6 * sizeof(float),  // stride: 5 float-а на вершину
        (void*)0            // offset: починаємо з 0
        );
    glEnableVertexAttribArray(0);

    GLuint colorAttribLocation = glGetAttribLocation(shaderProgram, "aColor");
    glVertexAttribPointer(
        colorAttribLocation,             // location - 1
        4,                               // 3 компоненти: r, g, b
        GL_FLOAT,                        // тип даних
        GL_FALSE,                        // не нормалізувати
        6 * sizeof(float),               // stride: 5 float-а на вершину
        (void*)(2 * sizeof(float))       // offset: після x, y
        );
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0); // деактивувати VBO
    glBindVertexArray(0); // деактивувати VAO

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
