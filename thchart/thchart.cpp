#include "thchart.h"
#include <QSplineSeries>
#include <QChartView>
#include <QChart>
QT_CHARTS_USE_NAMESPACE
#include "ui_thchart.h"

THchart::THchart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::THchart)
{
    ui->setupUi(this);

    QSplineSeries *series = new QSplineSeries();
    series->setName("spline");//设置该曲线名称

    series->append(0, 6);//加数据
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

//    series->setPointLabelsFormat("(@xPoint, @yPoint)");//两个坐标值都显示
    series->setPointLabelsFormat("@yPoint");//只显示Y值
    series->setPointLabelsVisible();//显示出来

    QChart *chart = new QChart();

    chart->addSeries(series);
    chart->setTitle("Simple spline chart example");//整个绘图窗体标题
    chart->createDefaultAxes();
    chart->axisY()->setRange(0, 10);//设置Y轴区间，不设置则为自动
//    chart->axisX()->setRange(0, 20);

//    chart->legend()->hide();//设置图例（上面的setname("spline")）不可见
//    chart->legend()->setVisible(true);//设置图例可见
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->widget->setChart(chart);
    ui->widget->setRenderHint(QPainter::Antialiasing);//使用可消除曲线锯齿（反走样），但是降低运行效率
}

THchart::~THchart()
{
    delete ui;
}
