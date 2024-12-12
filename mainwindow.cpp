#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include "fish.h"
#include "shark.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Fish::s_reproductionAge = 10;
    m_game.newWorld(10, 10);

    // Display 4 images in a 2x2 grid
    QStringList imagePaths =
    {
        "/home/luismi/Documents/repos/GameOfLife/fish.jpeg",
        "/home/luismi/Documents/repos/GameOfLife/shark.jpg",
        "/home/luismi/Documents/repos/GameOfLife/fish.jpeg",
        "/home/luismi/Documents/repos/GameOfLife/shark.jpg"
    };

   int row = 0;
   int col = 0;
   for (int row = 0; row< 10; row++)
   {
        for(int col = 0; col<10; col++)
        {
           QLabel *imageLabel = new QLabel();
           QPixmap pixmap(imagePaths[0]);
           imageLabel->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio)); // Adjust size as needed
           ui->gridLayout->addWidget(imageLabel, row, col);
        }
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}

