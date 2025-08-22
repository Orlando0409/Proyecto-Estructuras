#include "cajerosdialog.h"
#include <QSplitter>

extern nodoCajero* listaCajero;

CajerosDialog::CajerosDialog(QWidget *parent)
    : QDialog(parent)
    , selectedCajeroId(-1)
{
    setupUI();
    setWindowTitle("Módulo de Cajeros - Banco Quiebra Segura R.L.");
    setMinimumSize(900, 600);
    resize(1000, 700);
    
    // Connect table selection change
    connect(cajerosTable->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &CajerosDialog::onTableSelectionChanged);
    
    // Initial table population
    updateTable();
}

void CajerosDialog::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Title
    QLabel *titleLabel = new QLabel("Gestión de Cajeros", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #2c3e50; margin-bottom: 20px;");
    mainLayout->addWidget(titleLabel);
    
    // Create splitter for content
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    mainLayout->addWidget(splitter);
    
    // Left panel - Form
    formGroup = new QGroupBox("Información del Cajero", this);
    formGroup->setMaximumWidth(350);
    formLayout = new QGridLayout(formGroup);
    formLayout->setSpacing(15);
    
    // ID field
    idLabel = new QLabel("ID del Cajero:", this);
    idSpinBox = new QSpinBox(this);
    idSpinBox->setRange(1, 9999);
    idSpinBox->setValue(1);
    formLayout->addWidget(idLabel, 0, 0);
    formLayout->addWidget(idSpinBox, 0, 1);
    
    // Número de caja field
    numCajaLabel = new QLabel("Número de Caja:", this);
    numCajaSpinBox = new QSpinBox(this);
    numCajaSpinBox->setRange(1, 6);
    numCajaSpinBox->setValue(1);
    formLayout->addWidget(numCajaLabel, 1, 0);
    formLayout->addWidget(numCajaSpinBox, 1, 1);
    
    // Nombre field
    nombreLabel = new QLabel("Nombre del Cajero:", this);
    nombreLineEdit = new QLineEdit(this);
    nombreLineEdit->setPlaceholderText("Ingrese el nombre completo");
    formLayout->addWidget(nombreLabel, 2, 0);
    formLayout->addWidget(nombreLineEdit, 2, 1);
    
    // Form buttons
    formButtonLayout = new QHBoxLayout();
    addButton = new QPushButton("Agregar", this);
    addButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #27ae60;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #229954; }"
        "QPushButton:pressed { background-color: #1e8449; }"
    );
    connect(addButton, &QPushButton::clicked, this, &CajerosDialog::addCajero);
    
    editButton = new QPushButton("Modificar", this);
    editButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #f39c12;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #e67e22; }"
        "QPushButton:pressed { background-color: #d35400; }"
    );
    editButton->setEnabled(false);
    connect(editButton, &QPushButton::clicked, this, &CajerosDialog::editCajero);
    
    clearButton = new QPushButton("Limpiar", this);
    clearButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #95a5a6;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #7f8c8d; }"
        "QPushButton:pressed { background-color: #34495e; }"
    );
    connect(clearButton, &QPushButton::clicked, this, &CajerosDialog::clearForm);
    
    formButtonLayout->addWidget(addButton);
    formButtonLayout->addWidget(editButton);
    formButtonLayout->addWidget(clearButton);
    formLayout->addLayout(formButtonLayout, 3, 0, 1, 2);
    
    splitter->addWidget(formGroup);
    
    // Right panel - Table
    tableGroup = new QGroupBox("Lista de Cajeros", this);
    tableLayout = new QVBoxLayout(tableGroup);
    
    cajerosTable = new QTableWidget(this);
    cajerosTable->setColumnCount(3);
    QStringList headers;
    headers << "ID Cajero" << "Número de Caja" << "Nombre del Cajero";
    cajerosTable->setHorizontalHeaderLabels(headers);
    cajerosTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    cajerosTable->setSelectionMode(QAbstractItemView::SingleSelection);
    cajerosTable->setAlternatingRowColors(true);
    cajerosTable->horizontalHeader()->setStretchLastSection(true);
    cajerosTable->verticalHeader()->setVisible(false);
    tableLayout->addWidget(cajerosTable);
    
    // Table buttons
    tableButtonLayout = new QHBoxLayout();
    deleteButton = new QPushButton("Eliminar Seleccionado", this);
    deleteButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #e74c3c;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #c0392b; }"
        "QPushButton:pressed { background-color: #a93226; }"
    );
    deleteButton->setEnabled(false);
    connect(deleteButton, &QPushButton::clicked, this, &CajerosDialog::deleteCajero);
    
    refreshButton = new QPushButton("Actualizar", this);
    refreshButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #3498db;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #2980b9; }"
        "QPushButton:pressed { background-color: #21618c; }"
    );
    connect(refreshButton, &QPushButton::clicked, this, &CajerosDialog::refreshTable);
    
    tableButtonLayout->addWidget(deleteButton);
    tableButtonLayout->addStretch();
    tableButtonLayout->addWidget(refreshButton);
    tableLayout->addLayout(tableButtonLayout);
    
    splitter->addWidget(tableGroup);
    
    // Set splitter proportions
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    
    // Bottom buttons
    bottomButtonLayout = new QHBoxLayout();
    closeButton = new QPushButton("Cerrar", this);
    closeButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #34495e;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 10px 20px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #2c3e50; }"
        "QPushButton:pressed { background-color: #1b2631; }"
    );
    connect(closeButton, &QPushButton::clicked, this, &QDialog::close);
    
    bottomButtonLayout->addStretch();
    bottomButtonLayout->addWidget(closeButton);
    mainLayout->addLayout(bottomButtonLayout);
}

