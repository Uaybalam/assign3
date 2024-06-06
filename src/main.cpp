#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include "tiny_obj_loader.h"

float angle = 0.0f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
float cameraDistance = 5.0f;
int mouseX, mouseY;
bool isDragging = false;

void renderOBJ(const std::string& filename);
bool loadOBJ(const std::string& filename);
void saveScreenshot(const std::string& filename);

void timer(int value) {
    (void)value;  // Suppress unused parameter warning
    angle += 1.0f;
    if (angle > 360) angle -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void mouseMotion(int x, int y) {
    if (isDragging) {
        cameraAngleX += (x - mouseX) * 0.2f;
        cameraAngleY += (y - mouseY) * 0.2f;
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            mouseX = x;
            mouseY = y;
        } else {
            isDragging = false;
        }
    } else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            cameraDistance -= 0.5f;
            if (cameraDistance < 1.0f) cameraDistance = 1.0f;
        } else {
            cameraDistance += 0.5f;
        }
        glutPostRedisplay();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -cameraDistance);
    glRotatef(cameraAngleY, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleX, 0.0f, 1.0f, 0.0f);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    if (!loadOBJ("models/bugatti.obj")) {
        std::cerr << "Error loading model!" << std::endl;
    } else {
        renderOBJ("models/bugatti.obj");
    }

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D Model Viewer");

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        return 1;
    }

    glutDisplayFunc(display);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutTimerFunc(0, timer, 0);

    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
