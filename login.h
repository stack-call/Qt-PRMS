#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
 static int loginstatus;
public:
    explicit login(QWidget *parent = nullptr);
    ~login();


public slots:
    void adminlogin();
    void visitorlogin();

private:
    Ui::login *ui;



friend class PRMS;
};

#endif // LOGIN_H
