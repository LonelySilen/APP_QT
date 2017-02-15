#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
#include <QApplication>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QStackedWidget>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QTextEdit>
#include <QDomDocument>
#include <QTextStream>

#include "plotter.h"
#include "tablewidget.h"

class MainWindow : public QMainWindow
{
       Q_OBJECT

   public:
       explicit MainWindow(QWidget *parent = 0);
       ~MainWindow();

   protected:
       void paintEvent(QPaintEvent *);
       void mouseMoveEvent(QMouseEvent *);
       void mousePressEvent(QMouseEvent *);

   private slots:
       void on_menuBtn_clicked();

       void on_optionButton_clicked();

       void skin_change();

       void skin_xml_init();

   private:
       QWidget *centerWindow;
       QLabel *label_title;
       QLabel *label_logo;
       QLabel *label_checkUpdate;
       QLabel *label_version;
       QLabel *label_version2;

       QPushButton *minBtn;//最小化按钮
       QPushButton *nomalBtn;//最大化按钮
       QPushButton *closeBtn;//关闭按钮
       QPushButton *menuBtn;//选项按钮

       QVBoxLayout *main_layout;
       QHBoxLayout *title_layout;//标题栏
       QHBoxLayout *tool_layout;//工具菜单layout
       QHBoxLayout *content_layout;//工具菜单layout
       QHBoxLayout *status_layout;//状态栏layout
       QPushButton *pushButton_1;//菜单按钮
       QPushButton *pushButton_2;
       QPushButton *pushButton_3;
       QPushButton *pushButton_4;
       QPushButton *pushButton_5;
       QPushButton *pushButton_6;
       QPushButton *pushButton_7;
       QPushButton *pushButton_8;
       QPushButton *pushButton_9;


       QStackedWidget *stackedWidget;//堆栈窗体
       QWidget *page_1;//功能页1
       QWidget *page_2;//功能页2
       QWidget *page_3;//功能页3
       QWidget *page_4;//功能页4
       QWidget *page_5;//功能页5
       QWidget *page_6;//功能页6
       QWidget *page_7;//功能页7
       QWidget *page_8;//功能页8
       QWidget *page_9;//功能页9

       Plotter *plot;
       QTimer* theTimer;//动态坐标的定时器

       TableWidget *table1;

       QVector<QString> skins;

       QPixmap m_pixmapBg;
       QAction *m_AactionAboutQt;
       QMenu *m_menu;

       QPoint m_pointStart;
       QPoint m_pointPress;

       QVector <QPushButton* > m_vecBtn;

       ///成员变量初始化;
       void initData();

       ///自定义窗口样式;
       void setNomalStyle();

       ///功能选择函数;
       void setCurrentWidget();

private slots:
       void UpdateData();

};
#endif
