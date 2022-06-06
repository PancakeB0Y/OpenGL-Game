#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Matrix4.h"
#include "Parallelepiped.h"
#include "Obj.h"
#include "ObjFileModel.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    Parallelepiped* p = new Parallelepiped(1, 1, 1);
    p->setup();

    ObjFileModel* obj = new ObjFileModel("door.obj");
    obj->setup();;

    Obj* world = new Obj(NULL, Matrix4::Identity());
    Obj* test = new Obj(NULL, Matrix4::Identity());
    world->addChild(test);

    Obj* test1 = new Obj(p, Matrix4::Identity());
    test->addChild(test1);
    Obj* test2 = new Obj(p, Matrix4::Translation(0.3, 0, 0));
    test->addChild(test2);
    Obj* test3 = new Obj(p, Matrix4::Translation(-0.3, 0, 0));
    test->addChild(test3);
    Obj* test4 = new Obj(obj, Matrix4::Translation(0, -0.8, 0));
    test4->setTransform(Matrix4::Mul(test4->getTranform(), Matrix4::Scale(0.4, 0.4, 0.4)));
    test->addChild(test4);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // render loop
    // -----------
    GLfloat d = 0;
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        world->draw(Matrix4::Identity());
        test->setTransform(Matrix4::Mul(Matrix4::RotationY(0.0001), test->getTranform()));
        test2->setTransform(Matrix4::Mul(Matrix4::RotationX(0.0001), test2->getTranform()));

        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        d += 0.00001;
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}