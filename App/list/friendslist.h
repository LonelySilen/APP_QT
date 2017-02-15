#ifndef FRIENDSLIST_H
#define FRIENDSLIST_H

#include <QApplication>
#include <QWidget>
#include <QFile>
#include <QLabel>
#include <QPixmap>
#include <QToolBox>
#include <QTabWidget>
#include <QMainWindow>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <frienditem.h>

class ChatView;
class FriendsList : public QMainWindow
{
    Q_OBJECT

public:
    explicit FriendsList(QWidget *parent = 0);
    ~FriendsList();
//    QString UserID;


    void Update(QString msg);
    void ReciveFile(QString msg);
    void ReciveMsg(QString msg);
    void IsOnline(QHostAddress IP,qint16 Port);

    void Init();
    void FriendsInit();
    void GroupsInit();
    void NearInit();

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);         //自定义一个鼠标拖动事件函数
    void mousePressEvent(QMouseEvent *event);
//    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void on_Close_pushButton_clicked();
    void BoxChanged();
    void AnalyseMessage();

private:

    void setListStyle();

    QWidget *centerWindow;

    QPushButton *minBtn;//最小化按钮
    QPushButton *closeBtn;//关闭按钮

    QLabel *label_avatar;//头像
    QLabel *label_name;//用户名
    QLineEdit *signature;//个性签名

    QTabWidget *tabWidget;//标签页
    QWidget *list_friends;//好友列表
    QWidget *list_groups;//群组列表
    QWidget *list_recent;//最近

    QVBoxLayout *main_layout;
    QHBoxLayout *layout_title;
    QVBoxLayout *layout_info;
    QHBoxLayout *layout_card;
    QHBoxLayout *layout_name;
    QHBoxLayout *layout_sign;

    QPoint dragPosition;
    QToolBox *friends_box;
    QGroupBox *Groups_box;

    FriendItem *frienditem;

    ChatView *chatWindow;

    QVector <FriendItem*> FriendItemList;

};

#endif // FRIENDSLIST_H
