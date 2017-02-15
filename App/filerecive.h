#ifndef FILERECIVE_H
#define FILERECIVE_H

#include <QWidget>
#include <QMainWindow>
#include <QTcpSocket>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QSpacerItem>
#include <QLabel>
#include <QFile>
#include <QTime>
#include <QHostAddress>
#include "login/userdata.h"


class FileRecive : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileRecive(QWidget *parent = 0);
    ~FileRecive();
    void newConn();
    void setFileName(QString name);
    void Init(UserData::UserInfo *user);
private slots:

    void on_Refuse_pushButton_clicked();

    void readMsg();
    void displayErr(QAbstractSocket::SocketError);
    void on_pushButton_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
    void form_init();
    void paintEvent(QPaintEvent *);

private:

    QWidget *centerWindow;

    QPushButton *cancelBtn;//取消按钮
    QPushButton *closeBtn;//关闭按钮

    QLabel *label_receive_avatar;//接收者头像
    QLabel *label_send_avatar;//发送者头像
    QLabel *label_status;
    QProgressBar *progressBar;

    QVBoxLayout *main_layout;
    QHBoxLayout *layout_title;
    QVBoxLayout *layout_status;
    QHBoxLayout *layout_content;
    QHBoxLayout *layout_cancel;

    QTcpSocket *tClient;
    quint16 blockSize;
    QHostAddress hostAddr;
    qint16 tPort;

    qint64 totalBytes;
    qint64 bytesReceived;
    qint64 fileNameSize;
    QString fileName;
    QFile *localFile;
    QByteArray inBlock;
    QTime time;
    QPoint dragPosition;

    UserData::UserInfo *user;
};

#endif // FILERECIVE_H
