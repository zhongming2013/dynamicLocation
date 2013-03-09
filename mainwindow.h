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
#include "nodetablemodel.h"
#include "nodeview.h"
#include "employeeTableWidget.h"
#include "mobileTableModel.h"
#include "mobileTableView.h"

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
    void openMyCom();
    void closeMyCom();
    void readMyCom();
    void writeMyCom(const QByteArray);

    void openFindEmployDialog();
    void findEmployee();
    void openFindLocationDialog();
    void findLocation();

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

    QAction *switchScene;
    QAction *exitAct;
    QAction *addRefNodeAct;//添加参考节点
    QAction *deleteRefNodeAct;//删除参考节点
    QAction *openComAct;
    QAction *closeComAct;
    QAction *showRefNodeAct;
    QAction *findEmployeeAct;
    QAction *findLocationAct;
    QAction *aboutAct;

    MapScene *scene;
    MapView *view;
    EmployeeTableWidget *personalTableWidget;
    NodeTableModel *referenceNodeModel;
    NodeView *referenceNodeView;//显示参考节点信息，包括netID、房间号，温度等
    MobileTableModel *mobileTableModel;
    MobileTableView *mobileTableView;//显示移动节点配置信息
    QTextBrowser *sendTextBrowser;
    QTextBrowser *receivedTextBrowser;

    Win_QextSerialPort *myCom;

    QDialog *serialPortDialog;
    QComboBox *comComboBox;
    QComboBox *baudComboBox;
    QComboBox *dataComboBox;
    QComboBox *parityComboBox;
    QComboBox *stopComboBox;

    QDialog *findEmployeeDialog;
    QLineEdit *findLine;
    QComboBox *findTypeComboBox;

    QDialog *findLocationDialog;
    QSqlTableModel *locationRecordTableModel;
    QTableView *locationRecordTableView;
    QComboBox *room;
    QComboBox *time;
    QLineEdit *name;
};

#endif // MAINWINDOW_H
