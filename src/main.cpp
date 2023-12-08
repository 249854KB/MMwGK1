
#include <unistd.h>
#include <vector>
#include <GL/freeglut.h>

struct Point {
    float x;
    float y;
};

struct Triangle {
    float x;
    float y;
    float color[4]; // Color
};

int degree = 0;
const float speed = 1.5;
float rate = 1000000 / 60;

Point points[3] = {
    Point{-1.0, -1.0},
    Point{1.0, -1.0},
    Point{-1.0, 1.0}
};

std::vector<std::vector<Triangle>> triangles = {
    {
        Triangle{1, 3, {0.5, 0.2, 0.8, 1.0}}, // purple
        Triangle{-1, -1, {0.8, 0.7, 0.2, 1.0}}// yellow
        
    },
    {
        Triangle{1, 1, {0.2, 0.5, 0.8, 1.0}}, // light blue
        Triangle{3, 1, {0.8, 0.1, 0.1, 1.0}},  // dark red
        // Triangle{2, 2, {0.9, 0.8, 0.2, 1.0}},  // light yellow
        // Triangle{3, 1, {0.8, 0.2, 0.5, 1.0}}  // pinkish
    }
};

void show() {
    double rotation = (int)(degree * speed) % 360;
    degree += 1;
    double distance = abs(rotation / 360.0 * 2 - 1);

    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    for (int r = 0; r < 2; r++) {
        rotation = -rotation;

        for (int i = 0; i < 4; i++) {//4 razy rysujemy to samo tylko obrócone
            glPushMatrix();
            glRotated(90 * i, 0, 0, 1); 
            glRotated(-rotation, 0, 0, 1);
            glTranslated(0.5 * distance, 0.5 * distance, 0);

            for (Triangle triangle : triangles[r]) {
                glPushMatrix();
                glTranslated(triangle.x, triangle.y, 0);
                glTranslated(triangle.x * distance, triangle.y * distance, 0);
                glRotated(rotation * 2, 0, 0, 1);
                glColor4fv(triangle.color);

                glBegin(GL_POLYGON);
                glVertex2f(points[0].x, points[0].y);
                glVertex2f(points[1].x, points[1].y);
                glVertex2f(points[2].x, points[2].y);
                glEnd();

                glPopMatrix();
            }
            glPopMatrix();
        }
    }

    usleep(rate);
    glutPostRedisplay();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Lab 3");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, 800, 800);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glutDisplayFunc(show);
    glutMainLoop();
    return 0;
}
