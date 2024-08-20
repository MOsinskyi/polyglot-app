#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("PoliglotApp");

    buttons = {ui->lesson1, ui->lesson2, ui->lesson3, ui->lesson4, ui->lesson5};

    for (int i = 0; i < buttons.size(); ++i) {
        connect(buttons[i], &QPushButton::clicked, this, [this, i](){ openOptionsMenu(i + 1); });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openOptionsMenu(int lesson)
{
    selectOptionDialog = new SelectOptionDialog(nullptr, lesson);
    connect(selectOptionDialog, &QDialog::finished, selectOptionDialog, &QObject::deleteLater);
    selectOptionDialog->show();
}
