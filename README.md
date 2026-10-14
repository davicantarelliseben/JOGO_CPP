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

#### Opções na batalha :

- ATACAR (vai aparecer 4 ataques diferentes que o [[Personagem]] aprendeu durante o jogo cada Golpe tem sua acurácia mas não o dano(Estilo pokemon), Ataca primeiro aquele que tiver velocidade maior )
- USAR ITENS (Abre uma lista de itens que tem na mochila)
- FUGIR (Depende na sua velocidade e constituicão)
- CONVERSAR (Carisma,Inteligência e Sabedoria) //Opções de conversa(ideia)
- MAGIAS (Caso seja uma das [[Classes]] mágicas é habilitado para utilizar a lista de magias que o [[Personagem]] pode utilizar)

#### Condições de Acabar a batalha :
1. Derrotar o(s) inimigos
2. fugir
3. Conversar
4. Ser derrotado


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

