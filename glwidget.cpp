#include "glwidget.h"
#include <math.h>
#include "basicmesh.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

void GLWidget::initializeGL()
{
    glClearColor(1, 1, 1, 1);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void drawAxes(void)
{
    GLfloat zero[3] = {0,0,0};
    GLfloat X[3] = {1,0,0}, Y[3] = {0,1,0}, Z[3] = {0,0,1};
    glPushMatrix();

    glScalef(3, 3, 3);

    glLineWidth(2.0);

    glBegin(GL_LINES);
    // X -red
    {
        glColor3f(1,0,0);
        glVertex3fv(zero);
        glVertex3fv(X);
    }
    // Y - green
    {
        glColor3f(0,1,0);
        glVertex3fv(zero);
        glVertex3fv(Y);
    }
    // Z - blue
    {
        glColor3f(0,0,1);
        glVertex3fv(zero);
        glVertex3fv(Z);
    }
    glEnd();

    glPopMatrix();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
        glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
        glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
     glEnd();
}

void GLWidget::setXRotation(int angle)
{
    updateGL();
}

void GLWidget::setYRotation(int angle)
{
    updateGL();
}

void GLWidget::setZRotation(int angle)
{
    updateGL();
}
