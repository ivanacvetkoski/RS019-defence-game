#include "ExitBtn.h"
#include <QApplication>



ExitBtn::ExitBtn(): QGraphicsPixmapItem(){
    //Dugme za exit

    setPixmap(QPixmap(":/imgs/blue_boxCross.png"));
    setPos(1250,0);
}

void ExitBtn::mousePressEvent(QGraphicsSceneMouseEvent *event){
   QApplication::quit();
}
