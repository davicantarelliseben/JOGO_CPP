#include "Player.h"
#include "ItemManager.h"
#include "Event.h"
#include "Map.h"
#include <iostream>

int main() {
    std::cout << "========================================================\n";
    std::cout << "   SISTEMA DE EVENTOS BASEADO NAS ESPECIFICACOES        \n";
    std::cout << "========================================================\n\n";

    ItemManager itemManager;
    if (itemManager.loadItemsFromJson("Woodland_items.json")) {
        std::cout << "Itens carregados com sucesso! Total: " << itemManager.getAllItems().size() << "\n";
    }

    // Criando jogador inicial com 30 moedas e 6 slots de inventario
    Inventory inventario({}, 6, nullptr, nullptr);
    Player player("Guerreiro", 30, 20, 5, 2, 3, 30, inventario);

    // Equipando uma espada inicial na posicao 0
    player.addItem(Item(1, "Espada de Ferro", "Common", 0, 4, 0, 0));
    player.equipWeapon(0);

    Map map(30, true);

    std::cout << "\n--- Status Inicial do Jogador ---\n";
    player.printStats();
    player.printInventory();

    // 1. Evento: treasureChest
    // Roleta uma raridade e mostra 3 itens diferentes dessa raridade pro player escolher
    std::cout << "\n>>> [1/7] Executando Evento: treasureChest...\n";
    Event evBau(treasureChest, &player, &itemManager, &map, false);
    evBau.triggerEvent(treasureChest);

    // 2. Evento: bladeOils
    // Pode escolher um pra buffar a arma atual, nao pode repetir o mesmo oleo e quando troca de arma perde todos oleos
    std::cout << "\n>>> [2/7] Executando Evento: bladeOils (Aplicando 1o oleo)...\n";
    Event evOleo(bladeOils, &player, &itemManager, &map, false);
    evOleo.triggerEvent(bladeOils);

    // Tentando aplicar novamente (deve aplicar outro oleo sem repetir o mesmo oleo)
    std::cout << "\n>>> [2/7 - Cont.] Executando bladeOils novamente (aplicando 2o oleo diferente)...\n";
    evOleo.triggerEvent(bladeOils);

    // Testando a regra: "quando troca de arma perde todos oleos"
    std::cout << "\n>>> Testando troca de arma: adicionando 'Lanca Antiga' e equipando...\n";
    player.addItem(Item(2, "Lanca Antiga", "Common", 0, 5, 0, 1));
    std::cout << "Arma antes da troca: " << player.getWeapon()->getName() << "\n";
    std::cout << "Tem oleo de ataque? " << (player.getWeapon()->hasAttackOil() ? "Sim" : "Nao") << "\n";
    
    // Troca para o novo item
    player.equipWeapon(player.getInventory().getItemCount() - 1);
    std::cout << "Arma apos a troca: " << player.getWeapon()->getName() << "\n";
    std::cout << "Oleo preservado na nova arma? " << (player.getWeapon()->hasAttackOil() ? "Sim" : "Nao (Perdeu todos os oleos como especificado)") << "\n";

    // 3. Evento: campfire
    // Cura um pouco de vida e da +3 de vida maxima
    std::cout << "\n>>> [3/7] Executando Evento: campfire...\n";
    Event evFogueira(campfire, &player, &itemManager, &map, false);
    evFogueira.triggerEvent(campfire);

    // 4. Evento: forge
    // Da +1 de attack permanente pro jogador
    std::cout << "\n>>> [4/7] Executando Evento: forge...\n";
    Event evForja(forge, &player, &itemManager, &map, false);
    evForja.triggerEvent(forge);

    // 5. Evento: golem
    // Da +1 de armadura permanente pro jogador
    std::cout << "\n>>> [5/7] Executando Evento: golem...\n";
    Event evGolem(golem, &player, &itemManager, &map, false);
    evGolem.triggerEvent(golem);

    // 6. Evento: lookoutTower
    // Revela o mapa em torno do jogador e da +1 de speed permanente pro jogador
    std::cout << "\n>>> [6/7] Executando Evento: lookoutTower...\n";
    Event evTorre(lookoutTower, &player, &itemManager, &map, false);
    evTorre.triggerEvent(lookoutTower);

    // 7. Evento: travellingMerchant
    // Oferece 8 itens pro jogador comprar:
    // 4 primeiras opcoes: 5 moedas, Common
    // Posicoes 5, 6 e 7: 10 moedas, Rare
    // Ultima posicao (8): 15 moedas, Heroic
    std::cout << "\n>>> [7/7] Executando Evento: travellingMerchant...\n";
    Event evMercador(travellingMerchant, &player, &itemManager, &map, false);
    evMercador.triggerEvent(travellingMerchant);

    std::cout << "\n========================================================\n";
    std::cout << "             STATUS FINAL DO JOGADOR                    \n";
    std::cout << "========================================================\n";
    player.printStats();
    player.printInventory();

    return 0;
}
