#ifndef WINDOWCALL_H
#define WINDOWCALL_H

#include <QDialog>
#include <QString>
#include <QPixmap>

namespace Ui {
class WindowCall;
}

class WindowCall : public QDialog
{
    Q_OBJECT

public:
    explicit WindowCall(QWidget *parent = nullptr);
    ~WindowCall();

    QString nameSurname;
    QString phone;
    QString photo;


public slots:
    void slotGetDataToWinCall(QString NameSurname, QString Phone, QString Photo)
    {
        nameSurname = NameSurname;
        phone = Phone;
        photo = Photo;
        setData();
    }

private slots:
    void setData();
    void on_pushButton_clicked();

private:
    Ui::WindowCall *ui;
};

#endif // WINDOWCALL_H
