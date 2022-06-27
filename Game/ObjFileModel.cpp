#include "ObjFileModel.h"
#include "ObjFile.h"
#include "Utils.h"

static const char* vertexShaderSource = "#version 330 core\n"
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

ObjFileModel::ObjFileModel(string filename) {
    this->filename = filename;
    file.load(filename);
}

void ObjFileModel::setup() {
    program = compileProgram(vertexShaderSource, fragmentShaderSource);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * file.data.size(), &file.data[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

void ObjFileModel::cleanup() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(program);
}

void ObjFileModel::draw(Matrix4 m) {
    glFrontFace(GL_CCW);
    glUseProgram(program);
    unsigned int transformLoc = glGetUniformLocation(program, "trans");
    glUniformMatrix4fv(transformLoc, 1, GL_TRUE, m.getFloatMatirx());

    GLfloat lx = 1;
    GLfloat ly = 1;
    GLfloat lz = 1;

    GLfloat l = sqrt(lx * lx + ly * ly + lz * lz) / 0.5;
    lx /= l; ly /= l; lz /= l;

    unsigned int lightLoc = glGetUniformLocation(program, "light");
    glUniform3f(lightLoc, lx, ly, lz);

    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, file.data.size() / 8);
}