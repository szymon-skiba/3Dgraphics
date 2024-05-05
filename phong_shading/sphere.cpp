#include <GL/glut.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <thread>
#include "material.h"
#include "vector3.h"

using namespace std;


PhongMaterial material(
    Vector3(0.5, 0.5, 0.5), 
    Vector3(1., 1., 1.), 
    Vector3(0.9, 0.9, 0.9),
    Vector3(1., 1., 1.), 
    Vector3(0.1, 0.1, 0.1), 
    Vector3(1., 1., 1.),  
    30.0,
    100,
    100,
    Vector3(1.0, 1.0, 1.0), 
    Vector3(0.0, 0.0, 5.0)
    );

float rotation_angle = 0.0;

volatile bool needRedisplay = false;

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q': material.increaseDiffuse(0.1); break;
        case 'a': material.decreaseDiffuse(0.1); break;
        case 'w': material.increaseAmbient(0.1); break;
        case 's': material.decreaseAmbient(0.1); break;
        case 'e': material.increaseSpecular(0.1); break;
        case 'd': material.decreaseSpecular(0.1); break;
        case 'r': material.increaseExponent(0.1); break;
        case 'f': material.decreaseExponent(0.1); break;
        case 't': material.changeMerPar(5); break;
        case 'g': material.changeMerPar(-5); break;
        case 'z': rotation_angle -= 5.0; break;
        case 'x': rotation_angle += 5.0; break;
        case 'c': material.moveLightZ(0.5); break; 
        case 'v': material.moveLightZ(-0.5); break; 
        case ' ': rotation_angle = 0.0; break;
        default: break;
    }
    glutPostRedisplay(); 
}

void updateMaterialProperties() {
    while (true) {
        std::string property;
        float r, g, b;
        std::cout << "Enter the property to change (diffuse, specular, ambient) followed by RGB values: ";
        std::cin >> property >> r >> g >> b;

        if (property == "diffuse") {
            material.changeDiffuseColor(r, g, b);
        } else if (property == "specular") {
            material.changeSpecularColor(r, g, b);
        } else if (property == "ambient") {
            material.changeAmbientColor(r, g, b);
        } else {
            std::cout << "Invalid property. Please enter 'diffuse', 'specular', or 'ambient'." << std::endl;
            continue;
        }

        needRedisplay = true;
    }
}

void idleFunc() {
    if (needRedisplay) {
        glutPostRedisplay();
        needRedisplay = false;
    }
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 0.f);
}

void drawText(const char *text, int x, int y) {
    glMatrixMode(GL_PROJECTION); 
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix); 
    glLoadIdentity();
    glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -5.0, 5.0); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f); 
    glRasterPos2i(x, y);

    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);

    delete[] matrix;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity(); 
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(rotation_angle, 0.0, 1.0, 0.0); 

    GLUquadric* quad = gluNewQuadric(); 
    float radius = 1.0;

    int slices = material.getNmeridian();
    int stacks = material.getNparallel();

    for (int i = 0; i < slices; i++) {
        float theta = i * 2.0 * M_PI / slices; 
        float nextTheta = (i + 1) * 2.0 * M_PI / slices; 
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= stacks; j++) {
            float phi = j * M_PI / stacks; 
            Vector3 normals[2] = {
                Vector3(sin(phi) * cos(theta), cos(phi), sin(phi) * sin(theta)),
                Vector3(sin(phi) * cos(nextTheta), cos(phi), sin(phi) * sin(nextTheta))
            };
            Vector3 positions[2] = {
                radius * normals[0],
                radius * normals[1]
            };
            
            for (int k = 0; k < 2; k++) {
                normals[k] = normals[k].normalize();
                Vector3 color = material.Shade(positions[k], normals[k]);
                glColor3f(color.x, color.y, color.z); 
                glVertex3f(positions[k].x, positions[k].y, positions[k].z);
            }
        }
        glEnd();
    }

    gluDeleteQuadric(quad); 

    char info[128];
    Vector3 pos = material.getLightPosition();
    sprintf(info, "Light postion: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
    drawText(info, 325, 25);

    Vector3 matDiffuse = material.getMatDiffuse();
    Vector3 color = material.getDiffuseColor();
    sprintf(info, "Diffuse: %.2f", matDiffuse.x);
    drawText(info, 10, 25);
    sprintf(info, "Diffuse color: %.2f-%.2f-%.2f", color.x*255.f, color.y*255.f, color.z*255.f);
    drawText(info, 10, 40);

    Vector3 matAmbient = material.getMatAmbient();
    color = material.getAmbientColor();
    sprintf(info, "Ambient: %.2f", matAmbient.x);
    drawText(info, 10, 60);
    sprintf(info, "Ambient color: %.2f-%.2f-%.2f", color.x*255.f, color.y*255.f, color.z*255.f);
    drawText(info, 10, 75);

    Vector3 matSpecular = material.getMatSpecular();
    color = material.getSpecularColor();
    sprintf(info, "Specular: %.2f", matSpecular.x);
    drawText(info, 10, 95);
    sprintf(info, "Specular color: %.2f-%.2f-%.2f", color.x*255.f, color.y*255.f, color.z*255.f);
    drawText(info, 10, 110);

    float exponent = material.getExponent();
    sprintf(info, "Shineniness: %.2f", exponent);
    drawText(info, 10, 130);

    sprintf(info, "Number of quads: %dx%d", slices, stacks);
    drawText(info, 10, 145);



    glutSwapBuffers();
}



void startInputThread() {
    std::thread inputThread(updateMaterialProperties);
    inputThread.detach(); 
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT: material.moveLightX(0.5); break;
        case GLUT_KEY_LEFT: material.moveLightX(-0.5); break;
        case GLUT_KEY_UP: material.moveLightY(0.5); break;
        case GLUT_KEY_DOWN: material.moveLightY(-0.5); break; 
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(500, 500); 
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("3D Sphere with Phong Shading"); 

    init(); 
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape); 
    glutSpecialFunc(specialKeys); 
    glutIdleFunc(idleFunc);
    startInputThread(); 
    glutMainLoop();

    return 0;
}

