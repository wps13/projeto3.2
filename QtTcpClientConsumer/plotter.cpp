#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <cmath>

using namespace std;
/**
 * @brief Plotter::Plotter Construtor da Classe
 * @param parent
 */
Plotter::Plotter(QWidget *parent) : QWidget(parent)
{

}

/**
 * @brief Plotter::paintEvent Realiza o desenho da tela
 * @param event
 */
void Plotter::paintEvent(QPaintEvent *event)
{
    /**
     * @brief painter
     */
    QPainter painter(this);

    /**
     * @brief brush
     */
    QBrush brush;

    /**
     * @brief pen
     */
    QPen pen;

    /**
     * @brief x1 Posição inicial horizontal da reta
     */

    /**
     * @brief x2 Posição horizontal final da reta
     */

    /**
     * @brief y1 Posição vertical inicial da reta
     */

    /**
     * @brief y2 Posição vertical final da reta
     */
    int x1,x2,y1,y2;

    //define a cor e tipo do preenchimento do fundo da tela
    //brush.setColor(QColor(255,255,100));
    brush.setColor(QColor(51,51,51));

    brush.setStyle(Qt::SolidPattern);

    //define a cor da borda da tela
    //pen.setColor(QColor(255,0,0));
    pen.setColor(QColor(153,153,153));

    //define a largura da borda
    pen.setWidth(2);


    painter.setBrush(brush);

    painter.setPen(pen);


    painter.drawRect(0,0,width(),height());
    /*
    pen.setColor(QColor(255,180,0));
    painter.setPen(pen);
    */

    //define a cor das linhas da tela

    //pen.setColor(QColor(0,0,255));
    pen.setColor(QColor(255,255,255));
    painter.setPen(pen);

    //ALTERAR AS VARIAVÉIS DE FORMA QUE O GRÁFICO SEJA DO TEMPO X VALOR DO SERVIDOR

    //define as posições iniciais
    x1=0;
    y1=height();

    //desenha várias retas na tela de forma a desenhar o gráfico
    for(int i=1;i<width();i++)
    {
        x2=i;
        y2=0; //valor a ser alterado
        x1=x2;
        y1=y2;
    }


}
