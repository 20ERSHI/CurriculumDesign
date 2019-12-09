#include "staff.h"
#include "ui_staff.h"

staff::staff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::staff)
{
    ui->setupUi(this);
    this->db = initSQL();
    this->userstate = false;
}

staff::~staff()
{
    delete ui;
}
QSqlDatabase staff::initSQL(){
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

void staff::on_buttonLogin_clicked()
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

void staff::on_buttonShowAll_clicked()
{
    QString text;
    QSqlQuery query(db);



    for (int i=ui->tableWidget->rowCount();i>=0;i--) {
        ui->tableWidget->removeRow(i);
    }

    query.exec("SELECT * FROM user;");//获取员工列表
    if(query.size()>0){//查询不为空的时候
       QString uid,userlv,username,usertel;


        while (query.next()) {
           //sql获取环节
            uid = query.value("userid").toString();
            userlv = query.value("userlv").toString();
            username = query.value("username").toString();
            usertel = query.value("usertel").toString();



            //写入数据
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);//增加一行
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(uid));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(userlv));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(username));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(usertel));




        }




    }else{
        QMessageBox::information(NULL, "获取失败", "发生未知错误");
    }
}

void staff::on_buttonSearch_clicked()
{
    QSqlQuery query(this->db);
    query.prepare("SELECT * FROM user WHERE userid = :text OR username = :text OR userlv = :text OR usertel = :text;");
    query.bindValue(":text",ui->lineSearch->text());
    query.exec();
    for (int i=ui->tableWidget->rowCount();i>=0;i--) {
        ui->tableWidget->removeRow(i);
    }
    QString vipid,vipname,vippo,vippoint;
     while (query.next())
     {
        //sql获取环节
         vipid = query.value("userid").toString();
         vipname = query.value("userlv").toString();
         vippo = query.value("username").toString();
         vippoint = query.value("usertel").toString();
         //写入数据
         int row = ui->tableWidget->rowCount();
         ui->tableWidget->insertRow(row);//增加一行
         ui->tableWidget->setItem(row,0,new QTableWidgetItem(vipid));
         ui->tableWidget->setItem(row,1,new QTableWidgetItem(vipname));
         ui->tableWidget->setItem(row,2,new QTableWidgetItem(vippo));
         ui->tableWidget->setItem(row,3,new QTableWidgetItem(vippoint));
     }

}

void staff::on_buttonUpdate_clicked()
{
    //获取输入框中的内容，id不能为空
        QString uid,uname,ulv,utel;
        uid = ui->lineUID->text();
        uname = ui->lineUName->text();
        ulv = ui->lineUlevel->text();
        utel = ui->lineUtel->text();

        if(uid=="")//本地检查输入不能为空
        {
            QMessageBox::information(NULL, "输入错误", "员工不允许为空");
            return;//为空提示返回
        }else
        {
            QString text= uid;
            QSqlQuery query(db);
            query.prepare("SELECT * FROM user WHERE userid = :text;");//查询指定内容
            query.bindValue(":text",text);
            query.exec();
            //获取 列表
            if(query.size()>0)
            {//查询不为空的时候
               //查询id，如果id存在则执行更改操作
                query.clear();
                query.prepare("UPDATE user SET username = :uname , userlv = :ulv,usertel = :utel WHERE userid = :uid;");//查询指定内容
                query.bindValue(":uname",uname);
                query.bindValue(":ulv",ulv);
                query.bindValue(":uid",uid);
                query.bindValue(":utel",utel);
                query.exec();
                //UPDATE `smadata`.`vip` SET `userlvint` = '1' WHERE `userid` = 2
                QMessageBox::information(NULL, "成功", "数据写入成功");

                //提示更新信息成功，刷新单条信息
                //清空tableWidget
                for (int i=ui->tableWidget->rowCount();i>=0;i--) {
                    ui->tableWidget->removeRow(i);
                }
                query.clear();
                query.prepare("SELECT * FROM user WHERE userid = :uid;");
                query.bindValue(":uid",uid);
                query.exec();//获取员工列表
                if(query.size()>0)
                {//查询不为空的时候
                   QString userid,username,userlv,userlvint;
                    while (query.next())
                    {
                       //sql获取环节
                        userid = query.value("userid").toString();
                        username = query.value("username").toString();
                        userlv = query.value("userlv").toString();
                        utel = query.value("usertel").toString();
                        //写入数据
                        int row = ui->tableWidget->rowCount();
                        ui->tableWidget->insertRow(row);//增加一行
                        ui->tableWidget->setItem(row,0,new QTableWidgetItem(userid));
                        ui->tableWidget->setItem(row,1,new QTableWidgetItem(userlv));
                        ui->tableWidget->setItem(row,2,new QTableWidgetItem(username));
                        ui->tableWidget->setItem(row,3,new QTableWidgetItem(utel));
                    }
                }else
                {
                    QMessageBox::information(NULL, "错误", "无法获取数据");
                }
            }else{


                qDebug()<<"尝试写入数据";
                query.clear();
                query.prepare("INSERT INTO vip(userid,username,userlv,usertel)VALUES(:uid,:username,:userlv,:utel);");//查询指定内容
                query.bindValue(":uid",uid);
                query.bindValue(":username",uname);
                query.bindValue(":userlv",ulv);
                query.bindValue(":utel",utel);
                query.exec();
                //INSERT INTO `smadata`.`vip`(`userid`, `username`) VALUES (3, '李铁蛋')
                QMessageBox::information(NULL, "成功", "数据写入成功");
                //提示更新信息成功，刷新单条信息
                //清空tableWidget
                for (int i=ui->tableWidget->rowCount();i>=0;i--) {
                    ui->tableWidget->removeRow(i);
                }
                query.clear();
                query.prepare("SELECT * FROM user WHERE userid = :uid;");
                query.bindValue(":uid",uid);
                query.exec();//获取员工列表
                if(query.size()>0)
                {//查询不为空的时候
                   QString userid,username,userlv,userlvint;
                    while (query.next())
                    {
                       //sql获取环节
                        userid = query.value("userid").toString();
                        username = query.value("username").toString();
                        userlv = query.value("userlv").toString();
                        utel = query.value("usertel").toString();
                        //写入数据
                        int row = ui->tableWidget->rowCount();
                        ui->tableWidget->insertRow(row);//增加一行
                        ui->tableWidget->setItem(row,0,new QTableWidgetItem(userid));
                        ui->tableWidget->setItem(row,1,new QTableWidgetItem(userlv));
                        ui->tableWidget->setItem(row,2,new QTableWidgetItem(username));
                        ui->tableWidget->setItem(row,3,new QTableWidgetItem(utel));
                    }
            //提示创建成功，刷新单条信息

            }
            //查询不为空的时候
            //id不存在，执行创建操作

                            }
        }
}
