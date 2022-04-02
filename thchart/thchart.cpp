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
    m_valueLabel->setStyleSheet(QString("QLabel{color:#1564FF; font-family:\"Microsoft Yahei\"; font-size:12px; font-weight:bold;"
                                        " background-color:rgba(21, 100, 255, 51); border-radius:4px; text-align:center;}"));
    m_valueLabel->setFixedSize(44, 24);
    m_valueLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_valueLabel->hide();

    QPen penY(Qt::darkBlue,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    chart = new QChart();
    Tseries = new QSplineSeries;
    Hseries = new QSplineSeries;
    Point = new QScatterSeries;
    axisX = new QDateTimeAxis();
    axisY = new QValueAxis();

    chart->addSeries(Tseries);
    chart->addSeries(Hseries);
    chart->addSeries(Point);
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
    chart->legend()->setVisible(false);
    Tseries->attachAxis(axisX);                           //把数据添加到坐标轴上
    Tseries->attachAxis(axisY);
    Hseries->attachAxis(axisX);                           //把数据添加到坐标轴上
    Hseries->attachAxis(axisY);

    Point->setMarkerShape(QScatterSeries::MarkerShapeCircle);//圆形的点
    QRadialGradient radialGrad(QPointF(100, 100), 100);
         radialGrad.setColorAt(0, QColor(255, 255, 255));
         radialGrad.setColorAt(0.9, QColor(255, 255, 255));
         radialGrad.setColorAt(0.91, QColor(255, 0, 0));
         radialGrad.setColorAt(1, QColor(212, 227, 255));

    Point->setBrush(QBrush(radialGrad));//背景颜色
    Point->setMarkerSize(12);                     //点大小
    Point->attachAxis(axisX);
    Point->attachAxis(axisY);

    //把chart显示到窗口上
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);   //设置抗锯齿

    connect(Point, &QScatterSeries::hovered, this, &THchart::slotPointHoverd);//用于鼠标移动到点上显示数值
}

void THchart::DrawChart()
{
    //设置坐标轴显示范围
    chart->axes(Qt::Horizontal).back()->setRange(QDateTime::currentDateTime().addSecs(-60 * 1), QDateTime::currentDateTime().addSecs(0));
    Tseries->append(rcvTime, temp);
    Hseries->append(rcvTime, humi);
    Point->append(rcvTime, temp);
    Point->append(rcvTime, humi);
    //qDebug()<<rcvTime<<temp<<humi;
}

void THchart::slotPointHoverd(const QPointF &point, bool state)
{
    if (state) {
        m_valueLabel->setText(QString::asprintf("%1.0f", point.y()));
        QPoint curPos = mapFromGlobal(QCursor::pos());
        m_valueLabel->move(curPos.x() - m_valueLabel->width() / 2, curPos.y() - m_valueLabel->height() * 1.5);//移动数值
        m_valueLabel->show();//显示出来
    }
    else {
        m_valueLabel->hide();//进行
    }
}
