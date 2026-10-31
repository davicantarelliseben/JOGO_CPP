#include "../include/Player.h"
#include "../include/ItemManager.h"
#include "../include/Event.h"
#include "../include/Map.h"
#include "../include/Enemy.h"
#include <iostream>
#include <cctype>

int main() {
    ItemManager itemManager;
    itemManager.loadItemsFromJson("Woodland_items.json");

    Inventory inventario({}, 6);
    Player player("Guerreiro", 30, 30, 5, 2, 3, 30, inventario);

    Map gameMap;
    if (!gameMap.loadFromFile("grid.txt")) {
        return 1;
    }

    // Posição inicial do jogador (Spawn)
    int playerY = 3;
    int playerX = 3;

    // Raio de visão base do jogador (expande no dia e encurta à noite)
    const int baseVisionRadius = 3;

    // Popula o mapa com os eventos e inimigos
    gameMap.populateEventsAndBattles(playerY, playerX, &player, &itemManager);

    // Revela a área inicial ao redor do spawn antes do primeiro loop
    int initialVision = baseVisionRadius + gameMap.getVisionBonus();
    if (initialVision < 1) initialVision = 1;
    gameMap.revealAroundPlayer(playerY, playerX, initialVision);

    char comando;
    bool jogando = true;

    while (jogando) {
        // Exibe o mapa com o Player (P) destacado e o status da névoa/ciclo
        gameMap.printMap(playerY, playerX);

        std::cout << "Posicao Atual: (" << playerY << ", " << playerX << ")\n";
        std::cout << "Mover: [W] Cima | [S] Baixo | [A] Esquerda | [D] Direita | [I] Inventario/Stats | [Q] Sair\n";
        std::cout << "Escolha uma acao: ";
        std::cin >> comando;

        comando = std::tolower(comando);

        if (comando == 'q') {
            jogando = false;
            std::cout << "Saindo do jogo...\n";
            break;
        }

        // Opção para visualizar os atributos e inventário
        if (comando == 'i') {
            std::cout << "\n======================================================\n";
            std::cout << "               STATUS E INVENTARIO                   \n";
            std::cout << "======================================================\n";
            player.printStats();
            std::cout << "------------------------------------------------------\n";
            player.printInventory();
            std::cout << "======================================================\n\n";

            std::cout << "Pressione qualquer tecla + ENTER para fechar a mochila: ";
            char pausa;
            std::cin >> pausa;
            continue;
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
            // Move o jogador e atualiza o raio de visão aplicando os bônus/penalidades do ciclo
            if (gameMap.movePlayer(playerY, playerX, dir, baseVisionRadius)) {
                
                // Checa e processa o conteúdo do tile (Inimigo ou Evento)
                gameMap.checkTileContent(playerY, playerX, &player, &itemManager);

                // Encerra a partida se o jogador for derrotado
                if (!player.isAlive()) {
                    std::cout << "\n\033[1;31m>>> FIM DE JOGO: O seu heroi foi derrotado! <<<\033[0m\n";
                    jogando = false;
                }
            }
        }
    }

    return 0;
}