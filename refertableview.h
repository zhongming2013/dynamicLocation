#ifndef REFERTABLEVIEW_H
#define REFERTABLEVIEW_H

#include <QTableView>
#include <QAction>
#include <QVariant>
#include "refertablemodel.h"

class ReferTableView : public QTableView
{
    Q_OBJECT

public:
    ReferTableView(ReferTableModel *model);
    ~ReferTableView();

signals:
    void sendConfigMsg(const QByteArray);

private slots:
    void configMsgDialog();
    void okToSend();

private:
    QAction *sendMsgAct;

    QLineEdit *floorEdit;
    QLineEdit *numberEdit;
    QLineEdit *periodEdit;
    QString netId;//Ê®Áù½øÖÆ
};

#endif // REFERTABLEVIEW_H
