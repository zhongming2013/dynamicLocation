#ifndef MOBILENODE_H
#define MOBILENODE_H

#include "node.h"
#include <QString>
#include <QTimer>

class MobileNode : public QObject,public Node
{
    Q_OBJECT

public:
    MobileNode(QObject *parent = 0);
    ~MobileNode();
    void setHelp(int);
    int getHelp();
    void timerEvent(QTimerEvent * e);

signals:
    void itemSelected(const int fixId);

protected:
    //���Node�Ƿ�ѡȡ
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    int timerId1;
    int timerId2;
    int help;//������Ϣλ
};

#endif // MOBILENODE_H
