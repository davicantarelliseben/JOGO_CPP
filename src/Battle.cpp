#include "Battle.h"
#include "Inventory.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

namespace {

struct Lutador {
    Character* c;
    std::string nome;
    int vidaMax;
    int ataque;
    int escudo;
    int velocidade;
};

void pausa(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void mostrarStatus(const Lutador& a, const Lutador& b) {
    std::cout << "  " << a.nome << ": " << a.c->getCurrentLife() << "/" << a.vidaMax
              << " HP | " << a.escudo << " ARM"
              << "      " << b.nome << ": " << b.c->getCurrentLife() << "/" << b.vidaMax
              << " HP | " << b.escudo << " ARM\n";
}

void atacar(Lutador& atk, Lutador& def) {
    int dano = atk.ataque;
    int absorvido = std::min(dano, def.escudo);
    def.escudo -= absorvido;
    dano -= absorvido;

    def.c->takeDamage(dano);

    std::cout << "  " << atk.nome << " ataca " << def.nome << ": "
              << atk.ataque << " de dano";
    if (absorvido > 0) std::cout << " (" << absorvido << " bloqueado pela armadura)";
    std::cout << "\n";
}

} // namespace

Battle::Battle(Player* player, Enemy* enemy, int turno)
    : turno(turno), player(player), enemy(enemy) {}

void Battle::battleGoing() {
    const int LIMITE_TURNOS = 100;

    Lutador p{player, "Jogador",
              player->getTotalMaxLife(), player->getTotalAttack(),
              player->getTotalArmor(),   player->getTotalSpeed()};

    Lutador e{enemy, "Inimigo",
              enemy->getMaxLife(), enemy->getAttack(),
              enemy->getArmor(),   enemy->getSpeed()};

    Lutador* primeiro = (p.velocidade >= e.velocidade) ? &p : &e;
    Lutador* segundo  = (primeiro == &p) ? &e : &p;

    std::cout << "\n=== BATALHA! " << primeiro->nome << " e mais rapido e comeca ===\n";
    mostrarStatus(p, e);

    while (isBattleOver() == 0 && turno <= LIMITE_TURNOS) {
        std::cout << "\n--- Turno " << turno << " ---\n";

        atacar(*primeiro, *segundo);
        pausa(500);
        if (isBattleOver() != 0) break;

        atacar(*segundo, *primeiro);
        pausa(500);

        mostrarStatus(p, e);
        nextTurn();
    }

    mostrarStatus(p, e);
    switch (isBattleOver()) {
        case 1:  std::cout << "Jogador venceu!!\n"; break;
        case 2:  std::cout << "Inimigo venceu!!\n"; break;
        default: std::cout << "Empate (limite de turnos)\n"; break;
    }
}

void Battle::nextTurn() {
    this->turno++;
}

void Battle::calcDamage() {
    if (player == nullptr || enemy == nullptr) return;

    int danoJogador = player->getTotalAttack();
    int danoInimigo = enemy->getAttack();

    int defesaJogador = player->getTotalArmor();
    int defesaInimigo = enemy->getArmor();

    danoJogador = std::max(0, danoJogador - defesaInimigo);
    danoInimigo = std::max(0, danoInimigo - defesaJogador);

    int vidaJogador = std::max(0, player->getCurrentLife() - danoInimigo);
    int vidaInimigo = std::max(0, enemy->getCurrentLife() - danoJogador);

    player->setCurrentLife(vidaJogador);
    enemy->setCurrentLife(vidaInimigo);
}

int Battle::isBattleOver() {
    if (player->getCurrentLife() == 0) return 2;
    if (enemy->getCurrentLife() == 0) return 1;
    return 0;
}
