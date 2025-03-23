#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "fish.h"
#include "shark.h"

using namespace gameOfLifeCore;

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::showEvent(QShowEvent *event)
{
    ui->spinBoxFishReproductiveAge->setValue(Fish::s_reproductionTicks);
    ui->spinBoxFishLifetime->setValue(Fish::s_maxAge);

    ui->spinBoxSharkReproductiveAge->setValue(Shark::s_reproductionTicks);
    ui->spinBoxSharkLifetime->setValue(Shark::s_maxAge);

    QDialog::showEvent(event); // Call the base class implementation
}

void SettingsWindow::on_buttonBox_accepted()
{
    Fish::s_reproductionTicks = ui->spinBoxFishReproductiveAge->value();
    Fish::s_maxAge = ui->spinBoxFishLifetime->value();

    Shark::s_reproductionTicks = ui->spinBoxSharkReproductiveAge->value();
    Shark::s_maxAge = ui->spinBoxSharkLifetime->value();
}

