#ifndef USER_H
#define USER_H

#include <QWidget>
#include<QtDebug>
#include<QMessageBox>
#include <QSqlQuery>//执行sql语句相关
#include <QSqlDatabase>//连接数据库相关
#include <QSqlError>//数据库错误相关
#include <QSqlRecord>//数据库记录相关
#include <QSqlQueryModel>//数据查询模型
#include<QInputDialog>
namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    ~user();
    QSqlDatabase initSQL();

private slots:
    void on_buttonLogin_clicked();

    void on_buttonShowAll_clicked();

    void on_buttonUpdate_clicked();

    void on_buttonSearch_clicked();

private:
    Ui::user *ui;
    QSqlDatabase db;
    bool userstate = false;


};

#endif // USER_H