void CajerosDialog::addCajero()
{
    if (!validateForm()) {
        return;
    }
    
    int id = idSpinBox->value();
    int numCaja = numCajaSpinBox->value();
    QString nombre = nombreLineEdit->text().trimmed();
    
    // Check if ID already exists
    nodoCajero* actual = listaCajero;
    while (actual != nullptr) {
        if (actual->getId() == id) {
            QMessageBox::warning(this, "Error", "El ID del cajero ya existe.");
            return;
        }
        if (actual->getNumeroCaja() == numCaja) {
            QMessageBox::warning(this, "Error", "El número de caja ya está en uso.");
            return;
        }
        actual = actual->siguiente;
    }
    
    // Check maximum number of cashiers
    int count = 0;
    actual = listaCajero;
    while (actual != nullptr) {
        count++;
        actual = actual->siguiente;
    }
    
    if (count >= 6) {
        QMessageBox::warning(this, "Error", "No se pueden agregar más cajeros. Máximo 6 cajeros.");
        return;
    }
    
    // Create new cashier
    nodoCajero* nuevoCajero = new nodoCajero();
    nuevoCajero->setId(id);
    nuevoCajero->setNumeroCaja(numCaja);
    nuevoCajero->setNombreCajero(nombre.toStdString());
    nuevoCajero->siguiente = listaCajero;
    nuevoCajero->inicio = nullptr;
    listaCajero = nuevoCajero;
    
    QMessageBox::information(this, "Éxito", "Cajero agregado correctamente.");
    clearForm();
    updateTable();
}

void CajerosDialog::editCajero()
{
    if (selectedCajeroId == -1) {
        QMessageBox::warning(this, "Error", "Seleccione un cajero para modificar.");
        return;
    }
    
    if (!validateForm()) {
        return;
    }
    
    int newId = idSpinBox->value();
    int newNumCaja = numCajaSpinBox->value();
    QString newNombre = nombreLineEdit->text().trimmed();
    
    // Find the cashier to edit
    nodoCajero* actual = listaCajero;
    while (actual != nullptr) {
        if (actual->getId() == selectedCajeroId) {
            // Check if new ID conflicts with other cashiers
            if (newId != selectedCajeroId) {
                nodoCajero* check = listaCajero;
                while (check != nullptr) {
                    if (check->getId() == newId && check != actual) {
                        QMessageBox::warning(this, "Error", "El nuevo ID ya existe.");
                        return;
                    }
                    check = check->siguiente;
                }
            }
            
            // Check if new box number conflicts
            if (newNumCaja != actual->getNumeroCaja()) {
                nodoCajero* check = listaCajero;
                while (check != nullptr) {
                    if (check->getNumeroCaja() == newNumCaja && check != actual) {
                        QMessageBox::warning(this, "Error", "El nuevo número de caja ya está en uso.");
                        return;
                    }
                    check = check->siguiente;
                }
            }
            
            // Update cashier
            actual->setId(newId);
            actual->setNumeroCaja(newNumCaja);
            actual->setNombreCajero(newNombre.toStdString());
            
            QMessageBox::information(this, "Éxito", "Cajero modificado correctamente.");
            selectedCajeroId = newId;  // Update selected ID
            clearForm();
            updateTable();
            return;
        }
        actual = actual->siguiente;
    }
    
    QMessageBox::warning(this, "Error", "Cajero no encontrado.");
}

