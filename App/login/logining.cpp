#include "logining.h"
#include "mainwindow.h"
#include "list/friendslist.h"
#include <QDebug>

Logining::Logining(QWidget *parent)  :
    QMainWindow(parent)
{

    form_init();
    socket_init();

}
void Logining::socket_init()
{
    login_button->setText("取消");
    tcpClient=new QTcpSocket(this);
    tcpClient->abort();//取消原有连接
    tcpClient->connectToHost("127.0.0.1",12345);
    if (tcpClient->waitForConnected(1000))
    {
        label_info->setText("正在登录...");
        tcpClient->write(("#Login#"+UserData::Current_User.UserID+"#"+UserData::Current_User.Password
                          +"#"+UserData::Current_User.Client_Status).toLocal8Bit());

    }
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(ReadData()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));
}
void Logining::on_login_button_clicked()
{
    if(login_button->text() == "取消")
    {
        tcpClient->disconnectFromHost();
        tcpClient->waitForDisconnected(1000);
        if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))
        {
            login_button->setText("登录");

        }
        tcpClient->abort();
//        this->close();
//        Login *lw =new Login();
//        QRect winRect = this->geometry();//获得当前窗口位置
//        lw->move(winRect.left(),winRect.top());
//        lw->show();

        this->close();
        FriendsList *lw =new FriendsList();
        QRect winRect = this->geometry();//获得当前窗口位置
        lw->move(winRect.left(),winRect.top());
        lw->show();
    }
    else {

        tcpClient->connectToHost("127.0.0.1",12345);
        if (tcpClient->waitForConnected(1000))
        {
            label_info->setText("正在链接...");
            tcpClient->write(("#Login#"+UserData::Current_User.UserID+"#"+UserData::Current_User.Password
                              +"#"+UserData::Current_User.Client_Status).toLocal8Bit());
        }

    }
}

void Logining::ReadData()
{

    QByteArray buffer=tcpClient->readAll();
    QString s=QVariant(buffer).toString();
    if(buffer == "false")
    {
        label_info->setText("密码或帐号错误!");
    }
    else
    {
        label_info->setText("正在登录...");

        QStringList Info = s.split("&");
        QStringList OwnInfoString = Info[1].split("#");
        UserData::OwnInfo.SetValue(OwnInfoString);
        QStringList GroupsInfoString = Info[2].split("|");

        for(int i =0;i<GroupsInfoString.count()-1;i++)
        {
            QStringList FriendsInfoString = GroupsInfoString[i].split("@");
            UserData::FriendInfo fi;
            fi.GroupName = FriendsInfoString[0];
            UserData::UserInfo user;
            user.SetValue(FriendsInfoString[1].split("#"));
            bool is =false;

            for(QVector<UserData::FriendInfo>::iterator iter = UserData::Current_FriendInfo.begin(); iter!=UserData::Current_FriendInfo.end();++iter)
            {
                if(fi.GroupName == iter->GroupName)
                {
                    iter->Num +=1;
                    iter->UserInfo_List.append(user);
                    is =true;
                    break;
                }
            }
            if(!is)
            {
                fi.UserInfo_List.append(user);
                fi.Num =1;
                UserData::Current_FriendInfo.append(fi);
            }
        }

        MainWindow *w = new MainWindow();
        w->show();
        this->close();
    }

}

void Logining::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();
    login_button->setText("登录");
    label_info->setText("连接服务器失败");
}

void Logining::form_init()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(430,280);//设置窗体大小

    centerWindow = new QWidget();
    centerWindow->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    centerWindow->setObjectName(tr("centerWindow"));

    this->setCentralWidget(centerWindow);


    layout_avatar = new QHBoxLayout();
    label_avatar = new QLabel();
    label_avatar->setObjectName(tr("label_avatar"));
    label_avatar->setFixedSize(100,100);
    layout_avatar->addWidget(label_avatar);

    layout_progress = new QHBoxLayout();
    layout_progress->setAlignment(Qt::AlignCenter);
    progressBar = new QProgressBar();
    progressBar->setObjectName(tr("progressBar"));
    layout_progress->addWidget(progressBar);

    layout_info = new QHBoxLayout();
    layout_info->setAlignment(Qt::AlignCenter);
    label_info = new QLabel(tr("正在登录..."));
    label_info->setObjectName(tr("label_info"));
    layout_info->addWidget(label_info);

    layout_login = new QHBoxLayout();
    login_button = new QPushButton(tr("取消"));
    login_button->setObjectName(tr("login_button"));
    login_button->setFixedSize(200,40);
    layout_login->addWidget(login_button);
    connect(login_button, SIGNAL(clicked()), this, SLOT(on_login_button_clicked()));


    main_layout = new QVBoxLayout();
    main_layout->setSpacing(0);
    main_layout->addStretch();
    main_layout->addLayout(layout_avatar);
    main_layout->addSpacing(20);
    main_layout->addLayout(layout_progress);
    main_layout->addSpacing(8);
    main_layout->addLayout(layout_info);
    main_layout->addStretch();
    main_layout->addLayout(layout_login);
    main_layout->addStretch();

    centerWindow->setLayout(main_layout);

    MyHelper::FormInCenter(this);
    progressBar_init();
    timer = new QTimer();
    timer->setInterval(30);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(ProgressValue()));

    setLoginStyle();
}

void Logining::ProgressValue()
{
//    Progress_value += 1;
    ++Progress_value %=100;
    progressBar->setValue(Progress_value);
}
void Logining::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//创建一个QPainter对象
    painter.drawPixmap(50,0,QPixmap(UserData::LoginImagesPath));//绘制图片到窗口
}
Logining::~Logining()
{

}

void Logining::progressBar_init()
{
    Progress_value = 0;
    progressBar->setTextVisible(false);
    progressBar->setMaximum(100);
    progressBar->setMinimum(0);
    progressBar->setValue(Progress_value);

}
void Logining::on_Close_pushButton_clicked()
{
    exit(0);
}

void Logining::mousePressEvent(QMouseEvent *event)
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

void Logining::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口
        event->accept();
    }
}

void Logining::setLoginStyle()
{
    QFile styleSheet(":/login/res/qss/style_login.qss");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return;
    }
    qApp->setStyleSheet(styleSheet.readAll());
    styleSheet.close();
}
