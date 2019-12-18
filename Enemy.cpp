#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <QDebug>
#include <QGraphicsObject>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <vector>
#include "TowerSmallBullet.h"
#include "CannonBullet.h"
#include "Bomb.h"
#include "Hole.h"
#include "WeaponBullets.h"
#include "Player.h"
#include <iostream>

//int Player::coins = 0;
Enemy::Enemy():QObject(),  QGraphicsPixmapItem()
{


    //Pozicija protivnika je random
    int random_n = rand() % 500; // sa %500 ogranicavamo da se protivnik ne pravi na Y>500
    setPos(-20,random_n);
    //Crtamo protivnika
    QPixmap img(":/imgs/character_zombie_walk1.png");
    setPixmap(img.scaled(QSize(80,80)));
    // Timer koji pomera protivnika
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(200);


}


void Enemy::move(){
    //HIT DETECTION preuzet sa Stackoverflow-a
    QList<QGraphicsItem *> colliding_items = collidingItems();
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(TowerSmallBullet)
                    || typeid(*(colliding_items[i])) == typeid(CannonBullet1)
                    || typeid(*(colliding_items[i])) == typeid(CannonBullet2)
                    || typeid(*(colliding_items[i])) == typeid(WeaponBullet1)
                    || typeid(*(colliding_items[i])) == typeid(WeaponBullet2)
                    || typeid(*(colliding_items[i])) == typeid(WeaponBullet3)){
                this->HP -=1;
                if(this->HP==0){
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
            }
            if (typeid(*(colliding_items[i])) == typeid(Bomb)){
                scene()->removeItem(this);
                delete this;
                return;

            }
            if (typeid(*(colliding_items[i])) == typeid(Hole)){
                k=2;
            }
        }
    setPos(x()+k,y());
    if(pos().x() > 800 ){
        scene()->removeItem(this);
        delete this;
    }
    //Sa svakim otkucajem tajmere protivnik se pomera i menja se slika hoda
    if (this->n == 1){
        QPixmap img(":/imgs/character_zombie_walk2.png");
        setPixmap(img.scaled(QSize(80,80)));
        this->n=2;
    }else if(this->n==2){
        QPixmap img(":/imgs/character_zombie_walk3.png");
        setPixmap(img.scaled(QSize(80,80)));
        this->n=3;
    }else if(this->n==3){
        QPixmap img(":/imgs/character_zombie_walk1.png");
        setPixmap(img.scaled(QSize(80,80)));
        this->n=1;
    }

}


