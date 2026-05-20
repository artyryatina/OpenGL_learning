#include <iostream>
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
    window = glfwCreateWindow(width, height, "Cube", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSwapInterval(1);  // синхронізує рендер-цикл з частотою екрану
    glClearColor(0.9, 0.9, 0.9,  1.0);

    std::string vertexShaderName = "res/shaders/cube.vert";
    std::string fragmentShaderName = "res/shaders/cube.frag";
    GLuint shaderProgram = createProgram(
        vertexShaderName,
        fragmentShaderName);

    float vertices[] = {
        // -------- Задня грань (червона) --------
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,

        // -------- Передня грань (зелена) --------
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,

        // -------- Ліва грань (синя) --------
        -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,

        // -------- Права грань (жовта) --------
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,

        // -------- Нижня грань (бірюзова) --------
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,

        // -------- Верхня грань (фіолетова) --------
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,
    };

    unsigned int indices[] = {
        2, 1, 0,  3, 2, 0,       // задня червона
        4, 5, 6,  4, 6, 7,       // передня зелена
        10, 9, 8, 11,10, 8,       // ліва синя
       12,13,14, 14,15,12,       // права жовта
       18,17,16, 19,18,16,       // нижня
       22,21,20, 23,22,20        // верхня
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
        posAttribLocation,  // позиція атрибуту знайдена командою glGetAttribLocation
        3,                  // 3 компоненти: x, y, z
        GL_FLOAT,           // тип даних
        GL_FALSE,           // не нормалізувати
        6 * sizeof(float),  // stride: 6 float-а на вершину
        (void*)0            // offset: починаємо з 0
    );
    glEnableVertexAttribArray(posAttribLocation);

    GLuint normalAttribLocation = glGetAttribLocation(shaderProgram, "aNormal");
    glVertexAttribPointer(
        normalAttribLocation,       // позиція атрибуту знайдена командою glGetAttribLocation
        3,                          // 3 компоненти: nx, ny, nz
        GL_FLOAT,                   // тип даних
        GL_FALSE,                   // не нормалізувати
        6 * sizeof(float),          // stride: 6 float-а на вершину
        (void*)(3 * sizeof(float))  // offset: починаємо з 3
    );
    glEnableVertexAttribArray(normalAttribLocation);

    glBindVertexArray(0); // деактивувати VAO

    GLint model_loc = glGetUniformLocation(shaderProgram, "uModel");
    GLint view_loc = glGetUniformLocation(shaderProgram, "uView");
    GLint proj_loc = glGetUniformLocation(shaderProgram, "uProjection");

    // Uniform-локації для матеріалу
    GLint materialAmbient_loc  = glGetUniformLocation(shaderProgram, "uMaterialAmbient");
    GLint materialDiffuse_loc  = glGetUniformLocation(shaderProgram, "uMaterialDiffuse");
    GLint materialSpecular_loc = glGetUniformLocation(shaderProgram, "uMaterialSpecular");
    GLint shininess_loc        = glGetUniformLocation(shaderProgram, "uShininess");

    // Матеріал: copper — http://devernay.free.fr/cours/opengl/materials.html
    glm::vec3 materialAmbient = glm::vec3(0.19125, 0.0735, 0.0225);
    glm::vec3 materialDiffuse = glm::vec3(0.7038, 0.27048, 0.0828);
    glm::vec3 materialSpecular = glm::vec3(0.256777, 0.137622, 0.086014);
    float     shininess        = 0.01f * 128.0f;  // = 27.9f

    // // Матеріал: silver — http://devernay.free.fr/cours/opengl/materials.html
    // glm::vec3 materialAmbient = glm::vec3(0.19225	,0.19225	,0.19225);
    // glm::vec3 materialDiffuse = glm::vec3(0.50754	,0.50754	,0.50754);
    // glm::vec3 materialSpecular = glm::vec3(0.508273	,0.508273,	0.508273);
    // float     shininess        = 0.4f * 128.0f;  // = 27.9f

    // Матеріал: gold — http://devernay.free.fr/cours/opengl/materials.html
    // glm::vec3 materialAmbient = glm::vec3(0.24725,	0.1995	,0.0745);
    // glm::vec3 materialDiffuse = glm::vec3(0.75164,	0.60648	,0.22648);
    // glm::vec3 materialSpecular = glm::vec3(0.628281,	0.555802,	0.366065);
    // float     shininess        = 0.4f * 128.0f;  // = 27.9f

    // Матеріал: obsidian (obsidian) — http://devernay.free.fr/cours/opengl/materials.html
    // glm::vec3 materialAmbient = glm::vec3(0.05375, 0.05, 0.06625);
    // glm::vec3 materialDiffuse = glm::vec3(0.18275, 0.17, 0.22525);
    // glm::vec3 materialSpecular = glm::vec3(0.332741, 0.328634, 0.346435);
    // float     shininess        = 0.3f * 128.0f;  // = 27.9f

    // Матеріал: бронза (bronze) — http://devernay.free.fr/cours/opengl/materials.html
    // glm::vec3 materialAmbient = glm::vec3(0.2125, 0.1275, 0.054);
    // glm::vec3 materialDiffuse = glm::vec3(0.714, 0.4284, 0.18144);
    // glm::vec3 materialSpecular = glm::vec3(0.393548, 0.271906, 0.166721);
    // float     shininess        = 0.2f * 128.0f;  // = 27.9f

    // Матеріал: Brass (латунь) — http://devernay.free.fr/cours/opengl/materials.html
    // glm::vec3 materialAmbient  = glm::vec3(0.329412f, 0.223529f, 0.027451f);
    // glm::vec3 materialDiffuse  = glm::vec3(0.780392f, 0.568627f, 0.113725f);
    // glm::vec3 materialSpecular = glm::vec3(0.992157f, 0.941176f, 0.807843f);
    // float     shininess        = 0.21794872f * 128.0f;  // = 27.9f

    // Uniform-локації для напрямленого світла
    GLint lightDir_loc   = glGetUniformLocation(shaderProgram, "uLightDir");
    GLint lightColor_loc = glGetUniformLocation(shaderProgram, "uLightColor");
    GLint cameraPos_loc    = glGetUniformLocation(shaderProgram, "uCameraPos");


    // Параметри напрямленого світла
    glm::vec3 lightDir   = glm::normalize(glm::vec3(-1.0f, -0.2f, 0.2f)); // напрямок ВІД джерела
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);                  // біле світло

    glm::mat4 model = glm::mat4(1.0f);

    glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 4.0f); // позиція камери
    glm::mat4 view = glm::lookAt(
        cameraPos,                                // позиція камери
        glm::vec3(0.0f, 0.0f, 0.0f),        // куди дивимось
        glm::vec3(0.0f, 1.0f, 0.0f)         // вектор вгору
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

        model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform3fv(lightDir_loc,          1, glm::value_ptr(lightDir));
        glUniform3fv(lightColor_loc,        1, glm::value_ptr(lightColor));
        glUniform3fv(cameraPos_loc,           1, glm::value_ptr(cameraPos));

        glUniform3fv(materialAmbient_loc,   1, glm::value_ptr(materialAmbient));
        glUniform3fv(materialDiffuse_loc,   1, glm::value_ptr(materialDiffuse));
        glUniform3fv(materialSpecular_loc,  1, glm::value_ptr(materialSpecular));
        glUniform1f(shininess_loc,          shininess);

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
