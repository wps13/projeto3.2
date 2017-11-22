#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTextBrowser>
#include <QString>
#include <vector>
#include "plotter.h"

using namespace std;

/**
 * @brief MainWindow::MainWindow Construtor da classe
 * @param parent
 */
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

/**
 * @brief MainWindow::tcpDisconnect Desconecta-se do Ip
 */
void MainWindow::tcpDisconnect()
{
    socket->disconnectFromHost();
    qDebug() << "Desconectado";
}

/**
 * @brief MainWindow::start Inicia o recebimento dos dados
 */

void MainWindow::start()
{
    timer= startTimer(ui->horizontalSliderTiming->value() * 1000);
    qDebug ()<< "Timer Started";
}

/**
 * @brief MainWindow::stop Finaliza o recebimento dos dados
 */
void MainWindow::stop()
{
    killTimer(timer);
    qDebug() << "Timer Killed";
}

/**
 * @brief MainWindow::update Atualiza a lista de IPs conectados
 */

void MainWindow::update()
{
    //armazena o comando a ser enviado ao servidor
    QString strList;

    //armazena o ip coletado que está conectado ao servidor
    QString str;

    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "Pegando IP";
            strList = "list\r\n";
            socket->write(strList.toStdString().c_str());

              socket->waitForBytesWritten();
              socket->waitForReadyRead();
              qDebug() << socket->bytesAvailable();
              while(socket->bytesAvailable()){
                  //separa o tempo recebido do servidor do valor dado
                  str = socket->readLine().replace("\n","").replace("\r","");
                 ui->listWidget->addItem(str);

               }

        }
    }

}

/**
 * @brief MainWindow::getData Acessa o servidor e recolhe a data
 */
void MainWindow::getData(){
    QString str;
    QByteArray array;
    QStringList list;
    qint64 thetime;
    QString ipStr;
    vector<qint64> tempo;
    vector<int> valor;

    qDebug() << "to get data...";
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "reading...";

         ipStr = "get " + ui->lineEditIP->text() + " 5" + "\r\n";


          socket->write(ipStr.toStdString().c_str());

            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            qDebug() << socket->bytesAvailable();
            while(socket->bytesAvailable()){
                //separa o tempo recebido do servidor do valor dado
                str = socket->readLine().replace("\n","").replace("\r","");

                list = str.split(" ");
                if(list.size() == 2){
                    bool ok;
                    str = list.at(0);
                    thetime = str.toLongLong(&ok);
                    str = list.at(1);
                    qDebug() << thetime << ": " << str;

                    tempo.push_back(thetime);
                    valor.push_back(str.toInt());

                }
                if(tempo.size()==30)
                  ui->widget->plotGrafico(tempo,valor);
            }
        }
    }
}

/**
 * @brief MainWindow::timerEvent Ação a ser realizada no intervalo de tempo
 * @param e
 */
void MainWindow::timerEvent(QTimerEvent *e)
{
    getData();
    qDebug()<<"Getting data";
}

void MainWindow::getItem()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    ui->lineEditIP->setText( item->text());

}

/**
 * @brief MainWindow::~MainWindow Destrutor da classe
 */

MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
}
