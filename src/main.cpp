#include <iostream>
#include <unistd.h>
#include <cmath>
#include <GL/glut.h>
#include <cwchar>
#include <IL/il.h>

using namespace std;

const int edginess = 50;

double offset_of_the_compression = 0.09;
double scale = 0.4;

double k = 0.6;
double g = 9.8;
double mas = 1;
double velocity = 0;

double spread = 50;
double length_of_spring = 0.6 * 8 * M_PI;
float rate = 1000000 / 30;

GLfloat vertices[][3] = {
    {3, -2, 25},
    {3, 2, 25},
    {-3, 2, 25},
    {-3, -2, 25},
    {3, -2, 18},
    {3, 2, 18},
    {-3, -2, 18},
    {-3, 2, 18}};

GLint surfaces[][4] = {
    {0, 1, 2, 3},
    {3, 2, 7, 6},
    {6, 7, 5, 4},
    {4, 5, 1, 0},
    {1, 5, 7, 2},
    {4, 0, 3, 6}};

GLfloat Top_ver[5][edginess][3];
GLfloat Down_ver[5][edginess][3];

GLuint textures[2];void loadTexture(GLuint *texture, const wchar_t *path)
{
    ILuint imageID;
    ilGenImages(1, &imageID);
    if (imageID == 0)
    {
        printf("Failed to generate image ID.\n");
        // Handle the failure appropriately
    }
    ilBindImage(imageID);

    // Convert wide string to regular string
    size_t path_len = wcslen(path) + 1;
    char *path_str = new char[path_len];
    wcstombs(path_str, path, path_len);

    if (ilLoadImage(path_str))
    {
        ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);

        // Set texture parameters for mipmapping
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Generate mipmaps
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), GL_RGB, GL_UNSIGNED_BYTE, ilGetData());
    }
    else
    {
        printf("[Texture loader] \"%s\" failed to load!\n", path);
    }

    ilDeleteImages(1, &imageID);
    delete[] path_str;
}


void makeQuad(GLfloat vertices_list[][3])
{
    for (int i = 0; i < edginess - 1; i++)
    {
        glBegin(GL_QUADS);
        for (int j = 0; j < edginess; j++)
        {
            glTexCoord2f(0, 0);
            glVertex3fv(&vertices_list[i + 1][j]);
            glTexCoord2f(1, 0);
            glVertex3fv(&vertices_list[i][j]);
            glTexCoord2f(1, 1);
            glVertex3fv(&vertices_list[i][j + 1]);
            glTexCoord2f(0, 1);
            glVertex3fv(&vertices_list[i + 1][j + 1]);
        }
        glEnd();
    }
}

