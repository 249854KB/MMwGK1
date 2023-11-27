#include <GL/freeglut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);

    // Vertex 1: Red
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5, -0.5);

    // Vertex 2: Green
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.5, -0.5);

    // Vertex 3: Blue
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.0, 0.5);

    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Multi-Color Triangle");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

// Wszystkie kolory automatycznie zmieszały się na zasadzie gradietnu. Efekt końcowy w pliku Efekt-koncowy-1.png lub po uruchomieniu programu build/myprogram.exe