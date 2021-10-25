#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_tost_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("He11o, Qt!");
    msgBox.setWindowTitle("VisualGDB Qt Demo on Pi");
    msgBox.exec();
}
