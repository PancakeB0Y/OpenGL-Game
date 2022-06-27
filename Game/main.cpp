#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include "Matrix4.h"
#include "Parallelepiped.h"
#include "Obj.h"
#include "ObjFileModel.h"
#include "Calculate.h"

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;


Matrix4 cameraMatrix = Matrix4::Translation(0, 0, 0.5);
Matrix4 cameraMatrixX = Matrix4::Identity();


class Collider : public TriangleProcessor {
public:

    void process(double p0[3], double p1[3], double p2[3]) {

    }
} collider;

double collision(double pc[3], double vd[3], double p1[3], double p2[3], double p3[3]) {
    double v1[3]{ p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2] };
    double v2[3]{ p3[0] - p1[0], p3[1] - p1[1], p3[2] - p1[2] };

    double equation[3][4]{
        {vd[0], -v1[0], -v2[0], p1[0] - pc[0]},
        {vd[1], -v1[1], -v2[1], p1[1] - pc[1]},
        {vd[2], -v1[2], -v2[2], p1[2] - pc[2]}
    };

    bool r = Calculate::calcEq(equation);
    if (!r || equation[0][3] < 0 || equation[1][3] < 0 || equation[1][3] > 1
    || equation[2][3] < 0 || equation[2][3] > 1 || equation[1][3] + equation[2][3] > 1)
    return -1;
   
    return equation[0][3];
    
}

int main()
{
    

    /*Matrix4 m1 = Matrix4::Mul(Matrix4::Identity(), Matrix4::Translation(20, 0, 0));
    m1 = Matrix4::Mul(m1, Matrix4::RotationX(-1.57));
    m1 = Matrix4::Mul(m1, Matrix4::RotationY(1));

    Matrix4 m2 = Matrix4::Mul(Matrix4::Identity(), Matrix4::RotationY(-1));
    m2 = Matrix4::Mul(m2, Matrix4::RotationX(1.57));
    m2 = Matrix4::Mul(m2, Matrix4::Translation(-20, 0, 0));

    Matrix4 m3 = m1.Invert();

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            cout << m1.a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            cout << m2.a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            cout << m3.a[i][j] << " ";
        }
        cout << endl;
    }*/

    //cout << m1.a << endl << m2.a << endl << m3.a;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_SAMPLES, 4);

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    Parallelepiped* p = new Parallelepiped(0.5, 0.5, 0.5);
    p->setup();

    //ObjFileModel* obj = new ObjFileModel("door.obj");
    //obj->setup();;

    Obj* world = new Obj(NULL, Matrix4::Identity());
    Obj* test = new Obj(NULL, Matrix4::Translation(0, 0, 2));
    world->addChild(test);

    int n = 30;
    while (true) {
        double xRand = (rand() % 5 - 5.0) * 0.5;
        double zRand = (rand() % 5 - 5.0) * 0.5;
        Obj* test1 = new Obj(p, Matrix4::Translation(xRand, -0.70, zRand));
        test->addChild(test1);
        n--;
        if (n <= 0) {
            break;
        }

    }
    //Obj* test4 = new Obj(obj, Matrix4::Translation(0, 0, 0));
    //test4->setTransform(Matrix4::Mul(test4->getTranform(), Matrix4::Scale(0.4, 0.4, 0.4)));
    //test->addChild(test4);


    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_MULTISAMPLE);

    int cnt = 0;;
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

        //test->setTransform(Matrix4::Mul(Matrix4::Translation(0, 0, 2), Matrix4::RotationY(d)));
        //test2->setTransform(Matrix4::Mul(Matrix4::RotationX(d), Matrix4::Translation(0.3, 0, 0)));
        
        Matrix4 cameraFinal = Matrix4::Mul(cameraMatrix, cameraMatrixX);

        Matrix4 finalTransform = Matrix4::Mul(Matrix4::Projection(SCR_WIDTH, SCR_HEIGHT, 3.14 / 2, 0, 10), cameraFinal.Invert());

        world->processTriangles(&collider, finalTransform);

        world->draw(finalTransform);

        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        d += 0.00005;
        cnt++;
        //if ((cnt % 1000) == 0) cout << cnt << endl;
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
double curXpos = -1000000, curYpos = -1000000;

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        cameraMatrix = Matrix4::Mul(cameraMatrix, Matrix4::Translation(0, 0, 0.0001));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        cameraMatrix = Matrix4::Mul(cameraMatrix, Matrix4::Translation(0, 0, -0.0001));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        cameraMatrix = Matrix4::Mul(cameraMatrix, Matrix4::Translation(-0.0001, 0, 0));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        cameraMatrix = Matrix4::Mul(cameraMatrix, Matrix4::Translation(0.0001, 0, 0));
    }

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (curXpos > -1000000) {
        double dx = xpos - curXpos;
        double dy = ypos - curYpos;
        cameraMatrix = Matrix4::Mul(cameraMatrix, Matrix4::RotationY(dx / 100.0));
        cameraMatrixX = Matrix4::Mul(cameraMatrixX, Matrix4::RotationX(dy / 100.0));
    }

    curXpos = xpos;
    curYpos = ypos;

    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}