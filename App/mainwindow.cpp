#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    initData();
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), m_pixmapBg);
    setAutoFillBackground(true);//背景图片随窗口大小改变
    //painter.drawPixmap(m_pixmapBg.rect(), m_pixmapBg);

    //QPainter用于在位图上绘画
    //QPainter painter(this);
    //填充位图矩形框(用白色填充)
    //painter.fillRect(this->rect(),Qt::white);
    //painter.setBrush(QColor(0,0,0));
    //在位图上画圆角矩形(用黑色填充)
    //painter.drawRoundedRect(this->rect(),10,10);
    //使用setmask过滤即可
    //setMask(m_pixmapBg);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    this->move(e->globalPos() - m_pointStart);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_pointPress = e->globalPos();
    m_pointStart = m_pointPress - this->pos();

}

void MainWindow::setNomalStyle()
{
    QFile styleSheet(":/res/qss/style_main.qss");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return;
    }
    qApp->setStyleSheet(styleSheet.readAll());
    styleSheet.close();
}



void MainWindow::on_menuBtn_clicked()
{
    m_menu->exec(this->mapToGlobal(QPoint(0, 20)));
}

void MainWindow::initData()
{
    //设置窗体标题栏隐藏并设置位于顶层
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //可获取鼠标跟踪效果
    //setMouseTracking(true);
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(850,600);//设置窗体大小
    centerWindow = new QWidget;
    centerWindow->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    centerWindow->setObjectName(tr("centerWindow"));

    this->setCentralWidget(centerWindow);

/*************标题栏部分*******************************************************************************************************/
    label_title = new QLabel(tr("360安全卫士"), centerWindow);
    label_title->setObjectName(tr("label_title"));
    label_title->setFixedSize(81,24);
    label_title->setAlignment(Qt::AlignCenter);

    menuBtn = new QPushButton(centerWindow);
    menuBtn->setObjectName(tr("menuBtn"));
    menuBtn->setFixedSize(24,24);
    connect(menuBtn, SIGNAL(clicked()), this, SLOT(on_menuBtn_clicked()));

    minBtn = new QPushButton(centerWindow);
    minBtn->setObjectName(tr("minBtn"));
    minBtn->setFixedSize(24,24);
    minBtn->setToolTip("最小化");
    connect(minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));

    nomalBtn = new QPushButton(centerWindow);
    nomalBtn->setObjectName(tr("nomalBtn"));
    nomalBtn->setFixedSize(24,24);
    nomalBtn->setToolTip("最大化");
    connect(nomalBtn, SIGNAL(clicked()), this, SLOT(showMaximized()));

    closeBtn = new QPushButton(centerWindow);
    closeBtn->setObjectName(tr("closeBtn"));
    closeBtn->setFixedSize(24,24);
    closeBtn->setToolTip("关闭");
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(close()));

    title_layout = new QHBoxLayout();
    title_layout->setSpacing(0);
    title_layout->addWidget(menuBtn,0,Qt::AlignTop);
    title_layout->addWidget(label_title,0,Qt::AlignTop);
    title_layout->addStretch();
    title_layout->addWidget(minBtn, 0, Qt::AlignTop);
    title_layout->addWidget(nomalBtn, 0, Qt::AlignTop);
    title_layout->addWidget(closeBtn, 0, Qt::AlignTop);

/*************状态栏部分*******************************************************************************************************/
    label_checkUpdate = new QLabel(centerWindow);
    label_checkUpdate->setObjectName(tr("label_checkUpdate"));
    label_checkUpdate->setFixedSize(61,21);

    label_version = new QLabel(QStringLiteral("主程序版本:8.8.0"), centerWindow);
    label_version->setObjectName(tr("label_version"));
    label_version->setFixedSize(121,21);
    label_version->setAlignment(Qt::AlignCenter);

    label_version2 = new QLabel(QStringLiteral("备用木马库:2012-12-16"), centerWindow);
    label_version2->setObjectName(tr("label_version2"));
    label_version2->setFixedSize(131,21);

    status_layout = new QHBoxLayout();
    status_layout->setSpacing(0);
    status_layout->addWidget(label_version, 0, Qt::AlignCenter);
    status_layout->addWidget(label_version2, 0, Qt::AlignCenter);
    status_layout->addStretch();
    status_layout->addWidget(label_checkUpdate, 0, Qt::AlignCenter);


