#include <GL/freeglut.h>

GLfloat m_transX = 0;
GLfloat m_transY = 0;
GLfloat m_angle1 = 0;
GLfloat m_angle2 = 0;
GLuint ArmPart = 0;

GLfloat m_LeftDownPos[2] = {0.0, 0.0};
GLfloat m_RightDownPos[2] = {0.0, 0.0};
GLboolean m_LeftButtonDown = GL_FALSE;
GLboolean m_RightButtonDown = GL_FALSE;

void myPaint() {
    glPushMatrix();
    glTranslatef(m_transX, m_transY, 0);
    glRotatef(m_angle1, 0, 0, 1);

    glPushMatrix();
    glTranslatef(90, 0, 0);
    glRotatef(m_angle2, 0, 0, 1);
    glColor4f(0.0, 1.0, 0.0, 1.0);
    glCallList(ArmPart);
    glPopMatrix();

    glColor4f(1.0, 0.0, 0.0, 1.0);
    glCallList(ArmPart);
    glPopMatrix();
}

void drawArmPart() {
    glBegin(GL_POLYGON);
    glVertex2f(-10.0, 10.0);
    glVertex2f(-10.0, -10.0);
    glVertex2f(100.0, -10.0);
    glVertex2f(100.0, 10.0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    myPaint();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500.0 * (w / (float)h), 500.0 * (w / (float)h), -500.0 * (w / (float)h), 500.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

void motion(int x, int y) {
    if (m_LeftButtonDown) {
        m_angle1 += m_LeftDownPos[0] - x;
        m_angle2 += m_LeftDownPos[1] - y;
        m_LeftDownPos[0] = x;
        m_LeftDownPos[1] = y;
    } else if (m_RightButtonDown) {
        m_transX -= m_RightDownPos[0] - x;
        m_transY += m_RightDownPos[1] - y;
        m_RightDownPos[0] = x;
        m_RightDownPos[1] = y;
    }
    glutPostRedisplay();  // Request a redraw
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            m_LeftButtonDown = GL_TRUE;
            m_LeftDownPos[0] = x;
            m_LeftDownPos[1] = y;
        } else if (state == GLUT_UP) {
            m_LeftButtonDown = GL_FALSE;
        }
    } else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            m_RightButtonDown = GL_TRUE;
            m_RightDownPos[0] = x;
            m_RightDownPos[1] = y;
        } else if (state == GLUT_UP) {
            m_RightButtonDown = GL_FALSE;
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Double Pendulum");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    ArmPart = glGenLists(1);
    glNewList(ArmPart, GL_COMPILE);
    drawArmPart();
    glEndList();

    glutMainLoop();

    return 0;
}

//Udało się dodać płynną animację ruchu ręki. Dodawanie inputów w postaci myszki jest bardzo intuicyjne w opengl.