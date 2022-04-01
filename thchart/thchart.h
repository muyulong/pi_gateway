#ifndef THCHART_H
#define THCHART_H
#include <QSplineSeries>
#include <QChartView>
#include <QChart>
#include <QWidget>
#include <QVector>
#include <QTimer>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QDebug>
//#include <node/node.h>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class THchart;
}

class THchart : public QWidget
{
    Q_OBJECT

public:
    explicit THchart(QWidget *parent = nullptr);
    ~THchart();

    void InitChart();

signals:
    void gotData();

public slots:
    void setTHchart(qint64,int,int);

private slots:
    void DrawChart();

private:
    Ui::THchart *ui;

    QSplineSeries *Tseries;
    QSplineSeries *Hseries;
    QTimer *timer;                           //计时器
    QChart *chart;                           //画布
    QDateTimeAxis *axisX;                    //轴
    QValueAxis *axisY;
    qint64 rcvTime;
    int temp;
    int humi;
    //node *m_node;
};

#endif // THCHART_H