/*************工具栏部分*******************************************************************************************************/

    tool_layout = new QHBoxLayout();
    tool_layout->setObjectName(tr("tool_layout"));
    tool_layout->setSpacing(5);

    pushButton_1 = new QPushButton;
    pushButton_2 = new QPushButton;
    pushButton_3 = new QPushButton;
    pushButton_4 = new QPushButton;
    pushButton_5 = new QPushButton;
    pushButton_6 = new QPushButton;
    pushButton_7 = new QPushButton;
    pushButton_8 = new QPushButton;
    pushButton_9 = new QPushButton;


    pushButton_1->setObjectName(tr("pushButton_1"));
    pushButton_1->setFixedSize(70,78);
    tool_layout->addStretch();
    tool_layout->addWidget(pushButton_1, 0, Qt::AlignCenter);
    connect(pushButton_1, SIGNAL(clicked()), this, SLOT(on_optionButton_clicked()));

    pushButton_2->setObjectName(tr("pushButton_2"));
    pushButton_2->setFixedSize(70,78);
    tool_layout->addWidget(pushButton_2, 0, Qt::AlignCenter);
    connect(pushButton_2, SIGNAL(clicked()), this, SLOT(on_optionButton_clicked()));

    pushButton_3->setObjectName(tr("pushButton_3"));
    pushButton_3->setFixedSize(70,78);
    tool_layout->addWidget(pushButton_3, 0, Qt::AlignCenter);
    connect(pushButton_3, SIGNAL(clicked()), this, SLOT(on_optionButton_clicked()));

    pushButton_4->setObjectName(tr("pushButton_4"));
    pushButton_4->setFixedSize(70,78);
    tool_layout->addWidget(pushButton_4, 0, Qt::AlignCenter);
    connect(pushButton_4, SIGNAL(clicked()), this, SLOT(on_optionButton_clicked()));

    pushButton_5->setObjectName(tr("pushButton_5"));
    pushButton_5->setFixedSize(70,78);
    tool_layout->addWidget(pushButton_5, 0, Qt::AlignCenter);
    connect(pushButton_5, SIGNAL(clicked()), this, SLOT(on_optionButton_clicked()));

    pushButton_6->setObjectName(tr("pushButton_6"));
    pushButton_6->setFixedSize(70,78);
    tool_layout->addWidget(pushButton_6, 0, Qt::AlignCenter);
    connect(pushButton_6, SIGNAL(clicked()), this, SLOT(on_optionButton_clicked()));

    pushButton_7->setObjectName(tr("pushButton_7"));
    pushButton_7->setFixedSize(70,78);
    tool_layout->addWidget(pushButton_7, 0, Qt::AlignCenter);
    connect(pushButton_7, SIGNAL(clicked()), this, SLOT(on_optionButton_clicked()));

    pushButton_8->setObjectName(tr("pushButton_8"));
    pushButton_8->setFixedSize(70,78);
    tool_layout->addWidget(pushButton_8, 0, Qt::AlignCenter);
    connect(pushButton_8, SIGNAL(clicked()), this, SLOT(on_optionButton_clicked()));

    pushButton_9->setObjectName(tr("pushButton_9"));
    pushButton_9->setFixedSize(70,78);
    tool_layout->addWidget(pushButton_9, 0, Qt::AlignCenter);
    connect(pushButton_9, SIGNAL(clicked()), this, SLOT(on_optionButton_clicked()));

    label_logo = new QLabel(centerWindow);
    label_logo->setStyleSheet("background-image: url(:/res/image/360logo.png);");
    label_logo->setFixedSize(126,68);
    tool_layout->addStretch();
    tool_layout->addWidget(label_logo, 0, Qt::AlignCenter);

