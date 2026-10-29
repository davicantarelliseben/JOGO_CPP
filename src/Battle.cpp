#include "Battle.h"
#include "Inventory.h"
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
    int vidaMax;
    int ataque;
    int armadura;
    int velocidade;
};

void pausa(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

Lutador criarLutador(Player* player) {
    return {player, player->getName(), player->getTotalMaxLife(),
            player->getTotalAttack(), player->getTotalArmor(),
            player->getTotalSpeed()};
}

Lutador criarLutador(Enemy* enemy) {
    return {enemy, "Inimigo", enemy->getMaxLife(), enemy->getAttack(),
            enemy->getArmor(), enemy->getSpeed()};
}

void mostrarStatus(const Lutador& a, const Lutador& b) {
    std::cout << "  " << a.nome << ": " << a.c->getCurrentLife() << "/" << a.vidaMax
              << " HP | " << a.armadura << " ARM"
              << "      " << b.nome << ": " << b.c->getCurrentLife() << "/" << b.vidaMax
              << " HP | " << b.armadura << " ARM\n";
}

void atacar(Lutador& atk, Lutador& def) {
    const int ataque = std::max(0, atk.ataque);
    const int armadura = std::max(0, def.armadura);
    const int dano = std::max(0, ataque - armadura);
    const int absorvido = ataque - dano;

    def.c->takeDamage(dano);

    std::cout << "  " << atk.nome << " ataca " << def.nome << ": "
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

    Lutador p = criarLutador(player);
    Lutador e = criarLutador(enemy);
    const bool jogadorComeca = p.velocidade >= e.velocidade;

    std::cout << "\n=== BATALHA! "
              << (jogadorComeca ? p.nome : e.nome)
              << " e mais rapido e comeca ===\n";
    mostrarStatus(p, e);

    while (isBattleOver() == 0 && turno <= LIMITE_TURNOS) {
        std::cout << "\n--- Turno " << turno << " ---\n";

        calcDamage();
        pausa(500);
        mostrarStatus(p, e);
        if (isBattleOver() != 0) break;
        nextTurn();
    }

    mostrarStatus(p, e);
    switch (isBattleOver()) {
        case 1:  std::cout << p.nome << " venceu!!\n"; break;
        case 2:  std::cout << "Inimigo venceu!!\n"; break;
        default: std::cout << "Empate (limite de turnos)\n"; break;
    }
}

void Battle::nextTurn() {
    this->turno++;
}

void Battle::calcDamage() {
    Lutador p = criarLutador(player);
    Lutador e = criarLutador(enemy);
    Lutador* primeiro = (p.velocidade >= e.velocidade) ? &p : &e;
    Lutador* segundo = (primeiro == &p) ? &e : &p;

    atacar(*primeiro, *segundo);
    if (isBattleOver() == 0) {
        atacar(*segundo, *primeiro);
    }
}

int Battle::isBattleOver() {
    if (!player->isAlive()) return 2;
    if (!enemy->isAlive()) return 1;
    return 0;
}
