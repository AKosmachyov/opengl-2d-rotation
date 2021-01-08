#include "glview.hpp"

#include "basicmesh.h"

glView::glView()
{
    
}

static Mesh* cube;

void glView::initializeGL()
{
    cube = createCube(0.5);
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClearDepth(1.0);
    
    /* Use depth buffering for hidden surface elimination. */
    glEnable(GL_DEPTH_TEST);
    
    // Light settings
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat light_position[] = { -50.0, 50.0, 50.0, 1.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );
    
    glRotatef(-90, 1.0, 0.0, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);
}

void glView::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    
    QMatrix4x4 m;
    m.perspective(30, (qreal)w / (qreal)h, 1.0f, 1000.0f);
    glMultMatrixf(m.data());
}

void drawBox(GLfloat position[3])
{
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    
    {
        GLfloat color[] = { 1.0, 0.0, 1.0, 1.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        
        Mesh *mesh = cube;
        for (unsigned i=0; i < mesh->numIndices; i+=3) {
            glBegin(GL_TRIANGLES);
            for (int j=0; j<3; j++) {
                VertexData &v = mesh->vertices[mesh->indices[i+j]];
                glNormal3f(v.normal.x(), v.normal.y(), v.normal.z());
                glVertex3f(v.position.x(), v.position.y(), v.position.z());
            }
            glEnd();
        }
    }
    glPopMatrix();
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

void glView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    
    //Camera
    QMatrix4x4 m;
    m.lookAt(QVector3D(3, 6, 3),
//    m.lookAt(QVector3D(7.0, 8.0, 9.0),
             QVector3D(0.0, 0.0, 0.0),
             QVector3D(0.0, 1.0, 0.0) );
    glMultMatrixf(m.data());
    
    drawAxes();
    
    GLfloat positionFrontBox[3] = { 0, 1, 0};
    GLfloat positionTopBox[3] = { 0, 0, 1};
    GLfloat positionRightBox[3] = { 1, 0, 0};
    
    drawBox(positionFrontBox);
    drawBox(positionTopBox);
    drawBox(positionRightBox);
}
