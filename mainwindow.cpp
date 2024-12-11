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
   for (const QString &imagePath : imagePaths)
   {
       QLabel *imageLabel = new QLabel();
       QPixmap pixmap(imagePath);
       imageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio)); // Adjust size as needed
       ui->gridLayout->addWidget(imageLabel, row, col);

       col++;
       if (col == 2)
       {
           col = 0;
           row++;
       }
   }
}

MainWindow::~MainWindow()
{
    delete ui;
}

