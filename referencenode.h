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
    //参考节点移动后，保存新的坐标
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // REFERENCENODE_H
