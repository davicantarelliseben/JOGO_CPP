# JOGO_C-
Jogo desenvolvido em C++ na cadeira de Programação Orientada a Objetos

### Mecânicas  do nosso jogo : 
##### Atríbutos (usados em batalha) 

- VIDA (A vida que é setada pelos [[Atríbutos]] Iniciais e da classe(Que mudará os Atríbutos) não muda; **[[Atríbutos]] usados** = Constituição,Nível)
- DANO (Dano é um Atributo das Armas e magias que ao atacar calcula o dano dado as condições e [[Atríbutos]] do jogador; **[[Atríbutos]] usados** = Força,Destreza (outro atributo caso necessite))
- DEFESA (Defesa é um atributo da armadura que "Melhora a defesa do jogador" ele começa com uma certa defesa e dependendo do nível e Equipamento mudará ao longo do jogo; **[[Atríbutos]] usados** = Constituição,força)
- VELOCIDADE (Velocidade é um atributo do Jogador que é dependente dos [[Atríbutos]] e Equipamentos do personagem ; **[[Atríbutos]] usados** = Constituição,Destreza)

##### Variáveis (Usadas em Batalha) 

- ITENS
- ARMAMENTO
- EQUIPAMENTOS (Armaduras, Poções, Armas e etc...)
- MAGIAS

## Batalha :

#### Batalha automatica:

- Os combatentes atacam em sequencia sem comandos durante a luta.
- A velocidade determina quem ataca primeiro em cada rodada.
- A armadura absorve o dano antes de ele reduzir a vida.
- Uma pocao da mochila e consumida automaticamente quando a vida chega a 40% ou menos.
- Itens e equipamentos encontrados alteram os atributos e o resultado das batalhas.

#### Condições de Acabar a batalha :
1. Derrotar o inimigo
2. Ser derrotado


### Elementos que aparecem na HUB durante a Batalha : 

##### **Player** & **Enemy**
---
Vida
---
Armadura
---
Mana
---
Velocidade
---


## HUB da Batalha :

<img width="320" height="180" alt="New Piskel-1 png" src="https://github.com/user-attachments/assets/d3f802ce-8b93-438f-a6f5-d7a562cc5989" />

## Versao jogavel com raylib

O jogo abre em uma janela 1280x800. Compile a partir da raiz do repositorio:

```sh
make -C src
./src/jogo
```

O raylib e necessario para compilar e executar. O jogo le `Woodland_items.json`
da raiz do repositorio e interpreta os atributos dentro de `stats`; valores em
formato de progressao, como `"2 / 4 / 8"`, usam o primeiro valor.

### Controles

- **Setas esquerda/direita**: escolher a arma inicial.
- **WASD** ou **setas**: mover pelo mapa.
- **I**: abrir/fechar a mochila.
- **Setas esquerda/direita** e **Enter**: escolher uma recompensa.
- **Espaco** ou **Enter**: iniciar o jogo.

O mapa em matriz tem obstaculos, bau, fogueira, mercador, marco, fada e o
Guardiao da Floresta. Cada passo avanca o ciclo dia/noite e pode atrair inimigos.
As batalhas sao automaticas: a velocidade define quem ataca primeiro, os
combatentes atacam em sequencia e a armadura absorve dano antes da vida. Uma
pocao e usada automaticamente quando a vida do jogador chega a 40% ou menos.
