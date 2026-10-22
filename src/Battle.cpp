#include <Battle.h>
#include <vector>

Battle::Battle(Player* player, Enemy* enemy, unsigned int turno) : player(player), enemy(enemy), turno(1) {}

ç
bool Battle::isBattleGoing(){
    std::vector<Character> orderOfPreference;
    
    unsigned int PreferencePlayer = 
    unsigned int PreferenceEnemy  = 


    do{
        
        

    }while();

}



void Battle::nextTurn() {
    this->turno++;
}

bool Battle::isBattleOver() {
    if(player->getCurrentLife() <= 0) {
        return true;
    } else if(enemy->getCurrentLife() <= 0 && player->getCurrentLife() > 0){
        return false;
    }
}

void Battle::calcDamage() {
    
}