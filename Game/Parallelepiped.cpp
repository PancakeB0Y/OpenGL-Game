#include "Parallelepiped.h"
#include "Utils.h"
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aNorm;\n"
"uniform mat4 trans;\n"
"out vec3 norm;\n"
"void main()\n"
"{\n"
"   norm = aNorm;\n"
"   gl_Position = trans * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   gl_Position.z *= gl_Position.w;\n"
"}\0";

static const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 norm;\n"
"uniform vec3 light;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(vec3(1.0f, 0.5f, 0.2f) * (clamp(dot(norm, light), 0, 1.0f) + 0.5), 1.0f);\n"
"}\n\0";

Parallelepiped::Parallelepiped(GLfloat w, GLfloat h, GLfloat d): VAO(0), VBO(0) {
	this->w = w;
	this->h = h;
	this->d = d;
}

void Parallelepiped::setup() {
	program = compileProgram(vertexShaderSource, fragmentShaderSource);
    GLfloat v[] = {
        //cube front
        0.0f, 0.0f, 0.0f, 0, 0, -1,
        w, 0.0f, 0.0f, 0, 0, -1,
        0.0f, h, 0.0f, 0, 0, -1,

        w, 0.0f, 0.0f, 0, 0, -1, 
        w, h, 0.0f, 0, 0, -1, 
        0.0f, h, 0.0f, 0, 0, -1,
        //cube back
        w, 0.0f, d, 0, 0, 1, 
        0.0f, 0.0f, d, 0, 0, 1,  
        w, h, d, 0, 0, 1,

        0.0f, 0.0f, d, 0, 0, 1,  
        0.0f, h, d, 0, 0, 1,  
        w, h, d, 0, 0, 1,
        //cube left side
        0.0f, 0.0f, d, -1, 0, 0,
        0.0f, 0.0f, 0.0f,  -1, 0, 0,
        0.0f, h, d, -1, 0, 0,

        0.0f, 0.0f, 0.0f, -1, 0, 0,
        0.0f, h, 0.0f, -1, 0, 0,
        0.0f, h, d, -1, 0, 0,
        //cube right side
        w, 0.0f, 0.0f, 1, 0, 0,
        w, 0.0f, d, 1, 0, 0,
        w, h, 0.0f, 1, 0, 0,

        w, 0.0f, d, 1, 0, 0,
        w, h, d, 1, 0, 0,
        w, h, 0.0f, 1, 0, 0,
        //cube top
        0.0f, 0.0f, d, 0, -1, 0,
        w, 0.0f, d, 0, -1, 0,
        0.0f, 0.0f, 0.0f, 0, -1, 0,

        w, 0.0f, d, 0, -1, 0,
        w, 0.0f, 0.0f, 0, -1, 0,
        0.0f, 0.0f, 0.0f, 0, -1, 0,
        //cube bottom
        0.0f, h, d, 0, 1, 0, 
        w, h, d, 0, 1, 0,
        0.0f, h, 0.0f, 0, 1, 0,

        w, h, d, 0, 1, 0,
        w, h, 0.0f, 0, 1, 0,
        0.0f, h, 0.0f, 0, 1, 0,
    };

    memcpy(vertices, v, sizeof(vertices));

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

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
    glDisable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glUseProgram(program);
    unsigned int transformLoc = glGetUniformLocation(program, "trans");
    glUniformMatrix4fv(transformLoc, 1, GL_TRUE, m.getFloatMatirx());

    GLfloat lx = 1;
    GLfloat ly = 1;
    GLfloat lz = 1;

    GLfloat l = (GLfloat)(sqrt(lx * lx + ly * ly + lz * lz) / 0.5);
    lx /= l; ly /= l; lz /= l;

    unsigned int lightLoc = glGetUniformLocation(program, "light");
    glUniform3f(lightLoc, lx, ly, lz);

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Parallelepiped::processTriangles(TriangleProcessor* processor, Matrix4 m) {
    for (int i = 0; i < 12; i++) {
        double p0[3] = { vertices[i * 18], vertices[i * 18 + 1], vertices[i * 18 + 2] };
        double p1[3] = { vertices[i * 18 + 6], vertices[i * 18 + 7], vertices[i * 18 + 8] };
        double p2[3] = { vertices[i * 18 + 12], vertices[i * 18 + 13], vertices[i * 18 + 14] };
        m.TransformInPlace(p0);
        m.TransformInPlace(p1);
        m.TransformInPlace(p2);
        processor->process(p0, p1, p2);
    }
}