#include "nodeview.h"
#include "define.h"

#include <QHeaderView>
#include <QInputDialog>
#include <QModelIndexList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

NodeView::NodeView(NodeTableModel *model) : QTableView()
{
    setModel(model);
    setColumnHidden(0, true);
    resizeColumnsToContents();
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    sendMsgAct = new QAction(tr("Send Config Message"),this);
    verticalHeader()->addAction(sendMsgAct);
    verticalHeader()->setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(sendMsgAct, SIGNAL(triggered()), this, SLOT(configMsgDialog()));
}

NodeView::~NodeView()
{

}

void NodeView::configMsgDialog()
{
    QModelIndexList indexList = selectedIndexes();
    int r = indexList.first().row();//获取在model中的行数，按照netId升序排序
    QSqlQuery q;
    int floor,number,tempPeriod;
    q.exec("SELECT netId,floor,number,tempPeriod FROM referNode ORDER BY netId");
    while(q.next())//获取原来的配置信息
    {
        if(0 == r--)
        {

            this->netId = q.value(0).toString();
            floor = q.value(1).toInt();
            number = q.value(2).toInt();
            tempPeriod = q.value(3).toInt();
            break;
        }
    }

    QDialog *referConfigDialog = new QDialog;
    QLabel *floorLabel = new QLabel(tr("Floor:"), referConfigDialog);
    QLabel *numberLabel = new QLabel(tr("Number:"), referConfigDialog);
    QLabel *periodLabel = new QLabel(tr("Period:"), referConfigDialog);

    floorEdit = new QLineEdit;
    floorEdit->setText(QString::number(floor));
    numberEdit = new QLineEdit;
    numberEdit->setText(QString::number(number));
    periodEdit = new QLineEdit;
    periodEdit->setText(QString::number(tempPeriod));

    floorLabel->setBuddy(floorEdit);
    numberLabel->setBuddy(numberEdit);
    periodLabel->setBuddy(periodEdit);

    QPushButton *okButton = new QPushButton(tr("OK"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(okToSend()));
    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), referConfigDialog, SLOT(close()));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(floorLabel, 0, 0);
    layout->addWidget(floorEdit, 0, 1);
    layout->addWidget(numberLabel, 1, 0);
    layout->addWidget(numberEdit, 1, 1);
    layout->addWidget(periodLabel, 2, 0);
    layout->addWidget(periodEdit, 2, 1);
    layout->addWidget(okButton, 3, 0);
    layout->addWidget(closeButton, 3, 1);

    referConfigDialog->setLayout(layout);
    referConfigDialog->setWindowTitle(tr("Send Refer Config Message"));
    referConfigDialog->show();
}

void NodeView::okToSend()
{
    int newFloor,newNumber,newPeriod;
    newFloor = floorEdit->text().toInt();
    newNumber = numberEdit->text().toInt();
    newPeriod = periodEdit->text().toInt();

    if(newFloor && newNumber && newPeriod)
    {
        QByteArray array;
        bool ok;
        array.push_back(REFER_CFG_MSG & 0xFF);
        array.push_back(netId.left(2).toInt(&ok,16));
        array.push_back(netId.right(2).toInt(&ok,16));
        array.push_back(newFloor & 0xFF);
        array.push_back(newNumber & 0xFF);
        array.push_back(newPeriod & 0xFF);
        emit sendConfigMsg(array);
    }
}
