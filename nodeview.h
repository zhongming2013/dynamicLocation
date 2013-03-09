#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QTableView>
#include <QAction>
#include <QVariant>
#include "nodetablemodel.h"

class NodeView : public QTableView
{
    Q_OBJECT

public:
    NodeView(NodeTableModel *model);
    ~NodeView();

signals:
    void sendConfigMsg(const QByteArray);

private slots:
    void configMsgDialog();

private:
    QAction *sendMsgAct;
};

#endif // NODEVIEW_H
