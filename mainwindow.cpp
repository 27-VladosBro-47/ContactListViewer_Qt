#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Scene();
    scene->setSceneRect(0.0, 0.0, ui->graphicsView->size().width(), ui->graphicsView->size().height());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));

    ContactList = new ContactListProvider();

    WinCall = new WindowCall();

    connect(scene, &Scene::signalGetPtrChunkContainer, ContactList, &ContactListProvider::slotSendPtrChunkContainer);
    connect(scene, &Scene::signalCall, ContactList, &ContactListProvider::slotCall);
    connect(ContactList, &ContactListProvider::signalSendDataToMainWin, this, &MainWindow::slotGetDataToMainWin);
    connect(this, &MainWindow::signalSendDataToWinCall, WinCall, &WindowCall::slotGetDataToWinCall);
    connect(scene, &Scene::signalGetCurrWidthHeight, this, &MainWindow::slotSendCurrWidthHeight);
    connect(scene, &Scene::signalSetCenterOn, this, &MainWindow::slotSetCenterOn);
    connect(ContactList, &ContactListProvider::signalsetDisableButtons, this, &MainWindow::slotSetDisableButtons);

    ui->graphicsView->centerOn(0, 0);

    this->setFixedSize(380,600);

    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->radioButton->setDisabled(true);
    ui->radioButton_2->setDisabled(true);
    ui->lineEdit->setDisabled(true);
    ui->stackedWidget->setDisabled(true);
    slotSetDisableButtons(1,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(ContactList->getNameOfDirContacts())
    { ContactList->getContacts();

        ContactList->getChunk(ContactListProvider::ALL);
        scene->setContacts();

        ui->pushButton_2->setDisabled(false);
        ui->pushButton_3->setDisabled(false);
        ui->radioButton->setDisabled(false);
        ui->radioButton_2->setDisabled(false);
        ui->lineEdit->setDisabled(false);
        ui->stackedWidget->setDisabled(false);
    }
}

void MainWindow::slotSendCurrWidthHeight(int& W, int&H)
{
    W = ui->graphicsView->geometry().width();
    H = ui->graphicsView->geometry().height();
}

// Reactangle
void MainWindow::on_radioButton_2_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        scene->setFiguresType(1);
    }
}

// Square
void MainWindow::on_radioButton_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        scene->setFiguresType(0);
    }
}

// Show All
void MainWindow::on_pushButton_2_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk(ContactListProvider::ALL);
        scene->setContacts();
    }
}

// Show Favorites
void MainWindow::on_pushButton_3_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk(ContactListProvider::FAVORITES);
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::slotSetCenterOn(int W, int H)
{
    ui->graphicsView->centerOn(W, H);
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk(arg1);
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_24_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_30_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_36_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_10_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("A");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("B");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("C");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_12_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("D");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("E");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_16_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("F");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_17_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("G");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_20_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("H");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("I");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_19_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("J");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_22_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("K");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_23_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("L");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_26_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("M");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_21_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("N");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_25_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("O");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_28_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("P");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_29_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("Q");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_32_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("R");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_27_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("S");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_31_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("T");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_34_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("U");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_35_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("V");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_38_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("W");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_33_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("X");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_37_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("Y");
        scene->setContacts();
    }
}

void MainWindow::on_pushButton_39_clicked()
{
    if(ContactList->getQuantityOfContacts()!=0)
    {
        ContactList->getChunk("Z");
        scene->setContacts();
    }
}

void MainWindow::slotSetDisableButtons(int codeOfSymbol, bool flag)
{
    switch(codeOfSymbol)
    {
    case 65: { ui->pushButton_10->setDisabled(flag);  break;}
    case 66: { ui->pushButton_11->setDisabled(flag);  break;}
    case 67: { ui->pushButton_9->setDisabled(flag);  break;}
    case 68: { ui->pushButton_12->setDisabled(flag);  break;}
    case 69: { ui->pushButton_13->setDisabled(flag);  break;}
    case 70: { ui->pushButton_16->setDisabled(flag);  break;}
    case 71: { ui->pushButton_17->setDisabled(flag);  break;}
    case 72: { ui->pushButton_20->setDisabled(flag);  break;}
    case 73: { ui->pushButton_15->setDisabled(flag);  break;}
    case 74: { ui->pushButton_19->setDisabled(flag);  break;}
    case 75: { ui->pushButton_22->setDisabled(flag);  break;}
    case 76: { ui->pushButton_23->setDisabled(flag);  break;}
    case 77: { ui->pushButton_26->setDisabled(flag);  break;}
    case 78: { ui->pushButton_21->setDisabled(flag);  break;}
    case 79: { ui->pushButton_25->setDisabled(flag);  break;}
    case 80: { ui->pushButton_28->setDisabled(flag);  break;}
    case 81: { ui->pushButton_29->setDisabled(flag);  break;}
    case 82: { ui->pushButton_32->setDisabled(flag);  break;}
    case 83: { ui->pushButton_27->setDisabled(flag);  break;}
    case 84: { ui->pushButton_31->setDisabled(flag);  break;}
    case 85: { ui->pushButton_34->setDisabled(flag);  break;}
    case 86: { ui->pushButton_35->setDisabled(flag);  break;}
    case 87: { ui->pushButton_38->setDisabled(flag);  break;}
    case 88: { ui->pushButton_33->setDisabled(flag);  break;}
    case 89: { ui->pushButton_37->setDisabled(flag);  break;}
    case 90: { ui->pushButton_39->setDisabled(flag);  break;}
    default:
    {
        ui->pushButton_10->setDisabled(flag);
        ui->pushButton_11->setDisabled(flag);
        ui->pushButton_9->setDisabled(flag);
        ui->pushButton_12->setDisabled(flag);
        ui->pushButton_13->setDisabled(flag);
        ui->pushButton_16->setDisabled(flag);
        ui->pushButton_17->setDisabled(flag);
        ui->pushButton_20->setDisabled(flag);
        ui->pushButton_15->setDisabled(flag);
        ui->pushButton_19->setDisabled(flag);
        ui->pushButton_22->setDisabled(flag);
        ui->pushButton_23->setDisabled(flag);
        ui->pushButton_26->setDisabled(flag);
        ui->pushButton_21->setDisabled(flag);
        ui->pushButton_25->setDisabled(flag);
        ui->pushButton_28->setDisabled(flag);
        ui->pushButton_29->setDisabled(flag);
        ui->pushButton_32->setDisabled(flag);
        ui->pushButton_27->setDisabled(flag);
        ui->pushButton_31->setDisabled(flag);
        ui->pushButton_34->setDisabled(flag);
        ui->pushButton_35->setDisabled(flag);
        ui->pushButton_38->setDisabled(flag);
        ui->pushButton_33->setDisabled(flag);
        ui->pushButton_37->setDisabled(flag);
        ui->pushButton_39->setDisabled(flag);
    }
    }
}

