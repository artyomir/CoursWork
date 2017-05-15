 #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsScene>
#include <roomlabel.h>
#include <QGraphicsSvgItem>
#include "graphics_view_zoom.h"

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QString student, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_FindeButton_clicked();
    void on_showAllCheckBox_clicked(bool checked);

    void on_Housing2_clicked(bool checked);

    void on_Housing1_clicked(bool checked);

    void on_Housing3_clicked(bool checked);

    void on_mainFloor_clicked(bool checked);

    void on_plainFloor_clicked(bool checked);

private:
    QGraphicsSvgItem * map = new QGraphicsSvgItem(":/maps/corp2MAP.svg");
    int x; int y;
    QString filename = ":/Objects/corp2OBJ.svg";
    QString corp = "2";
    void removeAllObjects();
    void removeObject();
    Ui::MainWindow *ui;
    QGraphicsScene *dmap;
    QList <RoomLabel *> Rooms;
    QList <QList <RoomLabel *>> AllRooms;
    Graphics_view_zoom *z;
    void showAllObj();
};




#endif // MAINWINDOW_H
