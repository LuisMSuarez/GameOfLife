#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QMessageBox>
#include <list>
#include "fish.h"
#include "shark.h"
#include "creatureType.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Fish::s_reproductionAge = 5;
    Fish::s_maxAge = 35;

    int rows = 5;
    int cols = 5;
    m_world.initialize(rows, cols);
    m_world.addCreatures(CreatureType::fish, 7);
    m_world.addCreatures(CreatureType::shark, 2);
    renderWorld();
}

void MainWindow::renderWorld()
{
    std::list<QLabel*> widgets;
    QPixmap pixmapFish("/home/luismi/Documents/repos/GameOfLife/fish.jpeg");
    QPixmap pixmapShark("/home/luismi/Documents/repos/GameOfLife/shark.jpg");
    QPixmap pixmapWater("/home/luismi/Documents/repos/GameOfLife/water.jpg");

    int rows = 5;
    int cols = 5;
    //QMessageBox::information(this, "info", QString::number(ui->centralwidget->layout()->geometry().height()));
    int cellHeight = 160; // ui->centralwidget->height()/rows;
    int cellWidth = 160;  //ui->centralwidget->width()/cols;
    for (int row = 0; row<rows; row++)
    {
        for (int col = 0; col<cols; col++)
        {
            QPixmap pixmap;
            QLabel *imageLabel = new QLabel();
            if (auto creature = m_world(row,col).getCreature(); creature != nullptr)
            {
                if (auto fish = dynamic_cast<Fish*>(creature); fish != nullptr)
                {
                    pixmap = pixmapFish;
                    imageLabel->setProperty("cell.render", "fish.jpeg");
                }
                else if (auto shark = dynamic_cast<Shark*>(creature); shark != nullptr)
                {
                    pixmap = pixmapShark;
                    imageLabel->setProperty("cell.render", "shark.jpeg");
                }
                widgets.push_back(imageLabel);
            }
            else
            {
                pixmap = pixmapWater;
                imageLabel->setProperty("cell.render", "water.jpg");
            }
            imageLabel->setPixmap(pixmap.scaled(cellWidth, cellHeight, Qt::KeepAspectRatio)); // Adjust size as needed
            ui->gridLayout->addWidget(imageLabel, row, col);
        }
    }

    for (auto widget: widgets)
    {
      // ui->gridLayout->removeWidget(widget);
       //widget->setPixmap(pixmapWater.scaled(cellWidth, cellHeight, Qt::KeepAspectRatio)); // Adjust size as needed
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonTick_clicked()
{
    m_world.tick();
    renderWorld();
}

