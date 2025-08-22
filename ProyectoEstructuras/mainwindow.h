#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QStackedWidget>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>

class CajerosDialog;
class ClientesDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openCajerosModule();
    void openClientesModule();
    void showAbout();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    
    // Central widget and layout
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    
    // Welcome section
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QLabel *welcomeLabel;
    
    // Module buttons
    QPushButton *cajerosButton;
    QPushButton *clientesButton;
    QPushButton *exitButton;
    
    // Menu actions
    QAction *aboutAction;
    QAction *exitAction;
    
    // Dialog windows
    CajerosDialog *cajerosDialog;
    ClientesDialog *clientesDialog;
};

#endif // MAINWINDOW_H