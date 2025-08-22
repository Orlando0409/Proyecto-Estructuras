#include "mainwindow.h"
#include "cajerosdialog.h"
#include "clientesdialog.h"
#include <QApplication>
#include <QMessageBox>
#include <QFont>
#include <QPixmap>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(nullptr)
    , cajerosDialog(nullptr)
    , clientesDialog(nullptr)
{
    setupUI();
    setupMenuBar();
    setupStatusBar();
    
    // Initialize dialogs
    cajerosDialog = new CajerosDialog(this);
    clientesDialog = new ClientesDialog(this);
    
    // Set window properties
    setWindowTitle("Banco Quiebra Segura R.L. - Sistema de Gestión");
    setMinimumSize(800, 600);
    resize(900, 700);
}

MainWindow::~MainWindow()
{
    // Dialogs will be automatically deleted as children
}

void MainWindow::setupUI()
{
    // Create central widget and main layout
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(30);
    mainLayout->setContentsMargins(50, 50, 50, 50);
    
    // Title section
    titleLabel = new QLabel("Banco Quiebra Segura R.L.", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(28);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #2c3e50; margin-bottom: 10px;");
    
    subtitleLabel = new QLabel("Sistema de Gestión Bancaria", this);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    QFont subtitleFont = subtitleLabel->font();
    subtitleFont.setPointSize(16);
    subtitleFont.setItalic(true);
    subtitleLabel->setFont(subtitleFont);
    subtitleLabel->setStyleSheet("color: #34495e; margin-bottom: 30px;");
    
    welcomeLabel = new QLabel("Bienvenido al sistema de gestión bancaria.\nSeleccione el módulo que desea utilizar:", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    QFont welcomeFont = welcomeLabel->font();
    welcomeFont.setPointSize(14);
    welcomeLabel->setFont(welcomeFont);
    welcomeLabel->setStyleSheet("color: #555555; margin-bottom: 40px;");
    
    // Add title section to layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(subtitleLabel);
    mainLayout->addWidget(welcomeLabel);
    
    // Create button layout
    buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(30);
    
    // Create module buttons
    cajerosButton = new QPushButton("Módulo de Cajeros", this);
    cajerosButton->setMinimumSize(200, 80);
    cajerosButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #3498db;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 10px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #21618c;"
        "}"
    );
    connect(cajerosButton, &QPushButton::clicked, this, &MainWindow::openCajerosModule);
    
    clientesButton = new QPushButton("Módulo de Clientes", this);
    clientesButton->setMinimumSize(200, 80);
    clientesButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #2ecc71;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 10px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #27ae60;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #1e8449;"
        "}"
    );
    connect(clientesButton, &QPushButton::clicked, this, &MainWindow::openClientesModule);
    
    // Add buttons to layout
    buttonLayout->addStretch();
    buttonLayout->addWidget(cajerosButton);
    buttonLayout->addWidget(clientesButton);
    buttonLayout->addStretch();
    
    // Add button layout to main layout
    mainLayout->addLayout(buttonLayout);
    
    // Exit button
    exitButton = new QPushButton("Salir", this);
    exitButton->setMaximumSize(120, 40);
    exitButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #e74c3c;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    padding: 8px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #c0392b;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #a93226;"
        "}"
    );
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);
    
    // Add exit button centered at bottom
    QHBoxLayout *exitLayout = new QHBoxLayout();
    exitLayout->addStretch();
    exitLayout->addWidget(exitButton);
    exitLayout->addStretch();
    
    mainLayout->addStretch();
    mainLayout->addLayout(exitLayout);
}

void MainWindow::setupMenuBar()
{
    // Create menu bar
    QMenuBar *mBar = this->menuBar();
    
    // File menu
    QMenu *fileMenu = mBar->addMenu("&Archivo");
    
    exitAction = new QAction("&Salir", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);
    
    // Modules menu
    QMenu *modulesMenu = mBar->addMenu("&Módulos");
    
    QAction *cajerosAction = new QAction("&Cajeros", this);
    cajerosAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
    connect(cajerosAction, &QAction::triggered, this, &MainWindow::openCajerosModule);
    modulesMenu->addAction(cajerosAction);
    
    QAction *clientesAction = new QAction("C&lientes", this);
    clientesAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_2));
    connect(clientesAction, &QAction::triggered, this, &MainWindow::openClientesModule);
    modulesMenu->addAction(clientesAction);
    
    // Help menu
    QMenu *helpMenu = mBar->addMenu("&Ayuda");
    
    aboutAction = new QAction("&Acerca de", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    helpMenu->addAction(aboutAction);
}

void MainWindow::setupStatusBar()
{
    QStatusBar *sBar = this->statusBar();
    sBar->showMessage("Listo - Universidad Nacional de Costa Rica - Estructuras de Datos 2024");
}

void MainWindow::openCajerosModule()
{
    if (cajerosDialog) {
        cajerosDialog->show();
        cajerosDialog->raise();
        cajerosDialog->activateWindow();
    }
}

void MainWindow::openClientesModule()
{
    if (clientesDialog) {
        clientesDialog->show();
        clientesDialog->raise();
        clientesDialog->activateWindow();
    }
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, "Acerca de Banco Quiebra Segura R.L.",
        "Sistema de Gestión Bancaria\n\n"
        "Versión: 1.0\n"
        "Desarrollado para: Universidad Nacional de Costa Rica\n"
        "Curso: Estructuras de Datos 2024\n\n"
        "Este sistema permite gestionar cajeros y clientes\n"
        "de manera eficiente a través de una interfaz gráfica\n"
        "moderna y fácil de usar.");
}