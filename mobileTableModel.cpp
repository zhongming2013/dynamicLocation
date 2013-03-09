#include "mobileTableModel.h"
#include "define.h"

#include <QSqlRecord>
#include <QVector>

MobileTableModel::MobileTableModel(QObject *parent)
{
    setTable("mobileConfig");
    setSort(2, Qt::AscendingOrder);
    setHeaderData(1, Qt::Horizontal, tr("FixID"));
    setHeaderData(2, Qt::Horizontal, tr("Mode"));
    setHeaderData(3, Qt::Horizontal, tr("DST Address"));
    setHeaderData(4, Qt::Horizontal, tr("Period"));
    setHeaderData(5, Qt::Horizontal, tr("Self Address"));
    select();
}

void MobileTableModel::refreshMobileTable(const QVector<int> mobileMsg)
{
    int fixId,mode,dstAddr,period,selfAddr;
    QString dst,self;
    dst.fill('0',4);
    self.fill('0',4);
    fixId = mobileMsg.at(M_FIXID);
    mode = mobileMsg.at(M_LOC_MODE);
    dstAddr = mobileMsg.at(M_DST_ADDR_LO);
    dstAddr |= (mobileMsg.at(M_DST_ADDR_HI) << 8);
    dst.append(QString::number(dstAddr,16).toUpper());//转为十六进制
    period = mobileMsg.at(M_LOC_PERIOD);
    selfAddr = mobileMsg.at(M_SELF_ADDR_LO);
    selfAddr |= (mobileMsg.at(M_SELF_ADDR_HI) << 8);
    self.append(QString::number(selfAddr,16).toUpper());
    //添加或者更新参考节点配置信息数据表
    setFilter("fixId = " + QString::number(fixId));
    select();
    if(rowCount() == 1)//已经存在，更新数据
    {
        QSqlRecord record = this->record(0);
        record.setValue("fixId",fixId);
        record.setValue("mode", mode);
        record.setValue("dstAddr", dst.right(4));
        record.setValue("period", period);
        record.setValue("selfAddr", self.right(4));
        setRecord(0, record);
        submitAll();
        setFilter("");//清除过滤条件，否则只显示更新的一条
    }
    else if(rowCount() == 0)//不存在，添加新移动节点配置信息
    {
        int row = 0;
        insertRows(row, 1);
        setData(index(row, 1), fixId);
        setData(index(row, 2), mode);
        setData(index(row, 3), dst.right(4));
        setData(index(row, 4), period);
        setData(index(row, 5), self.right(4));
        submitAll();
        setFilter("");//清楚过滤条件，否则只显示更新的一条
        submitAll();
    }
}
