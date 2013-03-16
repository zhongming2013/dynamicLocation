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
    query.exec("SELECT * FROM mobileConfig ORDER BY fixId");
    int fixId,mode,period;
    QString dstAddr;
    while(query.next())//获取原来的配置信息
    {
        if(0 == r--)
        {
            fixId = query.value(1).toInt();
            mode = query.value(2).toInt();
            dstAddr = "0x" + query.value(3).toString();
            period = query.value(4).toInt();
            this->selfAddr = query.value(5).toString();
            break;
        }
    }
    QDialog *mobileConfigDialog = new QDialog;
    QLabel *fixIdLabel = new QLabel(tr("FixID:"), mobileConfigDialog);
    QLabel *modeLabel = new QLabel(tr("Mode:"), mobileConfigDialog);
    QLabel *dstAddrLabel = new QLabel(tr("DST Address:"), mobileConfigDialog);
    QLabel *periodLabel = new QLabel(tr("Period:"), mobileConfigDialog);
    fixIdEdit = new QLineEdit;
    fixIdEdit->setText(QString::number(fixId));
    modeEdit = new QLineEdit;
    modeEdit->setText(QString::number(mode));
    dstAddrEdit = new QLineEdit;
    dstAddrEdit->setText(dstAddr);
    periodEdit = new QLineEdit;
    periodEdit->setText(QString::number(period));
    fixIdLabel->setBuddy(fixIdEdit);
    modeLabel->setBuddy(modeEdit);
    dstAddrLabel->setBuddy(dstAddrEdit);
    periodLabel->setBuddy(periodEdit);

    QPushButton *okButton = new QPushButton(tr("OK"));
    connect(okButton, SIGNAL(clicked()), this, SLOT(okToSend()));
    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), mobileConfigDialog, SLOT(close()));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(fixIdLabel, 0, 0);
    layout->addWidget(fixIdEdit, 0, 1);
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
    int newFixId = fixIdEdit->text().toInt();
    int newMode = modeEdit->text().toInt();
    QString newDstAddr = dstAddrEdit->text().right(4);//去掉“0x"
    int newPeriod = periodEdit->text().toInt();

    if(newFixId && newPeriod)
    {
        QByteArray array;
        array.push_back(MOBILE_CFG_MSG & 0xFF);
        array.push_back(newFixId & 0xFF);
        array.push_back(newMode & 0xFF);
        array.push_back(newDstAddr.left(2).toInt(&ok, 16));//地址高位
        array.push_back(newDstAddr.right(2).toInt(&ok, 16));//地址低位
        array.push_back(newPeriod & 0xFF);
        array.push_back(selfAddr.left(2).toInt(&ok, 16));
        array.push_back(selfAddr.right(2).toInt(&ok, 16));
        emit sendConfigMsg(array);
    }
}
