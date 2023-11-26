
#include <GL/freeglut.h>

int currentView = 1;  // Default to the first view
void displayDefaultView() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_TRIANGLES);
     

    // Triangle 1 (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.25f);
    glVertex3f(-0.25f, -0.25f, 0.0f);
    glVertex3f(0.25f, -0.25f, 0.0f);

    // Triangle 2 (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.25f);
    glVertex3f(-0.25f, -0.25f, 0.0f);
    glVertex3f(0.0f, +0.25f, 0.0f);

    // Triangle 3 (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.25f);
    glVertex3f(0.25f, -0.25f, 0.0f);
    glVertex3f(0.0f, +0.25f, 0.0f);

    glEnd();

    glFlush();
}

void displayRightView() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);
    glBegin(GL_TRIANGLES);

    // Triangle 1 (Blue)
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.25f);
    glVertex3f(-0.25f, -0.25f, 0.0f);
    glVertex3f(0.25f, -0.25f, 0.0f);

    // Triangle 2 (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.25f);
    glVertex3f(-0.25f, -0.25f, 0.0f);
    glVertex3f(0.0f, +0.25f, 0.0f);

    // Triangle 3 (Green)
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.25f);
    glVertex3f(0.25f, -0.25f, 0.0f);
    glVertex3f(0.0f, +0.25f, 0.0f);

    glEnd();

    glFlush();
}

void display() {
    if (currentView == 1) {
        displayDefaultView();
    } else if (currentView == 2) {
        displayRightView();
    }

    glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y) {
    if (key == '1') {
        currentView = 1;
    } else if (key == '2') {
        currentView = 2;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("MMwGK - Lab 1");

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set clear color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Set orthographic projection

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
