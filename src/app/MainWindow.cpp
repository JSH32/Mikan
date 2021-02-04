#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) {
    QGridLayout* mainLayout = new QGridLayout;

    setLayout(mainLayout);
    setWindowTitle("mikan");
}

MainWindow::~MainWindow() {
    // Nothing yet
}