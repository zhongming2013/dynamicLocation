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

    QAction *switchScene;                        //�л�¥��
    QAction *exitAct;                                   //�˳�
    QAction *addRefNodeAct;                 //��Ӳο��ڵ�
    QAction *deleteRefNodeAct;            //ɾ���ο��ڵ�
    QAction *openComAct;                      //�򿪴���
    QAction *closeComAct;                      //�رմ���
    QAction *toggleRefNodeAct;           //�л���ʾ�ο��ڵ�
    QAction *findEmployeeAct;              //��ѯԱ��������Ϣ
    QAction *findLocationAct;                //��ѯ��ʷ��¼
    QAction *findTemperatureAct;        //��ѯ�¶���ʷ��¼
    QAction *aboutAct;                             //����

    MapScene *scene;
    MapView *view;

    EmployeeTableWidget *personalTableWidget;//��ʾԱ��������Ϣ

    ReferTableModel *referTableModel;
    ReferTableView *referTableView;//��ʾ�ο��ڵ���Ϣ������netID������ţ��¶ȼ�����ڵ�

    MobileTableModel *mobileTableModel;
    MobileTableView *mobileTableView;//��ʾ�ƶ��ڵ�������Ϣ

    QTextBrowser *sendTextBrowser;          //��ʾͨ�����ڷ��͵����ݼ�¼
    QTextBrowser *receivedTextBrowser;   //��ʾͨ�����ڽ��յ����ݼ�¼

    Win_QextSerialPort *com;                 //����
    SerialPortDialog *comDialog;                 //�򿪴������öԻ���
};

#endif // MAINWINDOW_H
