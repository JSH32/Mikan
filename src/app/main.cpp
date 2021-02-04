#include <iostream>

#include <QtWidgets>
#include "MainWindow.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/logo.png"));

    MainWindow window;
    window.show();
    
    return app.exec();
}