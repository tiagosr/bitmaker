#include "emulatorview.h"

EmulatorView::EmulatorView(QWidget *parent, const QGLWidget* shareWidget, Qt::WindowFlags f) :
    QGLWidget(parent) {
}

EmulatorView::~EmulatorView() {
}

void EmulatorView::initializeGL() {
    qglClearColor(QColor(0,0,0,255));

}

void EmulatorView::paintGL() {
    drawTexture(QRectF())
}

void EmulatorView::resizeGL() {

}
