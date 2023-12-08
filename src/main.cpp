#include <unistd.h>
#include <vector>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h> // Include SOIL for texture loading

struct Mass {
    float x;
    float y;
    float radius;
    GLuint textureID; // Texture for the mass
};

struct Spring {
    float x;
    float y;
    float length;
    GLuint textureID; // Texture for the spring
};

struct Ceiling {
    GLuint textureID; // Texture for the ceiling
};

float massPosition = 0.0;
const float springLength = 3.0;
const float springConstant = 0.1;
const float dampingFactor = 0.05;
const float gravity = 0.005;

Mass mass = {0.0, 0.0, 1.0}; // Initial position and radius of the mass
Spring spring = {0.0, 0.0, springLength}; // Initial position and length of the spring
Ceiling ceiling;

void loadTextures() {
    // Load textures for the mass, spring, and ceiling
    mass.textureID = SOIL_load_OGL_texture("mass.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    spring.textureID = SOIL_load_OGL_texture("spring.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    ceiling.textureID = SOIL_load_OGL_texture("ceiling.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

void updatePhysics() {
    float displacement = massPosition - springLength;
    float springForce = -springConstant * displacement;
    float dampingForce = -dampingFactor * massPosition;

    float totalForce = springForce + dampingForce - gravity;
    float acceleration = totalForce / mass.radius;

    massPosition += acceleration;
}

void drawMass() {
    glBindTexture(GL_TEXTURE_2D, mass.textureID);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex2f(mass.x - mass.radius, mass.y - massPosition - mass.radius);
    glTexCoord2d(1, 0); glVertex2f(mass.x + mass.radius, mass.y - massPosition - mass.radius);
    glTexCoord2d(1, 1); glVertex2f(mass.x + mass.radius, mass.y - massPosition + mass.radius);
    glTexCoord2d(0, 1); glVertex2f(mass.x - mass.radius, mass.y - massPosition + mass.radius);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawSpring() {
    glBindTexture(GL_TEXTURE_2D, spring.textureID);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex2f(spring.x - 0.1, spring.y);
    glTexCoord2d(1, 0); glVertex2f(spring.x + 0.1, spring.y);
    glTexCoord2d(1, 1); glVertex2f(spring.x + 0.1, spring.y - springLength);
    glTexCoord2d(0, 1); glVertex2f(spring.x - 0.1, spring.y - springLength);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawCeiling() {
    glBindTexture(GL_TEXTURE_2D, ceiling.textureID);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex2f(-10, 10);
    glTexCoord2d(1, 0); glVertex2f(10, 10);
    glTexCoord2d(1, 1); glVertex2f(10, 9.9);
    glTexCoord2d(0, 1); glVertex2f(-10, 9.9);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void show() {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    updatePhysics();

    drawCeiling();
    drawSpring();
    drawMass();

    usleep(10000);
    glutPostRedisplay();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Mass on Spring Animation");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, 800, 800);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);
    loadTextures();

    glutDisplayFunc(show);
    glutMainLoop();
    return 0;
}
