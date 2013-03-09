#include "nodetablemodel.h"
#include "define.h"

#include <QVector>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>

NodeTableModel::NodeTableModel(QObject *parent)
{
    setTable("referNode");
    setSort(2, Qt::AscendingOrder);
    setHeaderData(1, Qt::Horizontal, tr("NetID"));
    setHeaderData(2, Qt::Horizontal, tr("Floor"));
    setHeaderData(3, Qt::Horizontal, tr("Number"));
    setHeaderData(4, Qt::Horizontal, tr("Temperature"));
    select();
}

void NodeTableModel::refreshNodeTable(const QVector<int> referenceMsg)
{
    QString hexNetId;
    int floor,number;
    hexNetId.fill('0',4);//���ڲ��䲻��4λnetID��ǰ���0
    switch(referenceMsg.at(MSG_TYPE))
    {
    case REFERENCE_CFG_MSG:
        int netId;
        floor = referenceMsg.at(R_ROOM_FLOOR);
        number = referenceMsg.at(R_ROOM_NUMBER);
        netId = referenceMsg.at(R_NETID_LO);
        netId |= (referenceMsg.at(R_NETID_HI) << 8);
        hexNetId.append(QString::number(netId,16).toUpper());
        //��ӻ��߸��²ο��ڵ�������Ϣ���ݱ�
        setFilter(QString("floor=%1 AND number=%2").arg(floor).arg(number));
        select();
        if(rowCount() == 1)//�Ѿ����ڣ�����netId
        {
            QSqlRecord record = this->record(0);
            record.setValue("netId",hexNetId.right(4));
            setRecord(0,record);
            submitAll();
            setFilter("");//�����������������ֻ��ʾ���µ�һ��
        }
        else if(rowCount() == 0)//�����ڣ����netId
        {
            int row = 0;
            insertRows(row, 1);
            setData(index(row, 1),hexNetId.right(4));
            setData(index(row, 2), floor);
            setData(index(row, 3),number);
            setData(index(row, 4), 25);
            submitAll();
            setFilter("");//�����������������ֻ��ʾ���µ�һ��
            submitAll();
        }
        break;
    case REFERENCE_TMP_MSG:
        int tmp;
        tmp = referenceMsg.at(RT_ROOM_TEMP);
        floor = referenceMsg.at(RT_ROOM_FLOOR);
        number = referenceMsg.at(RT_ROOM_NUMBER);
        setFilter(QString("floor=%1 AND number=%2").arg(floor).arg(number));
        select();
        if(rowCount() == 1)//�Ѿ����ڣ������¶�
        {
            QSqlRecord record = this->record(0);
            record.setValue("temperature",tmp);
            setRecord(0,record);
            submitAll();
            setFilter("");//�����������������ֻ��ʾ���µ�һ��
        }
        break;
    }
}
