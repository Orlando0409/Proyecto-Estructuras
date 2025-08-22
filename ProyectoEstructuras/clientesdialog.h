#ifndef CLIENTESDIALOG_H
#define CLIENTESDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QSpinBox>
#include <QGroupBox>
#include <QMessageBox>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSplitter>
#include "Clientes.h"
#include "Cajero.h"

class ClientesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientesDialog(QWidget *parent = nullptr);

private slots:
    void addCliente();
    void serveCliente();
    void deleteCliente();
    void refreshQueues();
    void onQueueSelectionChanged();
    void clearForm();

private:
    void setupUI();
    void updateQueuesView();
    bool validateForm();
    
    // Main layout
    QVBoxLayout *mainLayout;
    QHBoxLayout *contentLayout;
    
    // Left panel - Client form
    QGroupBox *formGroup;
    QGridLayout *formLayout;
    QLabel *edadLabel;
    QSpinBox *edadSpinBox;
    QLabel *tipoLabel;
    QLabel *tipoValueLabel;
    
    // Form buttons
    QHBoxLayout *formButtonLayout;
    QPushButton *addClienteButton;
    QPushButton *clearButton;
    
    // Middle panel - Queue management
    QGroupBox *actionsGroup;
    QVBoxLayout *actionsLayout;
    QPushButton *serveButton;
    QPushButton *deleteClienteButton;
    QLabel *deleteLabel;
    QSpinBox *ticketSpinBox;
    
    // Right panel - Queues view
    QGroupBox *queuesGroup;
    QVBoxLayout *queuesLayout;
    QTreeWidget *queuesTree;
    
    // Queue buttons
    QHBoxLayout *queueButtonLayout;
    QPushButton *refreshButton;
    
    // Bottom buttons
    QHBoxLayout *bottomButtonLayout;
    QPushButton *closeButton;
    
    // Business logic
    Cliente clienteManager;
    
    // Current selection
    int selectedTicket;
};

#endif // CLIENTESDIALOG_H