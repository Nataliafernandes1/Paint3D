#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include<QColor>
#include<QString>
#include "sculptor.h"
#include<vector>
#include<qvector.h>


class Plotter : public QWidget
{
    Q_OBJECT
private:
    int Ncol, Nlin, Nplan, EspCol, EspLin, EspPlan;
    double altura, largura;
    QVector<QVector<QVector<Voxel>>> painter_sculptor;
    QVector<QVector<Voxel>> planAtual;
    Sculptor*sculptor;
    QString action;
    QColor color;
    int xbox, ybox, zbox, rsfera, rxEllipsoid, ryEllipsoid, rzEllipsoid;

    void ativacaoVoxel(Voxel &V, QColor color);
    void desVoxel(Voxel &V);
    bool limites (int lin, int col, int plan);




public:
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void changeSlideX(int, int);
    void changeSlideY(int, int);
    void changeSlideZ(int, int);
    void changeRSfera(int, int);
    void changeSlideR(int);
    void changeSlideG(int);
    void changeSlideB(int);
    void changeSlideA(int);

public slots:
    void changeColor();
    void saveSculptor();
    void cleanSculptor();
    void changePlanZ(int planZ);
    void changeRsfera(int _rsf);
    void changeRXEllipsoid(int _rxel);
    void changeRYEllipsoid(int _ryel);
    void changeRZEllipsoid(int _rzel);
    void changeXBox(int _x);
    void changeYBox(int _y);
    void changeZBox(int _z);
    void changeR(int _r);
    void changeG(int _g);
    void changeB(int _b);
};

#endif // PLOTTER_H
