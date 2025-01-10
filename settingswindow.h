#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>

namespace Ui {
class SettingsWindow;
}

/**
 * @brief The SettingsWindow class
 *
 * Represents the settings window of the application.
 */
class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new SettingsWindow object.
     *
     * @param parent Parent widget.
     */
    explicit SettingsWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroy the SettingsWindow object.
     */
    ~SettingsWindow();

protected:
    /**
     * @brief Reimplemented to handle the show event.
     *
     * @param event The show event.
     */
    void showEvent(QShowEvent *event) override;

private slots:
    /**
     * @brief Slot for handling the accepted signal of the button box.
     */
    void on_buttonBox_accepted();

private:
    Ui::SettingsWindow *ui; /**< UI object for the settings window. */
};

#endif // SETTINGSWINDOW_H
