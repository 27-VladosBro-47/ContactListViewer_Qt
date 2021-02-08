#include "windowcall.h"
#include "ui_windowcall.h"

WindowCall::WindowCall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindowCall)
{
    ui->setupUi(this);

    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_3->setAlignment(Qt::AlignCenter);
}

WindowCall::~WindowCall()
{
    delete ui;
}

void WindowCall::on_pushButton_clicked()
{
    done(0);
}

void WindowCall::setData()
{
    ui->label->setPixmap(QPixmap(photo));
    ui->label_2->setText(nameSurname);
    ui->label_3->setText(phone);
}
