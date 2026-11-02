#include "../include/Event.h"
#include "../include/Player.h"
#include "../include/ItemManager.h"
#include "../include/Map.h"
#include "../include/Item.h"
#include "../include/Inventory.h"
#include "../include/GameItemException.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

Event::Event(eventType type, Player* player, ItemManager* itemManager, Map* map, bool interactive)
    : type(type), player(player), itemManager(itemManager), map(map), interactive(interactive) {}

eventType Event::getEventType() const {
    return this->type;
}

void Event::setEventType(eventType newType) {
    this->type = newType;
}

void Event::setPlayer(Player* p) {
    this->player = p;
}

void Event::setItemManager(ItemManager* im) {
    this->itemManager = im;
}

void Event::setMap(Map* m) {
    this->map = m;
}

void Event::setInteractive(bool active) {
    this->interactive = active;
}

bool Event::isInteractive() const {
    return this->interactive;
}

void Event::triggerEvent(Player& p, ItemManager* im, Map* m) {
    this->player = &p;
    if (im != nullptr) this->itemManager = im;
    if (m != nullptr) this->map = m;
    triggerEvent(this->type);
}

void Event::triggerEvent(eventType newType, Player& p, ItemManager* im, Map* m) {
    this->type = newType;
    triggerEvent(p, im, m);
}

void Event::triggerEvent(eventType newType) {
    this->type = newType;
    switch (this->type) {
    case treasureChest:
        handleTreasureChest();
        break;
    case bladeOils:
        handleBladeOils();
        break;
    case campfire:
        handleCampfire();
        break;
    case forge:
        handleForge();
        break;
    case golem:
        handleGolem();
        break;
    case lookoutTower:
        handleLookoutTower();
        break;
    case travellingMerchant:
        handleTravellingMerchant();
        break;
    default:
        std::cout << "[Evento Desconhecido]: Nada aconteceu.\n";
        break;
    }
}

Event* Event::createRandomEvent(Player* player, ItemManager* itemManager, Map* map, bool interactive) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::discrete_distribution<int> dist({ 40, 15, 20, 10, 10, 3, 8 });

    int indiceSorteado = dist(gen);
    eventType selectedType = static_cast<eventType>(indiceSorteado);

    return new Event(selectedType, player, itemManager, map, interactive);
}

