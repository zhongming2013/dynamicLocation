#ifndef REFERENCENODE_H
#define REFERENCENODE_H

#include "node.h"

class ReferenceNode : public Node
{
public:
    ReferenceNode();
    ~ReferenceNode();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    //�ο��ڵ��ƶ��󣬱����µ�����
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // REFERENCENODE_H
