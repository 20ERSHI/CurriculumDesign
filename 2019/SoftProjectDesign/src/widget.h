#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<product.h>
#include<staff.h>
#include<user.h>
#include<string>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQueryModel>
#include<QtDebug>
#include<QMessageBox>
#include <QSqlQuery>//执行sql语句相关
#include <QSqlDatabase>//连接数据库相关
#include <QSqlError>//数据库错误相关
#include <QSqlRecord>//数据库记录相关
#include <QSqlQueryModel>//数据查询模型
#include<QInputDialog>

using namespace  std;
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setPp(double pp);//传入总价，显示在led上顺便设置pp
    void setUser(bool user){this->userstate = user;}
    void setpki(int lv){this->pki = lv;}
    void addLog(string str);
    void clearLog();
    void conductpp();
    QSqlDatabase initSQL();

private slots:





    void on_buttonClear_clicked();


    void on_buttonCheckOut_clicked();

    void on_buttonOpenPM_clicked();

    void on_buttonOpenUM_clicked();

    void on_buttonOpenSM_clicked();

    void initModel();

    void on_buttonDelRow_clicked();

    void on_buttonAddProduct_2_clicked();



    void on_buttonDelRow_2_clicked();

private:
    Ui::Widget *ui;
    user * userWindow;//新建一个login类指针
    staff * staffWindow;
    product * productWindow;
    double pp;
    int pki;
    bool userstate = false;
    QString  log;
    QSqlDatabase db;


};
#endif // WIDGET_H