void create_base()
{
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glEnable(GL_TEXTURE_2D);
    for (int i = 0; i < 6; i++)
    {
        glBegin(GL_QUADS);
        for (int j = 0; j < 4; j++)
        {
            int vertex = surfaces[i][j];
            GLfloat xv, yv;
            if (j == 0)
            {
                xv = 0.0;
                yv = 0.0;
            }
            else if (j == 1)
            {
                xv = 1.0;
                yv = 0.0;
            }
            else if (j == 2)
            {
                xv = 1.0;
                yv = 1.0;
            }
            else
            {
                xv = 0.0;
                yv = 1.0;
            }
            glTexCoord2f(xv, yv);
            glVertex3fv(vertices[vertex]);
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}

void create_sphere()
{
    glPushMatrix();
    GLUquadricObj *sphere = gluNewQuadric();
    glTranslatef(0, 0, 15);
    glPushMatrix();
    glTranslatef(0, 0, -15);
    glTranslatef(0, 0, length_of_spring - spread * scale + (length_of_spring - spread) * 0.05);
    glPushMatrix();
    glTranslatef(0, 0, -4.5);
    glTranslatef(0, 0, (length_of_spring - spread * scale) * 0.1);
    sphere = gluNewQuadric();
    gluSphere(sphere, 4, 32, 160);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void create_spring()
{
    GLfloat t[100], u[edginess];
    for (int i = 0; i < 100; i++)
    {
        t[i] = i * 8 * M_PI / 99.0;
    }
    for (int i = 0; i < edginess; i++)
    {
        u[i] = i * 2 * M_PI / (edginess - 1);
    }

    glPushMatrix();
    glTranslatef(0, 0, length_of_spring - spread * 0.4);
    glTranslatef(0, 0, (length_of_spring - spread * 0.4) * offset_of_the_compression);

    for (int i = 0; i < 99; i++)
    {
        glBegin(GL_QUADS);
        for (int j = 0; j < edginess; j++)
        {
            GLfloat point1[3] = {
                static_cast<GLfloat>(cos(t[i]) * (1.5 + cos(u[j]))),
                static_cast<GLfloat>(sin(t[i]) * (3.0 + cos(u[j]))),
                static_cast<GLfloat>(spread / length_of_spring * 0.4 * 0.6 * t[i] + sin(u[j]))};
            GLfloat point2[3] = {
                static_cast<GLfloat>(cos(t[i + 1]) * (1.5 + cos(u[j]))),
                static_cast<GLfloat>(sin(t[i + 1]) * (3.0 + cos(u[j]))),
                static_cast<GLfloat>(spread / length_of_spring * 0.4 * 0.6 * t[i + 1] + sin(u[j]))};
            GLfloat point3[3] = {
                static_cast<GLfloat>(cos(t[i + 1]) * (1.5 + cos(u[j + 1]))),
                static_cast<GLfloat>(sin(t[i + 1]) * (3.0 + cos(u[j + 1]))),
                static_cast<GLfloat>(spread / length_of_spring * 0.4 * 0.6 * t[i + 1] + sin(u[j + 1]))};
            GLfloat point4[3] = {
                static_cast<GLfloat>(cos(t[i]) * (1.5 + cos(u[j + 1]))),
                static_cast<GLfloat>(sin(t[i]) * (3.0 + cos(u[j + 1]))),
                static_cast<GLfloat>(spread / length_of_spring * 0.4 * 0.6 * t[i] + sin(u[j + 1]))};

            glTexCoord2f(0, 0);
            glVertex3fv(point1);
            glTexCoord2f(1, 0);
            glVertex3fv(point2);
            glTexCoord2f(1, 1);
            glVertex3fv(point3);
            glTexCoord2f(0, 1);
            glVertex3fv(point4);
        }
        glEnd();
    }
    glPopMatrix();
}

void create_top_sphere()
{
    glPushMatrix();
    GLUquadricObj *sphere = gluNewQuadric();
    glTranslatef(0, 0, 15);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, 1.5, 32, 160);
    glPopMatrix();
}

void create_two_spheres()
{
    glPushMatrix();
    GLUquadricObj *sphere = gluNewQuadric();
    glTranslatef(0, 0, length_of_spring - spread * scale + (length_of_spring - spread) * 0.01);
    glPushMatrix();
    glTranslatef(0, 0, (length_of_spring - spread * scale) * 0.1);
    glTranslatef(0, 0, -(4 * scale) * 0.1);

    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluSphere(sphere, 1.5, 32, 16);
    glPopMatrix();
    glPopMatrix();
}

void create_cylinders()
{
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glEnable(GL_TEXTURE_2D);

    makeQuad(Top_ver[0]);
    glPushMatrix();
    glTranslatef(0, 0, length_of_spring - spread * scale);
    glTranslatef(0, 0, (length_of_spring - spread * scale) * 0.06);
    glScalef(0.5, 0.5, spread / length_of_spring * scale);
    makeQuad(Top_ver[1]);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0, length_of_spring - spread * scale);
    glTranslatef(0, 0, (length_of_spring - spread * scale) * offset_of_the_compression);
    glScalef(0.5, 0.5, spread / length_of_spring * scale);
    makeQuad(Down_ver[0]);
    glPopMatrix();
    create_two_spheres();
    create_top_sphere();
    glDisable(GL_TEXTURE_2D);
}

void create_scene()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(270, 1, 0, 0);
    create_base();
    create_cylinders();
    create_spring();
    create_sphere();
    glPopMatrix();
}

void update_scene()
{
    create_scene();
    glutSwapBuffers();
    glutPostRedisplay();

    double delta_X = spread - length_of_spring;
    velocity += -k * delta_X + g * mas;
    spread += velocity;
    usleep(rate);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, static_cast<GLfloat>(w) / static_cast<GLfloat>(h), 1, 150);
    glTranslatef(0, 0, -50);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        exit(0);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    ilInit();  // Initialize DevIL
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    loadTexture(&textures[0], L"wood.jpg");
    loadTexture(&textures[1], L"C:\\Polibuda\\wood.png");
    glutCreateWindow("Spring Simulation");

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, 800.0 / 1000.0, 1, 150);
    glTranslatef(0, 0, -50);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(update_scene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
