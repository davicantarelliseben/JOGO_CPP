#include "../include/Player.h"
#include "../include/ItemManager.h"
#include "../include/Event.h"
#include "../include/Map.h"
#include "../include/Enemy.h"
#include <iostream>

int main() {
    ItemManager itemManager;
    itemManager.loadItemsFromJson("Woodland_items.json");

    Inventory inventario({}, 6);
    Player player("Guerreiro", 30, 20, 5, 2, 3, 30, inventario);

    Map gameMap;
    if (!gameMap.loadFromFile("grid.txt")) {
        return 1;
    }

    // Posição inicial do jogador (Spawn)
    int playerY = 3;
    int playerX = 3;

    gameMap.populateEventsAndBattles(playerY, playerX, &player, &itemManager);

    char comando;
    bool jogando = true;

    while (jogando) {
        // Exibe o mapa com o Player (P) destacado
        gameMap.printMap(playerY, playerX);

        std::cout << "Posicao Atual: (" << playerY << ", " << playerX << ")\n";
        std::cout << "Mover: [W] Cima | [S] Baixo | [A] Esquerda | [D] Direita | [Q] Sair\n";
        std::cout << "Escolha uma acao: ";
        std::cin >> comando;

        comando = std::tolower(comando);

        if (comando == 'q') {
            jogando = false;
            std::cout << "Saindo do jogo...\n";
            break;
        }

        Direction dir;
        bool direcaoValida = true;

        switch (comando) {
            case 'w': dir = Direction::UP; break;
            case 's': dir = Direction::DOWN; break;
            case 'a': dir = Direction::LEFT; break;
            case 'd': dir = Direction::RIGHT; break;
            default:
                std::cout << ">> Comando invalido!\n";
                direcaoValida = false;
                break;
        }

        if (direcaoValida) {
            // Se conseguir mover o jogador para a nova coordenada
            if (gameMap.movePlayer(playerY, playerX, dir)) {
                
                // Processa batalhas ou eventos presentes no tile atual e limpa a célula
                gameMap.checkTileContent(playerY, playerX, &player, &itemManager);

                // Checa se o jogador morreu durante uma batalha
                if (!player.isAlive()) {
                    std::cout << "\n\033[1;31m>>> FIM DE JOGO: O seu heroi foi derrotado! <<<\033[0m\n";
                    jogando = false;
                }
            }
        }
    }

    return 0;
}