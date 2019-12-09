#include "product.h"
#include "ui_product.h"

product::product(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::product)
{
    ui->setupUi(this);
    this->db = initSQL();
    this->userstate = false;
}

product::~product()
{
    delete ui;
}
QSqlDatabase product::initSQL(){
    //需要进行判断默认的连接名是否存在，
    //如果不存在才使用addDatabase()方法，如果存在则使用database()方法
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QMYSQL");
    //连接数据库
    db.setHostName("mysql.twentyy.cn"); //数据库服务器IP
    db.setPort(10140);
    db.setUserName("root");//用户名
    db.setPassword("wsc350626");//密码
    db.setDatabaseName("smadata");//使用的数据库
    qDebug()<<"DatabaseConnect";
    //打开数据库
    if(!db.open())//数据库打开失败
        {
        QMessageBox::warning(this,"错误",db.lastError().text());

    }
    return db;
}

void product::on_buttonLogin_clicked()
{
    //检测登陆状态，如果登陆提示已登录
    if(this->userstate==true){
        //弹窗提示已登录
        QMessageBox::information(NULL, "已登录","用户已登录");
    }else{
        //未登录，则弹出窗口输入员工号
        bool ok = false;
        QString text = QInputDialog::getText(NULL, "登陆",
                                        "输入宁的员工编号嗷",
                                        QLineEdit::Normal,
                                        "",
                                        &ok);
          if ( ok && !text.isEmpty() )
          {
               //数据库查询id和对应的权限是否为1
              QSqlQuery query(db);
              query.prepare("SELECT username FROM user WHERE userid = :text ;");//设置访问收银台需要权限1
              query.bindValue(":text",QString::number(text.toInt()));
              query.exec();
              if(query.size()>0){
                    query.next();
                    QString username = query.value("username").toString();

                    QMessageBox::information(NULL, "登录成功", username+",欢迎你");
                    userstate = true;

                    ui->labelState->setText("用户["+username+"]已登录");


              }else{
                  QMessageBox::information(NULL, "登录失败", "权限不足或不存在该用户");
              }


          }else {
                    QMessageBox::information(NULL, "输入错误", "输入错误");
                }


    }




}

void product::on_buttonSearch_clicked()//查询
{

    QSqlQuery query(this->db);
    query.prepare("SELECT * FROM product WHERE sn = :text OR name = :text OR price = :text OR stock = :text;");
    query.bindValue(":text",ui->lineSearch->text());
    query.exec();
    for (int i=ui->tableWidget->rowCount();i>=0;i--) {
        ui->tableWidget->removeRow(i);
    }
    QString psn,pname,pprice,pstock;
     while (query.next())
     {
        //sql获取环节
         psn = query.value("sn").toString();
         pname = query.value("name").toString();
         pprice = query.value("price").toString();
         pstock = query.value("stock").toString();
         //写入数据
         int row = ui->tableWidget->rowCount();
         ui->tableWidget->insertRow(row);//增加一行
         ui->tableWidget->setItem(row,0,new QTableWidgetItem(psn));
         ui->tableWidget->setItem(row,1,new QTableWidgetItem(pname));
         //ui->tableWidget->setItem(row,2,new QTableWidgetItem(pprice));
         ui->tableWidget->setItem(row,2,new QTableWidgetItem(pstock));
     }

}

void product::on_buttonShowAll_clicked()
{
    QString text;
    QSqlQuery query(db);



    for (int i=ui->tableWidget->rowCount();i>=0;i--) {
        ui->tableWidget->removeRow(i);
    }

    query.exec("SELECT * FROM product;");//获取Product列表
    if(query.size()>0){//查询不为空的时候
       QString uid,userlv,username,usertel;
        QString psn,pname,pprice,pstock;

        while (query.next()) {
           //sql获取环节
            psn = query.value("sn").toString();
            pname = query.value("name").toString();
            pprice = query.value("price").toString();
            pstock = query.value("stock").toString();



            //写入数据
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);//增加一行
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(psn));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(pname));
            //ui->tableWidget->setItem(row,2,new QTableWidgetItem(pprice));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(pstock));




        }




    }else{
        QMessageBox::information(NULL, "获取失败", "发生未知错误");
    }
}

void product::on_buttonAdd_clicked()
{
    QMessageBox::information(NULL, "错误", "时间有限，库存系统尚未完善");
}

void product::on_buttonNewProduct_clicked()
{
    QMessageBox::information(NULL, "错误", "时间有限，库存系统尚未完善");
}
