#include <QMessageBox>
#include <fstream>
#include <string>
#include <map>
#include <QDebug>
#include "login.h"
#include "ui_login.h"


int login::loginstatus = 0;
login::login(QWidget *parent) :QDialog(parent),ui(new Ui::login)
{
    ui->setupUi(this);
    QString str = "个人文献管理系统";//为了支持MSVC编译不乱码？或者在qmake文件里修改(即.pro)
    setWindowTitle(str);
    connect(ui->adminLoginButton,&QPushButton::clicked,this,&login::adminlogin);
    connect(ui->exitButton,&QPushButton::clicked,this,exit);//应该有比exit()更好的方法
    connect(ui->userLoginButton, &QPushButton::clicked, this, &login::visitorlogin);
}

login::~login()
{
    delete ui;
}

void login::adminlogin()
{
    std::ifstream inFile;
    inFile.open("admin.password");
    if (!inFile.is_open()) {
        QMessageBox::warning(this, tr("警告"),tr("密码读取错误!\n请检查密码文件"),QMessageBox::Yes);
        exit(-1);
    }
    std::string user = "admin";
    std::string password;
    inFile>>password;
    std::map<std::string, std::string> usermap;
    usermap.insert(std::pair<std::string, std::string>(user, password));
    //获得userNameLEd输入框的文本userNameLEd->text()；
    //trimmed()去掉前后空格
    //tr()函数，防止设置中文时乱码
    //qDebug()<<QString::fromStdString(usermap[user]);
    if(ui->usernameLine->text().trimmed() == tr("admin") &&
           ui->passwordLine->text() == tr(usermap[user].c_str()))
    {
        loginstatus = 1;
     accept();//关闭窗体，并设置返回值为Accepted
    }
    else
    {
       QMessageBox::warning(this, tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
       // 清空内容
       ui->usernameLine->clear();
       ui->passwordLine->clear();
       //定位光标
       ui->usernameLine->setFocus();
    }

}

void login::visitorlogin()
{
    loginstatus = -1;
    accept();
}