/*************内容部分*******************************************************************************************************/

    stackedWidget = new QStackedWidget(centerWindow);
    stackedWidget->setMinimumSize(850,467);
    stackedWidget->setObjectName(tr("stackedWidget"));

//    page_1 = new QWidget;
//    page_1->setObjectName(tr("page_1"));
//    QLabel *label_1 = new QLabel(tr("page_1"),page_1);
//    label_1->setObjectName(tr("label_1"));
    plot = new Plotter(this);
    plot->setTitle("坐标轴 实时数据 ");
    theTimer=new QTimer(this);
    theTimer->setInterval(1000);
    connect(theTimer,SIGNAL(timeout()),this,SLOT(UpdateData()));
    theTimer->start();

//    page_2 = new QWidget;
//    page_2->setObjectName(tr("page_2"));
//    QLabel *label_2 = new QLabel(tr("page_2"),page_2);
//    label_2->setObjectName(tr("label_2"));
    table1 = new TableWidget(this);

    page_3 = new QWidget;
    page_3->setObjectName(tr("page_3"));
    QLabel *label_3 = new QLabel(tr("page_3"),page_3);
    label_3->setObjectName(tr("label_3"));

    page_4 = new QWidget;
    page_4->setObjectName(tr("page_4"));
    QLabel *label_4 = new QLabel(tr("page_4"),page_4);
    label_4->setMinimumSize(850,477);
    label_4->setStyleSheet("background-image: url(:/res/image/meinv.png);");
    label_4->setObjectName(tr("label_4"));

    page_5 = new QWidget;
    page_5->setObjectName(tr("page_5"));
    QLabel *label_5 = new QLabel(tr("page_5"),page_5);
    label_5->setObjectName(tr("label_5"));

    page_6 = new QWidget;
    page_6->setObjectName(tr("page_6"));
    QLabel *label_6 = new QLabel(tr("page_6"),page_6);
    label_6->setObjectName(tr("label_6"));

    page_7 = new QWidget;
    page_7->setObjectName(tr("page_7"));
    QLabel *label_7 = new QLabel(tr("page_7"),page_7);
    label_7->setObjectName(tr("label_7"));

    page_8 = new QWidget;
    page_8->setObjectName(tr("page_8"));
    QLabel *label_8 = new QLabel(tr("page_8"),page_8);
    label_8->setObjectName(tr("label_8"));

    page_9 = new QWidget;
    page_9->setObjectName(tr("page_9"));
    QLabel *label_9 = new QLabel(tr("page_9"),page_9);
    label_9->setObjectName(tr("label_9"));

    stackedWidget->addWidget(plot);
    stackedWidget->addWidget(table1);
    stackedWidget->addWidget(page_3);
    stackedWidget->addWidget(page_4);
    stackedWidget->addWidget(page_5);
    stackedWidget->addWidget(page_6);
    stackedWidget->addWidget(page_7);
    stackedWidget->addWidget(page_8);
    stackedWidget->addWidget(page_9);

    content_layout = new QHBoxLayout;
    content_layout->setSpacing(0);
    content_layout->addWidget(stackedWidget, 0, Qt::AlignCenter);

