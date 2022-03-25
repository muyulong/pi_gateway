#include "thchart.h"
QT_CHARTS_USE_NAMESPACE
#include "ui_thchart.h"

THchart::THchart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::THchart)
{
    ui->setupUi(this);

    // 构建图表对象
    QChart* chart = new QChart();

    // 构建折线系列对象
    QLineSeries *series = new QLineSeries();
    for (quint32 i = 0; i < 100; i++)
    {
        // 参数 x 为循环自增变量 i，参数 y 为正弦函数Y值
        series->append(i, sin(static_cast<double>(0.6f*i)));
    }

    // 将系列添加到图表
    chart->addSeries(series);
    // 基于已添加到图表的 series 来创建默认的坐标轴
    chart->createDefaultAxes();

    // 将图表绑定到视图
    ui->widget->setChart(chart);
}

THchart::~THchart()
{
    delete ui;
}
