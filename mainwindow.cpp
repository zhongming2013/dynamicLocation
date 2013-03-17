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
#include "temperaturefrom.h"

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
    connect(closeComAct,SIGNAL(triggered()),this,SLOT(closeCom()));

    findEmployeeAct = new QAction(tr("Employee..."),this);
    findEmployeeAct->setStatusTip(tr("Find an employee"));
    connect(findEmployeeAct,SIGNAL(triggered()),this,SLOT(findEmployee()));
    findLocationAct = new QAction(tr("Location History..."),this);
    findLocationAct->setStatusTip(tr("Look up the location history"));
    connect(findLocationAct,SIGNAL(triggered()),this,SLOT(findLocation()));
    findTemperatureAct = new QAction(tr("Temperature History..."), this);
    findTemperatureAct->setStatusTip(tr("Look up the temperature history"));
    connect(findTemperatureAct, SIGNAL(triggered()), this, SLOT(findTemperature()));

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
    findMenu->addAction(findTemperatureAct);

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
    referTableModel = new ReferTableModel;
    referTableView = new ReferTableView(referTableModel);
    connect(referTableView, SIGNAL(sendConfigMsg(const QByteArray)),
            this, SLOT(writeCom(const QByteArray)));
    dock->setWidget(referTableView);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    viewMenu->addAction(dock->toggleViewAction());
    //移动节点配置信息停靠窗口
    dock = new QDockWidget(tr("Mobile Node Config Message"), this);
    dock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    mobileTableModel = new MobileTableModel;
    mobileTableView = new MobileTableView(mobileTableModel);
    connect(mobileTableView, SIGNAL(sendConfigMsg(const QByteArray)),
            this, SLOT(writeCom(const QByteArray)));
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
    comDialog = new SerialPortDialog(this);
    connect(comDialog, SIGNAL(okToOpen()), this, SLOT(openCom()));
    comDialog->show();
}

void MainWindow::openCom()
{
    comDialog->close();

    QString portName = comDialog->getComName();

    com = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);
    //定义串口对象，并初始化

    if(com->open(QIODevice::ReadWrite))
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
    switch(comDialog->getBaud())
    {
    case 9600:
        com->setBaudRate(BAUD9600);
        break;
    case 19200:
        com->setBaudRate(BAUD19200);
        break;
    case 38400:
        com->setBaudRate(BAUD38400);
        break;
    }
    if(comDialog->getData() == 8)
        com->setDataBits(DATA_8);
    else if(comDialog->getData() == 7)
        com->setDataBits(DATA_7);

    if(comDialog->getParity() == "N")
        com->setParity(PAR_NONE);

    if(comDialog->getStop() == 1)
        com->setStopBits(STOP_1);

    com->setFlowControl(FLOW_OFF);
    com->setTimeout(500);

    connect(com,SIGNAL(readyRead()),this,SLOT(readCom()));
    //当串口缓冲区有数据时进行读操作
}

void MainWindow::closeCom()
{
    com->close();
    delete com;
    closeComAct->setDisabled(true);
    openComAct->setDisabled(false);
    statusBar()->showMessage(tr("Close serial port successfully"));
}

void MainWindow::readCom()
{
    QByteArray temp = com->readAll();

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
        case REFER_TMP_MSG:
            view->getScene(incomeMsg.at(RT_ROOM_FLOOR))->doTemperatureMsg(incomeMsg);
            break;
        case REFER_CFG_MSG:
            referTableModel->refreshReferTable(incomeMsg);
            break;
        default:
            break;
        }
    }
}

void MainWindow::writeCom(const QByteArray array)
{
    int type = array.at(MSG_TYPE) & 0xFF;
    int len = 0;
    switch(type)
    {
    case REFER_CFG_MSG:
        len = REFER_CFG_MSG_LEN;
        break;
    case MOBILE_CFG_MSG:
        len = MOBILE_CFG_MSG_LEN;
        break;
    }
    com->write(array.left(len));//bug!,总是返回-1，暂时没办法判断信息一定发送成功！！！！
    sendTextBrowser->append(array.toHex());
    statusBar()->showMessage(tr("Send successfully!"));
}

void MainWindow::aboutDL()
{
    QMessageBox::about(this,tr("About Intelligent Building Regional Positioning"),
                       tr("<h2>  Intelligent Building Regional Positioning 2.0</h2>"
                          "<p>Copyright &copy; zhongming 2012.11"
                          "<p>The <b> Intelligent Building Regional Positioning</b> show the location"
                          "dynamicly.Also,it can config the reference node"
                          "and end-device node."));
}


void MainWindow::findEmployee()
{
    EmployeeForm *employee = new EmployeeForm(1,this);
    employee->show();
}

void MainWindow::findLocation()
{
    LocationRecordForm * form = new LocationRecordForm(this);
    form->show();
}

void MainWindow::findTemperature()
{
    TemperatureFrom *form = new TemperatureFrom;
    form->show();
}
