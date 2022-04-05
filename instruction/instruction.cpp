#include "instruction.h"
#include "ui_instruction.h"

instruction::instruction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::instruction)
{
    ui->setupUi(this);
    QString strExplain = "使用说明";
    ui->label_explain->setText(strExplain);
    ui->label_explain->setAlignment(Qt::AlignCenter);
}

instruction::~instruction()
{
    delete ui;
}
