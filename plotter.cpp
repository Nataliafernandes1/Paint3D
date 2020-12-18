#include "plotter.h"
#include<QPainter>
#include<QBrush>
#include<QPen>
#include<QColor>
#include<QMouseEvent>
#include<QColorDialog>
#include<QDebug>
#include<QFileDialog>
#include<QMessageBox>
#include<algorithm>
#include<iostream>
#include<math.h>
#include<stdlib.h>

Plotter::Plotter(QWidget *parent) : QWidget(parent)
{
    Ncol=Nlin=Nplan=0;
    EspCol=EspLin=EspPlan=0;
    altura=largura=0;
    xbox=ybox=zbox=0;
    rsfera=0;
    rxEllipsoid=ryEllipsoid=rzEllipsoid=0;
    color=QColor(0,0,0,255);
    sculptor=new Sculptor(Nlin, Ncol, Nplan);
    action=" ";
}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    QPen Pen;

    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);

    Pen.setColor(QColor(0,0,0));
    Pen.setStyle(Qt::SolidLine);
    Pen.setWidth(2);

    painter.setBrush(brush);
    painter.setPen(Pen);
    painter.drawRect(0,0,width(), height());

    if(Nlin !=0 && Ncol!=0 &&Nplan !=0){
        Pen.setWidth(2);
        painter.setPen(Pen);
        for(int i=1; i<=Nlin; i++){
            painter.drawLine(0, i*altura, width(), i*altura);
        }
        for(int i=1; i<Ncol; i++){
            painter.drawLine(i*largura,0,i*largura,height());
        }
    }
    brush.setColor(QColor(0,0,0));
    painter.setBrush(brush);
    for(int i=1; i<=Nlin; i++){
        for(int j=1; j<Ncol; j++){
            if(planAtual[i][j].isOn==true){
                qDebug()<<"entrou";
                int plin=i*altura;
                int pcol=j*largura;
                brush.setColor(QColor(211,215,207));
                painter.setBrush(brush);
                painter.drawRect(pcol,plin,largura,altura);
                Voxel auxiliar = planAtual[i][j];
                brush.setColor(QColor(auxiliar.r, auxiliar.g, auxiliar.b, auxiliar.a));
                painter.setBrush(brush);
                painter.drawEllipse(pcol, plin,largura,altura);
                            }
        }
    }
}
void Plotter::mousePressEvent(QMouseEvent *event){
    if(Nlin !=0 && Ncol !=0 && Nplan !=0){
           if(event->button() == Qt::LeftButton){

               // Posicao do Click
               int pos_col = event->x();
               int pos_lin = event->y();

               // Posição na Vector do Escultor
               EspLin = pos_lin/altura;
               EspCol = pos_col/largura;

               //QColor color(0,0,0,255);

               sculptor->setColor(color.red()/255.0f,color.green()/255.0f,color.blue()/255.0f,color.alpha()/255.0f);

               if(action.compare("PutVoxel",Qt::CaseInsensitive) == 0){
                   if (limites(EspLin,EspCol,EspPlan)){
                       ativacaoVoxel(painter_sculptor[EspPlan][EspLin][EspCol],color);
                       sculptor->putVoxel(EspLin,EspCol,EspPlan);
                   }
                   //sculptor->print_sculptor();
               }

               else if (action.compare("CutVoxel",Qt::CaseInsensitive) == 0) {
                   if (limites(EspLin,EspCol,EspPlan)){
                       desVoxel(painter_sculptor[EspPlan][EspLin][EspCol]);
                       sculptor->cutVoxel(EspLin,EspCol,EspPlan);
                   }
               }
               else if (action.compare("PutBox",Qt::CaseInsensitive) == 0) {
                   for(int k=0; k<zbox;k++){
                       for(int i=0;i<xbox;i++){
                           for(int j=0; j<ybox;j++){
                               if (limites(EspLin+i,EspCol+j,EspPlan+k)){
                                   ativacaoVoxel(painter_sculptor[EspPlan+k][EspLin+i][EspCol+j],color);
                                   sculptor->putVoxel(EspLin+i,EspCol+j,EspPlan+k);
                               }
                           }
                       }
                   }
               }

               else if (action.compare("CutBox",Qt::CaseInsensitive) == 0) {
                   for(int k=0; k<zbox;k++){
                       for(int i=0;i<xbox;i++){
                           for(int j=0; j<ybox;j++){
                               if (limites(EspLin+i,EspCol+j,EspPlan+k)){
                                   desVoxel(painter_sculptor[EspPlan+k][EspLin+i][EspCol+j]);
                                   sculptor->cutVoxel(EspLin+i,EspCol+j,EspPlan+k);
                               }
                           }
                       }
                   }
               }

               else if (action.compare("PutSphere",Qt::CaseInsensitive) == 0) {
                   double dist;
                   for(int k=EspPlan - rsfera; k<=EspPlan + rsfera; k++){
                       for (int i=EspLin - rsfera; i<=EspLin + rsfera; i++) {
                           for (int j=EspCol - rsfera; j<=EspCol + rsfera; j++){
                              dist = pow(i-EspLin,2) + pow(j-EspCol,2) + pow(k-EspPlan,2);
                              if (dist <= pow(rsfera,2)){
                                  if (limites(i,j,k)){
                                      ativacaoVoxel(painter_sculptor[k][i][j],color);
                                      sculptor->putVoxel(i,j,k);
                                  }
                              }
                           }
                       }
                   }
               }

               else if (action.compare("CutSphere",Qt::CaseInsensitive) == 0) {
                   double dist;
                   for(int k=EspPlan - rsfera; k<=EspPlan + rsfera; k++){
                       for (int i=EspLin - rsfera; i<=EspLin + rsfera; i++) {
                           for (int j=EspCol - rsfera; j<=EspCol + rsfera; j++){
                              dist = pow(i-EspLin,2) + pow(j-EspCol,2) + pow(k-EspPlan,2);
                              if (dist <= pow(rsfera,2)){
                                  if (limites(i,j,k)){
                                      desVoxel(painter_sculptor[k][i][j]);
                                      sculptor->cutVoxel(i,j,k);
                                  }
                              }
                           }
                       }
                   }
               }

               else if (action.compare("PutEllipsoid", Qt::CaseInsensitive)==0) {
                   double dist;

                   if (rxEllipsoid ==0){
                       for (int k=EspPlan - rzEllipsoid;k<=EspPlan + rzEllipsoid;k++) {
                           for (int j=EspCol - ryEllipsoid;j<=EspCol + ryEllipsoid;j++) {
                               dist =  pow(j-EspCol,2)/pow(ryEllipsoid,2) + pow(k-EspPlan,2)/pow(rzEllipsoid,2);
                               if(dist<=1){
                                   if (limites(EspLin,j,k)){
                                       ativacaoVoxel(painter_sculptor[k][EspLin][j],color);
                                       sculptor->putVoxel(EspLin,j,k);
                                   }

                             }
                           }
                       }
                   }

                   else if(ryEllipsoid==0){
                       for (int k=EspPlan - rzEllipsoid;k<=EspPlan + rzEllipsoid;k++) {
                           for (int i=EspLin - rxEllipsoid;i<=EspLin + rxEllipsoid;i++) {
                               dist =  pow(i-EspLin,2)/pow(rxEllipsoid,2) + pow(k-EspPlan,2)/pow(rzEllipsoid,2);
                               if(dist<=1){
                                   if (limites(i,EspCol,k)){
                                       ativacaoVoxel(painter_sculptor[k][i][EspCol],color);
                                       sculptor->putVoxel(i,EspCol,k);
                                   }

                             }
                           }
                       }
                   }
                   else if (rzEllipsoid==0) {
                       for (int i=EspLin - rxEllipsoid;i<=EspLin + rxEllipsoid;i++) {
                           for (int j=EspCol - ryEllipsoid;j<=EspCol + ryEllipsoid;j++) {
                               dist =  pow(i-EspLin,2)/pow(rxEllipsoid,2) + pow(j-EspCol,2)/pow(ryEllipsoid,2);
                               if(dist<=1){
                                   if (limites(i,j,EspPlan)){
                                       ativacaoVoxel(painter_sculptor[EspPlan][i][j],color);
                                       sculptor->putVoxel(i,j,EspPlan);
                                   }
                                   //t.putVoxel(i,j,EspPlan);
                             }
                           }
                       }
                   }
                   else{
                   for (int k=EspPlan - rzEllipsoid;k<=EspPlan + rzEllipsoid;k++) {
                       for (int i=EspLin - rxEllipsoid;i<=EspLin + rxEllipsoid;i++) {
                           for (int j=EspCol - ryEllipsoid;j<=EspCol + ryEllipsoid;j++) {
                                 dist = pow(i-EspLin,2)/pow(rxEllipsoid,2) + pow(j-EspCol,2)/pow(ryEllipsoid,2) + pow(k-EspPlan,2)/pow(rzEllipsoid,2);
                               if(dist<=1){
                                   if (limites(i,j,k)){
                                       ativacaoVoxel(painter_sculptor[k][i][j],color);
                                       sculptor->putVoxel(i,j,k);
                                   }

                               }

                           }

                       }
                    }
                 }


               }

               else if (action.compare("CutEllipsoid", Qt::CaseInsensitive)==0) {
                   double dist;

                   if (rxEllipsoid ==0){
                       for (int k=EspPlan - rzEllipsoid;k<=EspPlan + rzEllipsoid;k++) {
                           for (int j=EspCol - ryEllipsoid;j<=EspCol + ryEllipsoid;j++) {
                               dist =  pow(j-EspCol,2)/pow(ryEllipsoid,2) + pow(k-EspPlan,2)/pow(rzEllipsoid,2);
                               if(dist<=1){
                                   if (limites(EspLin,j,k)){
                                       desVoxel(painter_sculptor[k][EspLin][j]);
                                       sculptor->cutVoxel(EspLin,j,k);
                                   }

                             }
                           }
                       }
                   }

                   else if(ryEllipsoid==0){
                       for (int k=EspPlan - rzEllipsoid;k<=EspPlan + rzEllipsoid;k++) {
                           for (int i=EspLin - rxEllipsoid;i<=EspLin + rxEllipsoid;i++) {
                               dist =  pow(i-EspLin,2)/pow(rxEllipsoid,2) + pow(k-EspPlan,2)/pow(rzEllipsoid,2);
                               if(dist<=1){
                                   if (limites(i,EspCol,k)){
                                       desVoxel(painter_sculptor[k][i][EspCol]);
                                       sculptor->cutVoxel(i,EspCol,k);
                                   }

                             }
                           }
                       }
                   }
                   else if (rzEllipsoid==0) {
                       for (int i=EspLin - rxEllipsoid;i<=EspLin + rxEllipsoid;i++) {
                           for (int j=EspCol - ryEllipsoid;j<=EspCol + ryEllipsoid;j++) {
                               dist =  pow(i-EspLin,2)/pow(rxEllipsoid,2) + pow(j-EspCol,2)/pow(ryEllipsoid,2);
                               if(dist<=1){
                                   if (limites(i,j,EspPlan)){
                                       desVoxel(painter_sculptor[EspPlan][i][j]);
                                       sculptor->cutVoxel(i,j,EspPlan);
                                   }

                             }
                           }
                       }
                   }
                   else{
                   for (int k=EspPlan - rzEllipsoid;k<=EspPlan + rzEllipsoid;k++) {
                       for (int i=EspLin - rxEllipsoid;i<=EspLin + rxEllipsoid;i++) {
                           for (int j=EspCol - ryEllipsoid;j<=EspCol + ryEllipsoid;j++) {
                                 dist = pow(i-EspLin,2)/pow(rxEllipsoid,2) + pow(j-EspCol,2)/pow(ryEllipsoid,2) + pow(k-EspPlan,2)/pow(rzEllipsoid,2);
                               if(dist<=1){
                                   if (limites(i,j,k)){
                                       desVoxel(painter_sculptor[k][i][j]);
                                       sculptor->cutVoxel(i,j,k);
                                   }}}}}}}

               qDebug() << "Pos Plano: " << EspPlan;
               qDebug() << "Pos Linha: " << EspLin;
               qDebug() << "Pos Coluna: " << EspCol;

               planAtual = painter_sculptor[EspPlan];
               repaint();

           }
       }
}
void Plotter::changeColor()
{
    QColor c;
    QColorDialog dColor;
    dColor.exec();
    c = dColor.selectedColor();

    // Atualizando a cor dos Voxels
    color.setRed(c.red());
    color.setGreen(c.green());
    color.setBlue(c.blue());
    color.setAlpha(255);

    //Atualizando os Sliders das Cores
    emit changeR(c.red());
    emit changeG(c.green());
    emit changeB(c.blue());
