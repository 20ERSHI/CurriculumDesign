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


/*
目前存在的问题
1、商品重复叠加未解决
    遍历list 有无sn相同，有则相加
2、表格清空，使用循环删除，删除列 ---ok
3、数据库数据导入
4、总价计算问题
5、会员卡验证

*/

void Widget::on_buttonCheckOut_clicked()
{
//结账功能，验证是否有权限，需要实现统计清单的总价，弹出窗口输入会员号，超过200无会员号创建会员帐户，打印小票，生成流水号，上传清单至数据库
    conductpp();

    QString username;
    QString passoff;
    QString point;


    double pps = this->pp;
    bool ok = false;
    QString text = QInputDialog::getText(NULL, "输入会员卡号",
                                    "输入宁的会员编号嗷",
                                    QLineEdit::Normal,
                                    "",
                                    &ok);
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

//                QMessageBox::information(NULL, "登录成功", username+",欢迎你");
//                userstate = true;
//                addLog("用户"+username.toStdString()+"已登录\n");
//                ui->labelUserLogin->setText("用户["+username+"]已登录");
            //写入新的购物数据
                //写入vip表
                //UPDATE `smadata`.`vip` SET `vippoint` = '2' WHERE `vipid` = 1
                query.prepare("UPDATE vip SET vippoint = :newvalue WHERE vipid = :vipid");
                query.bindValue(":newvalue",QString::number(pps+=point.toDouble()));
                query.bindValue(":vipid",text);
                query.exec();
                query.clear();

                //生成流水号（数据库获取
                query.exec("SELECT MAX(wid) FROM water;");

                //query.next();
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




                //打印小票
                //**************************
                        //序号  品名   单价   数量   总价
                        //
                        //总价：         实收：
                        //会员卡号：0
                        //会员折扣：useroff*10+"折"
                        //XXX超市欢迎下次光临

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
                  QString text = QInputDialog::getText(NULL, "创建会员卡号",
                                                  "输入宁要创建的会员编号嗷",
                                                  QLineEdit::Normal,
                                                  "",
                                                  &ok);
                  if ( ok && !text.isEmpty() ){
                       //将会员卡号写入数据库
                  }else{
                      QMessageBox::information(NULL, "放弃创建", "将放弃创建会员");
                  }
              }
              QMessageBox::information(NULL, "抱歉", "此次购物额度未满会员入籍要求");
              //打印小票
              //**************************
                      //序号  品名   单价   数量   总价
                      //
                      //总价：         实收：
                      //会员卡号：0
                      //会员折扣：useroff*10+"折"
                      //XXX超市欢迎下次光临

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
                //打印小票
                //**************************
                        //序号  品名   单价   数量   总价
                        //
                        //总价：         实收：
                        //会员卡号：0
                        //会员折扣：useroff*10+"折"
                        //XXX超市欢迎下次光临

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
    //循环所有的
    for (int i =ui->tableWidget->rowCount();i>0;i--) {
        pps+= ui->tableWidget->item(i-1,4)->text().toDouble();
    }
    //函数写完列入所有增减清单的操作中
    setPp(pps);
}

void Widget::on_buttonDelRow_2_clicked()
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
