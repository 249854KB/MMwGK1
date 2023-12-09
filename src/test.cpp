#include <GL/glut.h>
#include <SOIL/SOIL.h>

GLuint textures[2];

void loadTexture(const char *file, GLuint &textureID) {
    int width, height;
    unsigned char *image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGB);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
}

void drawTexturedCube(GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-0.5, -0.5, -0.5);
    glTexCoord2f(1, 0);
    glVertex3f(0.5, -0.5, -0.5);
    glTexCoord2f(1, 1);
    glVertex3f(0.5, 0.5, -0.5);
    glTexCoord2f(0, 1);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw the textured cubes for the minimap
    glColor3f(1.0, 1.0, 1.0);

    // Draw the first textured cube
    glPushMatrix();
    glTranslatef(-1.5, 0.0, 0.0);
    drawTexturedCube(textures[0]);
    glPopMatrix();

    // Draw the second textured cube
    glPushMatrix();
    glTranslatef(1.5, 0.0, 0.0);
    drawTexturedCube(textures[1]);
    glPopMatrix();

    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    loadTexture("wood.jpg", textures[0]);
    loadTexture("wood.png", textures[1]);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 1, 10);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Minimap Textured Cubes");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
