#pragma once

class Character {
protected:
    int maxLife;
    int currentLife;
    int attack;
    int armor;
    int speed;

public:
    Character(int mLife = 0, int cLife = 0, int atk = 0, int armor = 0, int speed = 0);
    virtual ~Character(); // Destrutor virtual é essencial para polimorfismo!

    // Adicione virtual aqui:
    virtual int getMaxLife() const;
    virtual void setMaxLife(int valMaxLife);

    virtual int getCurrentLife() const;
    virtual void setCurrentLife(int valCurrentLife);

    virtual int getAttack() const;
    virtual void setAttack(int valAttack);

    virtual int getArmor() const;
    virtual void setArmor(int valArmor);

    virtual int getSpeed() const;
    virtual void setSpeed(int valSpeed);

    virtual bool isAlive() const;
    virtual void takeDamage(int dmg);
};