#ifndef FRIENDITEM_H
#define FRIENDITEM_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QGroupBox>
#include <QToolBox>
#include <QVBoxLayout>
#include <QToolButton>
#include <QUdpSocket>
#include <QTextCodec>
#include <QMessageBox>
#include <QSound>
#include <QEvent>
#include <QMouseEvent>
#include <QFile>
#include <QFileDialog>
#include <QStandardItemModel>
#include "chatview.h"
#include "frienditem.h"
#include "filerecive.h"
#include "login/userdata.h"
#include "login/myhelper.h"

class ChatView;
class FriendItem : public QWidget
{
    Q_OBJECT
public:
    explicit FriendItem(QWidget *parent = 0);
    FriendItem(QWidget *parent =0,int x =0,int y=0,UserData::UserInfo *user =NULL);
    QLabel *Avatar;
    QLabel *Status;
    QLabel *Name;
    QLabel *PS;
    QGroupBox *groupbox;
    QPixmap avatar_images;
    UserData::UserInfo *user;
signals:

public slots:

protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:

    void init(UserData::UserInfo *user);

    bool IsChatOpen;
    ChatView *w;




};

#endif // FRIENDITEM_H
