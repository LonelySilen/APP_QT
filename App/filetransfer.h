#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QTcpSocket>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QSpacerItem>
#include <QPainter>
#include <QMouseEvent>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QTime>
#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>
#include "login/userdata.h"


class FileTransfer : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileTransfer(QWidget *parent = 0);
    void Init(UserData::UserInfo *user);

    void refused();
    void initServer();


    ~FileTransfer();

private slots:
    void on_Open_pushButton_clicked();
    void on_Send_pushButton_clicked();
    void on_FileName_lineEdit_textChanged(const QString &arg1);
    void on_pushButton_clicked();
    void SendFile();
    void UpdateProgress(qint64 numBytes);

protected:
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
    void form_init();
    void paintEvent(QPaintEvent *);
    void sendFileName(QString fileName);
signals:

private:

    QWidget *centerWindow;

    QPushButton *closeBtn;//关闭按钮
    QPushButton *openBtn;//打开按钮
    QPushButton *sendBtn;//发送按钮
    QLineEdit *fileAddress;//

    QLabel *label_receive_avatar;//接收者头像
    QLabel *label_send_avatar;//发送者头像
    QLabel *label_status;
    QProgressBar *progressBar;

    QVBoxLayout *main_layout;
    QHBoxLayout *layout_title;
    QVBoxLayout *layout_status;
    QHBoxLayout *layout_content;
    QHBoxLayout *layout_cancel;


    qint16 tPort;
    QTcpServer *tServer;
    QString fileName;
    QString theFileName;
    QFile *localFile;
    QTcpSocket *clientConnection;
    QTime time;

    qint64 totalBytes;
    qint64 bytesWritten;
    qint64 bytesTobeWrite;
    qint64 payloadSize;

    QByteArray outBlock;
    QPoint dragPosition;

    UserData::UserInfo *user;


};

#endif // FILETRANSFER_H
