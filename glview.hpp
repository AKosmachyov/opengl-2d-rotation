#ifndef GLVIEW_HPP
#define GLVIEW_HPP

#include <QGLWidget>

struct glView : QGLWidget
{
    glView();

    void initializeGL()override;
    void resizeGL(int w, int h)override;
    void paintGL()override;

};

#endif // GLVIEW_HPP
