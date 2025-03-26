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

using namespace GameOfLifeCore;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int rows = 15;
    int cols = 15;
    cellHeight = this->geometry().height()/rows;
    cellWidth = this->geometry().width()/cols;
    m_world.initialize(rows, cols);
    m_world.createCreatures(CreatureType::fish, 10, /* randomAge */ true);
    m_world.createCreatures(CreatureType::shark, 5, /* randomAge */ true);
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
    QPixmap pixmapWater(":/water/water-default");

    int rows = m_world.rowCount();
    int cols = m_world.colCount();

    for (int row = 0; row<rows; row++)
    {
        for (int col = 0; col<cols; col++)
        {
            QPixmap pixmap;
            QString toolTip;
            if (auto creature = m_world(row,col).getCreature();
                creature != nullptr)
            {
                auto resource = QString::fromStdString(creature->getResourcePath());
                toolTip = resource;
                pixmap = QPixmap(resource);
            }
            else
            {
                pixmap = pixmapWater;
                toolTip = ":/water/water-default";
            }

            // as a rendering optimization, we only set the pixmap if it doesn't match the tooltip currently on the widget
            if (auto *widget = dynamic_cast<QLabel*>(ui->gridLayout->itemAtPosition(row, col)->widget());
                widget != nullptr &&
                widget->toolTip() != toolTip)
            {
                widget->setToolTip(toolTip);
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
    m_world.createCreatures(CreatureType::fish, 1);
    renderWorld();
}

void MainWindow::on_pushButtonAddShark_clicked()
{
    m_world.createCreatures(CreatureType::shark, 1);
    renderWorld();
}

void MainWindow::on_pushButtonReset_clicked()
{
    if (QMessageBox::Ok ==
        QMessageBox::question(this,
                              "Confirm",
                              "Do you want to pause and reset the current simulation?",
                              QMessageBox::Ok | QMessageBox::Cancel))
    {
        tickTimer.stop();
        ui->pushButtonStartPause->setText("Start");
        m_world.initialize(m_world.rowCount(), m_world.colCount());
        m_world.createCreatures(CreatureType::fish, 10, /* randomAge */ true);
        m_world.createCreatures(CreatureType::shark, 5, /* randomAge */ true);
        renderWorld();
    }
}

