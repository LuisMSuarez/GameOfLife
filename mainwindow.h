#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "world.h"
#include "settingswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 *
 * Represents the main window of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new MainWindow object.
     *
     * @param parent Parent widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroy the MainWindow object.
     */
    ~MainWindow();

private slots:
    /**
     * @brief Slot for handling the Start/Pause button click event.
     */
    void on_pushButtonStartPause_clicked();

    /**
     * @brief Slot for handling the Settings button click event.
     */
    void on_pushButtonSettings_clicked();

    /**
     * @brief Slot for handling the Add Fish button click event.
     */
    void on_pushButtonAddFish_clicked();

    /**
     * @brief Slot for handling the Add Shark button click event.
     */
    void on_pushButtonAddShark_clicked();

private:
    /**
     * @brief Render the world in the main window.
     */
    void renderWorld();

    /**
     * @brief Initialize the widgets in the main window.
     */
    void initializeWidgets();

    /**
     * @brief Delete the widgets in the main window.
     */
    void deleteWidgets();

    Ui::MainWindow *ui; /**< UI object for the main window. */
    SettingsWindow *settingsWindow; /**< Pointer to the settings window. */
    World m_world; /**< The world object representing the simulation. */
    QTimer tickTimer; /**< Timer for controlling the simulation ticks. */
    int cellHeight; /**< Height of each cell in the world. */
    int cellWidth; /**< Width of each cell in the world. */
};

#endif // MAINWINDOW_H
