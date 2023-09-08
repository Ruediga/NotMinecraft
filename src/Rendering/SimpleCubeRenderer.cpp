#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SimpleCubeRenderer.h"

SimpleCubeRenderer::SimpleCubeRenderer()
    :
    vao{ 0 }, vbo{ 0 },
    /*
    vertices{   0, 0, 0,  0, 0,
                0, 0, 0,  0, 1,
                0, 0, 0,  0, 2,
                0, 0, 0,  0, 3,
                0, 0, 0,  0, 4,
                0, 0, 0,  0, 5,

                0, 0, 0,  1, 0,
                0, 0, 0,  1, 1,
                0, 0, 0,  1, 2,
                0, 0, 0,  1, 3,
                0, 0, 0,  1, 4,
                0, 0, 0,  1, 5,

                0, 0, 0,  2, 0,
                0, 0, 0,  2, 1,
                0, 0, 0,  2, 2,
                0, 0, 0,  2, 3,
                0, 0, 0,  2, 4,
                0, 0, 0,  2, 5,

                0, 0, 0,  3, 0,
                0, 0, 0,  3, 1,
                0, 0, 0,  3, 2,
                0, 0, 0,  3, 3,
                0, 0, 0,  3, 4,
                0, 0, 0,  3, 5,

                0, 0, 0,  4, 0,
                0, 0, 0,  4, 1,
                0, 0, 0,  4, 2,
                0, 0, 0,  4, 3,
                0, 0, 0,  4, 4,
                0, 0, 0,  4, 5,

                0, 0, 0,  5, 0,
                0, 0, 0,  5, 1,
                0, 0, 0,  5, 2,
                0, 0, 0,  5, 3,
                0, 0, 0,  5, 4,
                0, 0, 0,  5, 5 }
                */
    vertices{
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 2.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 3.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 4.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 5.0f,

    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 2.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 3.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 4.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 5.0f,

    -0.5f,  0.5f,  0.5f,  2.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  2.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  2.0f, 2.0f,
    -0.5f, -0.5f, -0.5f,  2.0f, 3.0f,
    -0.5f, -0.5f,  0.5f,  2.0f, 4.0f,
    -0.5f,  0.5f,  0.5f,  2.0f, 5.0f,

     0.5f,  0.5f,  0.5f,  3.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  3.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  3.0f, 2.0f,
     0.5f, -0.5f, -0.5f,  3.0f, 3.0f,
     0.5f, -0.5f,  0.5f,  3.0f, 4.0f,
     0.5f,  0.5f,  0.5f,  3.0f, 5.0f,

    -0.5f, -0.5f, -0.5f,  4.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  4.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  4.0f, 2.0f,
     0.5f, -0.5f,  0.5f,  4.0f, 3.0f,
    -0.5f, -0.5f,  0.5f,  4.0f, 4.0f,
    -0.5f, -0.5f, -0.5f,  4.0f, 5.0f,

    -0.5f,  0.5f, -0.5f,  5.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  5.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  5.0f, 2.0f,
     0.5f,  0.5f,  0.5f,  5.0f, 3.0f,
    -0.5f,  0.5f,  0.5f,  5.0f, 4.0f,
    -0.5f,  0.5f, -0.5f,  5.0f, 5.0f }

    {
        shader = new Shader("src/Shaders/simpleCubeVertexShader.glsl", "src/Shaders/simpleCubeFragmentShader.glsl");

        unsigned int VAO, VBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /// position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // FaceID
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // VertexID
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(4 * sizeof(float)));
        glEnableVertexAttribArray(2);

        vao = VAO;
        vbo = VBO;
    }