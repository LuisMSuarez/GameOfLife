#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
   for (int row = 0; row< 25; row++)
   {
        for(int col = 0; col<25; col++)
        {
           QLabel *imageLabel = new QLabel();
           QPixmap pixmap(imagePaths[0]);
           imageLabel->setPixmap(pixmap.scaled(30, 30, Qt::KeepAspectRatio)); // Adjust size as needed
           ui->gridLayout->addWidget(imageLabel, row, col);
        }
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}

