#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTextBrowser>
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    tcpConnect();

    connect(ui->pushButtonStart,
            SIGNAL(clicked(bool)),
            this,
            SLOT(start()));

    connect(ui->pushButtonConnect,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));

            connect(ui->pushButtonDisconnect,
                    SIGNAL(clicked(bool)),
                    this,
                    SLOT(tcpDisconnect()));

    connect(ui->pushButtonStop,
            SIGNAL(clicked(bool)),
            this,
            SLOT(stop()));

    connect(ui->pushButtonUpdate,
            SIGNAL(clicked(bool)),
            this,
            SLOT(update()));


}

/**
 * @brief MainWindow::tcpConnect Conecta-se ao IP dado
 */
void MainWindow::tcpConnect(){
    socket->connectToHost(ui->lineEditIP->text(),1234);
    if(socket->waitForConnected(3000)){
        qDebug() << "Connected";
        }
    else{
        qDebug() << "Disconnected";
    }
}

void MainWindow::tcpDisconnect()
{
    socket->disconnectFromHost();
    qDebug() << "Desconectado";
}

void MainWindow::start()
{
    timer= startTimer(ui->horizontalSliderTiming->value() * 1000);
    qDebug ()<< "Timer Started";
}
void MainWindow::stop()
{
    killTimer(timer);
    timer=0;
    qDebug() << "Timer Killed";
}

void MainWindow::update()
{

}

void MainWindow::getData(){
    QString str;
    QByteArray array;
    QStringList list;
    qint64 thetime;
    qDebug() << "to get data...";
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "reading...";

            socket->write("get 127.0.0.1 5\r\n");

            //DEU ERRO
            //acho que esse 5 seria o valor aleatório do servidor, ALTERAR
            //socket->write("get " + ui->lineEditIP->text() + "5" +"\r\n");

            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            qDebug() << socket->bytesAvailable();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                list = str.split(" ");
                if(list.size() == 2){
                    bool ok;
                    str = list.at(0);
                    thetime = str.toLongLong(&ok);
                    str = list.at(1);
                    qDebug() << thetime << ": " << str;
                }
            }
        }
    }
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    getData();
    qDebug()<<"Getting data";
}



MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
}
