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

    int rows = 10;
    int cols = 10;
    cellHeight = this->geometry().height()/rows;
    cellWidth = this->geometry().width()/cols;

    m_world.initialize(rows, cols);
    m_world.addCreatures(CreatureType::fish, 10, /* randomAge */ true);
    m_world.addCreatures(CreatureType::shark, 2, /* randomAge */ true);
    initializeWidgets();
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
    QPixmap pixmapWater("/home/luismi/Documents/repos/GameOfLife/resources/water.jpg");

    int rows = m_world.rowCount();
    int cols = m_world.colCount();

    for (int row = 0; row<rows; row++)
    {
        for (int col = 0; col<cols; col++)
        {
            QPixmap pixmap;
            if (auto creature = m_world(row,col).getCreature(); creature != nullptr)
            {
                auto resource = QString::fromStdString(creature->getResourcePath());
                pixmap = QPixmap(resource);
            }
            else
            {
                pixmap = pixmapWater;
            }
            auto *widget = dynamic_cast<QLabel*>(ui->gridLayout->itemAtPosition(row, col)->widget());
            if (widget != nullptr)
            {
                widget->setPixmap(pixmap.scaled(cellWidth, cellHeight));
            }
        }
    }
}

void MainWindow::initializeWidgets()
{
    int rows = m_world.rowCount();
    int cols = m_world.colCount();

    for (int row = 0; row<rows; row++)
    {
        for (int col = 0; col<cols; col++)
        {
            QLabel *imageLabel = new QLabel();
            ui->gridLayout->addWidget(imageLabel, row, col);
        }
    }
}

void MainWindow::deleteWidgets()
{
    int rows = m_world.rowCount();
    int cols = m_world.colCount();

    for (int row = 0; row<rows; row++)
    {
        for (int col = 0; col<cols; col++)
        {
            auto *widget = dynamic_cast<QLabel*>(ui->gridLayout->itemAtPosition(row, col)->widget());
            if (widget != nullptr)
            {
                delete widget;
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete settingsWindow;
    deleteWidgets();
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
