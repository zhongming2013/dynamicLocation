#include "nodeview.h"
#include "define.h"

#include <QHeaderView>
#include <QInputDialog>
#include <QModelIndexList>
#include <QSqlQuery>
#include <QSqlRecord>

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
    int r = indexList.first().row();
    QSqlQuery query;
    query.exec("SELECT netId,roomId FROM node ORDER BY roomId");
    QString netId;//十六进制
    int roomId = 0;
    while(query.next())//获取原来的roomId
    {
        if(0 == r--)
        {
            netId = query.value(0).toString();
            roomId = query.value(1).toInt();
            break;
        }
    }
    int newRoomId = QInputDialog::getInt(this,tr("Set the new room ID"),tr("RoomId"),roomId);
    if(newRoomId && newRoomId != roomId)
    {
        QByteArray array;
        bool ok;
        array.push_back(REFERENCE_CFG_MSG & 0xFF);
        array.push_back(netId.left(2).toInt(&ok,16));
        array.push_back(netId.right(2).toInt(&ok,16));
        array.push_back((newRoomId >> 8) & 0xFF);
        array.push_back(newRoomId & 0xFF);
        emit sendConfigMsg(array);
    }
}
