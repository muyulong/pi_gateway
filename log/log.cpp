#include "log.h"
#include "ui_log.h"

log::log(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::log)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //初始化数据库和日志表
    QString  tableName="logs";
    QString columnName[4]={"time","user","event","type"};
    QString dataType[4]={"varchar","varchar","varchar","varchar"};
    int columnNum=4;
    //time varchar,user vachar,event varchar,type varchar
    initDatebase();
    createTable(tableName,columnName,dataType,columnNum);
    ui->setupUi(this);

    ui->radioButton_MutiSelect->setChecked(false);
    checkState=0;
}

log::~log()
{
    delete ui;
}

void log::logViewer(int typeId)
{
    QString type;
    switch (typeId) {
    case 1:
        type="全部";
        break;
    case 2:
        type="定时任务";
        break;
    case 3:
        type="操作日志";
        break;
    case 4:
        type="警告";
        break;
    default:
        break;
    }
    viewLog=getLog(type);

    size_row = viewLog.size();
    qDebug() << "接收到日志数量："<<viewLog.size();
    tableCreator(size_row);
}
void log::tableCreator(int size_row)
{
    //。。。。。。。。。。。。。
    QStandardItemModel* standItemModel = new QStandardItemModel(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;       //垂直布局
    mainLayout->setSpacing(50);         //设置控件间距
    mainLayout->setMargin(70);          //设置边缘间距
    //mainLayout.
    //添加QTableView代码
    tableView = new QTableView;
    //添加表头
    standItemModel->setColumnCount(3);
    standItemModel->setHeaderData(0,Qt::Horizontal,("时间"));   //设置表头内容
    standItemModel->setHeaderData(1,Qt::Horizontal,("事件"));
    standItemModel->setHeaderData(2,Qt::Horizontal,("用户"));
    //向表格添加内容
    for(int i=0;i<size_row;++i)
    {
        QString time=viewLog[i][0];
        QString user=viewLog[i][1];
        QString event=viewLog[i][2];
        standItemModel->setItem(i, 0, new QStandardItem(time));
        standItemModel->setItem(i, 1, new QStandardItem(event));
        standItemModel->setItem(i, 2, new QStandardItem(user));
        standItemModel->item(i,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        standItemModel->item(i,1)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        standItemModel->item(i,2)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
    }
    tableView->setModel(standItemModel);    //挂载表格模型
    //设置表格属性
    //tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);        //表头信息显示居中
    tableView->setColumnWidth(0,100);       //设定表格第0列宽度
    tableView->setColumnWidth(1,200);
    //tableView->verticalHeader()->hide();    //隐藏默认显示的行头
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时整行选中
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
    /* 设置列宽在可视界面自适应宽度 */
    tableView->horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);
    //qDebug() <<tableView->horizontalHeader();
    /* 行颜色交替显示 */
    tableView->setAlternatingRowColors(true);
    /* 不允许在图形界面修改内容 */
    //    tableView->setContextMenuPolicy(Qt::CustomContextMenu);         //需要在表格使用右键菜单，需要启动该属性
    //    tableView->sortByColumn(0,Qt::AscendingOrder);                 //表格第0列，按降序排列
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(tableView);    //添加控件
    this->ui->tabWidget->setLayout(mainLayout);
    //setLayout(mainLayout);        //显示垂直布局
    //。。。。。。。。。。。。。
}
void log::on_tabWidget_currentChanged(int index)
{
    delete ui->tabWidget->layout();
    currentTab=index+1;
    logViewer(currentTab);

}


void log::on_pushButton_delLog_clicked()
{
    //    int i = tableView->currentIndex().row()+1;
    //    qDebug()<<i;
    //    d.delLogs(i);
    //    delete ui->tabWidget->layout();
    //    logViewer(currentTab);
    //    QString dlgTitle=QString("删除");
    //    QString strInfo=QString("已删除第%1条记录！"). arg(i);
    //    QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    //    qDebug()<<tableView->selectionModel()->selectedRows();
    //    QModelIndexList indexList = tableView->selectionModel()->selectedRows();
    //    int row;
    //    int count=0;
    //    foreach (QModelIndex index, indexList) {
    //        row = index.row();
    //        count++;
    //        qDebug()<<row;
    //    }
    //    qDebug()<<count;
    QString dlgTitle=QString("删除");
    QString strInfo;
    int clickState=0;
    if(ui->radioButton_MutiSelect->isChecked())
    {
        //多选
        qDebug()<<tableView->selectionModel()->selectedRows();
        QModelIndexList indexList = tableView->selectionModel()->selectedRows();
        int count=0;
        vector<int> mutiRow;
        foreach (QModelIndex index, indexList) {
            //mutiRow[count] = index.row();
            mutiRow.push_back(index.row()+1);
            count++;
        }
        qDebug()<<mutiRow;
        qDebug()<<count;
        delLogs(mutiRow,2,count);
        strInfo=QString("已删除%1条记录！"). arg(count);
        //QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        if(count==0)
            clickState=0;
        else
            clickState=2;
    }
    else
    {
        //单选
        // qDebug()<<i;
        //delete ui->tabWidget->layout();
        //logViewer(currentTab);
        //qDebug()<<tableView->currentIndex().row();
        //QString strInfo=QString("已删除第%1条记录！"). arg(i);
        //QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        //=================
        int i;
        i= tableView->currentIndex().row()+1;
        qDebug()<<i;
        vector<int> singleRow(1,i);
        delLogs(singleRow,1,1);
        qDebug()<<singleRow;
        strInfo=QString("已删除第%1条记录！"). arg(singleRow[0]);
        //QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
        if(singleRow[0]==0)
            clickState=0;
        else
            clickState=1;
    }
    if(clickState==0)
    {
        strInfo="未选中任何行！";
    }
    QMessageBox::information(this, dlgTitle, strInfo,QMessageBox::Ok,QMessageBox::NoButton);
    delete ui->tabWidget->layout();
    logViewer(currentTab);
    ui->radioButton_MutiSelect->setChecked(false);
    checkState=0;
}


void log::on_radioButton_MutiSelect_clicked()
{
    //。。。。。。。。。。。。
    //设置多选


    if(!checkState)
    {
        delete ui->tabWidget->layout();
        logViewer(currentTab);
        tableView->setSelectionMode(QAbstractItemView::MultiSelection);
        checkState=1;
    }
    else
    {
        delete ui->tabWidget->layout();
        logViewer(currentTab);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        checkState=0;
    }
    qDebug()<<checkState;
    //。。。。。。。。。。。。
}


void log::on_pushButton_delAllTab_clicked()
{
    if(checkState==0)
    {
        on_radioButton_MutiSelect_clicked();
        ui->radioButton_MutiSelect->setChecked(true);
    }
    for(int i=0;i<=size_row;i++)
    {
        tableView->selectRow(i);
    }
    //on_pushButton_delLog_clicked();
    //tableView->selectRow();
    //删除多行数据库速度很慢
}

void log::addLog(QString user,int eventId){
    //QString newLog = user+" do "+event+" at "+"time";
    QString time =QDateTime::currentDateTime() .toString("yyyy-MM-dd hh:mm:ss ddd");
    QString event;
    QString type;
    switch (eventId) {
    case 1:
        event="登录系统";
        type="操作日志";
        break;
    case 2:
        event="退出系统";
        type="操作日志";
        break;
    case 3:
        event="初始化系统";
        type="操作日志";
        break;
    default:
        event="未知事件";
        type="全部";
        break;
    }
    query=QSqlQuery(db);
    query.prepare("INSERT INTO logs (time, user, event, type) "
                          "VALUES (?, ?, ?, ?)");
    query.addBindValue(time);
    query.addBindValue(user);
    query.addBindValue(event);
    query.addBindValue(type);
    query.exec();
}

vector<vector<QString>>  log::getLog(QString type)
{
    //在数据库中检索对应类型的日志
    query=QSqlQuery(db);
    QString search_sql="select * from logs where type=(?)";
    QString search_sql_all="select * from logs";
    if(type=="全部")
    {
        query.prepare(search_sql_all);
        qDebug() << "查找全部日志";
    }
    else
    {
        query.prepare(search_sql);
        query.addBindValue(type);
        qDebug() << "查找日志";
    }
    query.exec();
    //
    //    query.prepare(search_sql);
    //    query.addBindValue(type);
    //    query.exec();
    //qDebug()<<"执行query. exec()结果为："<<query.exec();
    //qDebug()<<"返回query. next()结果为："<<query.next();
    //qDebug() << "一共有"<<sqlSize(query)<<"条日志";
    int row=0,col=3;
    //    QString logs[i][3];
    vector<vector<QString> > logs(sqlSize(query),vector<QString>(col,0));
    while(query.next()&&row<=sqlSize(query))
    {
        //        logs[i-1][0]=query.value(0).toString();
        //        logs[i-1][1]=query.value(1).toString();
        //        logs[i-1][2]=query.value(2).toString();
        logs[row][0]=query.value(0).toString();
        logs[row][1]=query.value(1).toString();
        logs[row][2]=query.value(2).toString();
        row++;
        //qDebug() << "存入第"<<row<<"个日志";
        //QString line=QString(str("学号")+”%1"+str("姓名")+”%2"+str("身高")+”%3").arg(number).arg(name).arg(height);
        //QString line=QString("学号 %1     姓名 %2     身高 %3").arg(number,5).arg(name,10).arg(height,5);
        //qDebug()<<line;
        //ui->textEditList->append(line);


    }
    return logs;
}

//void Widget::on_listButton_clicked()//列表按钮
//{
//    int number;
//    QString name;
//    int height;
//    QString listStr=QString("select * from student");
//    QSqlQuery query;
//    query.exec(listStr);
//    ui->textEditList->clear();
//    while(query.next())
//    {
//        number=query.value(0).toInt();
//        name=query.value(1).toString();
//        height=query.value(2).toInt();
//        //QString line=QString(str("学号")+”%1"+str("姓名")+”%2"+str("身高")+”%3").arg(number).arg(name).arg(height);
//        QString line=QString("学号 %1     姓名 %2     身高 %3").arg(number,5).arg(name,10).arg(height,5);
//        //qDebug()<<line;
//        ui->textEditList->append(line);
//    }
//}


void log::delLogs(vector<int> row,int delType,int count)
{
    query=QSqlQuery(db);
    switch (delType) {
    case 1:
    {
        QString del_single_sql=QString("delete from logs where rowid =  '%1'"). arg(row[0]);
        query.prepare(del_single_sql);
        query.exec();
        qDebug()<<"执行了删除单行操作";
        break;
    }
    case 2:
    {
        for(int i=0;i<count;i++)
        {
            QString del_muti_sql=QString("delete from logs where rowid =  '%1'"). arg(row[i]);
            query.prepare(del_muti_sql);
            query.exec();
        }
        qDebug()<<"执行了删除多行操作";
        break;
    }
    default:
        break;
    }

    query.exec("vacuum");
    qDebug()<<"执行了刷新数据库操作";
}
