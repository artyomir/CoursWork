#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphics_view_zoom.h"
#include <QFile>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "svgreader.h"
#include <QGraphicsSvgItem>

MainWindow::MainWindow(QString student, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Student quarter Dubki");
    setWindowIcon(QIcon(":/fill/ICON.png"));

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->student->setText(student);

    z = new Graphics_view_zoom(ui->graphicsView);

    this->setMinimumHeight(600);
    this->setMinimumWidth(1000);

    dmap = new QGraphicsScene();
    dmap->setBackgroundBrush(QColor(156, 216, 209, 0));
    dmap->setSceneRect(QRectF(0, 0, 1100, 500));
    map = new QGraphicsSvgItem(":/fill/HSE.svg");
    map->setPos(QPointF(QPoint(235, -150)));

    dmap->addItem(map);

    ui->FindeButton->setDisabled(true);
    ui->showAllCheckBox->setDisabled(true);
    ui->Floors->setDisabled(true);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(dmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_FindeButton_clicked()
{
    if (ui->FindeLineEdit->text() != ""){
        if (Rooms.isEmpty()){
            Rooms = SvgReader::getElements(filename, ui->FindeLineEdit->text());
            ui->FindeLineEdit->clear();
            if (Rooms.isEmpty()){
                ui->label->setText("<font color=red>Not fonded!</font>");
                return;
            } else{
                QString s = "<font color=red>No information about this object</font>";
                qDebug() << "Start to draw";
                foreach (RoomLabel *item, Rooms) {
                    dmap->addItem(item->polyItem);
                    item->polyItem->setPos(QPointF(QPoint(x, y)));
                }
                if (Rooms[0]->info.size() > 2)
                    ui->label->setText(Rooms[0]->info);
                else
                    ui->label->setText("<font size=4>" + Rooms[0]->name + "</font>");
            }

        } else{
            if (SvgReader::getElements(filename, ui->FindeLineEdit->text()).isEmpty()){
                ui->label->setText("<font color=red>Not fonded!</font>");
                return;
            } else{
                removeObject();
                Rooms = SvgReader::getElements(filename, ui->FindeLineEdit->text());;
                foreach (RoomLabel *item, Rooms) {
                    dmap->addItem(item->polyItem);
                    item->polyItem->setPos(QPointF(QPoint(x, y)));
                }
                if (Rooms[0]->info.size() > 2)
                    ui->label->setText(Rooms[0]->info);
                else
                    ui->label->setText("<font size=4>" + Rooms[0]->name + "</font>");
            }
       }
   } else{
        return;
    }
}

void MainWindow::showAllObj(){
    AllRooms = SvgReader::getAllObjects(filename);
    foreach (QList <RoomLabel *> Rooms_, AllRooms) {
        foreach (RoomLabel *item, Rooms_) {
            dmap->addItem(item);
            dmap->addItem(item->polyItem);
            item->polyItem->setPos(QPointF(QPoint(x, y)));
            item->setPos(QPointF(QPoint(x, y)));
            if (Rooms_[0]->info.size() > 2){
                connect(item, &RoomLabel::signal1, [=](){ui->label->setText("<font size=4>" + Rooms_[0]->name + "</font>");});
                connect(item, &RoomLabel::signal1, [=](){ui->label->append(Rooms_[0]->info);});
            }
            else
                connect(item, &RoomLabel::signal1, [=](){ui->label->setText("<font size=4>" + Rooms_[0]->name + "</font>");});
        }
    }
}

void MainWindow::removeObject(){
    while(!Rooms.isEmpty()){
        delete Rooms[0]->polyItem;
        delete Rooms[0];
        Rooms.removeAt(0);
    }
}

void MainWindow::removeAllObjects(){
    while(!AllRooms.isEmpty()){
        while (!AllRooms[0].isEmpty()){
            delete AllRooms[0].at(0)->polyItem;
            delete AllRooms[0].at(0);
            AllRooms[0].removeAt(0);
        }
        AllRooms.removeAt(0);
    }
}

void MainWindow::on_showAllCheckBox_clicked(bool checked)
{
    if (checked){
        ui->FindeButton->setEnabled(false);
        removeObject();
        showAllObj();
        map->setPos(QPointF(QPoint(x, y)));

        ui->legend->clear();
        foreach (QString s, getlegend(filename)) {
            ui->legend->append(s);
        }
    } else{
        ui->FindeButton->setEnabled(true);
        removeAllObjects();
        ui->legend->clear();
    }
}

void MainWindow::on_Housing2_clicked(bool checked)
{
    if (checked){

        x = 0; y = 0; corp = "2";

        ui->Floors->setDisabled(false);
        ui->mainFloor->setChecked(true);
        emit ui->mainFloor->clicked(true);
    }

}

void MainWindow::on_Housing1_clicked(bool checked)
{
    if (checked){
        x = -100; y = 50; corp = "1";

        ui->Floors->setDisabled(false);
        ui->mainFloor->setChecked(true);
        emit ui->mainFloor->clicked(true);
    }
}

void MainWindow::on_Housing3_clicked(bool checked)
{
    if (checked){
        x = -150; y = -150; corp = "3";

        ui->Floors->setDisabled(false);
        ui->mainFloor->setChecked(true);
        emit ui->mainFloor->clicked(true);
    }
}

void MainWindow::on_mainFloor_clicked(bool checked)
{
    if(checked){
        z->set_modifiers(Qt::NoModifier);
        removeObject();
        removeAllObjects();
        delete map;
        delete dmap;
        map = new QGraphicsSvgItem(":/maps/corp" + corp + "MAP.svg");
        map->setPos(QPointF(QPoint(x, y)));

        filename = ":/Objects/corp" + corp + "OBJ.svg";

        dmap = new QGraphicsScene();
        dmap->setBackgroundBrush(QColor(156, 216, 209, 0));
        dmap->setSceneRect(QRectF(0, 0, 1100, 1100));
        dmap->addItem(map);

        ui->FindeButton->setDisabled(false);
        ui->showAllCheckBox->setChecked(false);
        ui->showAllCheckBox->setDisabled(false);
        ui->graphicsView->setScene(dmap);
    }
}

void MainWindow::on_plainFloor_clicked(bool checked)
{
    if(checked){
        removeObject();
        removeAllObjects();
        delete map;
        delete dmap;
        map = new QGraphicsSvgItem(":/maps/corp" + corp + "FLOOR.svg");
        filename = ":/Objects/corp" + corp + "FloorOBJ.svg";
        qDebug() << 1;
        dmap = new QGraphicsScene();
        dmap->setBackgroundBrush(QColor(156, 216, 209, 0));
        dmap->setSceneRect(QRectF(0, 0, 1100, 1100));
        dmap->addItem(map);

        map->setPos(QPointF(QPoint(x, y)));

        ui->FindeButton->setDisabled(false);
        ui->showAllCheckBox->setChecked(false);
        ui->showAllCheckBox->setDisabled(false);
        ui->graphicsView->setScene(dmap);
    }
}
