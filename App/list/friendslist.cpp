#include "friendslist.h"

FriendsList::FriendsList(QWidget *parent) :
    QMainWindow(parent)
{


    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    MyHelper::FormInCenter(this);
    MyHelper::FormNotResize(this);
    Init();


}

void FriendsList::Init()
{

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    //setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(300,650);//设置窗体大小

    centerWindow = new QWidget();
    centerWindow->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    centerWindow->setObjectName(tr("centerWindow"));

    this->setCentralWidget(centerWindow);

    minBtn = new QPushButton();
    minBtn->setObjectName(tr("minBtn"));
    minBtn->setFixedSize(20,20);
    closeBtn = new QPushButton();
    closeBtn->setObjectName(tr("closeBtn"));
    closeBtn->setFixedSize(20,20);

    label_avatar = new QLabel();
    label_avatar->setObjectName(tr("label_avatar"));
    label_avatar->setFixedSize(100,100);
    label_avatar->setPixmap(QPixmap(tr(":/login/res/images/avatar.png")));

    label_name = new QLabel();//用户名
    label_name->setObjectName(tr("label_name"));
    signature = new QLineEdit();//个性签名
    signature->setObjectName(tr("signature"));


    layout_title = new QHBoxLayout();
    layout_title->addStretch();
    layout_title->addWidget(minBtn);
    layout_title->addWidget(closeBtn);


    layout_name = new QHBoxLayout();
    layout_name->addWidget(label_name);
    layout_sign = new QHBoxLayout();
    layout_sign->addWidget(signature);
    layout_info = new QVBoxLayout();
    layout_info->addLayout(layout_name);
    layout_info->addLayout(layout_sign);
    layout_card = new QHBoxLayout();
    layout_card->addWidget(label_avatar);
    layout_card->addLayout(layout_info);



    tabWidget = new QTabWidget();//标签页
    tabWidget->setObjectName(tr("tabWidget"));
    tabWidget->setFixedSize(280,391);
    list_friends = new QWidget();//好友列表
    list_friends->setObjectName(tr("list_friends"));
    list_groups = new QWidget();//群组列表
    list_groups->setObjectName(tr("list_groups"));
    list_recent = new QWidget();//最近
    list_recent->setObjectName(tr("list_recent"));

    tabWidget->addTab(list_friends, tr("好友"));
    tabWidget->addTab(list_groups, tr("群组"));
    tabWidget->addTab(list_recent, tr("最近"));

    main_layout = new QVBoxLayout();
    main_layout->addLayout(layout_title);
    main_layout->setSpacing(3);
    main_layout->addLayout(layout_card);
    main_layout->setSpacing(5);
    main_layout->addWidget(tabWidget);
    main_layout->addStretch();

    centerWindow->setLayout(main_layout);


    label_name->setText(UserData::OwnInfo.UserName);//个人信息
    signature->setText(UserData::OwnInfo.UserPS);
    label_avatar->setPixmap(QPixmap(UserData::AvatarPath + UserData::OwnInfo.UserAvatar));

    //单例模式，建立一个聊天窗口
    chatWindow = ChatView::getInstance();
    //初始化UDPSocket和自己绑定自己的IP地址和端口号
    UserData::udpSocket = new QUdpSocket(this);
    UserData::port = UserData::OwnInfo.UserPort.toInt();
    UserData::udpSocket->bind(UserData::port);
    //槽链接，监听数据读入
    connect(UserData::udpSocket,SIGNAL(readyRead()),this,SLOT(AnalyseMessage()));
    FriendsInit();

    //setListStyle();



}


