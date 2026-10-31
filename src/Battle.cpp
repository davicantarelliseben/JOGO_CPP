#include "../include/Battle.h"
#include "../include/Inventory.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <stdexcept>

namespace {

struct Lutador {
    Character* c;
    std::string nome;

    // Métodos utilitários que sempre pegam os dados atualizados do objeto real
    int getVidaMax() const { return c->getMaxLife(); }
    int getAtaque() const { return c->getAttack(); }
    int getArmadura() const { return c->getArmor(); }
    int getVelocidade() const { return c->getSpeed(); }
};

void pausa(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void mostrarStatus(Player* p, Enemy* e) {
    std::cout << "  " << p->getName() << ": " << p->getCurrentLife() << "/" << p->getTotalMaxLife()
              << " HP | " << p->getTotalArmor() << " ARM"
              << "      Inimigo: " << e->getCurrentLife() << "/" << e->getMaxLife()
              << " HP | " << e->getArmor() << " ARM\n";
}

void atacar(Character* atk, Character* def, const std::string& nomeAtk, const std::string& nomeDef) {
    // Se for o Player, pega o ataque total (incluindo arma, óleos e bônus)
    int ataque = 0;
    Player* pAtk = dynamic_cast<Player*>(atk);
    if (pAtk != nullptr) {
        ataque = std::max(0, pAtk->getTotalAttack());
    } else {
        ataque = std::max(0, atk->getAttack());
    }

    // Se o defensor for o Player, pega a armadura total dele
    int armadura = 0;
    Player* pDef = dynamic_cast<Player*>(def);
    if (pDef != nullptr) {
        armadura = std::max(0, pDef->getTotalArmor());
    } else {
        armadura = std::max(0, def->getArmor());
    }

    const int dano = std::max(0, ataque - armadura);
    const int absorvido = ataque - dano;

    def->takeDamage(dano);

    std::cout << "  " << nomeAtk << " ataca " << nomeDef << ": "
              << dano << " de dano";
    if (absorvido > 0) std::cout << " (" << absorvido << " absorvido pela armadura)";
    std::cout << "\n";
}

} // namespace

Battle::Battle(Player* player, Enemy* enemy, int turno)
    : turno(turno), player(player), enemy(enemy) {
    if (player == nullptr || enemy == nullptr) {
        throw std::invalid_argument("Uma batalha precisa de um jogador e um inimigo validos.");
    }
}

void Battle::battleGoing() {
    const int LIMITE_TURNOS = 100;

    const bool jogadorComeca = player->getTotalSpeed() >= enemy->getSpeed();

    std::cout << "\n=== BATALHA! "
              << (jogadorComeca ? player->getName() : "Inimigo")
              << " e mais rapido e comeca ===\n";
    
    mostrarStatus(player, enemy);

    while (isBattleOver() == 0 && turno <= LIMITE_TURNOS) {
        std::cout << "\n--- Turno " << turno << " ---\n";

        calcDamage();
        pausa(500);
        mostrarStatus(player, enemy);
        
        if (isBattleOver() != 0) break;
        nextTurn();
    }

    std::cout << "\n=== FIM DE BATALHA ===\n";
    switch (isBattleOver()) {
        case 1:  std::cout << player->getName() << " venceu!!\n"; break;
        case 2:  std::cout << "Inimigo venceu!!\n"; break;
        default: std::cout << "Empate (limite de turnos)\n"; break;
    }
}

void Battle::nextTurn() {
    this->turno++;
}

void Battle::calcDamage() {
    bool pMaisRapido = player->getTotalSpeed() >= enemy->getSpeed();

    if (pMaisRapido) {
        atacar(player, enemy, player->getName(), "Inimigo");
        if (isBattleOver() == 0) {
            atacar(enemy, player, "Inimigo", player->getName());
        }
    } else {
        atacar(enemy, player, "Inimigo", player->getName());
        if (isBattleOver() == 0) {
            atacar(player, enemy, player->getName(), "Inimigo");
        }
    }
}

int Battle::isBattleOver() {
    if (!player->isAlive()) return 2;
    if (!enemy->isAlive()) return 1;
    return 0;
}