#ifndef LOGINING_H
#define LOGINING_H

#include <QWidget>
#include <QTimer>
#include <QTcpSocket>
#include <QPainter>
#include <QMouseEvent>
#include <QProgressBar>
#include "userdata.h"
#include "myhelper.h"
#include "login.h"

class Logining : public QMainWindow
{
    Q_OBJECT

public:
    explicit Logining(QWidget *parent = 0);
    ~Logining();
    void paintEvent(QPaintEvent *);
    QTcpSocket *tcpClient;
protected:
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
    void progressBar_init();
    void form_init();
    void socket_init();
private slots:
    void on_Close_pushButton_clicked();
    void ProgressValue();
    void on_login_button_clicked();
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);
private:

    QWidget *centerWindow;

    QTimer *timer;
    QPoint dragPosition;
    int Progress_value;

    QVBoxLayout *main_layout;
    QHBoxLayout *layout_avatar;
    QHBoxLayout *layout_progress;
    QHBoxLayout *layout_info;
    QHBoxLayout *layout_login;
    QLabel *label_avatar;//avatar
    QProgressBar *progressBar;//进度条
    QLabel *label_info;//提示信息
    QPushButton *login_button;//登录按钮

    ///自定义窗口样式;
    void setLoginStyle();

};

#endif // LOGINING_H
