#include "roomlabel.h"
#include <QDebug>
#include <QPainter>

RoomLabel::RoomLabel(QRectF field, QVector <QPoint> &coordinates, QString name, QString brush_, QString info)
    : QGraphicsObject(),
      coordinates(coordinates),
      field(field),
      name(name),
      brush_(brush_),
      info(info)
{
    QPolygon polygon;
    foreach(QPoint point, coordinates){
        polygon << point;
    }
    polyItem = new QGraphicsPolygonItem(QPolygonF(polygon));
    QStringList br = brush_.split(" ");
    polyItem->setBrush(QColor(br.at(0).toInt(),
                              br.at(1).toInt(),
                              br.at(2).toInt(),
                              br.at(3).toInt()));
    //polyItem->setFlag(QGraphicsItem::ItemIsSelectable);
    //polyItem->is
}

QRectF RoomLabel::boundingRect() const
{
    return field;
//    return QRectF(300, 300, 1000, 1000);
}

void RoomLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon;
    polygon << QPoint(200, 200);
    QStringList br = brush_.split(" ");
    painter->setBrush(QColor(br.at(0).toInt(),
                             br.at(1).toInt(),
                             br.at(2).toInt(),
                             br.at(3).toInt()));
    painter->drawPolygon(polygon);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void RoomLabel::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit signal1();
    QGraphicsItem::mousePressEvent(event);
}
