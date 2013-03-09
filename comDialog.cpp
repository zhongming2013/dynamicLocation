#include <QtGui>
#include "comDialog.h"


ComDialog::ComDialog(QWidget *parent)
    : QDialog(parent)
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
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topHLayout);
    mainLayout->addLayout(bottomHLayout);

    connect(openPushButton,SIGNAL(clicked()),this,SLOT(openMyCom()));
    connect(cancelPushButton,SIGNAL(clicked()),this,SLOT(close()));

    setLayout(mainLayout);
    setMinimumSize(200,200);
    setWindowTitle(tr("Config Serial Port"));
}

ComDialog::~ComDialog()
{

}

void ComDialog::openMyCom()
{
    close();

    QString portName = comComboBox->currentText();

    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);
    //定义串口对象，并初始化

    if(myCom->open(QIODevice::ReadWrite))
    {
        //statusBar()->showMessage(tr("Open %1 successfully").arg(portName));
        //configCloseComAct->setDisabled(false);
    }
    else
    {
        QMessageBox::critical(this,tr("Can't Open"),tr("Can not open %1.").arg(portName),QMessageBox::Ok);
        return;
    }
    //以可读可写的方式打开
    switch(baudComboBox->currentText().toInt())
    {
    case 9600:
        myCom->setBaudRate(BAUD9600);
        break;
    case 19200:
        myCom->setBaudRate(BAUD19200);
        break;
    case 38400:
        myCom->setBaudRate(BAUD38400);
        break;
    }
    if(dataComboBox->currentText() == tr("8"))
        myCom->setDataBits(DATA_8);
    else if(dataComboBox->currentText() == tr("7"))
        myCom->setDataBits(DATA_7);
    if(parityComboBox->currentText() == tr("N"))
        myCom->setParity(PAR_NONE);
    if(stopComboBox->currentText() == tr("1"))
        myCom->setStopBits(STOP_1);
    myCom->setFlowControl(FLOW_OFF);
    myCom->setTimeout(500);
}

Win_QextSerialPort* ComDialog::getMyCom()
{
    return myCom;
}
