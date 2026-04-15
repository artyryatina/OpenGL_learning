#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    auto vertexShaderCode = R"(
        #version 330 core
        out vec4 ourColor;

        layout(location = 0) in vec4 aPos;
        layout(location = 1) in vec4 aColor;

        void main() {
            gl_Position = aPos;
            ourColor = aColor;
        }
    )";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    auto fragmentShaderCode = R"(
        #version 330 core
        in vec4 ourColor;
        out vec4 FragColor;

        void main() {
            FragColor = ourColor;
       }
    )";
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);

    // Програма з шейдерів
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
    glVertexAttribPointer(
        0,                  // location - 0
        2,                  // 2 компоненти: x, y
        GL_FLOAT,           // тип даних
        GL_FALSE,           // не нормалізувати
        6 * sizeof(float),  // stride: 5 float-а на вершину
        (void*)0            // offset: починаємо з 0
        );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,                               // location - 1
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
