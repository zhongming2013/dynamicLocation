#include "serialportdialog.h"
#include <QLabel>
#include <QPushButton>
#include <QLayout>

SerialPortDialog::SerialPortDialog(QWidget *parent) :
    QDialog(parent)
{
    QLabel *comLabel = new QLabel(tr("Com:"));
    QLabel *baudLabel = new QLabel(tr("Baud:"));
    QLabel *dataLabel = new QLabel(tr("Data:"));
    QLabel *parityLabel = new QLabel(tr("Parity:"));
    QLabel *stopLabel = new QLabel(tr("Stop:"));

    comComboBox = new QComboBox;
    comComboBox->addItem(tr("COM1"));
    comComboBox->addItem(tr("COM2"));
    comComboBox->addItem(tr("COM3"));
    comComboBox->addItem(tr("COM4"));
    comComboBox->addItem(tr("COM5"));
    comComboBox->addItem(tr("COM6"));
    comComboBox->addItem(tr("COM7"));
    comComboBox->addItem(tr("COM8"));
    baudComboBox = new QComboBox;
    baudComboBox->addItem(tr("9600"));
    baudComboBox->addItem(tr("19200"));
    baudComboBox->addItem(tr("38400"));
    dataComboBox = new QComboBox;
    dataComboBox->addItem(tr("8"));
    dataComboBox->addItem(tr("7"));
    parityComboBox = new QComboBox;
    parityComboBox->addItem(tr("N"));
    parityComboBox->addItem(tr("O"));
    parityComboBox->addItem(tr("E"));
    stopComboBox = new QComboBox;
    stopComboBox->addItem(tr("1"));
    stopComboBox->addItem(tr("2"));

    QHBoxLayout *topHLayout = new QHBoxLayout;
    QVBoxLayout *labelLayout = new QVBoxLayout;
    QVBoxLayout *comboboxLayout = new QVBoxLayout;
    labelLayout->addWidget(comLabel);
    labelLayout->addWidget(baudLabel);
    labelLayout->addWidget(dataLabel);
    labelLayout->addWidget(parityLabel);
    labelLayout->addWidget(stopLabel);
    comboboxLayout->addWidget(comComboBox);
    comboboxLayout->addWidget(baudComboBox);
    comboboxLayout->addWidget(dataComboBox);
    comboboxLayout->addWidget(parityComboBox);
    comboboxLayout->addWidget(stopComboBox);
    topHLayout->addLayout(labelLayout);
    topHLayout->addLayout(comboboxLayout);

    QPushButton *openPushButton = new QPushButton(tr("Open COM"));
    QPushButton *cancelPushButton = new QPushButton(tr("Cancel"));
    QHBoxLayout *bottomHLayout = new QHBoxLayout;
    bottomHLayout->addWidget(cancelPushButton);
    bottomHLayout->addWidget(openPushButton);
    connect(openPushButton, SIGNAL(clicked()), this, SIGNAL(okToOpen()));
    connect(cancelPushButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topHLayout);
    mainLayout->addLayout(bottomHLayout);

    this->setLayout(mainLayout);
    this->setMinimumSize(200,200);
    this->setWindowTitle(tr("Config Serial Port"));
}

QString SerialPortDialog::getComName()
{
    return comComboBox->currentText();
}

int SerialPortDialog::getBaud()
{
    return baudComboBox->currentText().toInt();
}

int SerialPortDialog::getData()
{
    return dataComboBox->currentText().toInt();
}

QString SerialPortDialog::getParity()
{
    return parityComboBox->currentText();
}

int SerialPortDialog::getStop()
{
    return stopComboBox->currentText().toInt();
}
