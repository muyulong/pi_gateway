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
    m_valueLabel = new QLabel(this);
    m_valueLabel->setStyleSheet(QString("QLabel{color:#FFFFFF; font-family:\"Microsoft Yahei\"; font-size:14px; font-weight:bold;"
                                        " background-color:rgba(212, 146, 165, 90); border-radius:4px; text-align:center;}"));
    m_valueLabel->setFixedSize(70, 38);
    m_valueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_valueLabel->hide();

    QPen pen(Qt::white,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    chart = new QChart();
    Tseries = new QSplineSeries;
    Hseries = new QSplineSeries;
    TPoint = new QScatterSeries;
    HPoint = new QScatterSeries;
    axisX = new QDateTimeAxis();
    axisY = new QValueAxis();

    chart->addSeries(Tseries);
    chart->addSeries(Hseries);
    chart->addSeries(TPoint);
    chart->addSeries(HPoint);
    axisX->setTickCount(10);                             //设置坐标轴格数
    axisY->setTickCount(5);
    axisX->setFormat("hh:mm:ss");                        //设置时间显示格式
    axisY->setMin(0);                                    //设置Y轴范围
    axisY->setMax(100);
    axisX->setTitleText("实时时间");                       //设置X轴名称
    axisY->setTitleText("温度湿度");
    axisX->setLabelsFont(QFont("微软雅黑",10,-1,false));
    axisY->setLabelsFont(QFont("微软雅黑",10,-1,false));
    axisX->setTitleBrush(QColor(Qt::white));
    axisY->setTitleBrush(QColor(Qt::white));
    axisX->setLabelsColor(QColor(Qt::white));
    axisY->setLabelsColor(QColor(Qt::white));
    axisX->setLinePenColor(QColor(Qt::white));        //设置坐标轴颜色样式
    axisX->setGridLineColor(QColor(Qt::white));
    axisX->setGridLineVisible(false);                    //设置Y轴网格不显示
    axisY->setLinePen(pen);
    axisX->setLinePen(pen);
    chart->setTitle("温度湿度表");//整个绘图窗体标题
    chart->setTitleBrush(QColor(Qt::white));
    chart->setTitleFont(QFont("微软雅黑",14,-1,false));
    chart->addAxis(axisX,Qt::AlignBottom);               //设置坐标轴位于chart中的位置
    chart->addAxis(axisY,Qt::AlignLeft);
    chart->setBackgroundBrush(QColor(146, 165, 212));
    chart->legend()->setVisible(false);
    Tseries->attachAxis(axisX);                           //把数据添加到坐标轴上
    Tseries->attachAxis(axisY);
    Hseries->attachAxis(axisX);                           //把数据添加到坐标轴上
    Hseries->attachAxis(axisY);
    Tseries->setPen(QPen(QBrush(QColor(172, 227, 93)),4,Qt::SolidLine));
    Hseries->setPen(QPen(QBrush(QColor(247, 234, 101)),4,Qt::SolidLine));
    TPoint->setMarkerShape(QScatterSeries::MarkerShapeCircle);//圆形的点
    HPoint->setMarkerShape(QScatterSeries::MarkerShapeCircle);//圆形的点
    QRadialGradient radialGrad(QPointF(100, 100), 100);
    radialGrad.setColorAt(0, QColor(255, 255, 255));
    radialGrad.setColorAt(0.9, QColor(255, 255, 255));
    radialGrad.setColorAt(0.91, QColor(255, 0, 0));
    radialGrad.setColorAt(1, QColor(212, 227, 255));

    TPoint->setBrush(QBrush(radialGrad));//背景颜色
    TPoint->setMarkerSize(12);                     //点大小
    TPoint->attachAxis(axisX);
    TPoint->attachAxis(axisY);
    HPoint->setBrush(QBrush(radialGrad));//背景颜色
    HPoint->setMarkerSize(12);                     //点大小
    HPoint->attachAxis(axisX);
    HPoint->attachAxis(axisY);

    //把chart显示到窗口上
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);   //设置抗锯齿
    ui->chartView->setBackgroundBrush(QColor(122, 147, 207));

    connect(TPoint, &QScatterSeries::hovered, this, &THchart::slotTPointHoverd);//用于鼠标移动到点上显示数值
    connect(HPoint, &QSplineSeries::hovered, this, &THchart::slotHPointHoverd);//用于鼠标移动到点上显示数值
}

void THchart::DrawChart()
{
    //设置坐标轴显示范围
    chart->axes(Qt::Horizontal).back()->setRange(QDateTime::currentDateTime().addSecs(-60 * 1), QDateTime::currentDateTime().addSecs(0));
    Tseries->append(rcvTime, temp);
    Hseries->append(rcvTime, humi);
    TPoint->append(rcvTime, temp);
    HPoint->append(rcvTime, humi);
}

void THchart::slotTPointHoverd(const QPointF &point, bool state)
{
    if (state) {
        m_valueLabel->setText("温度:"+QString::asprintf("%1.0f", point.y())+"℃");
        QPoint curPos = mapFromGlobal(QCursor::pos());
        m_valueLabel->move(curPos.x() - m_valueLabel->width() / 2, curPos.y() - m_valueLabel->height() * 1.5);//移动数值
        m_valueLabel->show();//显示出来
    }
    else {
        m_valueLabel->hide();//进行
    }
}

void THchart::slotHPointHoverd(const QPointF &point, bool state)
{
    if (state) {
        m_valueLabel->setText("湿度:"+QString::asprintf("%1.0f", point.y())+"%");
        QPoint curPos = mapFromGlobal(QCursor::pos());
        m_valueLabel->move(curPos.x() - m_valueLabel->width() / 2, curPos.y() - m_valueLabel->height() * 1.5);//移动数值
        m_valueLabel->show();//显示出来
    }
    else {
        m_valueLabel->hide();//进行
    }
}
