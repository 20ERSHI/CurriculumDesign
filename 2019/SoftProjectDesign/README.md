# 收银台系统-软件工程课程设计



## 1.需求分析

* 具备添加购买商品和删除购买商品的功能，生成订单号

* 在确认结账之后，可以通过会员卡计算折扣后价格，并且打印小票（在窗口指定位置打印模拟小票打印环节

* 会员卡，可根据会员卡等级进行打折和积分，并且可以对会员的添加与删除

* 仓储管理，通过图形界面实现仓储管理

* 员工管理，通过员工数据库管理员工信息

* 通过QT5实现可视化图形界面，并通过mysql数据库实现数据的存储

  

## 2.总体设计

程序总共分成三个主要系统

### 1. 收银台系统，主要实现并模拟超市当中收银台所需要执行的工作
### 2.会员系统，主要实现会员信息的增加、修改与删除，并与收银台系统处理会员折扣
### 3.仓储系统，实现商品数量的及时更新，方便及时进货和出货
### 4.员工系统，不同的员工有不同的权限，以对应各个模块的执行权和操作权

## 3.详细设计
### 3.1 收银台系统
  收银员在登录收银系统之后，通过键入商品编号和商品数量，软件会自动从数据库中获取商品名和商品单价。并通过信息处理获取此项商品的购买总额。最后统计所有商品的价格和计算会员折扣的价格

![image-20191205021745665](README/image-20191205021745665.png)

### 3.2 会员系统

会员系统主要是记录会员ID、名字、消费总额度、还有会员的折扣
会员系统的ID自动累加，只需要键入会员的名字即可。会员默认的折扣为9折（0.9），最低消费额度为200可以加入会员。

![image-20191205021834375](README/image-20191205021834375.png)

### 3.3 仓储管理

商品库存系统记录了商品的编号（product_id）还有商品的品名、单价、库存数量。

收银系统可以通过对数据库的查询，获取商品信息以进行操作。

![image-20191205021850687](README/image-20191205021850687.png)

###  3.4员工登陆管理

在操作时可以登录，从数据库中获取员工信息，以实现登陆账号的效果

![image-20191205023533965](README/image-20191205023533965.png)

## 4.数据库设计

  product商品表

![image-20191205022939245](README/image-20191205022939245.png)

![image-20191205023108332](README/image-20191205023108332.png)



user -员工信息表

![image-20191205023008405](README/image-20191205023008405.png)

![image-20191205023129670](README/image-20191205023129670.png)

vip-会员信息表

![image-20191205023029734](README/image-20191205023029734.png)

![image-20191205023141901](README/image-20191205023141901.png)



water-交易流水表

![image-20191205023051757](README/image-20191205023051757.png)

![image-20191205023157116](README/image-20191205023157116.png)



## 5.实现与测试

5.1 测试

5.1.1 模拟收银

![image-20191205023819910](README/image-20191205023819910.png)

输入商品编号，模拟扫码枪扫码，录入数据。实现了条形码相同。数量叠加并计算单样产品总价

![image-20191205024011751](README/image-20191205024011751.png)

点击结账，会要求输入会员编号，进行积分和折扣。

![image-20191205024245038](README/image-20191205024245038.png)

成功结算之后会模拟打印小票，并进行折扣

![image-20191205024320462](README/image-20191205024320462.png)

在不输入会员卡号的时候，会提示放弃创建会员



5.1.2 模拟员工登陆

​	员工登陆测试

![image-20191205023404533](README/image-20191205023404533.png)

![image-20191205023417181](README/image-20191205023417181.png)

![image-20191205023426101](README/image-20191205023426101.png)



5.1.3 修改员工信息

修改员工信息

![image-20191205022729438](README/image-20191205022729438.png)

![image-20191205022741253](README/image-20191205022741253.png)

![image-20191205022746822](README/image-20191205022746822.png)

5.1.4增加员工信息

![image-20191205022510879](README/image-20191205022510879.png)

![image-20191205022519174](README/image-20191205022519174.png)



5.1.5 查询员工信息

![image-20191205022817046](README/image-20191205022817046.png)

![image-20191205022836757](README/image-20191205022836757.png)

5.1.6 会员信息查询

![image-20191205024514349](README/image-20191205024514349.png)

5.1.7 创建会员信息

