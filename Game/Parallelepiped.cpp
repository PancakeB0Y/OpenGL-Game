#include "Parallelepiped.h"
#include "Utils.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 trans;\n"
"void main()\n"
"{\n"
"   gl_Position = trans * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

Parallelepiped::Parallelepiped(GLfloat w, GLfloat h, GLfloat d) {
	this->w = w;
	this->h = h;
	this->d = d;
}

void Parallelepiped::setup() {
	program = compileProgram(vertexShaderSource, fragmentShaderSource);
    GLfloat vertices[] = {
        0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
        0.5f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
        //cube sides
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.5f,

        0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f,
        //cube back
        0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f,
        0.0f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

void Parallelepiped::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(program);
}

void Parallelepiped::draw(Matrix4 m) {
    glUseProgram(program);
    unsigned int transformLoc = glGetUniformLocation(program, "trans");
    glUniformMatrix4fv(transformLoc, 1, GL_TRUE, (GLfloat*)m.a);

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_LINES, 0, 24);
}