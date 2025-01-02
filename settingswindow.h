#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SettingsWindow *ui;
};

#endif // SETTINGSWINDOW_H
