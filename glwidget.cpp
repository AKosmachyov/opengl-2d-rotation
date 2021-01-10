#include "glwidget.h"
#include <math.h>
#include <QDebug>

float scale[2] = { 1, 1};
float position[2] = { 0, 0};
float rotation = 0;

int matrixSize = 3;
float frustumSize = 10.0;

GLfloat nodeMatrix[16] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    font = QFont();
    font.setBold(true);
}

void GLWidget::initializeGL()
{
    glClearColor(1, 1, 1, 1);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glLoadIdentity();

    float aspect = (float)w / h;
    if (aspect >= 1)
        glOrtho(-frustumSize * aspect,
                frustumSize * aspect,
                -frustumSize,
                frustumSize,
                1.0, -1.0);
    else
      glOrtho(-frustumSize,
              frustumSize,
              -frustumSize / aspect,
              frustumSize / aspect,
              1.0, -1.0);
}

void GLWidget::drawGrid()
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

    glColor3f(0.4, 0.4, 0.4);
    renderText(0.2, step * 2 , 0, "2", font);
    renderText(step * 2, 0.2, 0, "2", font);
}

void GLWidget::drawAxes(float color[3])
{
    GLfloat zero[3] = {0,0,0};
    glPushMatrix();
    {
        glScalef(frustumSize, frustumSize, 0);

        glColor3fv(color);

        glLineWidth(2);

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
        glEnd();

        renderText(0.9, 0, 0, "X", font);
        renderText(0, 0.9, 0, "Y", font);
    }
    glPopMatrix();
}

void drawArchimedeanSpiral(bool isLeftDirection)
{
    float fiStart = 0;
    float fiEnd = 2.12 * M_PI * 2;
    float steps = 100;
    float b = 0.5;

    float fiStep = (fiEnd - fiStart) / steps;
    if (isLeftDirection) {
        fiStep *= -1;
    }

    glColor3f(0, 0, 0);
    GLenum mode = isLeftDirection ? GL_LINES : GL_LINE_STRIP;
    glBegin(mode);
    for (int i = 0; i < steps; i++)
    {
        float angle = fiStep * i;
        float x = b * angle * cos(angle);
        float y = b * angle * sin(angle);

        glVertex2f(x, y);
    }
    glEnd();
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

void calculateViewMatrix(float rotation, float scale[2], float position[2], GLfloat final[16])
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

    multiply(translationMatrix, rotationMatrix, temp);
    multiply(temp, scaleMatrix, matrix);

    // column-major ordering https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glLoadMatrix.xml
    final[0] = matrix[0][0]; final[4] = matrix[0][1]; /* */ final[12] = matrix[0][2];
    final[1] = matrix[1][0]; final[5] = matrix[1][1]; /* */ final[13] = matrix[1][2];
    //
    final[3] = matrix[2][0]; final[7] = matrix[2][1]; /* */ final[15] = matrix[2][2];
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawGrid();
    float greyColor[3] = {0.52, 0.52, 0.52};
    drawAxes(greyColor);

    glPushMatrix();
    {
        glMultMatrixf(nodeMatrix);

        drawArchimedeanSpiral(false);
        drawArchimedeanSpiral(true);

        if (rotation != 0 || position[0] != 0 || position[1] != 0) {
            float axisColor[3] = {0.257, 0.71, 0.388};
            drawAxes(axisColor);
        }
    }
    glPopMatrix();
}

void GLWidget::setRotation(double angle)
{
    rotation = angle;
    updateMatrix();
}

void GLWidget::setXScale(double xScale)
{
    scale[0] = xScale;
    updateMatrix();
}

void GLWidget::setYScale(double yScale)
{
    scale[1] = yScale;
    updateMatrix();
}

void GLWidget::setXTransform(double xTransform)
{
    position[0] = xTransform;
    updateMatrix();
}

void GLWidget::setYTransform(double yTransform)
{
    position[1] = yTransform;
    updateMatrix();
}

void GLWidget::updateMatrix()
{
    calculateViewMatrix(rotation, scale, position, nodeMatrix);
    updateGL();
}


// Notes

// Draw lines
//    glPushMatrix();
//    {
//        glBegin(GL_LINES);
//            glColor3f(1, 0, 1);
//            glVertex3f(0, 0, 0); glVertex3f(-1, 0, 0);
//            glVertex3f(0, 1, 0); glVertex3f(-5, 1, 0);
//        glEnd();
//    }
//    glPopMatrix();

// Copy current matrix
// float mat[16];
// glGetFloatv(GL_MODELVIEW_MATRIX, mat);

// Replace current matrix
// glLoadMatrixf(viewMatrix);
