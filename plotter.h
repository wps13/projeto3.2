#ifndef PLOTTER_H
#define PLOTTER_H
#include <QWidget>
#include <vector>

using namespace std;

class Plotter : public QWidget
{
    Q_OBJECT
private :


public:
    Plotter(QWidget *parent);
    void paintEvent(QPaintEvent *event);
    void plotGrafico(vector<qint64> &t,vector<int> &v);

signals:

private slots:


public slots:


};

#endif // PLOTTER_H
