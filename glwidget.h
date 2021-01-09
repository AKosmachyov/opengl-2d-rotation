#ifndef GLVIEW_HPP
#define GLVIEW_HPP

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public slots:
    void setRotation(double);
    void setXScale(double);
    void setYScale(double);
    void setXTransform(double);
    void setYTransform(double);
};

#endif // GLVIEW_HPP
