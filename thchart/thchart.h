#ifndef THCHART_H
#define THCHART_H
#include <QSplineSeries>
#include <QScatterSeries>
#include <QChartView>
#include <QChart>
#include <QWidget>
#include <QVector>
#include <QTimer>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QDebug>
#include <QLabel>
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
    void slotPointHoverd(const QPointF &point, bool state);

private:
    Ui::THchart *ui;

    QSplineSeries *Tseries;
    QSplineSeries *Hseries;
    QScatterSeries *Point;
    QTimer *timer;                           //计时器
    QChart *chart;                           //画布
    QDateTimeAxis *axisX;                    //轴
    QValueAxis *axisY;
    qint64 rcvTime;
    int temp;
    int humi;
    QLabel *m_valueLabel;
};

#endif // THCHART_H
