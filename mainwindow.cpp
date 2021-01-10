#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    float transformMin = -10;
    float transformMax = 10;
    float transformStep = 0.5;

    float scaleMin = 0.01;
    float scaleMax = 10;
    float scaleStep = 1;

    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QVBoxLayout *vbox = new QVBoxLayout;

    QLabel *scaleLabel = new QLabel(tr("Масштаб"));
    vbox->addWidget(scaleLabel);

    QLabel *xScaleLabel = new QLabel(tr("X"));
    QDoubleSpinBox *xScaleSpinBox= new QDoubleSpinBox;
    xScaleSpinBox->setRange(scaleMin, scaleMax);
    xScaleSpinBox->setSingleStep(scaleStep);
    xScaleSpinBox->setValue(1);
    vbox->addWidget(xScaleLabel);
    vbox->addWidget(xScaleSpinBox);

    QLabel *yScaleLabel = new QLabel(tr("Y"));
    QDoubleSpinBox *yScaleSpinBox= new QDoubleSpinBox;
    yScaleSpinBox->setRange(scaleMin, scaleMax);
    yScaleSpinBox->setSingleStep(scaleStep);
    yScaleSpinBox->setValue(1);
    vbox->addWidget(yScaleLabel);
    vbox->addWidget(yScaleSpinBox);

    QLabel *rotationLabel = new QLabel(tr("Поворот"));
    QDoubleSpinBox *rotationSpinBox= new QDoubleSpinBox;
    rotationSpinBox->setRange(-360, 360);
    rotationSpinBox->setSingleStep(20);
    rotationSpinBox->setValue(0);
    vbox->addWidget(rotationLabel);
    vbox->addWidget(rotationSpinBox);

    QLabel *transformLabel = new QLabel(tr("Смещение"));
    vbox->addWidget(transformLabel);

    QLabel *xTransformLabel = new QLabel(tr("X"));
    QDoubleSpinBox *xTransformSpinBox= new QDoubleSpinBox;
    xTransformSpinBox->setRange(transformMin, transformMax);
    xTransformSpinBox->setSingleStep(transformStep);
    xTransformSpinBox->setValue(0);
    vbox->addWidget(xTransformLabel);
    vbox->addWidget(xTransformSpinBox);

    QLabel *yTransformLabel = new QLabel(tr("Y"));
    QDoubleSpinBox *yTransformSpinBox= new QDoubleSpinBox;
    yTransformSpinBox->setRange(transformMin, transformMax);
    yTransformSpinBox->setSingleStep(transformStep);
    yTransformSpinBox->setValue(0);
    vbox->addWidget(yTransformLabel);
    vbox->addWidget(yTransformSpinBox);

    QGroupBox *groupBox = new QGroupBox(tr("Управление"));
    groupBox->setLayout(vbox);

    glWidget = new GLWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(glWidget);
    mainLayout->addWidget(groupBox);
    widget->setLayout(mainLayout);

    setWindowTitle(tr("Rotation 3D"));

    connect(rotationSpinBox, SIGNAL(valueChanged(double)), glWidget, SLOT(setRotation(double)));
    connect(xScaleSpinBox, SIGNAL(valueChanged(double)), glWidget, SLOT(setXScale(double)));
    connect(yScaleSpinBox, SIGNAL(valueChanged(double)), glWidget, SLOT(setYScale(double)));
    connect(xTransformSpinBox, SIGNAL(valueChanged(double)), glWidget, SLOT(setXTransform(double)));
    connect(yTransformSpinBox, SIGNAL(valueChanged(double)), glWidget, SLOT(setYTransform(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
