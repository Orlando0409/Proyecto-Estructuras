#ifndef CAJEROSDIALOG_H
#define CAJEROSDIALOG_H

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
#include "Cajero.h"

class CajerosDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CajerosDialog(QWidget *parent = nullptr);

private slots:
    void addCajero();
    void editCajero();
    void deleteCajero();
    void refreshTable();
    void onTableSelectionChanged();
    void clearForm();

private:
    void setupUI();
    void updateTable();
    void populateForm(int id, int numCaja, const QString &nombre);
    bool validateForm();
    
    // Main layout
    QVBoxLayout *mainLayout;
    QHBoxLayout *contentLayout;
    
    // Left panel - Form
    QGroupBox *formGroup;
    QGridLayout *formLayout;
    QLabel *idLabel;
    QSpinBox *idSpinBox;
    QLabel *numCajaLabel;
    QSpinBox *numCajaSpinBox;
    QLabel *nombreLabel;
    QLineEdit *nombreLineEdit;
    
    // Form buttons
    QHBoxLayout *formButtonLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *clearButton;
    
    // Right panel - Table
    QGroupBox *tableGroup;
    QVBoxLayout *tableLayout;
    QTableWidget *cajerosTable;
    
    // Table buttons
    QHBoxLayout *tableButtonLayout;
    QPushButton *deleteButton;
    QPushButton *refreshButton;
    
    // Bottom buttons
    QHBoxLayout *bottomButtonLayout;
    QPushButton *closeButton;
    
    // Business logic
    Cajero cajeroManager;
    
    // Current selection
    int selectedCajeroId;
};

#endif // CAJEROSDIALOG_H