/*************组件封装*******************************************************************************************************/

    main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addLayout(tool_layout);
    QSpacerItem* vSpacer = new QSpacerItem(0, 10, QSizePolicy::Minimum, QSizePolicy::Minimum);
    main_layout->addSpacerItem(vSpacer);
    main_layout->addLayout(content_layout);
    main_layout->addStretch();
    main_layout->addLayout(status_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    centerWindow->setLayout(main_layout);


/*************弹出菜单部分*******************************************************************************************************/
    m_menu = new QMenu();
    m_menu->addAction(QStringLiteral("设置"));
    m_menu->addAction(QStringLiteral("新版特性"));
    m_menu->addAction(QStringLiteral("检查更新"));
    m_menu->addSeparator();
    m_menu->addAction(QStringLiteral("在线帮助"));
    m_menu->addAction(QStringLiteral("论坛求助"));
    m_menu->addAction(QStringLiteral("360网站"));
    m_menu->addAction(QStringLiteral("隐私保护"));
    m_menu->addAction(QStringLiteral("关于我们"));
    m_AactionAboutQt = new QAction(QStringLiteral("&About Qt"), this);
    connect(m_AactionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    m_menu->addAction(m_AactionAboutQt);

/*************背景及功能部分*******************************************************************************************************/
    ///背景加载;
    m_pixmapBg.load(":/res/image/frame.png");

    m_vecBtn.push_back(pushButton_1);
    m_vecBtn.push_back(pushButton_2);
    m_vecBtn.push_back(pushButton_3);
    m_vecBtn.push_back(pushButton_4);
    m_vecBtn.push_back(pushButton_5);
    m_vecBtn.push_back(pushButton_6);
    m_vecBtn.push_back(pushButton_7);
    m_vecBtn.push_back(pushButton_8);
    m_vecBtn.push_back(pushButton_9);

    for (int i = 0; i != m_vecBtn.size(); ++i)
    {
        ///功能选择键只有一个被选中;
        m_vecBtn[i]->setCheckable(true);
        m_vecBtn[i]->setAutoExclusive(true);
    }

    ///状态栏加上链接QLabel;
    label_checkUpdate->setText(
                tr("<a href=http://www.baidu.com>")
                   +QStringLiteral("<font color=white>检查更新</font></a>"));
    label_checkUpdate->setOpenExternalLinks(true);

    setNomalStyle();
}


void MainWindow::on_optionButton_clicked()
{
    setCurrentWidget();
}


void MainWindow::setCurrentWidget()
{
    for (int i = 0; i != m_vecBtn.size(); ++i)
    {
        if ( m_vecBtn[i]->isChecked() )
        {
            stackedWidget->setCurrentIndex(i);
        }
    }
}


void MainWindow::skin_change()
{
    QFile styleSheet(":/res/qss/style_main2.qss");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file2.");
        return;
    }
    qApp->setStyleSheet(styleSheet.readAll());
    styleSheet.close();
}

void MainWindow::skin_xml_init()
{
    QFile file("/res/qss/skin.xml");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qWarning("Open skin.xml error!");
        return;
    }
    QDomDocument doc;
    // 添加处理指令
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml", "version =\" 1.0\" encoding = \" UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement(tr("skins"));
    doc.appendChild(root);

    // 添加book元素及其子元素
    QDomElement book = doc.createElement(tr("skin"));
    QDomAttr id = doc.createAttribute(tr("NO"));
    QDomElement title = doc.createElement(tr("name"));
    QDomText text;

    id.setValue(tr("default"));
    book.setAttributeNode(id);
    text = doc.createTextNode(tr("style_main"));
    title.appendChild(text);
    book.appendChild(title);
    root.appendChild(book);


    //添加第二个book元素及其子元素
    book = doc.createElement(tr("skin"));
    id = doc.createAttribute(tr("NO"));
    title = doc.createElement(tr("name"));

    id.setValue(tr("2"));
    book.setAttributeNode(id);
    text = doc.createTextNode(tr("style_main2"));
    title.appendChild(text);
    book.appendChild(title);
    root.appendChild(book);

    QTextStream out(&file);
    doc.save(out,4);   //将文档保存到文件，4为子元素缩进字符数
    file.close();
}


void MainWindow::UpdateData()
{

    plot->addData(qrand()%100);
}
