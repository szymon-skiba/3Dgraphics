#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

#include "cube.h"
#include "transformations.h"
#include <stdio.h>

std::vector<Cube> globalCubes;
bool rightKeyPressed = false;
bool leftKeyPressed = false;
bool upKeyPressed = false;
bool downKeyPressed = false;
bool frowardKeyPressed = false;
bool backwardKeyPressed = false;
bool aKeyPressed = false;
bool dKeyPressed = false;
bool iKeyPressed = false;
bool oKeyPressed = false;
bool cursorInside = false;
bool zoomInKeyPressed = false;
bool zoomOutKeyPressed = false;
double xpos= -9999;
double ypos= -9999;
const Vector4 zoomCenter(0.0f, 0.0f, 0.0f); 




void drawCube(const Cube& cube) {
    glBegin(GL_LINES);
    const int lines[12][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};

    for (const auto& line : lines) {
        const auto& start = cube.vertices[line[0]];
        const auto& end = cube.vertices[line[1]];
        glVertex3f(start.x, start.y, start.z); 
        glVertex3f(end.x, end.y, end.z);
    }
    glEnd();
}

void translateCube(Cube& cube, const Matrix4x4& translationMatrix) {
    for (auto& vertex : cube.vertices) {
        vertex = translationMatrix * vertex; 
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_RIGHT) {
        rightKeyPressed = action != GLFW_RELEASE;
    }
    if (key == GLFW_KEY_LEFT) {
        leftKeyPressed = action != GLFW_RELEASE;
    }
    if (key == GLFW_KEY_UP) {
        upKeyPressed = action != GLFW_RELEASE;
    }
    if (key == GLFW_KEY_DOWN) {
        downKeyPressed = action != GLFW_RELEASE;
    }
    if (key == GLFW_KEY_W) {
        frowardKeyPressed = action != GLFW_RELEASE;
    }
    if (key == GLFW_KEY_S) {
        backwardKeyPressed = action != GLFW_RELEASE;
    }
    if (key == GLFW_KEY_A) {
        aKeyPressed = action != GLFW_RELEASE;
    }
    if (key == GLFW_KEY_D) {
        dKeyPressed = action != GLFW_RELEASE;
    }
    if (key == GLFW_KEY_I ) {
        TransformationManager::zoom(globalCubes, 1.2f,zoomCenter);
    }
    if (key == GLFW_KEY_O) {
        TransformationManager::zoom(globalCubes, 0.8f,zoomCenter); 
    } 
}

void manualPerspective(float fov, float aspect, float near, float far) {
    float f = 1.0f / tan(fov / 2.0f);
    float mat[16] = {
        f / aspect, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (far + near) / (near - far), (2.0f * far * near) / (near - far),
        0, 0, -1, 0
    };

    glLoadMatrixf(mat); 
}

void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = 1.0f; 
    manualPerspective(60.0 * M_PI / 180.0, aspect, 1.0f, 15.0f); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void renderScene() {
    for (const auto& cube : globalCubes) {
        drawCube(cube);
    }
}

void initializeCubes() {
    globalCubes.push_back(Cube(-10.0, 0.0f, -20.0, 10.0f));
    globalCubes.push_back(Cube(10.0, 0.0f, -20.0, 10.0f));
    globalCubes.push_back(Cube(-10.0, 0.0f, -40.0, 10.0f));
    globalCubes.push_back(Cube(10.0, 0.0f, -40.0, 10.0f));
}

void controlls(){   
    if (rightKeyPressed) {
        TransformationManager::moveRight(globalCubes);
    }
    if (leftKeyPressed) {
        TransformationManager::moveLeft(globalCubes);
    }
    if (upKeyPressed) {
        TransformationManager::moveUp(globalCubes);
    }
    if (downKeyPressed) {
        TransformationManager::moveDown(globalCubes);
    }
    if (frowardKeyPressed) {
        TransformationManager::moveForward(globalCubes);
    }
    if (backwardKeyPressed) {
        TransformationManager::moveBackward(globalCubes);
    }
    if (aKeyPressed) {
        TransformationManager::rotateZ(globalCubes, -0.002f); 
    }
    if (dKeyPressed) {
        TransformationManager::rotateZ(globalCubes, 0.002f); 
    }

    if(xpos<40 && xpos>1){
        TransformationManager::rotateY(globalCubes, 0.002f);
    }else if(xpos>600 && xpos<640){
        TransformationManager::rotateY(globalCubes, -0.002f);
    }

    if(ypos<40 && ypos>1){
        TransformationManager::rotateX(globalCubes, 0.002f);
    }else if(ypos>440 && ypos<480){
        TransformationManager::rotateX(globalCubes, -0.002f);
    }
}

void cursorEnterLeaveCallback(GLFWwindow* window, int entered) {
    if (!entered) {
        cursorInside = false;
        xpos=-9999;
        ypos=-9999;
    }else{
        cursorInside = true;
    }
}

void setUpControlls(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorEnterCallback(window, cursorEnterLeaveCallback);
}


int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(640, 480, "3D Cubes", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    setUpControlls(window);
    
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);

    initializeCubes(); 
    

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if(cursorInside){
            glfwGetCursorPos(window, &xpos, &ypos);
        }
        controlls();
        setupCamera();
        renderScene();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
