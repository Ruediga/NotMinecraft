#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SimpleCubeRenderer.h"

SimpleCubeRenderer::SimpleCubeRenderer()
    :
    vao{ 0 }, vbo{ 0 },
    vertices{
        // Back face
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 5.0f,
        // Front face
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 5.0f,
        // Left face
        0.0f, 0.0f, 0.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 2.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 2.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 2.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 2.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 2.0f, 5.0f,
        // Right face
        0.0f, 0.0f, 0.0f, 3.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 3.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 3.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 3.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 3.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 3.0f, 5.0f,
        // Top Face
        0.0f, 0.0f, 0.0f, 4.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 4.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 4.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 4.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 4.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 4.0f, 5.0f,
        // Bottom face
        0.0f, 0.0f, 0.0f, 5.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 5.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 5.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 5.0f, 3.0f,
        0.0f, 0.0f, 0.0f, 5.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 5.0f, 5.0f }

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