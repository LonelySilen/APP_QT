#include "tablewidget.h"
#include "qdelegate.h"
#include <QtSql>
#include <QDebug>

TableWidget::TableWidget(QWidget *parent) :
    QWidget(parent)
{

    QString dbFile1 = "res/data/ECSTool.db";
    if (QFile::exists(dbFile1)) {
        qDebug() << dbFile1 << "不存在！";
    }
    QSqlDatabase db1;
    if(QSqlDatabase::contains("ECSTool"))
        db1 = QSqlDatabase::database("ECSTool");
    else
        db1 = QSqlDatabase::addDatabase("QSQLITE", "ECSTool");
    db1.setDatabaseName(qApp->applicationDirPath() + dbFile1);
    if (!db1.open()) {
        qDebug() << dbFile1 << "数据库打开出错！";
    }
    //db1.open();

    model1 = new QSqlTableModel(this, QSqlDatabase::database("ECSTool"));
    model1->setTable("NmDegLog");
    model1->setSort(0, Qt::DescendingOrder);
    model1->setHeaderData(0, Qt::Horizontal, "保存时间");
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model1->select();

    tableView1 = new QTableView();
    tableView1->setMinimumSize(300,250);

    btn_layout = new QVBoxLayout();
    btnAdd = new QPushButton("添加");
    btnDelete = new QPushButton("删除");
    btnSave = new QPushButton("保存");
    btnReturn = new QPushButton("撤销");
    btn_layout->setSpacing(0);
    btn_layout->addWidget(btnAdd);
    btn_layout->addWidget(btnDelete);
    btn_layout->addWidget(btnSave);
    btn_layout->addWidget(btnReturn);

    connect(btnAdd, SIGNAL(clicked()), this, SLOT(on_btnAdd_clicked()));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(on_btnDelete_clicked()));
    connect(btnSave, SIGNAL(clicked()), this, SLOT(on_btnSave_clicked()));
    connect(btnReturn, SIGNAL(clicked()), this, SLOT(on_btnReturn_clicked()));

    table_layout =  new QHBoxLayout(this);
    table_layout->addWidget(tableView1);
    table_layout->addLayout(btn_layout);

    QDelegate *d_dt = new QDelegate(this);
    d_dt->SetDeleteType("QDateTimeEdit");
    tableView1->setItemDelegateForColumn(0, d_dt);

    QDelegate *d_cbox = new QDelegate(this);
    d_cbox->SetDeleteType("QComboBox");
    d_cbox->SetDeleteValue(QStringList() << "1" << "2" << "3");
    tableView1->setItemDelegateForColumn(1, d_cbox);

    tableView1->setModel(model1);
    tableView1->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView1->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableView1->setColumnHidden(6, true);
    tableView1->resizeRowsToContents();
    tableView1->resizeColumnsToContents();
    tableView1->horizontalHeader()->setStretchLastSection(true);

}

TableWidget::~TableWidget()
{

}

void TableWidget::on_btnAdd_clicked()
{
    int rowNum = model1->rowCount();
    model1->insertRow(rowNum);
    model1->setData(model1->index(rowNum, 0), QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

    tableView1->setCurrentIndex(model1->index(model1->rowCount() - 1, 0));
}

void TableWidget::on_btnDelete_clicked()
{
    int curRow = tableView1->currentIndex().row();
    model1->removeRow(curRow);
    model1->submitAll();

    tableView1->setCurrentIndex(model1->index(model1->rowCount() - 1, 0));
}

void TableWidget::on_btnSave_clicked()
{
    model1->database().transaction();
    if (model1->submitAll()) {
        model1->database().commit();
    } else {
        model1->database().rollback();
    }
}

void TableWidget::on_btnReturn_clicked()
{
    model1->revertAll();
}
