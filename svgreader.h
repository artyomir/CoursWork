#ifndef SVGREADER_H
#define SVGREADER_H

#include <QList>
#include <QGraphicsRectItem>
#include <QDomDocument>
#include "roomlabel.h"

class SvgReader
{
public:
    SvgReader();
    static QList<RoomLabel *> getElements(const QString filename, const QString objectName);
    static QGraphicsPolygonItem * getPolygon(QDomNode node);
    static RoomLabel * getPolygon(QDomNode node, QDomNode rect, bool f = false);
    static QList <QList <RoomLabel *>> getAllObjects(const QString filename);
    //static QStringList getlegend(const QString filename);
};
QStringList getlegend(const QString filename);
QRectF getSize(const QDomNode svgElement);
QStringList getId(const QString filename);
QString getName(const QDomNode element);
QString getBrush (const QDomNode element);
QString getInfo (const QDomNode element);
#endif // SVGREADER_H
