#include "instruction.h"
#include "ui_instruction.h"
#include <QFile>
#include <QDebug>

instruction::instruction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::instruction)
{
    ui->setupUi(this);
}
instruction::~instruction()
{
    delete ui;
}
