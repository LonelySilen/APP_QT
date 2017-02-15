#include "login.h"
#include <QDebug>

Login::Login(QWidget *parent) :
    QMainWindow(parent)
{
    init();

    systemTrayIcon= new QSystemTrayIcon();
    systemTrayIcon->setIcon(QIcon(":/login/res/images/logo.png"));
    systemTrayIcon->setVisible(true);
    systemTrayIcon->setToolTip(tr("我是托盘图标"));

    MyHelper::FormInCenter(this);
    MyHelper::FormNotResize(this);
    Status_init();

    UserData::LoginImagesPath = "./images/LoginBack.png";
}
void Login::init()
{

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(430,280);//设置窗体大小

    centerWindow = new QWidget();
    centerWindow->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    centerWindow->setObjectName(tr("centerWindow"));

    this->setCentralWidget(centerWindow);


/*************标题栏部分*******************************************************************************************************/

    minBtn = new QPushButton();
    minBtn->setFixedSize(20,20);
    minBtn->setObjectName(tr("minBtn"));
    minBtn->setToolTip("最小化");
    connect(minBtn, SIGNAL(clicked()), this, SLOT(on_Min_pushButton_clicked()));

    closeBtn = new QPushButton();
    closeBtn->setFixedSize(20,20);
    closeBtn->setObjectName(tr("closeBtn"));
    closeBtn->setToolTip("关闭");
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

    title_layout = new QHBoxLayout();
    title_layout->setSpacing(0);
    title_layout->addStretch();
    title_layout->addWidget(minBtn, 0, Qt::AlignTop);
    title_layout->addWidget(closeBtn, 0, Qt::AlignTop);

/*************logo部分*******************************************************************************************************/

    label_logo = new QLabel();
    label_logo->setObjectName(tr("label_logo"));
    label_logo->setFixedSize(240,32);

    logo_layout = new QHBoxLayout();
    logo_layout->setSpacing(0);
    logo_layout->addWidget(label_logo,0,Qt::AlignCenter);

/*************form部分*******************************************************************************************************/


    label_name = new QLabel(tr("账号："));
    label_name->setFixedSize(57,25);
    label_name->setObjectName(tr("label_name"));

    username = new QComboBox();
    username->setFixedSize(146,25);
    username->setEditable(true);
    username->setObjectName(tr("username"));

    layout_name = new QHBoxLayout();
    layout_name->setSpacing(0);
    layout_name->addWidget(label_name,0,Qt::AlignCenter);
    layout_name->addStretch();
    layout_name->addWidget(username,0,Qt::AlignCenter);


    label_pwd = new QLabel(tr("密码："));
    label_pwd->setFixedSize(57,25);
    label_pwd->setObjectName(tr("label_pwd"));

    password = new QLineEdit();
    password->setFixedSize(146,25);
    password->setObjectName(tr("password"));

    layout_pwd = new QHBoxLayout();
    layout_pwd->setSpacing(0);
    layout_pwd->addWidget(label_pwd,0,Qt::AlignCenter);
    layout_pwd->addStretch();
    layout_pwd->addWidget(password,0,Qt::AlignCenter);


    remeberPwd = new QCheckBox();
    remeberPwd->setFixedSize(90,22);
    remeberPwd->setObjectName(tr("remeberPwd"));
    remeberPwd->setText("记住密码");

    autoLogin = new QCheckBox();
    autoLogin->setFixedSize(90,22);
    autoLogin->setObjectName(tr("autoLogin"));
    autoLogin->setText("自动登录");

    layout_check = new QHBoxLayout();
    layout_check->setSpacing(0);
    layout_check->addWidget(remeberPwd,0,Qt::AlignCenter);
    layout_check->addWidget(autoLogin,0,Qt::AlignCenter);

    form_vlayout = new QVBoxLayout();
    form_vlayout->setSpacing(0);
    form_vlayout->addLayout(layout_name);
    form_vlayout->addLayout(layout_pwd);
    form_vlayout->addLayout(layout_check);

    label_avatar = new QLabel();
    label_avatar->setObjectName("label_avatar");
    label_avatar->setFixedSize(100,100);
    label_avatar->setAlignment(Qt::AlignCenter);

    statusBtn = new QMenuButton(label_avatar);
    statusBtn->setGeometry(70,70,25,25);
    statusBtn->setObjectName(tr("statusBtn"));
    statusBtn->setToolTip("状态");
    statusBtn->setIcon(QIcon(":/login/res/images/status-online-1.svg"));
    //connect(statusBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));


    form_hlayout = new QHBoxLayout();
    form_hlayout->setSpacing(0);
    form_hlayout->addWidget(label_avatar);
    form_hlayout->addSpacing(20);
    form_hlayout->addLayout(form_vlayout);
    form_hlayout->addStretch();


    login_layout = new QHBoxLayout();
    loginBtn = new QPushButton();
    loginBtn->setFixedSize(200,40);
    loginBtn->setObjectName(tr("loginBtn"));
    loginBtn->setText(tr("登录"));
    loginBtn->setToolTip("登录");
    login_layout->addWidget(loginBtn);
    connect(loginBtn, SIGNAL(clicked()), this, SLOT(on_login_button_clicked()));

    main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addLayout(logo_layout);
    main_layout->addStretch();
    main_layout->addLayout(form_hlayout);
    main_layout->addStretch();
    main_layout->addLayout(login_layout);
    main_layout->addStretch();

    centerWindow->setLayout(main_layout);

    setLoginStyle();

/*************状态栏和登录记录部分*******************************************************************************************************/

    Status =QString("在线/隐身/忙碌/离开/求扰/勿扰/离线").split("/");
    //label_register->installEventFilter(this);//注册事件
    userFile.setFileName("/userInfo/user.cookies");

    if(!userFile.open(QIODevice::ReadWrite))
    {qWarning("Can't open userFile.");
        userFile.close();
        return;
    }
//    QTextStream in(&userFile);
//    QString line;
//    while (!in.atEnd())
//    {
//        line=in.readLine();
//        if(line == "")
//        {
//            continue;
//        }
//        QStringList user = line.split("|");

//    }
//    if()
//    {
//    }
}

