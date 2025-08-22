#include "clientesdialog.h"

extern nodoCajero* listaCajero;
extern int ticket;

ClientesDialog::ClientesDialog(QWidget *parent)
    : QDialog(parent)
    , selectedTicket(-1)
{
    setupUI();
    setWindowTitle("Módulo de Clientes - Banco Quiebra Segura R.L.");
    setMinimumSize(1000, 700);
    resize(1200, 800);
    
    // Connect age change to update type
    connect(edadSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [this](int edad) {
                if (edad >= 65) {
                    tipoValueLabel->setText("Adulto Mayor (Prioridad)");
                    tipoValueLabel->setStyleSheet("color: #e74c3c; font-weight: bold;");
                } else {
                    tipoValueLabel->setText("Cliente Regular");
                    tipoValueLabel->setStyleSheet("color: #27ae60; font-weight: bold;");
                }
            });
    
    // Initial queue population
    updateQueuesView();
}

void ClientesDialog::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Title
    QLabel *titleLabel = new QLabel("Gestión de Clientes y Colas", this);
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
    
    // Left panel - Client form
    formGroup = new QGroupBox("Agregar Nuevo Cliente", this);
    formGroup->setMaximumWidth(300);
    formLayout = new QGridLayout(formGroup);
    formLayout->setSpacing(15);
    
    // Age field
    edadLabel = new QLabel("Edad del Cliente:", this);
    edadSpinBox = new QSpinBox(this);
    edadSpinBox->setRange(18, 120);
    edadSpinBox->setValue(30);
    formLayout->addWidget(edadLabel, 0, 0);
    formLayout->addWidget(edadSpinBox, 0, 1);
    
    // Type field (read-only)
    tipoLabel = new QLabel("Tipo de Cliente:", this);
    tipoValueLabel = new QLabel("Cliente Regular", this);
    tipoValueLabel->setStyleSheet("color: #27ae60; font-weight: bold;");
    formLayout->addWidget(tipoLabel, 1, 0);
    formLayout->addWidget(tipoValueLabel, 1, 1);
    
    // Form buttons
    formButtonLayout = new QHBoxLayout();
    addClienteButton = new QPushButton("Agregar a Cola", this);
    addClienteButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #27ae60;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 10px 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #229954; }"
        "QPushButton:pressed { background-color: #1e8449; }"
    );
    connect(addClienteButton, &QPushButton::clicked, this, &ClientesDialog::addCliente);
    
    clearButton = new QPushButton("Limpiar", this);
    clearButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #95a5a6;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 10px 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #7f8c8d; }"
        "QPushButton:pressed { background-color: #34495e; }"
    );
    connect(clearButton, &QPushButton::clicked, this, &ClientesDialog::clearForm);
    
    formButtonLayout->addWidget(addClienteButton);
    formButtonLayout->addWidget(clearButton);
    formLayout->addLayout(formButtonLayout, 2, 0, 1, 2);
    
    splitter->addWidget(formGroup);
    
    // Middle panel - Actions
    actionsGroup = new QGroupBox("Acciones", this);
    actionsGroup->setMaximumWidth(250);
    actionsLayout = new QVBoxLayout(actionsGroup);
    actionsLayout->setSpacing(20);
    
    // Serve client section
    QLabel *serveLabel = new QLabel("Atender Cliente:", this);
    serveLabel->setStyleSheet("font-weight: bold; color: #2c3e50;");
    actionsLayout->addWidget(serveLabel);
    
    serveButton = new QPushButton("Atender Próximo Cliente", this);
    serveButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #3498db;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 12px 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #2980b9; }"
        "QPushButton:pressed { background-color: #21618c; }"
    );
    connect(serveButton, &QPushButton::clicked, this, &ClientesDialog::serveCliente);
    actionsLayout->addWidget(serveButton);
    
    // Separator
    QFrame *separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    actionsLayout->addWidget(separator);
    
    // Delete client section
    deleteLabel = new QLabel("Eliminar Cliente por Ticket:", this);
    deleteLabel->setStyleSheet("font-weight: bold; color: #2c3e50;");
    actionsLayout->addWidget(deleteLabel);
    
    QLabel *ticketLabel = new QLabel("Número de Ticket:", this);
    actionsLayout->addWidget(ticketLabel);
    
    ticketSpinBox = new QSpinBox(this);
    ticketSpinBox->setRange(1, 9999);
    ticketSpinBox->setValue(1);
    actionsLayout->addWidget(ticketSpinBox);
    
    deleteClienteButton = new QPushButton("Eliminar Cliente", this);
    deleteClienteButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #e74c3c;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 10px 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #c0392b; }"
        "QPushButton:pressed { background-color: #a93226; }"
    );
    connect(deleteClienteButton, &QPushButton::clicked, this, &ClientesDialog::deleteCliente);
    actionsLayout->addWidget(deleteClienteButton);
    
    actionsLayout->addStretch();
    
    splitter->addWidget(actionsGroup);
    
    // Right panel - Queues view
    queuesGroup = new QGroupBox("Estado de las Colas", this);
    queuesLayout = new QVBoxLayout(queuesGroup);
    
    queuesTree = new QTreeWidget(this);
    queuesTree->setHeaderLabels(QStringList() << "Cajero / Cliente" << "Información");
    queuesTree->setAlternatingRowColors(true);
    queuesTree->setRootIsDecorated(true);
    queuesTree->header()->setStretchLastSection(true);
    queuesLayout->addWidget(queuesTree);
    
    // Queue buttons
    queueButtonLayout = new QHBoxLayout();
    refreshButton = new QPushButton("Actualizar Colas", this);
    refreshButton->setStyleSheet(
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
    connect(refreshButton, &QPushButton::clicked, this, &ClientesDialog::refreshQueues);
    
    queueButtonLayout->addStretch();
    queueButtonLayout->addWidget(refreshButton);
    queuesLayout->addLayout(queueButtonLayout);
    
    splitter->addWidget(queuesGroup);
    
    // Set splitter proportions
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 0);
    splitter->setStretchFactor(2, 1);
    
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