void CajerosDialog::deleteCajero()
{
    if (selectedCajeroId == -1) {
        QMessageBox::warning(this, "Error", "Seleccione un cajero para eliminar.");
        return;
    }
    
    int reply = QMessageBox::question(this, "Confirmar", 
        "¿Está seguro de que desea eliminar este cajero?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply != QMessageBox::Yes) {
        return;
    }
    
    // Find and delete cashier
    nodoCajero* anterior = nullptr;
    nodoCajero* actual = listaCajero;
    
    while (actual != nullptr) {
        if (actual->getId() == selectedCajeroId) {
            // Check if cashier has clients
            if (actual->inicio != nullptr) {
                QMessageBox::warning(this, "Error", 
                    "No se puede eliminar el cajero porque tiene clientes en cola.");
                return;
            }
            
            if (anterior == nullptr) {
                listaCajero = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            
            delete actual;
            QMessageBox::information(this, "Éxito", "Cajero eliminado correctamente.");
            selectedCajeroId = -1;
            clearForm();
            updateTable();
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    
    QMessageBox::warning(this, "Error", "Cajero no encontrado.");
}

void CajerosDialog::refreshTable()
{
    updateTable();
}

void CajerosDialog::updateTable()
{
    cajerosTable->clearContents();
    cajerosTable->setRowCount(0);
    
    nodoCajero* actual = listaCajero;
    int row = 0;
    
    while (actual != nullptr) {
        cajerosTable->insertRow(row);
        
        cajerosTable->setItem(row, 0, new QTableWidgetItem(QString::number(actual->getId())));
        cajerosTable->setItem(row, 1, new QTableWidgetItem(QString::number(actual->getNumeroCaja())));
        cajerosTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(actual->getNombreCajero())));
        
        row++;
        actual = actual->siguiente;
    }
}

void CajerosDialog::onTableSelectionChanged()
{
    QList<QTableWidgetItem*> selectedItems = cajerosTable->selectedItems();
    
    if (selectedItems.isEmpty()) {
        selectedCajeroId = -1;
        editButton->setEnabled(false);
        deleteButton->setEnabled(false);
        return;
    }
    
    int selectedRow = selectedItems.first()->row();
    QTableWidgetItem* idItem = cajerosTable->item(selectedRow, 0);
    QTableWidgetItem* numCajaItem = cajerosTable->item(selectedRow, 1);
    QTableWidgetItem* nombreItem = cajerosTable->item(selectedRow, 2);
    
    if (idItem && numCajaItem && nombreItem) {
        selectedCajeroId = idItem->text().toInt();
        populateForm(selectedCajeroId, numCajaItem->text().toInt(), nombreItem->text());
        editButton->setEnabled(true);
        deleteButton->setEnabled(true);
    }
}

void CajerosDialog::populateForm(int id, int numCaja, const QString &nombre)
{
    idSpinBox->setValue(id);
    numCajaSpinBox->setValue(numCaja);
    nombreLineEdit->setText(nombre);
}

void CajerosDialog::clearForm()
{
    idSpinBox->setValue(1);
    numCajaSpinBox->setValue(1);
    nombreLineEdit->clear();
    selectedCajeroId = -1;
    editButton->setEnabled(false);
    deleteButton->setEnabled(false);
    cajerosTable->clearSelection();
}

bool CajerosDialog::validateForm()
{
    if (nombreLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "El nombre del cajero es obligatorio.");
        nombreLineEdit->setFocus();
        return false;
    }
    
    return true;
}