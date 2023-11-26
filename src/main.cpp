#include <GL/freeglut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

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

    // glutSwapBuffers();
    glFlush(); // Required in single buffering
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("MMwGK - Lab 1");

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set clear color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Set orthographic projection

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