void ClientesDialog::addCliente()
{
    if (!validateForm()) {
        return;
    }
    
    if (listaCajero == nullptr) {
        QMessageBox::warning(this, "Error", "No hay cajeros disponibles para atender clientes.");
        return;
    }
    
    int edad = edadSpinBox->value();
    
    // Create new client
    nodoCliente* nuevoCliente = new nodoCliente();
    nuevoCliente->setEdad(edad);
    nuevoCliente->setFicha(ticket++);
    
    // Find the best cashier (shortest queue or empty)
    nodoCajero* actual = listaCajero;
    
    // First, check for empty cashiers
    while (actual != nullptr) {
        if (actual->inicio == nullptr) {
            actual->inicio = nuevoCliente;
            QMessageBox::information(this, "Éxito", 
                QString("Cliente agregado al cajero vacío. Ticket: %1").arg(nuevoCliente->getFicha()));
            clearForm();
            updateQueuesView();
            return;
        }
        actual = actual->siguiente;
    }
    
    // If no empty cashiers, find the best position based on priority
    actual = listaCajero;
    
    if (nuevoCliente->getTipo() == "A") { // Adulto mayor - priority
        // Try to find a cashier with other priority clients first
        while (actual != nullptr) {
            if (actual->inicio != nullptr && actual->inicio->getTipo() == "A") {
                // Insert after other priority clients but before regular clients
                nodoCliente* clienteActual = actual->inicio;
                nodoCliente* anterior = nullptr;
                
                while (clienteActual != nullptr && clienteActual->getTipo() == "A") {
                    anterior = clienteActual;
                    clienteActual = clienteActual->siguiente;
                }
                
                if (anterior == nullptr) {
                    // Insert at beginning
                    nuevoCliente->siguiente = actual->inicio;
                    actual->inicio = nuevoCliente;
                } else {
                    // Insert after last priority client
                    nuevoCliente->siguiente = anterior->siguiente;
                    anterior->siguiente = nuevoCliente;
                }
                
                QMessageBox::information(this, "Éxito", 
                    QString("Cliente de prioridad agregado. Ticket: %1").arg(nuevoCliente->getFicha()));
                clearForm();
                updateQueuesView();
                return;
            }
            actual = actual->siguiente;
        }
        
        // If no cashier with priority clients, add to shortest queue at beginning
        actual = listaCajero;
        nodoCajero* mejorCajero = nullptr;
        int menorCola = INT_MAX;
        
        while (actual != nullptr) {
            int contadorCola = 0;
            nodoCliente* clienteActual = actual->inicio;
            while (clienteActual != nullptr) {
                contadorCola++;
                clienteActual = clienteActual->siguiente;
            }
            
            if (contadorCola < menorCola) {
                menorCola = contadorCola;
                mejorCajero = actual;
            }
            actual = actual->siguiente;
        }
        
        if (mejorCajero != nullptr) {
            nuevoCliente->siguiente = mejorCajero->inicio;
            mejorCajero->inicio = nuevoCliente;
            QMessageBox::information(this, "Éxito", 
                QString("Cliente de prioridad agregado al inicio de la cola. Ticket: %1").arg(nuevoCliente->getFicha()));
        }
    } else {
        // Regular client - add to shortest queue at the end
        nodoCajero* mejorCajero = nullptr;
        int menorCola = INT_MAX;
        
        while (actual != nullptr) {
            int contadorCola = 0;
            nodoCliente* clienteActual = actual->inicio;
            while (clienteActual != nullptr) {
                contadorCola++;
                clienteActual = clienteActual->siguiente;
            }
            
            if (contadorCola < menorCola) {
                menorCola = contadorCola;
                mejorCajero = actual;
            }
            actual = actual->siguiente;
        }
        
        if (mejorCajero != nullptr) {
            if (mejorCajero->inicio == nullptr) {
                mejorCajero->inicio = nuevoCliente;
            } else {
                nodoCliente* clienteActual = mejorCajero->inicio;
                while (clienteActual->siguiente != nullptr) {
                    clienteActual = clienteActual->siguiente;
                }
                clienteActual->siguiente = nuevoCliente;
            }
            QMessageBox::information(this, "Éxito", 
                QString("Cliente regular agregado al final de la cola. Ticket: %1").arg(nuevoCliente->getFicha()));
        }
    }
    
    clearForm();
    updateQueuesView();
}