// ---------------------------------------------------------------------------
// 1. Treasure Chest
// ---------------------------------------------------------------------------
void Event::handleTreasureChest() {
    try {
        if (player == nullptr) {
            throw GameItemException("Jogador nao configurado para o evento Bau de Tesouro!");
        }
        if (itemManager == nullptr) {
            throw GameItemException("ItemManager nao disponivel para carregar itens do bau!");
        }

        std::string raridadeSorteada = itemManager->getRandomRarity();
        std::cout << "\n======================================================\n";
        std::cout << " [EVENTO]: Bau de Tesouro (Treasure Chest)\n";
        std::cout << " Raridade sorteada para o bau: [" << raridadeSorteada << "]\n";
        std::cout << "======================================================\n";

        std::vector<Item> opcoes = itemManager->getDistinctItemsByRarity(raridadeSorteada, 3);
        if (opcoes.empty()) {
            throw GameItemException("Nenhum item encontrado no catalogo para a raridade " + raridadeSorteada);
        }

        // Exibe apenas armas (isWeapon()) em vermelho negrito
        auto exibirOpcao = [](int num, const Item& item) {
            std::cout << " [" << num << "] ";
            if (item.isWeapon()) {
                std::cout << "\033[1;31m" << item.getName()
                          << " [" << item.getRarity() << "]"
                          << " | VIDA " << (item.getLife() >= 0 ? "+" : "") << item.getLife()
                          << " | ATK "  << (item.getAttack() >= 0 ? "+" : "") << item.getAttack()
                          << " | ARM "  << (item.getArmor() >= 0 ? "+" : "") << item.getArmor()
                          << " | SPD "  << (item.getSpeed() >= 0 ? "+" : "") << item.getSpeed()
                          << "\033[0m\n";
            } else {
                std::cout << item.getName()
                          << " [" << item.getRarity() << "]"
                          << " | VIDA " << (item.getLife() >= 0 ? "+" : "") << item.getLife()
                          << " | ATK "  << (item.getAttack() >= 0 ? "+" : "") << item.getAttack()
                          << " | ARM "  << (item.getArmor() >= 0 ? "+" : "") << item.getArmor()
                          << " | SPD "  << (item.getSpeed() >= 0 ? "+" : "") << item.getSpeed() << "\n";
            }
        };

        int numOpcoes = opcoes.size();
        std::cout << "Escolha um dos " << numOpcoes << " itens disponiveis:\n";
        for (int i = 0; i < numOpcoes; ++i) {
            exibirOpcao(i + 1, opcoes[i]);
        }

        int escolha = 1;
        if (interactive) {
            while (true) {
                std::cout << "\nDigite o numero do item desejado (1-" << numOpcoes << "): ";
                if (std::cin >> escolha && escolha >= 1 && escolha <= numOpcoes) {
                    break;
                }
                std::cout << ">> Opcao invalida! Digite um numero entre 1 e " << numOpcoes << ".\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        } else {
            auto pontuarItem = [](const Item& it) {
                return it.getLife() + it.getAttack() * 2 + it.getArmor() * 2 + it.getSpeed();
            };
            int melhorIndice = 0;
            int maiorScore = pontuarItem(opcoes[0]);
            for (int i = 1; i < numOpcoes; ++i) {
                int score = pontuarItem(opcoes[i]);
                if (score > maiorScore) {
                    maiorScore = score;
                    melhorIndice = i;
                }
            }
            escolha = melhorIndice + 1;
            std::cout << ">> Escolha do jogador: [" << escolha << "] " << opcoes[escolha - 1].getName() << "\n";
        }

        Item itemEscolhido = opcoes[escolha - 1];

        // Lógica de substituição exclusiva para Armas
        if (itemEscolhido.isWeapon()) {
            std::cout << "\n\033[1;31m[ARMA ENCONTRADA]: '" << itemEscolhido.getName() 
                      << "' possui " << itemEscolhido.getAttack() << " de ATK.\033[0m\n";
            std::cout << "Deseja equipa-la agora e descartar a sua arma atual? [S/N]: ";
            
            char resp;
            if (interactive && std::cin >> resp && (resp == 's' || resp == 'S')) {
                player->addItem(itemEscolhido);
                int ultimoSlot = player->getInventory().getItemCount() - 1;
                player->equipWeaponFromSlot(ultimoSlot);
            } else {
                std::cout << ">> Voce deixou a arma para tras.\n";
            }
        } 
        else {
            if (!player->addItem(itemEscolhido)) {
                std::cout << ">> Mochila cheia! Nao foi possivel guardar o item.\n";
            } else {
                std::cout << ">> Item '" << itemEscolhido.getName() << "' guardado na mochila com sucesso!\n";
            }
        }

    } catch (const GameItemException& e) {
        std::cerr << "[GameItemException no Bau]: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[Excecao Padrao no Bau]: " << e.what() << "\n";
    }
}

// ---------------------------------------------------------------------------
// 2. Blade Oils
// ---------------------------------------------------------------------------
void Event::handleBladeOils() {
    try {
        if (player == nullptr) {
            throw GameItemException("Jogador invalido no evento Oleos de Lamina!");
        }

        const Item* arma = player->getWeapon();

        if (arma == nullptr) {
            throw GameItemException("O jogador nao possui nenhuma arma equipada para aplicar oleos!");
        }

        std::cout << "\n======================================================\n";
        std::cout << " [EVENTO]: Oleos de Lamina (Blade Oils)\n";
        std::cout << " Arma Atual Equipada: \033[1;31m" << arma->getName() << "\033[0m\n";
        std::cout << "======================================================\n";
        arma->printItem();

        auto oleoJaAplicado = [arma](int tipo) -> bool {
            if (tipo == 1) return arma->hasAttackOil();
            if (tipo == 2) return arma->hasArmorOil();
            if (tipo == 3) return arma->hasSpeedOil();
            return false;
        };

        auto getNomeOleo = [](int tipo) -> std::string {
            if (tipo == 1) return "Oleo de Ataque (+1 ATK)";
            if (tipo == 2) return "Oleo de Armadura (+1 ARM)";
            if (tipo == 3) return "Oleo de Velocidade (+1 SPD)";
            return "Desconhecido";
        };

        std::cout << "Oleos disponiveis para refinar a arma:\n";
        for (int i = 1; i <= 3; ++i) {
            std::cout << " [" << i << "] " << getNomeOleo(i);
            if (oleoJaAplicado(i)) {
                std::cout << " [JA APLICADO - NAO PODE REPETIR]";
            }
            std::cout << "\n";
        }

        int escolhaOleo = 1;
        if (interactive) {
            while (true) {
                std::cout << "\nEscolha um oleo (1, 2 ou 3): ";
                if (std::cin >> escolhaOleo && escolhaOleo >= 1 && escolhaOleo <= 3) {
                    if (oleoJaAplicado(escolhaOleo)) {
                        std::cout << ">> Este oleo ja foi aplicado nesta arma! Escolha outro.\n";
                        continue;
                    }
                    break;
                }
                std::cout << ">> Opcao invalida! Digite 1, 2 ou 3.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        } else {
            bool encontrado = false;
            for (int i = 1; i <= 3; ++i) {
                if (!oleoJaAplicado(i)) {
                    escolhaOleo = i;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                std::cout << ">> A arma atual ja possui todos os oleos aplicados!\n";
                return;
            }
            std::cout << ">> Escolha do oleo: [" << escolhaOleo << "] " << getNomeOleo(escolhaOleo) << "\n";
        }

        if (!player->applyWeaponOil(escolhaOleo)) {
            throw GameItemException("Falha ao aplicar oleo na arma atual!");
        }

        std::cout << ">> Sucesso! " << getNomeOleo(escolhaOleo) << " aplicado em '\033[1;31m" << arma->getName() << "\033[0m'!\n";
        arma->printItem();

    } catch (const GameItemException& e) {
        std::cerr << "[GameItemException em Oleos de Lamina]: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[Excecao Padrao em Oleos de Lamina]: " << e.what() << "\n";
    }
}

// ---------------------------------------------------------------------------
// 3. Campfire
// ---------------------------------------------------------------------------
void Event::handleCampfire() {
    try {
        if (player == nullptr) {
            throw GameItemException("Jogador invalido no evento Acampamento!");
        }

        std::cout << "\n======================================================\n";
        std::cout << " [EVENTO]: Acampamento (Campfire)\n";
        std::cout << "======================================================\n";

        auto calcularCura = [](unsigned int maxHp) -> unsigned int {
            return std::max(8u, maxHp / 4);
        };

        unsigned int cura = calcularCura(player->getTotalMaxLife());

        player->addMaxLife(3);
        player->heal(cura);

        std::cout << ">> Voce descansou no acampamento!\n";
        std::cout << ">> Curou " << cura << " de vida e recebeu +3 de VIDA MAXIMA permanente!\n";
        std::cout << "Vida: " << player->getCurrentLife() << " / " << player->getTotalMaxLife() << "\n";

    } catch (const GameItemException& e) {
        std::cerr << "[GameItemException no Acampamento]: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[Excecao Padrao no Acampamento]: " << e.what() << "\n";
    }
}

// ---------------------------------------------------------------------------
// 4. Forge
// ---------------------------------------------------------------------------
void Event::handleForge() {
    try {
        if (player == nullptr) {
            throw GameItemException("Jogador invalido no evento Forja!");
        }

        std::cout << "\n======================================================\n";
        std::cout << " [EVENTO]: Forja (Forge)\n";
        std::cout << "======================================================\n";

        auto forjarAtaque = [](Player* p) {
            p->addAttack(1);
        };

        forjarAtaque(player);

        std::cout << ">> As chamas da forja temperaram seu espirito guerreiro!\n";
        std::cout << ">> +1 de ATAQUE permanente concedido ao jogador!\n";
        std::cout << "Ataque base: " << player->getAttack() << " | Ataque Total: " << player->getTotalAttack() << "\n";

    } catch (const GameItemException& e) {
        std::cerr << "[GameItemException na Forja]: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[Excecao Padrao na Forja]: " << e.what() << "\n";
    }
}

// ---------------------------------------------------------------------------
// 5. Golem
// ---------------------------------------------------------------------------
void Event::handleGolem() {
    try {
        if (player == nullptr) {
            throw GameItemException("Jogador invalido no evento Golem!");
        }

        std::cout << "\n======================================================\n";
        std::cout << " [EVENTO]: Golem de Pedra (Golem)\n";
        std::cout << "======================================================\n";

        auto abencoarArmadura = [](Player* p) {
            p->addArmor(1);
        };

        abencoarArmadura(player);

        std::cout << ">> O Golem tocou seu escudo com sua mao de granito!\n";
        std::cout << ">> +1 de ARMADURA permanente concedido ao jogador!\n";
        std::cout << "Armadura base: " << player->getArmor() << " | Armadura Total: " << player->getTotalArmor() << "\n";

    } catch (const GameItemException& e) {
        std::cerr << "[GameItemException no Golem]: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[Excecao Padrao no Golem]: " << e.what() << "\n";
    }
}

// ---------------------------------------------------------------------------
// 6. Lookout Tower
// ---------------------------------------------------------------------------
void Event::handleLookoutTower() {
    try {
        if (player == nullptr) {
            throw GameItemException("Jogador invalido no evento Torre de Vigia!");
        }

        std::cout << "\n======================================================\n";
        std::cout << " [EVENTO]: Torre de Vigia (Lookout Tower)\n";
        std::cout << "======================================================\n";

        auto revelarMapa = [this]() {
            if (map != nullptr) {
                map->revealAroundPlayer(5); // Revela um raio de 5 tiles ao redor da torre
                map->addSteps(10);
            } else {
                std::cout << ">> Visao panoramica revela o mapa em torno da torre!\n";
            }
        };

        revelarMapa();

        player->addSpeed(1);

        std::cout << ">> Do topo da torre, voce enxerga alem da nevoa!\n";
        std::cout << ">> O conhecimento do relevo concedeu +10 passos e +1 de VELOCIDADE permanente!\n";
        std::cout << "Velocidade base: " << player->getSpeed() << " | Velocidade Total: " << player->getTotalSpeed() << "\n";

    } catch (const GameItemException& e) {
        std::cerr << "[GameItemException na Torre de Vigia]: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[Excecao Padrao na Torre de Vigia]: " << e.what() << "\n";
    }
}

// ---------------------------------------------------------------------------
// 7. Travelling Merchant
// ---------------------------------------------------------------------------
void Event::handleTravellingMerchant() {
    try {
        if (player == nullptr) {
            throw GameItemException("Jogador invalido no evento Mercador Viajante!");
        }
        if (itemManager == nullptr) {
            throw GameItemException("ItemManager nao disponivel para o Mercador Viajante!");
        }

        std::cout << "\n======================================================\n";
        std::cout << " [EVENTO]: Mercador Viajante (Travelling Merchant)\n";
        std::cout << " Moedas atuais do jogador: " << player->getCoins() << "\n";
        std::cout << "======================================================\n";

        struct OfertaMercador {
            Item item;
            int preco;
        };

        std::vector<OfertaMercador> ofertas;

        auto montarOfertas = [&](const std::string& raridade, int quantidade, int preco) {
            std::vector<Item> itens = itemManager->getDistinctItemsByRarity(raridade, quantidade);
            for (const auto& it : itens) {
                ofertas.push_back({it, preco});
            }
        };

        montarOfertas("Common", 4, 5);
        montarOfertas("Rare", 3, 10);
        montarOfertas("Heroic", 1, 15);

        int totalOfertas = ofertas.size();
        if (totalOfertas < 8) {
            throw GameItemException("Nao foi possivel carregar as 8 ofertas do catalogo de itens!");
        }

        auto exibirOfertas = [&ofertas, totalOfertas]() {
            for (int i = 0; i < totalOfertas; ++i) {
                const auto& of = ofertas[i];
                std::cout << " [" << (i + 1) << "] ";

                if (of.item.isWeapon()) {
                    std::cout << "\033[1;31m" << of.item.getName() << " [" << of.item.getRarity() << "]"
                              << " | Preco: " << of.preco << " moedas"
                              << " | VIDA " << (of.item.getLife() >= 0 ? "+" : "") << of.item.getLife()
                              << " | ATK "  << (of.item.getAttack() >= 0 ? "+" : "") << of.item.getAttack()
                              << " | ARM "  << (of.item.getArmor() >= 0 ? "+" : "") << of.item.getArmor()
                              << " | SPD "  << (of.item.getSpeed() >= 0 ? "+" : "") << of.item.getSpeed()
                              << "\033[0m\n";
                } else {
                    std::cout << of.item.getName() << " [" << of.item.getRarity() << "]"
                              << " | Preco: " << of.preco << " moedas"
                              << " | VIDA " << (of.item.getLife() >= 0 ? "+" : "") << of.item.getLife()
                              << " | ATK "  << (of.item.getAttack() >= 0 ? "+" : "") << of.item.getAttack()
                              << " | ARM "  << (of.item.getArmor() >= 0 ? "+" : "") << of.item.getArmor()
                              << " | SPD "  << (of.item.getSpeed() >= 0 ? "+" : "") << of.item.getSpeed() << "\n";
                }
            }
            std::cout << " [0] Nao comprar nada / Sair\n";
        };

        std::cout << "Itens a venda na carroca do mercador:\n";
        exibirOfertas();

        int escolha = -1;

        if (interactive) {
            while (true) {
                std::cout << "\nDigite o numero do item para comprar (1 a 8, ou 0 para sair): ";
                if (std::cin >> escolha && escolha >= 0 && escolha <= 8) {
                    if (escolha == 0) break;

                    const auto& selecionada = ofertas[escolha - 1];
                    if (player->getCoins() < selecionada.preco) {
                        std::cout << ">> Moedas insuficientes! Saldo: " << player->getCoins() 
                                  << ", Preco: " << selecionada.preco << ". Tente outra opcao.\n";
                        continue;
                    }

                    // Se não for arma, valida capacidade da mochila
                    if (!selecionada.item.isWeapon() && player->getInventory().isFull()) {
                        std::cout << ">> Mochila cheia! Nao e possivel comprar este item utilitario.\n";
                        return;
                    }

                    break;
                }

                std::cout << ">> Opcao invalida! Digite um numero entre 0 e 8.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        } else {
            std::cout << ">> Evento executado em modo nao-interativo. Nenhuma compra realizada.\n";
            return;
        }

        if (escolha == 0) {
            std::cout << "Voce se despede do mercador sem comprar nada.\n";
            return;
        }

        const auto& selecionada = ofertas[escolha - 1];

        if (selecionada.item.isWeapon()) {
            std::cout << "\n\033[1;31m[ATENCAO]: '" << selecionada.item.getName() << "' e uma arma.\033[0m\n";
            std::cout << "Ao compra-la, ela sera equipada imediatamente e a sua arma atual sera descartada.\n";
            std::cout << "Deseja confirmar a compra e equipar? [S/N]: ";
            
            char resp;
            if (std::cin >> resp && (resp == 's' || resp == 'S')) {
                player->spendCoins(selecionada.preco);
                player->addItem(selecionada.item);
                
                int ultimoSlot = player->getInventory().getItemCount() - 1;
                player->equipWeaponFromSlot(ultimoSlot);
                
                std::cout << ">> Compra realizada! '\033[1;31m" << selecionada.item.getName() << "\033[0m' foi equipada.\n";
            } else {
                std::cout << ">> Compra cancelada pelo jogador.\n";
            }
        } 
        else {
            player->spendCoins(selecionada.preco);
            player->addItem(selecionada.item);
            std::cout << ">> Compra realizada com sucesso! '" << selecionada.item.getName()
                      << "' guardado na mochila por " << selecionada.preco << " moedas!\n";
        }

    } catch (const GameItemException& e) {
        std::cerr << "[GameItemException no Mercador]: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[Excecao Padrao no Mercador]: " << e.what() << "\n";
    }
}