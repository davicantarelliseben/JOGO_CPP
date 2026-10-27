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

    std::string Aventureiro;
    std::string selected= "";
    bool isPlayerReal = false;
    int selectedItem;
    

    Item espada("Espada Legal",1,1,1,1);
    Item Arma2("Cintaralho Explosivo",3,4,0,10);
    Item graveto = Item("Graveto",0,1,0,0);

    std::vector<Item> kitInicial = {espada,Arma2,graveto};

    std::vector<Item> slots;
    unsigned int tamanhoMaximo = 10;

    Inventory inv(slots,tamanhoMaximo,nullptr,nullptr);

    Player *player =  new Player(Aventureiro,10,10,0,0,0,0,inv);


      while(selected != "stop" ){
        std::cout << "\n--- MENU ---" << std::endl;
        
        std::cout << "Digite 'battle' para iniciar batalha ou 'stop' para sair (Caso não tenha criado algum personagem digite : 'create' ) : ";
        std::cin >> selected;

        if(selected == "create"){
            std::cout << "Fale o nome do seu Aventureiro : ";
            std::cin >> Aventureiro;
            
        }else if(selected == "battle"){
            std::cout << "iniciando batalha..." << std::endl;
            
            Enemy Urso(20,20,2,2,2,BEAR,1);//Enemy(unsigned int max_life, unsigned int currentLife, unsigned int attack, unsigned int armor, unsigned int speed, enemyType type, unsigned int level);
            Urso.Buff(BEAR);
            
            Battle batalha(player,&Urso,1);//Battle::Battle(Player* player, Enemy* enemy, unsigned int turno) : player(player), enemy(enemy), turno(1)

           batalha.battleGoing();//isso começa a batalha 

        }else if(selected == "stats"){
            player->printStats();
            std::cout << std::endl;
            inv.printInventory();

        }else if(selected == "heal"){
            std::cout << "Vida Curada : de " << player->getCurrentLife() << " => para =>" ;
            player->fullHeal();
            std::cout << player->getCurrentLife() << "\n";

        }else if(selected == "itens"){
            player->printInventory();

        }else if(selected == "iniciar"){
            
            std::cout << "Escolha seu item inicial :" << "\n";
            for(int i = 0 ; i < kitInicial.size(); i++){
                std::cout << i + 1 << ". "; 
                kitInicial[i].printItem();
            }
            
            int k;

            std::cout << "Selecione seu item inicial 1-" << kitInicial.size() <<": ";
            std::cin >> k;

            player->addItem(kitInicial.at(k - 1));

        }else if (selected == "remover"){
            unsigned int p;
            player->printInventory();
            std::cout << "\n";

            std::cout << "Digite o item que será removido :"; std::cin >> p ;
            player->removeItem(p - 1);
        }
        
    }

  
    return 0;
}