void FriendsList::FriendsInit()
{

    //在好友tab里新建了一个QToolBox实现好友列表
    friends_box = new QToolBox(tabWidget);
    friends_box->setGeometry(10,10,260,250);
    friends_box->setStyleSheet("QToolBox::tab {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);border-radius: 5px;color: darkgray; }QToolBox::tab:selected { /* italicize selected tabs */font: italic; color: white;}");
    friends_box->show();
    int i=0;
    for(QVector<UserData::FriendInfo>::iterator iter = UserData::Current_FriendInfo.begin(); iter!=UserData::Current_FriendInfo.end();++iter)
    {
        //在每一个好友分组内建立QGroupBox，用来存储好友
        QGroupBox *groupBox=new QGroupBox;
        int j=0;
        QVector<UserData::UserInfo>::iterator it = iter->UserInfo_List.begin();
        for(;it != iter->UserInfo_List.end();++j,++it)
        {
            //新建好友项FriendItem，用来表示每一个好友,宽度设为70
            FriendItem *frienditem = new FriendItem(groupBox,0,j*70+2,it);//
            this->FriendItemList.append(frienditem);
            qDebug()<<frienditem->user->UserName<<"11111111111111111111111111111111111111111111";

        }
        //QToolBox添加每一个好友分组，每个Item代表一个分组
        friends_box->insertItem(i++,groupBox,iter->GroupName);//
//        +"["+QString("%1").arg(iter->Num)+"/"+QString("%1").arg(iter->Num)+"]"
    }
    //槽链接,每个分组人数不同，所以BoxChanged()改变QToolBox的高度
    connect(friends_box,SIGNAL(currentChanged(int)),this,SLOT(BoxChanged()));
}
void FriendsList::GroupsInit()
{


    Groups_box = new QGroupBox(list_groups);
    Groups_box->setGeometry(10,10,260,250);
    Groups_box->setStyleSheet("QGroupBox{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);border-radius: 5px;color: darkgray; }");


}
void FriendsList::NearInit()
{

}


/*! ****************************************************************************/
void FriendsList::AnalyseMessage()
{
    //弹出聊天窗口
    QByteArray Buffer;
    UserData::udpSocket->hasPendingDatagrams();
    Buffer.resize(UserData::udpSocket->pendingDatagramSize());
    QHostAddress IP;
    quint16 Port;
    UserData::udpSocket->readDatagram(Buffer.data(), Buffer.size(),&IP,&Port);
    QString msg = QVariant(Buffer).toString();
    qDebug()<<"&&&&&&&&&&&"<<msg;

    if(msg.startsWith("#Update#"))
    {
        Update(msg);
        return;

    }
    else if(msg.startsWith("#FILE#"))
    {
        ReciveFile(msg);
        return;
    }
    else if(msg.startsWith("#IsOnline#"))
    {
        IsOnline(IP,Port);
        return;
    }
    else
    {

        ReciveMsg(msg);
        return;
    }
}

/*! *****************************************************************************/
void FriendsList::Update(QString msg)
{

    qDebug()<<"update"<<msg;
    QSound::play("./Sound/system.wav");
    QStringList msglist = msg.remove(0,8).split("|");
    UserData::UserStatus newUser;
    newUser.SetValue(msglist);
    for(QVector<UserData::FriendInfo>::iterator iter = UserData::Current_FriendInfo.begin(); iter!=UserData::Current_FriendInfo.end();++iter)
    {
        //遍历每一个分组
        QVector<UserData::UserInfo>::iterator it = iter->UserInfo_List.begin();
        for(;it != iter->UserInfo_List.end();it++)
        {
            //遍历每一个好友

            if(newUser.UserID == it->UserID)
            {//找到发送消息的好友是哪个
                it->UserIP = newUser.UserIP;
                it->UserPort = newUser.UserPort;
                it->UserStatus = newUser.UserStatus;

                for(int i =0;i< this->FriendItemList.count();++i)
                {
                    if(this->FriendItemList.at(i)->user->UserID == newUser.UserID)
                    {
                        this->FriendItemList.at(i)->user->UserIP = newUser.UserIP;
                        this->FriendItemList.at(i)->user->UserPort = newUser.UserPort;
                        this->FriendItemList.at(i)->user->UserStatus = newUser.UserStatus;

                        if(it->UserStatus == "1")
                        {
                            this->FriendItemList.at(i)->Status->setStyleSheet("color:red;");
                        }
                        else
                        {
                            this->FriendItemList.at(i)->Status->setStyleSheet("color:gray;");
                        }
                        this->FriendItemList.at(i)->Status->setText(UserData::Status[newUser.UserStatus.toInt()]);

                    }
                }

                return;

            }

        }

    }
}


