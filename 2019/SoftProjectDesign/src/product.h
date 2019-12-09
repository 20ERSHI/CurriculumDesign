#ifndef PRODUCT_H
#define PRODUCT_H

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
class product;
}

class product : public QWidget
{
    Q_OBJECT

public:
    explicit product(QWidget *parent = nullptr);
    ~product();
    QSqlDatabase initSQL();

private slots:
    void on_buttonLogin_clicked();

    void on_buttonSearch_clicked();

    void on_buttonShowAll_clicked();

    void on_buttonAdd_clicked();

    void on_buttonNewProduct_clicked();

private:
    Ui::product *ui;
    QSqlDatabase db;
    bool userstate = false;

};

#endif // PRODUCT_H
