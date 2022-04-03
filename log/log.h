#ifndef LOG_H
#define LOG_H

#include <QWidget>
#include <database/dataBase.h>
#include <QVector>
#include <QStandardItemModel>
#include "QHBoxLayout"
#include <QTableView>
#include <QHeaderView>
#include <QMessageBox>

namespace Ui
{
    class log;
}

class log : public QWidget, public dataBase
{
    Q_OBJECT

public:
    explicit log(QWidget *parent = nullptr);

    void logViewer(int typeId);
    void tableCreator(int size_row);

    void addLog(QString user, int eventId, QString eventContent);
    QVector<QVector<QString>> getLog(QString type);
    void delLogs(QVector<int> row, int delType, int count);

    ~log();

private slots:
    void on_tabWidget_currentChanged(int index);

    void on_pushButton_delLog_clicked();

    void on_radioButton_MutiSelect_clicked();

    void on_pushButton_delAllTab_clicked();

private:
    Ui::log *ui;
    QTableView *tableView;
    QVector<QVector<QString>> viewLog;
    int currentTab;
    bool checkState;
    int size_row;
};

#endif // LOG_H