void FriendsList::ReciveFile(QString msg)
{

//    QSound::play("./Sound/file.wav");
    QStringList msglist = msg.remove(0,6).split("|");
    for(QVector<UserData::FriendInfo>::iterator iter = UserData::Current_FriendInfo.begin(); iter!=UserData::Current_FriendInfo.end();++iter)
    {
        //遍历每一个分组
        QVector<UserData::UserInfo>::iterator it = iter->UserInfo_List.begin();
        for(;it != iter->UserInfo_List.end();it++)
        {
            //遍历每一个好友
            if(msglist[0] == it->UserID)
            {//找到发送消息的好友是哪个

                chatWindow->addChat(it);//没打开的话弹出聊天窗口
                chatWindow->show();
                int btn = QMessageBox::information(this,tr("接受文件"),tr("文件：%1,是否接收？").arg(msglist[2]),QMessageBox::Yes,QMessageBox::No);
                if (btn == QMessageBox::Yes) {
                    qDebug()<<"1111111111111111111111111111111111111111"<<QString("./UserInfo/"+UserData::OwnInfo.UserID+"/"+msglist[2]);
                    QString name = QFileDialog::getSaveFileName(this,tr("保存文件"),"./UserInfo/"+UserData::OwnInfo.UserID+"/"+msglist[2]);
                    qDebug()<<name;
                    if(!name.isEmpty())
                    {
                        FileRecive *clnt = new FileRecive;
                        clnt->setFileName("./UserInfo/"+UserData::OwnInfo.UserID+"/"+msglist[2]);
                        clnt->Init(it);
                        clnt->newConn();
                        clnt->show();
                        return;
                    }
                } else {
                    QByteArray refuse = QString("#Refuse#").toLatin1();
//                    Send_UdpSocket->writeDatagram(refuse,refuse.size(),QHostAddress(user->UserIP),user->UserPort.toInt());
                }
                return;

            }

        }
    }


}


void FriendsList::ReciveMsg(QString msg)
{

    QSound::play("./Sound/msg.wav");
    QStringList msglist = msg.split("|");
//    发来的消息包括发送ID，所以拆分开来
    for(QVector<UserData::FriendInfo>::iterator iter = UserData::Current_FriendInfo.begin(); iter!=UserData::Current_FriendInfo.end();++iter)
    {
        //遍历每一个分组
        QVector<UserData::UserInfo>::iterator it = iter->UserInfo_List.begin();
        for(;it != iter->UserInfo_List.end();it++)
        {
            //遍历每一个好友
            if(msglist[0] == it->UserID)
            {//找到发送消息的好友是哪个
                for(int i = 0;i <chatWindow->Chating_UserId.count();++i)
                {

                    if(chatWindow->Chating_UserId.at(i) == it->UserID)
                    {
                        //如果窗口已经打开
                        chatWindow->addMsg(i,msglist[2]);
                        return;
                    }

                }

                chatWindow->addChat(it);//没打开的话弹出聊天窗口
                chatWindow->show();

                chatWindow->addMsg(chatWindow->Chating_UserId.count() -1,msglist[2]);

                return;

            }

        }


    }


}



void FriendsList::IsOnline(QHostAddress IP,qint16 Port)
{
//    23456
    QByteArray reply = QString("#IsOnline#"+UserData::OwnInfo.UserID).toLatin1();
    UserData::udpSocket->writeDatagram(reply,reply.size(),IP,Port);

}
///
/// UDP接收到信息
///




/*! *****************************************************************************/




void FriendsList::BoxChanged()
{

    int M = friends_box->count();

    int N =0;
    for(QVector<UserData::FriendInfo>::iterator iter = UserData::Current_FriendInfo.begin(); iter!=UserData::Current_FriendInfo.end();++iter)
    {
        if(iter->GroupName == friends_box->itemText(friends_box->currentIndex()))
        {
            N = iter->Num;
        }

    }
    friends_box->setGeometry(10,10,260,30*M + N*85);

}

FriendsList::~FriendsList()
{

}
/*! *****************************************************************************/



/*! *****************************************************************************/
/**
 * @brief FriendsList::paintEvent
 */
void FriendsList::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//创建一个QPainter对象
    painter.drawPixmap(0,0,QPixmap(UserData::FriendsImagesPath));//绘制图片到窗口
}
/**
 * @brief FriendsList::mousePressEvent
 * @param event
 */
void FriendsList::mousePressEvent(QMouseEvent *event)

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

void FriendsList::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口

        event->accept();
    }
}

void FriendsList::on_Close_pushButton_clicked()
{
    exit(0);
}

void FriendsList::setListStyle()
{
    QFile styleSheet(":/list/res/qss/style_list.qss");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file [style_list.qss].");
        return;
    }
    qApp->setStyleSheet(styleSheet.readAll());
    styleSheet.close();
}