![image-20191205024547205](README/image-20191205024547205.png)

![image-20191205024559814](README/image-20191205024559814.png)

![image-20191205024607325](README/image-20191205024607325.png)

![image-20191205024611749](README/image-20191205024611749.png)

5.1.8  仓储信息查看

![image-20191205024644756](README/image-20191205024644756.png)

5.1.9 查询仓储信息

![image-20191205024712772](README/image-20191205024712772.png)

5.2 功能实现

​	5.2.1 数据库连接

​		数据库链接使用了QT5自带的QsqlDatabase库，结合QT的图形化界面

```c++
 QSqlDatabase db;
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
    QSqlQuery query(db);
              query.prepare("SELECT * FROM vip WHERE vipid = :text ;");
              query.bindValue(":text",QString::number(text.toInt()));
              query.exec();
```

​	通过类似代码实现数据库链接

5.2.2  widget.cpp -收银台界面代码

```c++
#include "widget.h"
#include "ui_widget.h"
#include<QLCDNumber>
#include <QStandardItemModel>
#include<QTableWidget>
#include <QSqlQuery>//执行sql语句相关
#include <QSqlDatabase>//连接数据库相关
#include <QSqlError>//数据库错误相关
#include <QSqlRecord>//数据库记录相关
#include <QSqlQueryModel>//数据查询模型
#include<QInputDialog>
#include<QString>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->pp=0;
    this->db = initSQL();
    initModel();
}
Widget::~Widget()
{
    delete ui;
}
QSqlDatabase Widget::initSQL(){

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
void Widget::initModel(){
    //初始化数据库
    //初始化lcd
    ui->lcdNumber->setDigitCount(13);
    this->pp = 0.0;
    ui->lcdNumber->display(this->pp);
    //init list
        //设置选择模式
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//按行选择
    //init output text
    ui->textEdit->setReadOnly(true);//设置输出窗口为只读

}
void Widget::on_buttonClear_clicked()//实现清理清单的效果
{
    //清空lcd
    ui->lcdNumber->display(0.00);
    //clear list function
    for (int i=ui->tableWidget->rowCount();i>=0;i--) {
        ui->tableWidget->removeRow(i);
    }
    //clear plot price
    this->pp = 0;
}
void Widget::on_buttonCheckOut_clicked()
{
//结账功能，验证是否有权限，需要实现统计清单的总价，弹出窗口输入会员号，超过200无会员号创建会员帐户，打印小票，生成流水号，上传清单至数据库
    conductpp();
    QString username;
    QString passoff;
    QString point;
    double pps = this->pp;
    bool ok = false;
    QString text = QInputDialog::getText(NULL, "输入会员卡号","输入宁的会员编号嗷",QLineEdit::Normal,"", &ok);
      if ( ok && !text.isEmpty() )
      {
           //数据库查询id
          QSqlQuery query(db);
          query.prepare("SELECT * FROM vip WHERE vipid = :text ;");//设置访问收银台需要权限1
          query.bindValue(":text",QString::number(text.toInt()));
          query.exec();
          if(query.size()>0){//如果数据存在
                query.next();
                username = query.value("vipname").toString();
                passoff = query.value("vippo").toString();
                point = query.value("vippoint").toString();
                qDebug()<<username<<passoff<<point;
            //写入新的购物数据
                //写入vip表
                //UPDATE `smadata`.`vip` SET `vippoint` = '2' WHERE `vipid` = 1
                query.prepare("UPDATE vip SET vippoint = :newvalue WHERE vipid = :vipid");
                query.bindValue(":newvalue",QString::number(pps+=point.toDouble()));
                query.bindValue(":vipid",text);
                query.exec();
                query.clear();
                query.exec("SELECT MAX(wid) FROM water;");
                //生成流水号（数据库获取
                int waterid;
                while (query.next()) {
                    waterid = query.value("MAX(wid)").toInt()+1;
                }
                int pid,pamount;
                //上传数据
                for (int i =ui->tableWidget->rowCount();i>0;i--) {
                     pid = ui->tableWidget->item(i-1,0)->text().toInt();//挨个获取商品列表的id
                     pamount = ui->tableWidget->item(i-1,2)->text().toInt();//数量
                     query.clear();
                     query.prepare("INSERT INTO water(wid,pid,amount,time) VALUES (:waterid,:pid,:pamount,NOW());");
                     //INSERT INTO `smadata`.`water`(`wid`, `pid`, `amount`, `time`) VALUES (1, 2, '1', '2019-12-01 05:16:18')
                     query.bindValue(":waterid",waterid);
                     query.bindValue(":pid",pid);
                     query.bindValue(":pamount",pamount);
                     query.exec();
                     qDebug()<<"写入数据库";
                }
                addLog("**************************\n");
                addLog("\nSN码\t品名\t单价\t数量\t总价");
                for (int i =ui->tableWidget->rowCount();i>0;i--) {
                    addLog("\n"+ui->tableWidget->item(i-1,0)->text().toStdString());
                    addLog("\t"+ui->tableWidget->item(i-1,1)->text().toStdString());
                    addLog("\t"+ui->tableWidget->item(i-1,3)->text().toStdString());
                    addLog("\t"+ui->tableWidget->item(i-1,2)->text().toStdString());
                    addLog("\t"+ui->tableWidget->item(i-1,4)->text().toStdString());
                }
                pps= 0;
                for (int i =ui->tableWidget->rowCount();i>0;i--){
                    pps+= ui->tableWidget->item(i-1,4)->text().toDouble();
                }
                QString str = QString::number(pps);
                addLog("\n\n--------------------------------");
                addLog("\n总价："+str.toStdString());
                double ppss=passoff.toDouble()*pps;
                addLog("       实收："+QString::number(ppss).toStdString());
                addLog("\n会员卡号："+text.toStdString());
                addLog("\n会员折扣："+QString::number((passoff.toDouble()*10)).toStdString()+"折");

                addLog("**************************\n");
          }else{//数据不存在
              if(pps>=200){//如果消费额度大于200
                  QString text = QInputDialog::getText(NULL, "创建会员卡号", "输入宁要创建的会员编号嗷", QLineEdit::Normal,"",&ok);
                  if ( ok && !text.isEmpty() ){
                       //将会员卡号写入数据库
                  }else{
                      QMessageBox::information(NULL, "放弃创建", "将放弃创建会员");
                  }
              }
              QMessageBox::information(NULL, "抱歉", "此次购物额度未满会员入籍要求");
              addLog("**************************\n");
              addLog("\nSN码\t品名\t单价\t数量\t总价");
              for (int i =ui->tableWidget->rowCount();i>0;i--) {
                  addLog("\n"+ui->tableWidget->item(i-1,0)->text().toStdString());
                  addLog("\t"+ui->tableWidget->item(i-1,1)->text().toStdString());
                  addLog("\t"+ui->tableWidget->item(i-1,3)->text().toStdString());
                  addLog("\t"+ui->tableWidget->item(i-1,2)->text().toStdString());
                  addLog("\t"+ui->tableWidget->item(i-1,4)->text().toStdString());
              }
              pps= 0;
              for (int i =ui->tableWidget->rowCount();i>0;i--){
                  pps+= ui->tableWidget->item(i-1,4)->text().toDouble();
              }
              QString str = QString::number(pps);
              addLog("\n\n--------------------------------");
              addLog("\n总价："+str.toStdString());
              double ppss=passoff.toDouble()*pps;
              addLog("       实收："+QString::number(ppss).toStdString());
              addLog("\n会员卡号："+text.toStdString());
              addLog("\n会员折扣："+QString::number((passoff.toDouble()*10)).toStdString()+"折");
              addLog("**************************\n");
          }
      }else {//输入为空
                QMessageBox::information(NULL, "放弃创建", "将放弃创建会员");
                addLog("**************************\n");
                addLog("\nSN码\t品名\t单价\t数量\t总价");
                for (int i =ui->tableWidget->rowCount();i>0;i--) {
                    addLog("\n"+ui->tableWidget->item(i-1,0)->text().toStdString());
                    addLog("\t"+ui->tableWidget->item(i-1,1)->text().toStdString());
                    addLog("\t"+ui->tableWidget->item(i-1,3)->text().toStdString());
                    addLog("\t"+ui->tableWidget->item(i-1,2)->text().toStdString());
                    addLog("\t"+ui->tableWidget->item(i-1,4)->text().toStdString());
                }
                pps= 0;
                for (int i =ui->tableWidget->rowCount();i>0;i--){
                    pps+= ui->tableWidget->item(i-1,4)->text().toDouble();
                }
                QString str = QString::number(pps);
                addLog("\n\n--------------------------------");
                addLog("\n总价："+str.toStdString());
                double ppss=passoff.toDouble()*pps;
                addLog("       实收："+QString::number(ppss).toStdString());
                addLog("\n会员卡号："+text.toStdString());
                addLog("\n会员折扣："+QString::number((passoff.toDouble()*10)).toStdString()+"折");
                addLog("**************************\n");
            }
}
void Widget::on_buttonOpenPM_clicked()
{
    //show product window
    productWindow = new product();
    productWindow->show();
}
void Widget::on_buttonOpenUM_clicked()
{
    //show user window
    userWindow = new user();
    userWindow->show();
}
void Widget::on_buttonOpenSM_clicked()
{
    //show staff window
    staffWindow = new staff();
    staffWindow->show();
}
void Widget::on_buttonDelRow_clicked()
{
    //删除选定的行
    int rows = ui->tableWidget->currentRow();
    if(rows!= -1) ui->tableWidget->removeRow(rows);
    //算总价
}
void Widget::on_buttonAddProduct_2_clicked()
{
    //获取text的数字
    int getsn = ui->lineEdit->text().toInt();//获取在框中输入的商品编号

    //为空则不执行
    if(getsn!=0){
        //数据库查询，假设商品编码长度一致且编码唯一
        QString sql = QString("SELECT * FROM product WHERE sn = '%1';")
                .arg(getsn);
        qDebug()<<sql;
        //执行SQL语句
        QSqlQuery query(this->db);
        query.exec(sql);
        //获取内容
        //query.next();
        QString sn;
        QString name;
        QString amout;
        QString price;
        QString p_price;
        while(query.next()){
            sn = query.value("sn").toString();
            name = query.value("name").toString();
            amout ="1";
            price=query.value("price").toString();
            p_price = QString::number(amout.toDouble()*price.toDouble());
        }
        //从数据库中获取如下数据
        bool state = false;//false 则执行添加操作  ture则获取存在的数量加上添加的数量
        //验证list中是否存在相同sn
        int rows;
        for (int i = ui->tableWidget->rowCount();i>0;i--) {
            if(ui->tableWidget->item(i-1,0)->text().toInt()==getsn){
               state =true;
               rows =i-1;
            }
        }
        if(query.size()<=0){
           QMessageBox::information(NULL, "添加失败", "没有查询到该SN码对应的商品");
            return;
        }
        //添加商品
        if(state == false){
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);//增加一行
            qDebug()<<sn;
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(sn));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(name));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(amout));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(price));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(p_price));
        }else{
            //叠加
            ui->tableWidget->setItem(rows,2,new QTableWidgetItem(\
                                         QString::number(ui->tableWidget->item(rows,2)->text().toInt()+1)));
            double pps = ui->tableWidget->item(rows,2)->text().toDouble() * \
                    ui->tableWidget->item(rows,3)->text().toDouble();
            ui->tableWidget->setItem(rows,4,new QTableWidgetItem(QString::number(pps)));
        }
        //然后计算总价
        addLog("添加商品["+name.toStdString()+"]成功\n");
    conductpp();
    }
}
void Widget::setPp(double pp)//传入总价，显示在led上顺便设置pp
{
    this->pp = pp;
    ui->lcdNumber->display(pp);
}
void Widget::addLog(string str){
ui->textEdit->insertPlainText(QString::fromStdString(str));
}
void Widget::clearLog(){
    ui->textEdit->clear();
}
void Widget::conductpp()//计算清单中所有商品的价格
{
    double pps=0;
    for (int i =ui->tableWidget->rowCount();i>0;i--) {
        pps+= ui->tableWidget->item(i-1,4)->text().toDouble();
    }
    setPp(pps);
}
void Widget::on_buttonDelRow_2_clicked()
{
    if(this->userstate==true){
        QMessageBox::information(NULL, "已登录","用户已登录");
    }else{
        bool ok = false;
        QString text = QInputDialog::getText(NULL, "登陆","输入宁的员工编号嗷",QLineEdit::Normal,"",&ok);
          if ( ok && !text.isEmpty() )
          {
              QSqlQuery query(db);
              query.prepare("SELECT username FROM user WHERE userid = :text ;");//设置访问收银台需要权限1
              query.bindValue(":text",QString::number(text.toInt()));
              query.exec();
              if(query.size()>0){
                    query.next();
                    QString username = query.value("username").toString();
                    QMessageBox::information(NULL, "登录成功", username+",欢迎你");
                    userstate = true;
                    addLog("用户"+username.toStdString()+"已登录\n");
                    ui->labelUserLogin->setText("用户["+username+"]已登录");
              }else{
                  QMessageBox::information(NULL, "登录失败", "权限不足或不存在该用户");
              }
          }else {
                    QMessageBox::information(NULL, "输入错误", "输入错误");
                }
    }
}

```

