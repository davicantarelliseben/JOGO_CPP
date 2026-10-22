#include "include/Character.h"
#include "include/Player.h"
#include "include/Inventory.h"
#include "include/Item.h"
#include "include/Battle.h"
#include "include/Enemy.h"

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

int main() {

    std::string selected= "";

    Item espada(5,5,5,5);

    std::vector<Item> slots;
    unsigned int tamanhoMaximo = 10;

    Inventory inv(slots,tamanhoMaximo,nullptr,&espada);

    inv.addItem(espada);

    Player c1(10,10,10,10,10,4,inv);

    std::cout << c1.getMaxLife() << '\n';
    std::cout << c1.getAttack() << '\n';
    std::cout << c1.getArmor() << '\n';
    std::cout << c1.getSpeed() << '\n';

      while(selected != "stop" ){
        std::cout << "\n--- MENU ---" << std::endl;
        std::cout << "Digite 'battle' para iniciar batalha ou 'stop' para sair : ";
        std::cin >> selected;

        if(selected == "battle"){
            std::cout << "iniciando batalha..." << std::endl;
            
            Enemy Urso(10,10,1,10,1,BEAR,1);//Enemy(unsigned int max_life, unsigned int currentLife, unsigned int attack, unsigned int armor, unsigned int speed, enemyType type, unsigned int level);
            Battle batalha(&c1,&Urso,1);//Battle::Battle(Player* player, Enemy* enemy, unsigned int turno) : player(player), enemy(enemy), turno(1)

           batalha.battleGoing();
        }
    }

  
    return 0;
}