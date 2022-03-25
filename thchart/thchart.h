#ifndef THCHART_H
#define THCHART_H
#include <QWidget>

namespace Ui {
class THchart;
}

class THchart : public QWidget
{
    Q_OBJECT

public:
    explicit THchart(QWidget *parent = nullptr);
    ~THchart();

private:
    Ui::THchart *ui;
};

#endif // THCHART_H
