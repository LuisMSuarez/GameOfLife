#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "world.h"
#include "settingswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonStartPause_clicked();
    void on_pushButtonSettings_clicked();
    void on_pushButtonAddFish_clicked();
    void on_pushButtonAddShark_clicked();

private:
    Ui::MainWindow *ui;
    SettingsWindow *settingsWindow;
    World m_world;
    void renderWorld();
    void initializeWidgets();
    void deleteWidgets();
    QTimer tickTimer;
    int cellHeight, cellWidth;
};
#endif // MAINWINDOW_H
