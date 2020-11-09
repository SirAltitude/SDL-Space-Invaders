//
// Created by Anton on 28-4-2020.
//

#ifndef PROGRAMMEREN_ENTITY_H
#define PROGRAMMEREN_ENTITY_H


class Entity {
public:
    void setX(int xCoordinaat);
    void setY(int yCoordinaat);
    void setBreedte(int width);
    void setHoogte(int height);
    void setData(int x, int y, int b, int h);
    int getX();
    int getY();
    int getB();
    int getH();
    void printData();

    virtual void visualize(double scaleX, double scaleY) = 0;
    bool collision(Entity* object);

protected:
    int xPos, yPos, Breedte, Hoogte;
    bool collided = false;
};


#endif //PROGRAMMEREN_ENTITY_H
