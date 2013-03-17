#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QGraphicsScene> //provides a surface for managing a large number of 2D graphical items
#include <QGraphicsView>  //a widget for displaying the contents of a QGraphicsScene
#include <QSqlTableModel>
#include <QVector>

class QTextBrowser;
class QTableWidget;
class QComboBox;
class QToolBar;
class QLineEdit;

#include "win_qextserialport.h"
#include "mapview.h"
#include "mapscene.h"
#include "node.h"
#include "refertablemodel.h"
#include "refertableview.h"
#include "employeeTableWidget.h"
#include "mobileTableModel.h"
#include "mobileTableView.h"
#include "serialportdialog.h"

class QMenu;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void openSerialPortDialog();
    void openCom();
    void closeCom();
    void readCom();
    void writeCom(const QByteArray);

    void findEmployee();
    void findLocation();
    void findTemperature();

    void aboutDL();

private:
    void createActions();
    void createMenus();
    void createStatusBar();
    void createToolBars();
    void createDockWidgets();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *findMenu;
    QMenu *helpMenu;
    QToolBar *openCOMToolBar;

    QAction *switchScene;                        //切换楼层
    QAction *exitAct;                                   //退出
    QAction *addRefNodeAct;                 //添加参考节点
    QAction *deleteRefNodeAct;            //删除参考节点
    QAction *openComAct;                      //打开串口
    QAction *closeComAct;                      //关闭串口
    QAction *toggleRefNodeAct;           //切换显示参考节点
    QAction *findEmployeeAct;              //查询员工具体信息
    QAction *findLocationAct;                //查询历史记录
    QAction *findTemperatureAct;        //查询温度历史记录
    QAction *aboutAct;                             //关于

    MapScene *scene;
    MapView *view;

    EmployeeTableWidget *personalTableWidget;//显示员工具体信息

    ReferTableModel *referTableModel;
    ReferTableView *referTableView;//显示参考节点信息，包括netID、房间号，温度检测周期等

    MobileTableModel *mobileTableModel;
    MobileTableView *mobileTableView;//显示移动节点配置信息

    QTextBrowser *sendTextBrowser;          //显示通过串口发送的数据记录
    QTextBrowser *receivedTextBrowser;   //显示通过串口接收的数据记录

    Win_QextSerialPort *com;                 //串口
    SerialPortDialog *comDialog;                 //打开串口配置对话框
};

#endif // MAINWINDOW_H
