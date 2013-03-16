#include "referencenode.h"
#include <QSqlQuery>
#include <QInputDialog>
#include <QGraphicsSceneMouseEvent>

ReferenceNode::ReferenceNode()
{
    setTextColor(Qt::black);
    setBackgroundColor(Qt::yellow);
    setOutlineColor(Qt::darkRed);

    setFlags(ItemIsSelectable | ItemIsMovable |
             ItemIsSelectable | ItemSendsGeometryChanges);
}

ReferenceNode::~ReferenceNode()
{

}

QVariant ReferenceNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    static bool itemMove = false;
    if(change == QGraphicsItem::ItemPositionHasChanged)
        itemMove = true;

    if(change == QGraphicsItem::ItemSelectedChange && itemMove)//Node��ѡ��
    {
        int roomId = this->text().toInt();
        int floor,number;
        floor = roomId/100;
        number = roomId%100;//TODO:�������ݵĺϷ��ԣ�Ȼ����ܲ���
        QSqlQuery query;
        query.prepare("UPDATE room SET x=?,y=? WHERE floor=? AND number=?");
        query.addBindValue(this->pos().x());
        query.addBindValue(this->pos().y());
        query.addBindValue(floor);
        query.addBindValue(number);
        query.exec();
        itemMove = false;
    }

    return QGraphicsItem::itemChange(change, value);
}

void ReferenceNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QString text = QInputDialog::getText(event->widget(),
                                         QObject::tr("Edit Text"),
                                         QObject::tr("Enter new text:"),
                                         QLineEdit::Normal, this->text());
    if(!text.isEmpty() && text != "ref")
    {
        this->setText(text);
        int roomId = text.toInt();
        int floor = roomId/100;
        int number = roomId%100;
        int x = this->pos().x();
        int y = this->pos().y();

        QSqlQuery query;
        query.prepare("SELECT id FROM room WHERE floor = ? AND number = ?");
        query.addBindValue(floor);
        query.addBindValue(number);
        query.exec();
        query.next();
        if(query.value(1).toInt() >= 1)//������ݿ����Ѿ��洢����ֻ���¡�
        {
            query.prepare("UPDATE room SET x=?,y=? WHERE floor = ? AND number = ?");
        }
        else//û������ӵ��ο��ڵ����ݱ��room���ݱ�
        {
            QSqlQuery q;
            q.exec(QString("INSERT INTO referNode (netId,floor,number,tempPeriod) values('0',%1,%2,30)").arg(floor).arg(number));
            query.prepare("INSERT INTO room (floor,number,x,y) values(?,?,?,?)");
        }
        query.addBindValue(floor);
        query.addBindValue(number);
        query.addBindValue(x);
        query.addBindValue(y);
        query.exec();
    }
}
