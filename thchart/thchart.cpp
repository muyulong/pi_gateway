#include "thchart.h"
#include "ui_thchart.h"

THchart::THchart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::THchart)
{
    ui->setupUi(this);

    connect(this,SIGNAL(gotData()),this,SLOT(DrawChart()));

    InitChart();
}

THchart::~THchart()
{
    delete ui;
}

void THchart::setTHchart(qint64 pTime,int pTemp,int pHumi)
{
    rcvTime = pTime;
    temp = pTemp;
    humi = pHumi;
    emit gotData();
}

void THchart::InitChart()
{
    QPen penY(Qt::darkBlue,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    chart = new QChart();
    Tseries = new QSplineSeries;
    Hseries = new QSplineSeries;
    axisX = new QDateTimeAxis();
    axisY = new QValueAxis();

    chart->addSeries(Tseries);
    chart->addSeries(Hseries);
    axisX->setTickCount(10);                             //设置坐标轴格数
    axisY->setTickCount(5);
    axisX->setFormat("hh:mm:ss");                        //设置时间显示格式
    axisY->setMin(0);                                    //设置Y轴范围
    axisY->setMax(100);
    axisX->setTitleText("实时时间");                       //设置X轴名称
    axisY->setTitleText("温度湿度");
    axisY->setLinePenColor(QColor(Qt::darkBlue));        //设置坐标轴颜色样式
    axisY->setGridLineColor(QColor(Qt::darkBlue));
    axisY->setGridLineVisible(false);                    //设置Y轴网格不显示
    axisY->setLinePen(penY);
    axisX->setLinePen(penY);
    chart->setTitle("温度湿度表");//整个绘图窗体标题
    chart->addAxis(axisX,Qt::AlignBottom);               //设置坐标轴位于chart中的位置
    chart->addAxis(axisY,Qt::AlignLeft);
    Tseries->attachAxis(axisX);                           //把数据添加到坐标轴上
    Tseries->attachAxis(axisY);
    Hseries->attachAxis(axisX);                           //把数据添加到坐标轴上
    Hseries->attachAxis(axisY);

    //把chart显示到窗口上
    ui->widget->setChart(chart);
    ui->widget->setRenderHint(QPainter::Antialiasing);   //设置抗锯齿
}

void THchart::DrawChart()
{
    //设置坐标轴显示范围
    chart->axes(Qt::Horizontal).back()->setRange(QDateTime::currentDateTime().addSecs(-60 * 1), QDateTime::currentDateTime().addSecs(0));
    Tseries->append(rcvTime, temp);
    Hseries->append(rcvTime, humi);
    //qDebug()<<rcvTime<<temp<<humi;
}
