#include "include/Battle.h"
#include <vector>
#include <iostream>

Battle::Battle(Player* player, Enemy* enemy, unsigned int turno) : player(player), enemy(enemy), turno(1) {
    //pensei em quando se constroi a batalha ela executa um metodo batalha para comecar a batalha e loudar a batalha em si
}


void Battle::battleGoing(){

        //1)Aparecer em tela os elementos e stats 

        //Turno :
        unsigned int turno = turno;

        //atributos player :
        unsigned int pML = player->getMaxLife();
        unsigned int pCL = player->getCurrentLife();
        unsigned int pATK = player->getAttack();
        unsigned int pARM = player->getArmor();
        unsigned int pSP = player->getSpeed();

        //atributos enemy :

        unsigned int eML = enemy->getMaxLife();
        unsigned int eCL = enemy->getCurrentLife();
        unsigned int eATK = enemy->getAttack();
        unsigned int eARM = enemy->getArmor();
        unsigned int eSP = enemy->getSpeed();

        //Fila de prioridade :
        std::vector<Character> charactersTurns;
        
        if(player->getSpeed() >= enemy->getSpeed()){
            charactersTurns.push_back(*player);
            charactersTurns.push_back(*enemy);
        }else {
            charactersTurns.push_back(*enemy);
            charactersTurns.push_back(*player); 
        }

        Character firstCha = charactersTurns[0];
        Character secondCha = charactersTurns[1];

        //2) Puxar todos os buffs dos itens 


        std::cout << firstCha.getAttack() << " " << secondCha.getAttack() << std::endl;
    //depois fazer a implementação da tela (como faremos não tenho menor ideia)
    do{

        secondCha.takeDamage(firstCha);
        isBattleOver();
        firstCha.takeDamage(secondCha);
        isBattleOver();
        nextTurn();
        //2) Começa o turno e quem vier primeiro ataca e sege

    }while(isBattleOver() == 0);
    
    if(isBattleOver() == 1){std::cout << "Player venceu !!"<< std::endl;}
    else if(isBattleOver() == 2){std::cout << "inimigo venceu !!"<< std::endl;}

    //Vai ter uma funcão de go back pra tela de exploração

}



void Battle::nextTurn() {
    this->turno++;
}

int Battle::isBattleOver() {
    if(player->getCurrentLife() <= 0 && enemy->getCurrentLife() <= 0) {
        //Player venceu
        return 1;
    } else if(enemy->getCurrentLife() <= 0 && player->getCurrentLife() > 0){
        //Enemy venceu
        return 2;
    }else{
        //Nenhum no turno ganhou logo continuar
        return 0;
    }
}

void Battle::calcDamage() {
    
}