void ClientesDialog::serveCliente()
{
    if (listaCajero == nullptr) {
        QMessageBox::warning(this, "Error", "No hay cajeros disponibles.");
        return;
    }
    
    nodoCajero* actual = listaCajero;
    bool clienteAtendido = false;
    
    // Find first cashier with clients
    while (actual != nullptr) {
        if (actual->inicio != nullptr) {
            nodoCliente* clienteParaAtender = actual->inicio;
            QString mensaje = QString("Cliente atendido:\nTicket: %1\nEdad: %2\nTipo: %3\nCajero: %4")
                            .arg(clienteParaAtender->getFicha())
                            .arg(clienteParaAtender->getEdad())
                            .arg(QString::fromStdString(clienteParaAtender->getTipo()))
                            .arg(actual->getNumeroCaja());
            
            actual->inicio = clienteParaAtender->siguiente;
            delete clienteParaAtender;
            clienteAtendido = true;
            
            QMessageBox::information(this, "Cliente Atendido", mensaje);
            updateQueuesView();
            return;
        }
        actual = actual->siguiente;
    }
    
    if (!clienteAtendido) {
        QMessageBox::information(this, "Información", "No hay clientes en cola para atender.");
    }
}

void ClientesDialog::deleteCliente()
{
    int ticketBuscar = ticketSpinBox->value();
    
    nodoCajero* actual = listaCajero;
    bool ticketeEncontrado = false;
    
    while (actual != nullptr && !ticketeEncontrado) {
        if (actual->inicio != nullptr && actual->inicio->getFicha() == ticketBuscar) {
            // Client is at the beginning of the queue
            nodoCliente* clienteActual = actual->inicio;
            actual->inicio = clienteActual->siguiente;
            delete clienteActual;
            ticketeEncontrado = true;
            QMessageBox::information(this, "Éxito", "Cliente eliminado correctamente.");
        } else if (actual->inicio != nullptr) {
            // Search in the middle/end of the queue
            nodoCliente* anterior = actual->inicio;
            nodoCliente* clienteActual = anterior->siguiente;
            
            while (clienteActual != nullptr) {
                if (clienteActual->getFicha() == ticketBuscar) {
                    anterior->siguiente = clienteActual->siguiente;
                    delete clienteActual;
                    ticketeEncontrado = true;
                    QMessageBox::information(this, "Éxito", "Cliente eliminado correctamente.");
                    break;
                }
                anterior = clienteActual;
                clienteActual = clienteActual->siguiente;
            }
        }
        actual = actual->siguiente;
    }
    
    if (!ticketeEncontrado) {
        QMessageBox::warning(this, "Error", "El ticket no existe en ninguna cola.");
    } else {
        updateQueuesView();
    }
}

