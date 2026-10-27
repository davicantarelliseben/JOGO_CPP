#include "include/Battle.h"
#include "include/Inventory.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

// ---------------------------------------------------------------------------
// Auxiliares internos da batalha 
// ---------------------------------------------------------------------------
namespace {

struct Lutador {
    Character*   c;
    std::string  nome;
    unsigned int vidaMax;     // base + itens
    unsigned int ataque;      // base + itens
    unsigned int escudo;      // base + itens (gasta durante a luta, volta cheia na proxima)
    unsigned int velocidade;  // base + itens
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

// Estilo He Is Coming: a armadura absorve o dano primeiro e é consumida,
// o que sobrar vai para a vida.
void atacar(Lutador& atk, Lutador& def) {
    unsigned int dano      = atk.ataque;
    unsigned int absorvido = std::min(dano, def.escudo);
    def.escudo -= absorvido;
    dano       -= absorvido;

    def.c->takeDamage(dano);

    std::cout << "  " << atk.nome << " ataca " << def.nome << ": "
              << atk.ataque << " de dano";
    if (absorvido > 0) std::cout << " (" << absorvido << " bloqueado pela armadura)";
    std::cout << "\n";
}

} // namespace

// ---------------------------------------------------------------------------

Battle::Battle(Player* player, Enemy* enemy, unsigned int turno)
    : player(player), enemy(enemy), turno(turno) {}

void Battle::battleGoing() {
    const unsigned int LIMITE_TURNOS = 100;   // evita loop infinito (ex.: ninguém tem ataque)

    // 1) Monta os lutadores com PONTEIROS (nada de copiar o objeto!)
    Lutador p{player, "Jogador",
              player->getTotalMaxLife(), player->getTotalAttack(),
              player->getTotalArmor(),   player->getTotalSpeed()};

    Lutador e{enemy, "Inimigo",
              enemy->getMaxLife(), enemy->getAttack(),
              enemy->getArmor(),   enemy->getSpeed()};

    // 2) Quem tem mais velocidade ataca primeiro (empate = jogador)
    Lutador* primeiro = (p.velocidade >= e.velocidade) ? &p : &e;
    Lutador* segundo  = (primeiro == &p) ? &e : &p;

    // TODO: aqui entram os efeitos de "início de batalha" dos itens

    std::cout << "\n=== BATALHA! " << primeiro->nome << " e mais rapido e comeca ===\n";
    mostrarStatus(p, e);

    // 3) Loop automático: ninguém escolhe nada, cada um ataca no seu turno
    while (isBattleOver() == 0 && turno <= LIMITE_TURNOS) {
        std::cout << "\n--- Turno " << turno << " ---\n";

        atacar(*primeiro, *segundo);
        pausa(500);
        if (isBattleOver() != 0) break;      // morto não revida

        atacar(*segundo, *primeiro);
        pausa(500);

        mostrarStatus(p, e);
        nextTurn();
    }

    // 4) Resultado
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

// 0 = continua | 1 = jogador venceu | 2 = inimigo venceu
int Battle::isBattleOver() {
    if (player->getCurrentLife() == 0) return 2;
    if (enemy->getCurrentLife()  == 0) return 1;
    return 0;
}

