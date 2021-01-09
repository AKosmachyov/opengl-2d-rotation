#include "glwidget.h"
#include <math.h>

float scale[2] = { 1, 1};
float position[2] = { 0, 0};
float rotation = 0;

int matrixSize = 3;

GLfloat viewMatrix[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

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
    glOrtho(-4, 4, -4, 4, 0, 10);
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
        glColor3f(0,0,0);
        glVertex3fv(zero);
        glVertex3fv(X);
    }
    // Y - green
    {
        glColor3f(0,0,0);
        glVertex3fv(zero);
        glVertex3fv(Y);
    }
    glEnd();

    glPopMatrix();
}

void multiply(float mat1[3][3],
              float mat2[3][3],
              float res[3][3])
{
    int i, j, k;
    for (i = 0; i < matrixSize; i++) {
        for (j = 0; j < matrixSize; j++) {
            res[i][j] = 0;
            for (k = 0; k < matrixSize; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}

GLfloat * calculateViewMatrix(float rotation, float scale[2], float position[2])
{
    float matrix[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float temp[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    float translationMatrix[3][3] = {
        {1, 0, position[0]},
        {0, 1, position[1]},
        {0, 0, 1}
    };

    float rad = rotation * M_PI / 180;
    float rotationMatrix[3][3] = {
        {cos(rad), -sin(rad), 0},
        {sin(rad), cos(rad),  0},
        {0,        0,         1}
    };

    float scaleMatrix[3][3] = {
        {scale[0], 0,        0},
        {0,        scale[1], 0},
        {0,        0,        1}
    };

    multiply(scaleMatrix, rotationMatrix, temp);
    multiply(temp, translationMatrix, matrix);

    // column-major ordering https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glLoadMatrix.xml
    viewMatrix[0] = matrix[0][0]; viewMatrix[4] = matrix[0][1]; /* */ viewMatrix[12] = matrix[0][2];
    viewMatrix[1] = matrix[1][0]; viewMatrix[5] = matrix[1][1]; /* */ viewMatrix[13] = matrix[1][2];
    //
    viewMatrix[3] = matrix[2][0]; viewMatrix[7] = matrix[2][1]; /* */ viewMatrix[15] = matrix[2][2];
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    glPushMatrix();
    {
        glLoadMatrixf(viewMatrix);

        // Space between the spirals
        float a = 3, b = 2;

        glColor3f(1, 0, 0);
        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < 100; i++)
        {
            float angle = 0.1 * i;
            float x = (a + b * angle) * cos(angle);
            float y = (a + b * angle) * sin(angle);

            float length = x * x + y * y;
            float normX = x / length;
            float normY = y / length;
            glVertex3f(normX, normY, 0);
        }
        glEnd();

    }
    glPopMatrix();

//    glPushMatrix();
//    {
//        glLoadIdentity();

////        glRotatef(10, 0, 0, 1);

//        float mat[16];
//        glGetFloatv(GL_MODELVIEW_MATRIX, mat);
//        int qwe = 1;
//    }
//    glPopMatrix();

//
//    glColor3f(1, 1, 1);
//    drawSpiral(2, 2);

//    glBegin(GL_LINES);
//        glColor3f(1, 0, 0); glVertex3f(-1, -1, 0);
//        glColor3f(0, 1, 0); glVertex3f(0, 0, 0);
//        glColor3f(0, 0, 1); glVertex3f(1, -1, 0);
//    glEnd();
}

void GLWidget::setRotation(double angle)
{
    rotation = angle;
    calculateViewMatrix(rotation, scale, position);
    updateGL();
}

void GLWidget::setXScale(double xScale)
{
    scale[0] = xScale;
    calculateViewMatrix(rotation, scale, position);
    updateGL();
}

void GLWidget::setYScale(double yScale)
{
    scale[1] = yScale;
    calculateViewMatrix(rotation, scale, position);
    updateGL();
}

void GLWidget::setXTransform(double xTransform)
{
    position[0] = xTransform;
    calculateViewMatrix(rotation, scale, position);
    updateGL();
}

void GLWidget::setYTransform(double yTransform)
{
    position[1] = yTransform;
    calculateViewMatrix(rotation, scale, position);
    updateGL();
}
