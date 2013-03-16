#include "nodetablemodel.h"
#include "define.h"

#include <QVector>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>

NodeTableModel::NodeTableModel(QObject *parent)
{
    setTable("referNode");
    setSort(1, Qt::AscendingOrder);
    setHeaderData(1, Qt::Horizontal, tr("NetID"));
    setHeaderData(2, Qt::Horizontal, tr("Floor"));
    setHeaderData(3, Qt::Horizontal, tr("Number"));
    setHeaderData(4, Qt::Horizontal, tr("TMP_Period"));
    select();
}

void NodeTableModel::refreshNodeTable(const QVector<int> referenceMsg)
{
    QString hexNetId;
    int floor,number;
    hexNetId.fill('0',4);//用于补充不够4位netID的前面的0

    int netId,tmpPeriod;
    floor = referenceMsg.at(R_ROOM_FLOOR);
    number = referenceMsg.at(R_ROOM_NUMBER);
    netId = referenceMsg.at(R_NETID_LO);
    netId |= (referenceMsg.at(R_NETID_HI) << 8);
    hexNetId.append(QString::number(netId,16).toUpper());
    tmpPeriod = referenceMsg.at(R_TEMP_PERIOD);
    //添加或者更新参考节点配置信息数据表
    setFilter(QString("floor=%1 AND number=%2").arg(floor).arg(number));
    select();
    if(rowCount() == 1)//已经存在，更新netId
    {
        QSqlRecord record = this->record(0);
        record.setValue("netId",hexNetId.right(4));
        record.setValue("tempPeriod", tmpPeriod);
        setRecord(0,record);
        submitAll();
        setFilter("");//清楚过滤条件，否则只显示更新的一条
    }
    else if(rowCount() == 0)//不存在，添加netId
    {
        int row = 0;
        insertRows(row, 1);
        setData(index(row, 1),hexNetId.right(4));
        setData(index(row, 2), floor);
        setData(index(row, 3),number);
        setData(index(row, 4), tmpPeriod);
        submitAll();
        setFilter("");//清楚过滤条件，否则只显示更新的一条
        submitAll();
    }
}
