#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



public slots:


private slots:
    void getData();
    void tcpConnect();
    void tcpDisconnect();
    void start();
    void stop();
    void update();
    void timerEvent(QTimerEvent *e);

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    int timer;
};

#endif // MAINWINDOW_H
