#include "glwidget.h"
#include <math.h>

float scale[2] = { 1, 1};
float position[2] = { 0, 0};
float rotation = 0;

int matrixSize = 3;
float frustumSize = 10;

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

    glOrtho(-frustumSize, frustumSize, -frustumSize, frustumSize, 0, 10);

//    float aspect = w / h;
//    glOrtho(frustumSize * aspect / -2,
//            frustumSize * aspect / 2,
//            frustumSize / -2,
//            frustumSize / 2,
//            0, 10);
}

void drawGrid(void)
{
    glColor3f(0.8, 0.8, 0.8);
    float size = frustumSize;
    float step = 1;

    float i;
    for (i = 0; i < size; i+=step) {
        glBegin(GL_LINES);
            // Vertical
            glVertex2f(i, -size); glVertex2f(i, size);
            glVertex2f(-i, -size); glVertex2f(-i, size);

            // Horizontal
            glVertex2f(-size, i); glVertex2f(size, i);
            glVertex2f(-size, -i); glVertex2f(size, -i);
        glEnd();
    }
}

void drawAxes(float color[3])
{
    GLfloat zero[3] = {0,0,0};
    glPushMatrix();
    {
        glScalef(frustumSize, frustumSize, frustumSize);

        glColor3fv(color);

        glLineWidth(3);

        glBegin(GL_LINES);
        // X
        {
            glVertex3fv(zero);
            glVertex2f(1, 0);
        }
        // Y
        {
            glVertex3fv(zero);
            glVertex2f(0, 1);
        }
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

    drawGrid();
    float blackColor[3] = {0,0,0};
    drawAxes(blackColor);

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

        if (rotation != 0 || position[0] != 0 || position[1] != 0) {
            float axisColor[3] = {0.257, 0.71, 0.388};
            drawAxes(axisColor);
        }
    }
    glPopMatrix();

//    glPushMatrix();
//    {
//        glLoadIdentity();

//        glRotatef(10, 0, 0, 1);

//        float mat[16];
//        glGetFloatv(GL_MODELVIEW_MATRIX, mat);
//        int qwe = 1;
//    }
//    glPopMatrix();

//    glBegin(GL_LINES);
//        glColor3f(1, 0, 1);
//        glVertex3f(0, 0, 0); glVertex3f(-1, 0, 0);
//        glVertex3f(0, 0.2, 0); glVertex3f(-5, 0.2, 0);
//        glVertex3f(0, 0.4, 0); glVertex3f(-9, 0.4, 0);
//        glVertex3f(0, 0.6, 0); glVertex3f(-10, 0.6, 0);
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
