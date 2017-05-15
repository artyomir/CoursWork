#ifndef ROOMLABEL_H
#define ROOMLABEL_H

#include <QObject>
#include <QGraphicsObject>
#include <QMouseEvent>

class RoomLabel : public QGraphicsObject
{
    Q_OBJECT
public:
    RoomLabel(QRectF field, QVector <QPoint> &coordinates, QString name = "", QString brush_ = "168 18 165 127", QString info = "");

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QString info;
    QString name;
    QGraphicsPolygonItem * polyItem;


signals:
    void signal1();
private:
    QRectF boundingRect() const;
    QRectF field;
    QVector <QPoint> coordinates;
    QString brush_;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ROOMLABEL_H
