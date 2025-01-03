#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settingswindow.h"
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QMessageBox>
#include "fish.h"
#include "shark.h"
#include "creatureType.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Fish::s_reproductionTicks = 3;
    Fish::s_maxAge = 35;

    Shark::s_reproductionTicks = 25;
    Shark::s_maxAge = 40;

    int rows = 5;
    int cols = 5;
    m_world.initialize(rows, cols);
    m_world.addCreatures(CreatureType::fish, 10, /* randomAge */ true);
    m_world.addCreatures(CreatureType::shark, 2, /* randomAge */ true);
    renderWorld();

    QObject::connect(&tickTimer, &QTimer::timeout, [this]()
    {
        m_world.tick();
        renderWorld();
    });

    settingsWindow = new SettingsWindow(this);
}

void MainWindow::renderWorld()
{
    QPixmap pixmapFish1("/home/luismi/Documents/repos/GameOfLife/resources/fish1.jpg");
    QPixmap pixmapShark("/home/luismi/Documents/repos/GameOfLife/resources/shark.jpg");
    QPixmap pixmapWater("/home/luismi/Documents/repos/GameOfLife/resources/water.jpg");

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
                    pixmap = QPixmap(QString::fromStdString(fish->getResourcePath()));
                    imageLabel->setProperty("cell.render", "fish.jpeg");
                }
                else if (auto shark = dynamic_cast<Shark*>(creature); shark != nullptr)
                {
                    pixmap = QPixmap(QString::fromStdString(shark->getResourcePath()));
                    imageLabel->setProperty("cell.render", "shark.jpeg");
                }
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
}

MainWindow::~MainWindow()
{
    delete settingsWindow;
    delete ui;
}


void MainWindow::on_pushButtonStartPause_clicked()
{
    if (tickTimer.isActive())
    {
        ui->pushButtonStartPause->setText("Start");
        tickTimer.stop();
    }
    else
    {
        ui->pushButtonStartPause->setText("Pause");
        tickTimer.start(1000);
    }
}


void MainWindow::on_pushButtonSettings_clicked()
{
   settingsWindow->exec(); // Shows the dialog modally
}

void MainWindow::on_pushButtonAddFish_clicked()
{
    m_world.addCreatures(CreatureType::fish, 1);
    renderWorld();
}


void MainWindow::on_pushButtonAddShark_clicked()
{
    m_world.addCreatures(CreatureType::shark, 1);
    renderWorld();
}

