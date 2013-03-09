#include "mobileTableView.h"
#include "define.h"
#include <QModelIndexList>
#include <QSqlQuery>
#include <QByteArray>
#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QHeaderView>
#include <QPushButton>

MobileTableView::MobileTableView(MobileTableModel *model)
{
    setModel(model);
    setColumnHidden(0, true);
    resizeColumnsToContents();
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    sendMsgAct = new QAction(tr("Send config message"),this);
    verticalHeader()->addAction(sendMsgAct);
    verticalHeader()->setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(sendMsgAct, SIGNAL(triggered()), this, SLOT(configMsgDialog()));
}

MobileTableView::~MobileTableView()
{

}

void MobileTableView::configMsgDialog()
{
    QModelIndexList indexList = selectedIndexes();
    int r = indexList.first().row();
    QSqlQuery query;
    query.exec("SELECT * FROM mobileConfig ORDER BY netId");
    int netId,mode,dstAddr,period;
    QString dstAddrHex(4, '0');
    while(query.next())//获取原来的配置信息
    {
        if(0 == r--)
        {
            netId = query.value(1).toInt();
            mode = query.value(2).toInt();
            dstAddr = query.value(3).toInt();
            period = query.value(4).toInt();
            selfAddr = query.value(5).toInt();
            break;
        }
    }
    dstAddrHex.append(QString::number(dstAddr, 16).toUpper());
    QDialog *mobileConfigDialog = new QDialog;
    QLabel *netIdLabel = new QLabel(tr("NetID:"), mobileConfigDialog);
    QLabel *modeLabel = new QLabel(tr("Mode:"), mobileConfigDialog);
    QLabel *dstAddrLabel = new QLabel(tr("DST Address:"), mobileConfigDialog);
    QLabel *periodLabel = new QLabel(tr("Period:"), mobileConfigDialog);
    netIdEdit = new QLineEdit;
    netIdEdit->setText(QString::number(netId));
    modeEdit = new QLineEdit;
    modeEdit->setText(QString::number(mode));
    dstAddrEdit = new QLineEdit;
    dstAddrEdit->setText(dstAddrHex.right(4));
    periodEdit = new QLineEdit;
    periodEdit->setText(QString::number(period));
    netIdLabel->setBuddy(netIdEdit);
    modeLabel->setBuddy(modeEdit);
    dstAddrLabel->setBuddy(dstAddrEdit);
    periodLabel->setBuddy(periodEdit);

    QPushButton *okButton = new QPushButton(tr("OK"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(okToSend()));
    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), mobileConfigDialog, SLOT(close()));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(netIdLabel, 0, 0);
    layout->addWidget(netIdEdit, 0, 1);
    layout->addWidget(modeLabel, 1, 0);
    layout->addWidget(modeEdit, 1, 1);
    layout->addWidget(dstAddrLabel, 2, 0);
    layout->addWidget(dstAddrEdit, 2, 1);
    layout->addWidget(periodLabel, 3, 0);
    layout->addWidget(periodEdit, 3, 1);
    layout->addWidget(okButton, 4, 0);
    layout->addWidget(closeButton, 4, 1);

    mobileConfigDialog->setLayout(layout);
    mobileConfigDialog->setWindowTitle(tr("Send Mobile Config Message"));
    mobileConfigDialog->show();
}

void MobileTableView::okToSend()
{
    bool ok;
    int newNetId = netIdEdit->text().toInt();
    int newMode = modeEdit->text().toInt();
    int newDstAddr = dstAddrEdit->text().toInt(&ok, 16);
    int newPeriod = periodEdit->text().toInt();

    if(newNetId && newPeriod)
    {
        QByteArray array;
        array.push_back(MOBILE_CFG_MSG & 0xFF);
        array.push_back(newNetId & 0xFF);
        array.push_back(newMode & 0xFF);
        array.push_back((newDstAddr >> 8) & 0xFF);
        array.push_back(newDstAddr & 0xFF);
        array.push_back(newPeriod & 0xFF);
        array.push_back((selfAddr >> 8) & 0xFF);
        array.push_back(selfAddr & 0xFF);
        emit sendConfigMsg(array);
    }
}
