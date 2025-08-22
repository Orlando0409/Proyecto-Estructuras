#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("Banco Quiebra Segura R.L.");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Universidad Nacional de Costa Rica");
    
    // Create and show main window
    MainWindow window;
    window.show();
    
    return app.exec();
}