#include "task.h"
#include "ui_task.h"

task::task(QWidget *parent)
    : QWidget(parent), ui(new Ui::task)
{
    ui->setupUi(this);
    this->initTask();
}

task::~task()
{
    delete ui;
}

void task::initTask()
{
    //初始化数据库和任务表
    QString tableName = "tasks";
    QString columnName[4] = {"time", "content", "isActive"};
    QString dataType[4] = {"varchar", "varchar", "bool"};
    int columnNum = 4;
    // time varchar,user vachar,event varchar,type varchar
    initDatebase();
    createTable(tableName, columnName, dataType, columnNum);

    ui->comboBox_event->addItems(QStringList() << "打开灯泡"
                                               << "关闭灯泡"
                                               << "打开风扇"
                                               << "关闭风扇"
                                               << "监测温度");
    radioSelect = 0;
    ui->radioButton_time->click();
}

//添加任务
void task::addTask(QDateTime dateTime, QTime time, int taskContentID, bool radioSelect)
{
    query = QSqlQuery(db);
    QString time_sql = "每天" + time.toString();
    QString dataTime_sql = dateTime.toString("yyyy-MM-dd hh:mm");
    QString content_sql = QString::fromLocal8Bit("");
    taskStatus = 0;
    switch (taskContentID)
    {
    case 0:
        content_sql = "打开灯泡";
        break;
    case 1:
        content_sql = "关闭灯泡";
        break;
    case 2:
        content_sql = "打开风扇";
        break;
    case 3:
        content_sql = "关闭风扇";
        break;
    case 4:
        content_sql = "监测温度";
        break;
    default:
        break;
    }
    query.prepare("INSERT INTO tasks (time, content,isActive) "
                  "VALUES (?, ?, ?)");
    if (radioSelect)
    {
        query.addBindValue(time_sql);
        query.addBindValue(content_sql);
        query.addBindValue(taskStatus);
    }
    else
    {
        query.addBindValue(dataTime_sql);
        query.addBindValue(content_sql);
        query.addBindValue(taskStatus);
    }
    query.exec();
    // qDebug()<<time<<" "<<dateTime<<" "<<taskContentID<<" "<<radioSelect;
    // qDebug()<<time_sql<<" "<<dataTime_sql;
}
//获取任务
vector<vector<QString>> task::getTask()
{
    query = QSqlQuery(db);
    QString search_sql = "select * from tasks";
    query.prepare(search_sql);
    query.exec();
    qDebug() << "查找全部计划任务";
    int row = 0, col = 3;
    vector<vector<QString>> tasks(sqlSize(query), vector<QString>(col, 0));
    while (query.next() && row <= sqlSize(query))
    {
        tasks[row][0] = query.value(0).toString();
        tasks[row][1] = query.value(1).toString();
        tasks[row][2] = query.value(2).toString();
        row++;
    }
    return tasks;
}
//删除任务
bool task::delTask(int taskID)
{
    if (isTaskActive(taskID))
    {
        return 0;
    }
    else
    {
        query = QSqlQuery(db);
        QString del_sql = QString("delete from tasks where rowid =  '%1'").arg(taskID);
        query.prepare(del_sql);
        query.exec();
        qDebug() << "执行了删除单行操作";
        query.exec("vacuum");
        qDebug() << "执行了刷新数据库操作";
        return 1;
    }
}
//判断任务是否处于运行状态
bool task::isTaskActive(int taskID)
{
    query = QSqlQuery(db);
    QString find_sql = QString("select * from tasks where rowid =  '%1'").arg(taskID);
    query.prepare(find_sql);
    query.exec();
    query.next();
    if (query.record().value(2).toBool())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void task::setTask(int taskID, bool status)
{
    query = QSqlQuery(db);
    // UPDATE tasks SET isActive=0 WHERE ROWID = 1
    QString update_sql = QString("update tasks set isActive = '%1' where rowid = '%2' ").arg(status).arg(taskID);
    query.prepare(update_sql);
    query.exec();
}

//----------------------------------
//从主界面移植的代码

void task::on_pushButton_setTask_clicked()
{
    QDateTime datetime;
    QTime time;
    int taskContentID;
    datetime = ui->dateTimeEdit->dateTime();
    time = ui->timeEdit->time();
    taskContentID = ui->comboBox_event->currentIndex();
    addTask(datetime, time, taskContentID, radioSelect);
    taskViewer();
}

void task::on_radioButton_time_clicked()
{
    ui->dateTimeEdit->setEnabled(false);
    ui->timeEdit->setEnabled(true);
    radioSelect = 1;
}

void task::on_radioButton_dateTime_clicked()
{
    ui->dateTimeEdit->setEnabled(true);
    ui->timeEdit->setEnabled(false);
    radioSelect = 0;
}

void task::taskViewer()
{
    viewTask = getTask();
    size_row = viewTask.size();
    qDebug() << "接收到任务数量：" << viewTask.size();
    taskTable(size_row);
}

void task::taskTable(int size_row)
{
    //。。。。。。。。。。。。。
    QStandardItemModel *standItemModel = new QStandardItemModel(this);
    standItemModel->setColumnCount(3);
    // standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("时间"));   //设置表头内容
    standItemModel->setHeaderData(0, Qt::Horizontal, ("时间")); //设置表头内容
    standItemModel->setHeaderData(1, Qt::Horizontal, ("任务"));
    standItemModel->setHeaderData(2, Qt::Horizontal, ("状态"));
    //向表格添加内容
    for (int i = 0; i < size_row; ++i)
    {

        QString time = viewTask[i][0];
        QString task = viewTask[i][1];
        QString status = viewTask[i][2];
        if (status == "0")
        {
            status = "未运行";
        }
        if (status == "1")
        {
            status = "运行中";
        }
        standItemModel->setItem(i, 0, new QStandardItem(time));
        standItemModel->setItem(i, 1, new QStandardItem(task));
        standItemModel->setItem(i, 2, new QStandardItem(status));
        standItemModel->item(i, 0)->setTextAlignment(Qt::AlignCenter); //设置表格内容居中
        standItemModel->item(i, 1)->setTextAlignment(Qt::AlignCenter); //设置表格内容居中
        standItemModel->item(i, 2)->setTextAlignment(Qt::AlignCenter); //设置表格内容居中
    }
    ui->tableView_task->setModel(standItemModel); //挂载表格模型
    //设置表格属性
    // tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);        //表头信息显示居中
    // ui->tableView_task->setColumnWidth(0,150);       //设定表格宽度
    // ui->tableView_task->setColumnWidth(1,80);
    // ui->tableView_task->setColumnWidth(2,75);
    // tableView->verticalHeader()->hide();    //隐藏默认显示的行头
    ui->tableView_task->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时整行选中
    ui->tableView_task->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
    /* 设置列宽在可视界面自适应宽度 */
    ui->tableView_task->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // qDebug() <<tableView->horizontalHeader();
    /* 行颜色交替显示 */
    ui->tableView_task->setAlternatingRowColors(true);
    /* 不允许在图形界面修改内容 */
    //    tableView->setContextMenuPolicy(Qt::CustomContextMenu);         //需要在表格使用右键菜单，需要启动该属性
    //    tableView->sortByColumn(0,Qt::AscendingOrder);                 //表格第0列，按降序排列
    ui->tableView_task->setSelectionMode(QAbstractItemView::SingleSelection);
    //。。。。。。。。。。。。。
}

void task::on_pushButton_startTask_clicked()
{
    int i = 0;
    i = ui->tableView_task->currentIndex().row() + 1;
    setTask(i, 1);
    taskViewer();
}

void task::on_pushButton_stopTask_clicked()
{
    int i = 0;
    i = ui->tableView_task->currentIndex().row() + 1;
    setTask(i, 0);
    taskViewer();
}

void task::on_pushButton_delTask_clicked()
{
    QString dlgTitle = QString("删除");
    QString strInfo;
    int i = 0;
    i = ui->tableView_task->currentIndex().row() + 1;
    qDebug() << i;
    if (i == 0)
    {
        strInfo = "未选中任何行！";
    }
    else
    {
        bool dT = delTask(i);
        if (!dT)
        {
            strInfo = QString("无法删除正在运行中的任务！");
        }
        if (dT)
        {
            strInfo = QString("已删除第%1条记录！").arg(i);
        }
    }
    QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok, QMessageBox::NoButton);
    taskViewer();
}
