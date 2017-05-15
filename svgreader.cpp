#include "svgreader.h"
#include <QPen>
#include <QFile>
#include <QMessageBox>
#include <QDomDocument>
#include <QStringList>
#include <QDebug>

SvgReader::SvgReader()
{
}

QList<RoomLabel *> SvgReader::getElements(const QString filename, const QString objectName){
    QList<RoomLabel *> rectList;    // Объявим в стеке список прямоугольников
    QDomDocument doc;       // объект документа
    QFile file(filename);   // Открываем наш SVG-файл
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)){
        return rectList;    // то возвратим список, но пустой
    }
    QDomNodeList gList = doc.elementsByTagName("g");
    int i;
    for (i = 0; i < gList.size(); i++) {
        if (gList.item(i).toElement().attribute("name").toLower() == objectName.toLower()){
            QDomNodeList Polygons = gList.item(i).toElement().elementsByTagName("polygon");
            rectList.append(getPolygon(Polygons.item(0), gList.item(i), true));
            for (int j = 1; j < Polygons.size(); j++){
                rectList.append(getPolygon(Polygons.item(j), gList.item(i)));
            }
        }

    }
    file.close();
    return rectList;
}

QStringList getlegend(const QString filename){
    QStringList legends;
    QDomDocument doc;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)){
        return legends;
    }
    QDomNodeList gList = doc.elementsByTagName("g");
    int i;
    for (i = 0; i < gList.size(); i++) {
        if (gList.item(i).toElement().attribute("legend").size() > 5){
            QString color = gList.item(i).toElement().attribute("legend");
            QString name = gList.item(i).toElement().attribute("name");
            legends.push_back("<font size=4 color=" + color + ">" + name + "</font>");
        }

    }
    file.close();
    return legends;
}

RoomLabel *SvgReader::getPolygon(QDomNode node, QDomNode rect, bool f){
    QDomElement p = node.toElement();
    QVector <QPoint> points;
    QStringList txtpoints = p.attribute("points").trimmed().split(" ");
    foreach(QString s, txtpoints){
        QStringList point = s.split(",");
        QString x = point[0];
        QString y = point[1];
        points << QPoint(x.toDouble(), y.toDouble());
    }
    RoomLabel * room;
    if (f){
        room = new RoomLabel(getSize(rect),points,getName(rect), getBrush(rect), getInfo(rect));
        return room;
    } else {
        room = new RoomLabel(QRectF(0, 0, 0, 0),points,getName(rect), getBrush(rect));
        return room;
    }   return room;
}

//QStringList getId(const QString filename){
//    QFile file(filename);
//    QStringList objId;
//    if(!file.open(QFile::ReadOnly | QFile::Text)){
//        qDebug() << "Ошибка открытия файла для чтения ID комнат";
//        return objId;
//    }
//    while (!file.atEnd()){
//        objId << file.readLine().trimmed();
//    }
//    foreach (QString s, objId) {
//    }
//    return objId;
//}


QRectF getSize(const QDomNode svgElement)
{
    QStringList parameters = svgElement.toElement().attribute("viewBox").trimmed().split(" ");
    if (parameters.size() != 4){
        return QRectF(0,0,0,0);
    } else{

        return QRectF(QPointF(QPoint(parameters.at(0).toDouble(),
                      parameters.at(1).toDouble())),
                      QPointF(QPoint(parameters.at(2).toDouble(),
                      parameters.at(3).toDouble())));

    }
}

QString getName(const QDomNode element){;
    return element.toElement().attribute("name");
}

QString getBrush (const QDomNode element){
    return element.toElement().attribute("fill");
}

QString getInfo (const QDomNode element){
    return element.toElement().attribute("info");
}

QList <QList <RoomLabel *>> SvgReader::getAllObjects(const QString filename){
    QList <QList <RoomLabel *>> rectList;
    QDomDocument doc;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)){
        return rectList;
    }
    QDomNodeList gList = doc.elementsByTagName("g");
    for (int i = 0; i < gList.size(); i++){
        if (gList.item(i).toElement().attribute("name") != ""){
            QDomNodeList Polygons = gList.item(i).toElement().elementsByTagName("polygon");
            QList <RoomLabel *> list;
            list.append(getPolygon(Polygons.item(0), gList.item(i), true));
            for (int j = 1; j < Polygons.size(); j++){
                list.append(getPolygon(Polygons.item(j), gList.item(i)));
            }
            rectList.append(list);
        }
    file.close();
    }
    return rectList;
}
