#include "node.h"
#include "ui_node.h"

node::node(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::node)
{
    ui->setupUi(this);
}

node::~node()
{
    delete ui;
}