void ClientesDialog::refreshQueues()
{
    updateQueuesView();
}

void ClientesDialog::updateQueuesView()
{
    queuesTree->clear();
    
    if (listaCajero == nullptr) {
        QTreeWidgetItem* noDataItem = new QTreeWidgetItem(queuesTree);
        noDataItem->setText(0, "No hay cajeros disponibles");
        noDataItem->setText(1, "");
        return;
    }
    
    nodoCajero* actual = listaCajero;
    int totalClientes = 0;
    
    while (actual != nullptr) {
        QTreeWidgetItem* cajeroItem = new QTreeWidgetItem(queuesTree);
        cajeroItem->setText(0, QString("Cajero %1 - %2")
                           .arg(actual->getNumeroCaja())
                           .arg(QString::fromStdString(actual->getNombreCajero())));
        
        int clientesEnCola = 0;
        nodoCliente* cliente = actual->inicio;
        
        if (cliente == nullptr) {
            cajeroItem->setText(1, "Cola vacía");
            cajeroItem->setForeground(1, QBrush(QColor("#95a5a6")));
        } else {
            while (cliente != nullptr) {
                QTreeWidgetItem* clienteItem = new QTreeWidgetItem(cajeroItem);
                clienteItem->setText(0, QString("Ticket %1").arg(cliente->getFicha()));
                clienteItem->setText(1, QString("Edad: %1, Tipo: %2")
                                   .arg(cliente->getEdad())
                                   .arg(QString::fromStdString(cliente->getTipo())));
                
                if (cliente->getTipo() == "A") {
                    clienteItem->setForeground(0, QBrush(QColor("#e74c3c")));
                    clienteItem->setForeground(1, QBrush(QColor("#e74c3c")));
                } else {
                    clienteItem->setForeground(0, QBrush(QColor("#27ae60")));
                    clienteItem->setForeground(1, QBrush(QColor("#27ae60")));
                }
                
                cliente = cliente->siguiente;
                clientesEnCola++;
            }
            
            cajeroItem->setText(1, QString("%1 clientes en cola").arg(clientesEnCola));
            totalClientes += clientesEnCola;
        }
        
        actual = actual->siguiente;
    }
    
    queuesTree->expandAll();
    
    // Update window title with client count
    setWindowTitle(QString("Módulo de Clientes - Total: %1 clientes en sistema").arg(totalClientes));
}

void ClientesDialog::onQueueSelectionChanged()
{
    // This could be used for future enhancements
}

void ClientesDialog::clearForm()
{
    edadSpinBox->setValue(30);
    tipoValueLabel->setText("Cliente Regular");
    tipoValueLabel->setStyleSheet("color: #27ae60; font-weight: bold;");
}

bool ClientesDialog::validateForm()
{
    // Age validation is handled by the spin box range
    return true;
}