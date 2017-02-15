#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>

class QSqlTableModel;


class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = 0);
    ~TableWidget();

private slots:
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_btnSave_clicked();
    void on_btnReturn_clicked();

private:
    QSqlTableModel *model1;
    QSqlTableModel *model2;

    QTableView *tableView1;
    QTableView *tableView2;

    QHBoxLayout *table_layout;
    QVBoxLayout *btn_layout;

    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnSave;
    QPushButton *btnReturn;

};

#endif // TABLEWIDGET_H