5.2.2  vip.cpp -会员管理界面代码

```c++
#include "user.h"
#include "ui_user.h"
#include<QtDebug>
#include<QMessageBox>
#include <QSqlQuery>//执行sql语句相关
#include <QSqlDatabase>//连接数据库相关
#include <QSqlError>//数据库错误相关
#include <QSqlRecord>//数据库记录相关
#include <QSqlQueryModel>//数据查询模型
user::user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    this->db = initSQL();
    this->userstate = false;
}

user::~user()
{
    delete ui;
}
QSqlDatabase user::initSQL(){
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
void user::on_buttonLogin_clicked()
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
                    QMessageBox::information(NULL, "登录成功", username+",欢迎你")
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
void user::on_buttonShowAll_clicked()
{
    QString text;
    QSqlQuery query(db);
    for (int i=ui->tableWidget->rowCount();i>=0;i--) {
        ui->tableWidget->removeRow(i);
    }

    query.exec("SELECT * FROM vip;");//获取员工列表
    if(query.size()>0){//查询不为空的时候
       QString vipid,vipname,vippo,vippoint;
        while (query.next()) {
           //sql获取环节
            vipid = query.value("vipid").toString();
            vipname = query.value("vipname").toString();
            vippo = query.value("vippo").toString();
            vippoint = query.value("vippoint").toString();
            //写入数据
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);//增加一行
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(vipid));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(vipname));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(vippo));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(vippoint));
        }
    }else{
        QMessageBox::information(NULL, "获取失败", "发生未知错误");
    }
}
void user::on_buttonUpdate_clicked()
{
    //获取输入框中的内容，id不能为空
    QString uid,uname,upo,upoint;
    uid = ui->lineVID->text();
    uname = ui->lineVName->text();
    upo = ui->lineVPO->text();
    upoint = ui->lineVPoint->text();

    if(uid=="")//本地检查输入不能为空
    {
        QMessageBox::information(NULL, "输入错误", "vipID不允许为空");
        return;//为空提示返回
    }else
    {
        QString text= uid;
        QSqlQuery query(db);
        query.prepare("SELECT * FROM vip WHERE vipid = :text;");//查询指定内容
        query.bindValue(":text",text);
        query.exec();
        //获取 列表
        if(query.size()>0)
        {//查询不为空的时候
           //查询id，如果id存在则执行更改操作
            query.clear();
            query.prepare("UPDATE vip SET vipname = :uname , vippo = :upo WHERE vipid = :uid;");//查询指定内容
            query.bindValue(":uname",uname);
            query.bindValue(":upo",upo);
            query.bindValue(":uid",uid);
            query.exec();
            //UPDATE `smadata`.`vip` SET `vippoint` = '1' WHERE `vipid` = 2
            QMessageBox::information(NULL, "成功", "数据写入成功");

            //提示更新信息成功，刷新单条信息
            //清空tableWidget
            for (int i=ui->tableWidget->rowCount();i>=0;i--) {
                ui->tableWidget->removeRow(i);
            }
            query.clear();
            query.prepare("SELECT * FROM vip WHERE vipid = :uid;");
            query.bindValue(":uid",uid);
            query.exec();//获取员工列表
            if(query.size()>0)
            {//查询不为空的时候
               QString vipid,vipname,vippo,vippoint;
                while (query.next())
                {
                   //sql获取环节
                    vipid = query.value("vipid").toString();
                    vipname = query.value("vipname").toString();
                    vippo = query.value("vippo").toString();
                    vippoint = query.value("vippoint").toString();
                    //写入数据
                    int row = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(row);//增加一行
                    ui->tableWidget->setItem(row,0,new QTableWidgetItem(vipid));
                    ui->tableWidget->setItem(row,1,new QTableWidgetItem(vipname));
                    ui->tableWidget->setItem(row,2,new QTableWidgetItem(vippo));
                    ui->tableWidget->setItem(row,3,new QTableWidgetItem(vippoint));
                }
            }else
            {
                QMessageBox::information(NULL, "错误", "无法获取数据");
            }
        }else{
            QString vipid,vipname,vippo,vippoint;
            vipid = uid;
            vipname = uname;
            vippo = upo;
            vippoint =upoint;
            qDebug()<<"尝试写入数据";
            query.clear();
            query.prepare("INSERT INTO vip(vipid,vipname,vippo,vippoint)VALUES(:uid,:vipname,:vippo,:vippoint);");//查询指定内容
            query.bindValue(":uid",uid);
            query.bindValue(":vipname",uname);
            query.bindValue(":vippo",upo);
            query.bindValue(":vippoint",upoint);
            query.exec();
            //INSERT INTO `smadata`.`vip`(`vipid`, `vipname`) VALUES (3, '李铁蛋')
            QMessageBox::information(NULL, "成功", "数据写入成功");
            //提示更新信息成功，刷新单条信息
            //清空tableWidget
            for (int i=ui->tableWidget->rowCount();i>=0;i--) {
                ui->tableWidget->removeRow(i);
            }
            query.clear();
            query.prepare("SELECT * FROM vip WHERE vipid = :uid;");
            query.bindValue(":uid",uid);
            query.exec();//获取员工列表
            if(query.size()>0)
            {//查询不为空的时候
               QString vipid,vipname,vippo,vippoint;
                while (query.next())
                {
                   //sql获取环节
                    vipid = query.value("vipid").toString();
                    vipname = query.value("vipname").toString();
                    vippo = query.value("vippo").toString();
                    vippoint = query.value("vippoint").toString();
                    //写入数据
                    int row = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(row);//增加一行
                    ui->tableWidget->setItem(row,0,new QTableWidgetItem(vipid));
                    ui->tableWidget->setItem(row,1,new QTableWidgetItem(vipname));
                    ui->tableWidget->setItem(row,2,new QTableWidgetItem(vippo));
                    ui->tableWidget->setItem(row,3,new QTableWidgetItem(vippoint));
                }
        //提示创建成功，刷新单条信息
        }
        //查询不为空的时候
        //id不存在，执行创建操作
                     }
    }
}
void user::on_buttonSearch_clicked()
{
    //SELECT * FROM vip WHERE vipid = '5' OR vipname = '5' OR vippoint = '5' OR vippo = '5';
    QSqlQuery query(this->db);
    query.prepare("SELECT * FROM vip WHERE vipid = :text OR vipname = :text OR vippoint = :text OR vippo = :text;");
    query.bindValue(":text",ui->lineSearch->text());
    query.exec();
    for (int i=ui->tableWidget->rowCount();i>=0;i--) {
        ui->tableWidget->removeRow(i);
    }
    QString vipid,vipname,vippo,vippoint;
     while (query.next())
     {
        //sql获取环节
         vipid = query.value("vipid").toString();
         vipname = query.value("vipname").toString();
         vippo = query.value("vippo").toString();
         vippoint = query.value("vippoint").toString();
         //写入数据
         int row = ui->tableWidget->rowCount();
         ui->tableWidget->insertRow(row);//增加一行
         ui->tableWidget->setItem(row,0,new QTableWidgetItem(vipid));
         ui->tableWidget->setItem(row,1,new QTableWidgetItem(vipname));
         ui->tableWidget->setItem(row,2,new QTableWidgetItem(vippo));
         ui->tableWidget->setItem(row,3,new QTableWidgetItem(vippoint));
     }
}
```

5.2.3  staff.cpp -员工管理界面代码

```c++
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
```

5.2.3  product.cpp -员工管理界面代码

```c++
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
```

5.3.1 其他代码

其他代码包括，图形界面设计、qmake编译文件、用于构造测试数据的mysql数据查询文件、打包的可执行文件、还有开发过程的git日志、原工程文件，一并打包在附件中。

## 6.总结

通过此次的软件工程课程设计的完成，对于如何高效的使用软件工程进行高效的软件设计和开发有了极大的了解。