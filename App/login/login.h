#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>
#include <QWidget>
#include <QCryptographicHash>
#include <QSystemTrayIcon>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QFile>
#include <QLabel>
#include <QRect>
#include <QMainWindow>
#include "userdata.h"
#include "myhelper.h"
#include "logining.h"
#include "qmenubutton.h"

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    //    UserData userdata;
    void paintEvent(QPaintEvent *);
protected:
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);


private slots:

    void on_login_button_clicked();
    void on_pushButton_clicked();
    void on_Min_pushButton_clicked();
    void on_AutoLogin_checkBox_clicked();
    void on_RemeberPwd_checkBox_clicked();
    void Status_Changed();
    void on_username_editTextChanged(const QString &arg1);

private:

    QWidget *centerWindow;

    QPushButton *minBtn;//最小化按钮
    QPushButton *closeBtn;//关闭按钮
    QMenuButton *statusBtn;//状态按钮
    QPushButton *loginBtn;//登录按钮
    QVBoxLayout *main_layout;
    QHBoxLayout *title_layout;//标题栏
    QHBoxLayout *logo_layout;//logo的layout
    QVBoxLayout *form_vlayout;//表单layout
    QHBoxLayout *form_hlayout;//表单layout
    QHBoxLayout *layout_name;//名字layout
    QHBoxLayout *layout_pwd;//密码layout
    QHBoxLayout *layout_check;//checkBox的layout
    QHBoxLayout *login_layout;//登录layout

    QLabel *label_logo;//logo
    QLabel *label_avatar;//头像
    QLabel *label_name;//用户名
    QLabel *label_pwd;//密码
    QLabel *label_register;//注册label

    QComboBox *username;
    QLineEdit *password;
    QCheckBox *remeberPwd;//记住密码
    QCheckBox *autoLogin;//自动登录

    QAction *action[6];
    QString ImagesIcon[6];
    QPoint dragPosition;
    QSystemTrayIcon *systemTrayIcon;
    void Status_init();
    void init();
    QStringList Status;

    QFile userFile;
    ///自定义窗口样式;
    void setLoginStyle();

};

#endif // LOGIN_H
