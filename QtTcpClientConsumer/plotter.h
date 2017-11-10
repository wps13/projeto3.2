#ifndef PLOTTER_H
#define PLOTTER_H
#include <QWidget>

class Plotter : public QWidget
{
    Q_OBJECT
private :

public:
    Plotter(QWidget *parent);
    void paintEvent(QPaintEvent *event);

signals:

public slots:


};

#endif // PLOTTER_H