void Login::Status_init()
{
    QMenu * menu = statusBtn->getmenu();
    QActionGroup *actionGroup = new QActionGroup(this);
    menu->setStyleSheet("QMenu {color: white;background-color:#E78261; border: 1px solid black;width:70px;}"
                        "QMenu::item {background-color: transparent; }"
                        "QMenu::item:selected { background-color: #FF781F;}");
    action[0] = new QAction(QIcon(":/login/res/images/imonline.png"), tr("在线"), this);
    action[1] = new QAction(QIcon(":/login/res/images/imhidden.png"), tr("隐身"), this);
    action[2] = new QAction(QIcon(":/login/res/images/imbusy.png"), tr("忙碌"), this);
    action[3] = new QAction(QIcon(":/login/res/images/imaway.png"), tr("离开"), this);
    action[4] = new QAction(QIcon(":/login/res/images/imcallme.png"), tr("求扰"), this);
    action[5] = new QAction(QIcon(":/login/res/images/imsilent.png"), tr("勿扰"), this);

    ImagesIcon[0] = ":/login/res/images/status-online-1.svg";
    ImagesIcon[1] = ":/login/res/images/status-hidden-1.svg";
    ImagesIcon[2] = ":/login/res/images/status-busy-1.svg";
    ImagesIcon[3] = ":/login/res/images/status-away-1.svg";
    ImagesIcon[4] = ":/login/res/images/status-callme-1.svg";
    ImagesIcon[5] = ":/login/res/images/status-silent-1.svg";
    for(int i =0;i<6;i++)
    {
        menu->addAction(actionGroup->addAction(action[i]));
        action[i]->setCheckable(true);
        connect(action[i], SIGNAL(triggered()), this, SLOT(Status_Changed()));
    }
    action[0]->setChecked(true);
}

void Login::on_login_button_clicked()
{

    UserData::Current_User.UserID = Login::username->currentText();
    QByteArray pwd;
    pwd = QCryptographicHash::hash (Login::password->text().toLatin1(), QCryptographicHash::Md5 );
    UserData::Current_User.Password =pwd.toHex();

    for(int i=0;i<6;i++)
    {
        if(action[i]->isChecked())
        {
            UserData::Current_User.Client_Status = tr("%1").arg(i+1);
        }

    }
    qDebug()<<UserData::Current_User.Client_Status;

    if(Login::autoLogin->isChecked())
    {
        UserData::Current_User.AutoLogin = true;
        UserData::Current_User.RememberPwd = true;
    }
    else {
        UserData::Current_User.AutoLogin = false;
        if(Login::remeberPwd->isChecked())
        {
            UserData::Current_User.RememberPwd = true;
        }
        else {
            UserData::Current_User.RememberPwd = false;
        }
    }

    Logining *lw = new Logining();
    QRect winRect = this->geometry();//获得当前窗口位置
    lw->move(winRect.left(),winRect.top());
    lw->show();
    this->close();
}

void Login::Status_Changed()
{
    for(int i =0;i<6;i++)
    {
        if(action[i]->isChecked())
        {
            statusBtn->setIcon(QIcon(ImagesIcon[i]));
            UserData::Current_User.Client_Status = tr("%1").arg(i+1);
            break;
        }
    }
}

void Login::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//创建一个QPainter对象
    painter.drawPixmap(50,0,QPixmap(UserData::LoginImagesPath));//绘制图片到窗口
}

Login::~Login()
{

}

void Login::mousePressEvent(QMouseEvent *event)

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

void Login::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) //当满足鼠标左键被点击时。
    {
        this->move(event->globalPos() - dragPosition);//移动窗口
        event->accept();
    }
}

bool Login::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == Login::label_register) {
        if (event->type() == QEvent::MouseButtonRelease) { //随便判断什么事件都可以了

//            Register *r = new Register();
//            this->close();
//            r->show();

            return true;
        } else {
            return false;
        }
    } else {
        return Login::eventFilter(obj, event);
    }
}

void Login::on_pushButton_clicked()
{
    exit(0);
}

void Login::on_Min_pushButton_clicked()
{
    this->hide();
    //this->isMinimized();
    //    event->ignore();
    if (this->systemTrayIcon->isVisible()) {
        hide();
    }
}

void Login::on_AutoLogin_checkBox_clicked()
{
    if(autoLogin->isChecked())
    {
        remeberPwd->setChecked(true);
    }
}

void Login::on_RemeberPwd_checkBox_clicked()
{
    if(autoLogin->isChecked())
    {
        remeberPwd->setChecked(true);
    }
}

void Login::on_username_editTextChanged(const QString &arg1)
{
    QString path =UserData::AvatarPath + arg1+".png";
    QFile avatar(path);
    if(!avatar.exists())
    {
        return;
    }
    label_avatar->setPixmap(QPixmap(path));

}

void Login::setLoginStyle()
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
