#include "filerecive.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
FileRecive::FileRecive(QWidget *parent) :
    QMainWindow(parent)
{
    form_init();
    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;

    tClient = new QTcpSocket(this);
    tPort = 5555;

    connect(tClient, SIGNAL(readyRead()), this, SLOT(readMsg()));
    connect(tClient, SIGNAL(error(QAbstractSocket::SocketError)), this,SLOT(displayErr(QAbstractSocket::SocketError)));
}

void FileRecive::Init(UserData::UserInfo *user)
{
    this->user = user;
    label_receive_avatar->setPixmap(QPixmap(UserData::AvatarPath+user->UserAvatar));
    label_send_avatar->setPixmap(QPixmap(UserData::AvatarPath+UserData::OwnInfo.UserAvatar));
//    ui->transProgressBar->hide();
//    ui->Send_pushButton->setEnabled(false);

}
void FileRecive::readMsg()
{
    QDataStream in(tClient);
    in.setVersion(QDataStream::Qt_5_3);

    float useTime = time.elapsed();
    qDebug()<<"1";
    if (bytesReceived <= sizeof(qint64)*2) {
        qDebug()<<"2";
        if ((tClient->bytesAvailable() >= sizeof(qint64)*2) && (fileNameSize == 0))
        {
            in>>totalBytes>>fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        qDebug()<<"3";
        if((tClient->bytesAvailable() >= fileNameSize) && (fileNameSize != 0)){
            in>>fileName;
            bytesReceived +=fileNameSize;

            if(!localFile->open(QFile::WriteOnly)){
                QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件 %1:\n%2.").arg(fileName).arg(localFile->errorString()));
                return;
            }
        } else {
            return;
        }
    }
    qDebug()<<"4";
    if (bytesReceived < totalBytes) {
        bytesReceived += tClient->bytesAvailable();
        inBlock = tClient->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    qDebug()<<"5";
   progressBar->setMaximum(totalBytes);
    progressBar->setValue(bytesReceived);

    double speed = bytesReceived / useTime;
    label_status->setText(tr("已接收 %1MB (%2MB/s) \n共%3MB 已用时：%4秒\n估计剩余时间：%5秒")
                                      .arg(bytesReceived / (1024*1024))
                                      .arg(speed*1000/(1024*1024),0,'f',2)
                                      .arg(totalBytes / (1024 * 1024))
                                      .arg(useTime/1000,0,'f',0)
                                      .arg(totalBytes/speed/1000 - useTime/1000,0,'f',0));

    qDebug()<<"6";
    if(bytesReceived == totalBytes)
    {
        localFile->close();
        tClient->close();
        label_status->setText(tr("接收文件 %1 完毕").arg(fileName));
        cancelBtn->setText("完成");
    }
}
void FileRecive::setFileName(QString name)
{
    localFile = new QFile(name);
}

void FileRecive::newConn()
{
    blockSize = 0;
    tClient->abort();
    tClient->connectToHost("127.0.0.1", tPort);
    time.start();
}


void FileRecive::displayErr(QAbstractSocket::SocketError sockErr)
{
    switch(sockErr)
    {
    case QAbstractSocket::RemoteHostClosedError : break;
    default : qDebug() << tClient->errorString();
    }
}

FileRecive::~FileRecive()
{

}



void FileRecive::on_pushButton_clicked()
{
    tClient->abort();
    if (localFile->isOpen())
        localFile->close();
    close();
}
void FileRecive::on_Refuse_pushButton_clicked()
{
    if(cancelBtn->text() == "完成")
    {
        tClient->abort();
        if (localFile->isOpen())
            localFile->close();
        close();
    }
    else{
        tClient->abort();
        if (localFile->isOpen())
            localFile->close();
    }

}



void FileRecive::form_init()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    centerWindow = new QWidget();
    centerWindow->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    centerWindow->setObjectName(tr("centerWindow"));

    cancelBtn = new QPushButton();//取消按钮
    closeBtn = new QPushButton();//关闭按钮

    label_receive_avatar = new QLabel();//接收者头像
    label_send_avatar = new QLabel();//发送者头像
    label_status = new QLabel();
    progressBar = new QProgressBar();

    main_layout = new QVBoxLayout();
    layout_title = new QHBoxLayout();
    layout_title->addStretch();
    layout_title->addWidget(closeBtn);
    layout_status = new QVBoxLayout();
    layout_status->addWidget(label_status);
    layout_status->addWidget(progressBar);
    layout_content = new QHBoxLayout();
    layout_content->addWidget(label_receive_avatar);
    layout_content->addLayout(layout_status);
    layout_content->addWidget(label_send_avatar);
    layout_cancel = new QHBoxLayout();
    layout_cancel->addWidget(cancelBtn);
    main_layout->addLayout(layout_title);
    main_layout->addLayout(layout_content);
    main_layout->addLayout(layout_cancel);
    centerWindow->setLayout(main_layout);

}
void FileRecive::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//创建一个QPainter对象
    painter.drawPixmap(0,0,QPixmap(":/images/images/LoginBack1.png"));//绘制图片到窗口
}

void FileRecive::mousePressEvent(QMouseEvent *event)

{

    if(event->button()==Qt::LeftButton)

    {

        dragPosition=event->globalPos()-frameGeometry().topLeft();

        event->accept();

    }

    if(event->button()==Qt::RightButton)
    {
    }
}

void FileRecive::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口

        event->accept();
    }
}


