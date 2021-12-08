#ifndef NODE_H
#define NODE_H

#include <QDialog>

namespace Ui {
class node;
}

class node : public QDialog
{
    Q_OBJECT

public:
    explicit node(QWidget *parent = nullptr);
    ~node();

private:
    Ui::node *ui;
};

#endif // NODE_H
