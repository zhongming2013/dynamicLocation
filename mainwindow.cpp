#include <QtGui>
#include <QTextEdit>
#include <QDockWidget>
#include <QTableWidget>
#include <QDialog>
#include <QMessageBox>
#include <QAbstractGraphicsShapeItem>
#include <math.h>
#include <QPropertyAnimation>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVector>
#include <QString>

#include "mainwindow.h"
#include "mapscene.h"
#include "employeeform.h"
#include "referencenode.h"
#include "mobilenode.h"
#include "define.h"
#include "locationRecordForm.h"
#include "room.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new MapScene;
    scene->setFloor(6,false);
    view = new MapView;
    view->setScene(scene);
    view->setCurrentScene(scene);
    view->addScene(scene->getFloor(),scene);

    createActions();
    createMenus();
    createStatusBar();
    createToolBars();
    createDockWidgets();

    connect(scene, SIGNAL(refreshEmployeeTableWidget(const int)),
            personalTableWidget, SLOT(updateTable(const int)));
    connect(toggleRefNodeAct, SIGNAL(triggered()), view, SLOT(sceneShowReferNode()));
    connect(addRefNodeAct, SIGNAL(triggered()), view, SLOT(sceneAddReferNode()));
    connect(deleteRefNodeAct, SIGNAL(triggered()), view, SLOT(sceneDeleteReferNode()));

    setCentralWidget(view);
    setMinimumSize(1000,550);
    setWindowIcon(QIcon(":/images/icon.jpg"));
    setWindowTitle(tr("IB Location"));
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    switchScene = new QAction(tr("Switch Floor"),this);
    switchScene->setStatusTip(tr("Switch to another floor scene"));
    connect(switchScene, SIGNAL(triggered()), view, SLOT(switchScenes()));

    exitAct = new QAction(tr("Exit"),this);
    exitAct->setStatusTip(tr("Close the windows"));
    connect(exitAct,SIGNAL(triggered()),this,SLOT(close()));

    addRefNodeAct = new QAction(tr("Add Ref..."),this);
    addRefNodeAct->setToolTip(tr("Add Reference"));
    addRefNodeAct->setStatusTip(tr("Add reference node"));
    deleteRefNodeAct = new QAction(tr("Delete Ref"), this);
    deleteRefNodeAct->setToolTip(tr("Delete Reference Node"));
    deleteRefNodeAct->setStatusTip(tr("Delete reference Node"));
    toggleRefNodeAct = new QAction(tr("Toggle Ref"),this);
    toggleRefNodeAct->setToolTip(tr("Toggle Show All Reference Node"));
    toggleRefNodeAct->setStatusTip(tr("Toggle Show All Reference Node"));

    openComAct = new QAction(tr("Open COM..."),this);
    openComAct->setStatusTip(tr("Config and open the serial port"));
    connect(openComAct,SIGNAL(triggered()),this,SLOT(openSerialPortDialog()));
    closeComAct = new QAction(tr("Close COM"),this);
    closeComAct->setDisabled(true);
    closeComAct->setStatusTip(tr("Close the serial port"));
    connect(closeComAct,SIGNAL(triggered()),this,SLOT(closeMyCom()));

    findEmployeeAct = new QAction(tr("Employee..."),this);
    findEmployeeAct->setStatusTip(tr("Find an employee"));
    connect(findEmployeeAct,SIGNAL(triggered()),this,SLOT(openFindEmployDialog()));
    findLocationAct = new QAction(tr("Location History..."),this);
    findLocationAct->setStatusTip(tr("Look up the location history"));
    connect(findLocationAct,SIGNAL(triggered()),this,SLOT(findLocation()));

    aboutAct = new QAction(tr("&About DL"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(aboutDL()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(openComAct);
    editMenu->addAction(closeComAct);
    editMenu->addSeparator();
    editMenu->addAction(addRefNodeAct);
    editMenu->addAction(deleteRefNodeAct);
    editMenu->addAction(toggleRefNodeAct);
    editMenu->addAction(switchScene);

    viewMenu = menuBar()->addMenu(tr("&View"));

    findMenu = menuBar()->addMenu(tr("&Find"));
    findMenu->addAction(findEmployeeAct);
    findMenu->addAction(findLocationAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createToolBars()
{
    openCOMToolBar = addToolBar(tr("&ToolBar"));
    openCOMToolBar->addAction(openComAct);
    openCOMToolBar->addAction(closeComAct);
    openCOMToolBar->addSeparator();
    openCOMToolBar->addAction(addRefNodeAct);
    openCOMToolBar->addAction(deleteRefNodeAct);
    openCOMToolBar->addAction(toggleRefNodeAct);
    openCOMToolBar->addAction(switchScene);
}

void MainWindow::createDockWidgets()
{
    //设置员工个人信息停靠窗口
    QDockWidget *dock=new QDockWidget(tr("Employee Information"),this);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    personalTableWidget = new EmployeeTableWidget;
    personalTableWidget->updateTable(1);
    dock->setWidget(personalTableWidget);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

    //设置参考节点信息停靠窗口
    dock=new QDockWidget(tr("Node Information"),this);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    referenceNodeModel = new NodeTableModel;
    referenceNodeView = new NodeView(referenceNodeModel);
    connect(referenceNodeView, SIGNAL(sendConfigMsg(const QByteArray)),
            this, SLOT(writeMyCom(const QByteArray)));
    dock->setWidget(referenceNodeView);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());
    //移动节点配置信息停靠窗口
    dock = new QDockWidget(tr("Mobile Node Config Message"), this);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    mobileTableModel = new MobileTableModel;
    mobileTableView = new MobileTableView(mobileTableModel);
    connect(mobileTableView, SIGNAL(sendConfigMsg(const QByteArray)),
            this, SLOT(writeMyCom(const QByteArray)));
    dock->setWidget(mobileTableView);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

    //设置接收信息历史停靠窗口
    dock=new QDockWidget(tr("Received History"),this);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    receivedTextBrowser = new QTextBrowser();
    receivedTextBrowser->setText(tr("Display all received message"));
    dock->setWidget(receivedTextBrowser);
    addDockWidget(Qt::BottomDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());

    //设置发送命令历史停靠窗口
    dock=new QDockWidget(tr("Send History"),this);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    sendTextBrowser = new QTextBrowser();
    sendTextBrowser->setText(tr("Display all send message"));
    dock->setWidget(sendTextBrowser);
    addDockWidget(Qt::BottomDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());
}

void MainWindow::openSerialPortDialog()
{
    serialPortDialog = new QDialog(this);

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
    connect(openPushButton,SIGNAL(clicked()),this,SLOT(openMyCom()));
    connect(cancelPushButton,SIGNAL(clicked()),serialPortDialog,SLOT(close()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topHLayout);
    mainLayout->addLayout(bottomHLayout);

    serialPortDialog->setLayout(mainLayout);
    serialPortDialog->setMinimumSize(200,200);
    serialPortDialog->setWindowTitle(tr("Config Serial Port"));

    serialPortDialog->show();
}

void MainWindow::openMyCom()
{
    serialPortDialog->close();

    QString portName = comComboBox->currentText();

    myCom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);
    //定义串口对象，并初始化

    if(myCom->open(QIODevice::ReadWrite))
    {
        statusBar()->showMessage(tr("Open %1 successfully").arg(portName));
        closeComAct->setDisabled(false);
        openComAct->setDisabled(true);
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

    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //当串口缓冲区有数据时进行读操作

    delete serialPortDialog;
}

void MainWindow::closeMyCom()
{
    myCom->close();
    delete myCom;
    closeComAct->setDisabled(true);
    openComAct->setDisabled(false);
    statusBar()->showMessage(tr("Close serial port successfully"));
}

void MainWindow::readMyCom()
{
    QByteArray temp = myCom->readAll();

    //读串口中的所有数据
    if(!temp.isEmpty())
    {
        receivedTextBrowser->append(temp.toHex());
        //转为整数数组
        int s = temp.size();
        QVector<int> incomeMsg;
        for(int i = 0; i != s; i++)
            incomeMsg.push_back(temp.at(i) & 0xFF);

        int type = incomeMsg.at(MSG_TYPE);
        switch(type)
        {
        case MOBILE_CFG_MSG:
            mobileTableModel->refreshMobileTable(incomeMsg);
            break;
        case MOBILE_LOC_MSG:
            view->getScene(incomeMsg.at(M_ROOM_FLOOR))->doMobileMsg(incomeMsg);
            break;
        case REFERENCE_TMP_MSG://此处不用break
            view->getScene(incomeMsg.at(RT_ROOM_FLOOR))->doTemperatureMsg(incomeMsg);
        case REFERENCE_CFG_MSG:
            referenceNodeModel->refreshNodeTable(incomeMsg);
            break;
        default:
            break;
        }
    }
}

void MainWindow::writeMyCom(const QByteArray array)
{
    int type = array.at(MSG_TYPE) & 0xFF;
    int len = 0;
    switch(type)
    {
    case REFERENCE_CFG_MSG:
        len = REFERENCE_CFG_MSG_LEN;
        break;
    case MOBILE_CFG_MSG:
        len = MOBILE_CFG_MSG_LEN;
        break;
    }
    myCom->write(array.left(len));//bug!,总是返回-1，暂时没办法判断信息一定发送成功！！！！
    sendTextBrowser->append(array.toHex());
    statusBar()->showMessage(tr("Send successfully!"));
}

void MainWindow::aboutDL()
{
    QMessageBox::about(this,tr("About Dynamic Location"),
                       tr("<h2> Dynamic Location 2.0</h2>"
                          "<p>Copyright &copy; zhongming 2012.11"
                          "<p>The <b>Dynamic Location</b> show the location"
                          "dynamicly.Also,it can config the reference node"
                          "and end-device node."));
}


void MainWindow::openFindEmployDialog()
{
    EmployeeForm *employee = new EmployeeForm(1,this);
    employee->show();
}

void MainWindow::openFindLocationDialog()
{
    locationRecordTableModel = new QSqlTableModel(this);
    locationRecordTableModel->setTable("location");
    locationRecordTableModel->setSort(0,Qt::AscendingOrder);
    locationRecordTableModel->setHeaderData(1, Qt::Horizontal, tr("NetID"));
    locationRecordTableModel->setHeaderData(2, Qt::Horizontal, tr("RoomID"));
    locationRecordTableModel->setHeaderData(3, Qt::Horizontal, tr("Help"));
    locationRecordTableModel->setHeaderData(4, Qt::Horizontal, tr("Time"));
    locationRecordTableModel->select();
    locationRecordTableView = new QTableView;//不能构造为this，否则无法弹出
    locationRecordTableView->setModel(locationRecordTableModel);
    locationRecordTableView->setColumnHidden(0, true);
    locationRecordTableView->resizeColumnsToContents();
    locationRecordTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    locationRecordTableView->show();
}

void MainWindow::findEmployee()
{

}

void MainWindow::findLocation()
{
    LocationRecordForm * form = new LocationRecordForm(this);
    form->show();
}
