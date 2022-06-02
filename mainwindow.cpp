#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QMessageBox>
#include "version.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList names;
    auto ports = QSerialPortInfo::availablePorts();
    for(auto port: ports) {
        names.append(port.portName());
    }
    ui->name->addItems(names);
    if (!names.isEmpty()) {
        ui->name->setCurrentIndex(1);
    }

    QList<int> baudRates = {1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
    QStringList baudRates_;
    for(auto rate: baudRates) {
        baudRates_.append(QString::number(rate));
    }
    ui->baudRate->addItems(baudRates_);
    ui->baudRate->setCurrentIndex(baudRates.indexOf(9600));

    setWindowTitle(QString("mugi-serial %1").arg(VERSION));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateButtons() {
    ui->close->setEnabled(m_port != nullptr);
}

void MainWindow::on_open_clicked()
{
    if (m_port && m_port->isOpen()) {
        on_close_clicked();
    }

    QString name = ui->name->currentText();
    int baudRate = ui->baudRate->currentText().toInt();

    QSerialPort* port = new QSerialPort(name);
    port->setBaudRate(baudRate);
    if (!port->open(QIODevice::ReadWrite)) {
        QMessageBox::critical(this, "Error", QString("Cannot open %1").arg(name));
    } else {
        m_port = port;
        connect(m_port,SIGNAL(readyRead()), this,SLOT(onReadyRead()));
    }
    updateButtons();
}

void MainWindow::onReadyRead() {
    QByteArray data = m_port->readAll();
    ui->log->moveCursor(QTextCursor::End);
    ui->log->insertPlainText(QString::fromUtf8(data));
    ui->log->moveCursor(QTextCursor::End);
}

void MainWindow::on_close_clicked()
{
    m_port->close();
    m_port = nullptr;
    updateButtons();
}

void MainWindow::on_clean_clicked()
{
    ui->log->setPlainText("");
}
