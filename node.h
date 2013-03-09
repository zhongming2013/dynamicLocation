#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QObject>
class QString;
class QColor;

class Node : public QGraphicsItem
{
public:
    Node();
    ~Node();
    //Node外观控制
    void setText(const QString &text);
    QString text() const;
    void setTextColor(const QColor &color);
    QColor textColor() const;
    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;
    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    //重新实现基类函数
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QRectF outlineRect() const;
    int roundness(double size) const;

    QString myText;
    QColor myTextColor;
    QColor myBackgroundColor;
    QColor myOutlineColor;
};

#endif // NODE_H
