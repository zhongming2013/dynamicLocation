#ifndef MOBILETABLEVIEW_H
#define MOBILETABLEVIEW_H

#include <QTableView>
#include <QAction>
#include "mobileTableModel.h"

class MobileTableView : public QTableView
{
    Q_OBJECT

public:
    MobileTableView(MobileTableModel *model);
    ~MobileTableView();

signals:
    void sendConfigMsg(const QByteArray);

private slots:
    void configMsgDialog();
    void okToSend();

private:
    QAction *sendMsgAct;

    QLineEdit *fixIdEdit;
    QLineEdit *modeEdit;
    QLineEdit *dstAddrEdit;
    QLineEdit *periodEdit;
    QString selfAddr;
};

#endif // MOBILETABLEVIEW_H
