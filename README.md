# Pokemon-No-Arduino-IoT
Repositório criado para versionar o código em C++ utilizado para desenvolver o projeto "Pokemon no Arduino" para cumprir uma disciplina de Desenvolvimento IoT.

## Insight

Dois jogadores se enfrentarão em uma batalha PvP em um jogo inspirado na franquia Pokémon. O "console" será um composto por um Arduino Uno R3, além de sensores e componentes.

## Mecânica do Jogo

Os players terão um time pré definido com 6 Pokémon, dos tipos Luta, Fogo, Água, Fantasma, Psíquico e Normal, e lutarão em turnos até que um dos jogadores reduza as vidas de todos os Pokémon do adversário a 0 ou menos.

Os players terão um Pokémon ativo que poderá atacar e/ou ser atacado. Todos os Pokémon poderão utilizar 6 ataques dos tipos citados acima para causar dano ao Pokémon ativo do oponente, cada Pokémon inicia a batalha com 5 vidas e sofrem dano maior ou menor de acordo com as relações de fraqueza e resistência entre os tipos. Um ataque neutro causa 2 vidas de dano, se o Pokémon utilizar um ataque do mesmo tipo que o seu a mecânica STAB (Same Type Attack Bonus) é ativada e o dano recebe um multiplicador x1.5, além disso, o ataque pode ser super efetivo ou menos efetivo, recebendo multiplicador x2 e x1/2 respectivamente. Atacar encerra o turno do jogador.

Alguns ataques precisarão do acionamento de um sensor específico com limite de tempo após a seleção para concretizar o ataque e acertar o Pokémon adversário, do contrário o ataque será considerado errado e não causará danos. Ataques do tipo Normal não precisarão de sensores e causarão dano automaticamente de acordo com as mecânicas de STAB e Fraqueza e Resistência. Os tipos de ataque a seguir precisarão dos seus respectivos sensores: Luta - Sensor de Distância Ultrassônico; Água - Sensor de Chuva; Fogo - Sensor de Temperatura; Psíquico - Sensor Infravermelho; Fantasma - Sensor de Presença.

Outra mecânica pode ser utilizada para obter vantagem sobre o adversário, que é a troca. O jogador pode utilizar seu turno para visualizar os seus Pokémon e os do adversário ilimitadamente, mas se pressionar o botão de confirmar sobre um de seus Pokémon, aquele se tornará o seu ativo e o turno do player será encerrado. Um jogador só poderá trocar para um Pokémon que possuir 1 ou mais vidas.

## Componentes, Sensores, Funcionalidades e Quantidade de Portas Necessárias

Botão - Ataque Normal
Sensor de Proximidade - Ataque de Luta (1 pd, 1 pd pwm)
Sendor de Pressão e Temperatura - Ataque de Fogo (1 pa)
Sensor de Chuva - Ataque de Água (1 pa)
Sensor de Presença - Ataque Fantasma (1 pd)
Sensor Infravermelho - Ataque Psíquico (1 pa)

Joystick - Selecionar Ataques (2 pd)
Botão - Salvar Ataque (1 pd)
Buzzer - Efeitos Sonoros (1 pd pwm)
Led RGB - Efeitos Visuais (3 pd pwm)
LCD - Pixel Art (2 pa)

Servo Motor - Acionar Hélice (1 pd)
Hélice - Efeitos de Vento (ñ ocupa)

Interruptor - Liga e Desliga (1 pd)

Resistor
Diodo

## Sprites Utilizados

### Eevee

1 0 0 1 0, 1 1 1 1 1, 0 1 0 0 0, 0 1 0 0 0
1 1 0 1 1, 0 0 0 0 0, 1 0 0 0 0, 1 0 0 1 1
1 1 1 1 0, 0 0 0 0 0, 0 1 1 0 1, 0 0 1 1 1
0 1 1 0 0, 0 0 0 0 0, 0 0 0 1 0, 1 1 1 1 0
0 1 1 0 0, 0 0 0 0 0, 0 0 0 0 0, 1 1 0 0 0
1 0 0 0 0, 0 0 0 0 0, 0 0 0 0 0, 0 0 0 1 1
1 0 0 1 0, 0 0 0 0 0, 1 0 0 0 1, 1 1 1 0 0
1 0 1 0 1, 0 0 0 0 1, 0 1 0 0 0, 1 0 0 0 0

1 0 1 1 1, 0 0 0 0 1, 1 1 0 0 0, 1 1 0 0 0
1 0 0 1 0, 0 0 0 0 0, 1 0 0 0 0, 1 0 1 0 0
1 0 0 0 0, 0 1 0 0 0, 0 0 0 0 0, 1 0 0 1 0
0 1 0 0 0, 1 0 0 0 0, 0 0 0 0 1, 0 0 0 0 1
0 1 0 0 0, 0 1 1 1 0, 0 0 0 0 1, 0 0 0 1 1
0 0 1 0 0, 0 0 0 0 0, 0 0 0 1 0, 0 0 0 1 0
0 0 0 1 1, 0 0 0 0 0, 1 1 1 0 0, 0 0 0 1 0
0 0 0 0 0, 1 1 1 1 1, 0 0 0 0 0, 0 0 0 1 0

### Machop

0 0 0 0 0, 0 0 1 1 1, 1 1 0 0 0, 0 0 0 0 0
0 0 0 0 0, 0 1 0 1 0, 1 0 1 0 0, 0 0 0 0 0
0 0 0 0 0, 1 0 1 0 1, 0 0 0 1 0, 0 0 0 0 0
0 0 0 0 1, 0 1 0 1 0, 0 1 1 1 0, 0 0 0 0 0
0 0 0 0 1, 0 1 0 1 0, 1 0 0 1 1, 0 0 0 0 0
0 0 0 0 0, 1 1 0 1 1, 0 0 0 0 1, 0 0 0 0 0
0 0 0 0 1, 0 1 1 0 0, 1 1 0 0 1, 1 0 0 0 0
0 0 0 1 1, 0 0 0 0 1, 0 1 0 0 1, 1 0 0 0 0

0 0 1 0 1, 0 0 0 0 0, 0 1 0 1 0, 0 1 0 0 0
0 0 1 0 0, 1 0 0 1 0, 0 0 0 1 0, 0 0 1 0 0
0 0 1 0 0, 0 1 1 1 0, 0 0 1 1 1, 0 0 1 0 0
0 0 0 1 1, 0 0 1 0 0, 0 0 0 0 0, 0 0 1 0 0
0 0 0 0 0, 1 1 0 0 1, 1 0 0 0 0, 1 1 0 0 0
0 0 0 0 0, 0 1 1 0 1, 1 0 0 1 1, 0 0 0 0 0
0 0 0 0 0, 0 1 0 0 1, 1 0 1 1 0, 0 0 0 0 0
0 0 0 0 0, 0 1 1 0 1, 1 0 0 1 0, 0 0 0 0 0

### Magikarp

0 0 0 0 0, 1 1 1 1 1, 1 1 1 0 0, 0 0 1 0 0
0 0 0 0 1, 0 0 0 0 0, 0 0 0 1 0, 0 0 1 0 0
0 0 0 1 0, 0 0 1 1 0, 0 0 0 0 1, 0 0 1 0 0
0 0 0 1 0, 0 0 1 0 1, 0 0 0 0 1, 1 0 0 1 0
0 0 1 0 0, 0 0 1 1 1, 0 0 0 1 1, 1 0 0 1 0
0 0 1 1 1, 0 0 0 1 1, 0 1 1 0 0, 0 1 0 0 1
0 1 1 1 1, 1 0 0 0 0, 1 0 0 0 0, 1 0 0 0 1
0 1 1 0 0, 1 1 0 0 1, 1 0 0 0 0, 1 1 0 0 1

0 0 1 0 0, 1 1 0 1 0, 1 1 0 0 0, 1 1 1 1 1
0 1 1 0 0, 0 1 1 0 1, 1 0 1 0 1, 1 0 1 1 1
1 0 1 1 0, 0 1 1 0 0, 0 1 0 1 0, 1 0 0 0 0
0 1 0 1 1, 1 0 0 0 0, 0 1 0 1 1, 0 0 0 0 0
0 1 0 0 1, 1 1 0 0 0, 1 1 0 1 1, 0 0 0 0 0
1 0 1 0 0, 0 0 1 1 0, 0 0 1 0 0, 1 0 0 0 0
0 1 0 1 0, 0 0 0 0 1, 0 1 0 1 1, 0 0 0 0 0
0 0 1 0 1, 0 0 0 0 0, 1 0 1 0 0, 1 0 0 0 0

### Charmander

0 0 0 0 1, 1 1 1 0 0, 0 0 0 0 0, 0 0 1 0 0
0 0 0 1 0, 0 0 0 1 0, 0 0 0 0 0, 0 1 0 1 0
0 0 1 0 0, 0 0 0 0 1, 0 0 0 0 0, 0 1 0 0 1
0 0 1 0 0, 0 0 0 0 1, 0 0 0 0 0, 0 1 0 0 1
0 1 0 0 0, 0 0 0 0 0, 1 0 0 0 0, 1 0 0 1 0
1 0 0 0 1, 1 1 0 0 0, 1 0 0 0 0, 1 0 1 1 0
1 0 0 0 1, 0 1 0 0 0, 0 1 0 0 0, 1 0 1 1 0
1 0 0 0 0, 1 1 0 0 0, 0 1 0 0 0, 0 1 1 1 1

0 1 0 0 0, 0 0 0 0 0, 0 0 1 0 0, 0 1 0 1 0
0 0 1 1 0, 0 0 0 0 0, 0 0 0 1 0, 1 0 0 1 0
0 0 0 0 1, 1 1 0 0 1, 0 0 0 1 1, 0 0 1 0 0
0 0 0 0 0, 1 0 0 1 0, 0 0 0 0 1, 0 0 1 0 0
0 0 0 0 0, 1 0 0 0 1, 1 1 0 0 1, 0 1 0 0 0
0 0 0 0 1, 1 1 0 0 0, 0 0 0 0 1, 1 0 0 0 0
0 0 0 0 0, 1 1 1 0 0, 0 0 0 1 1, 0 0 0 0 0

### Mew

0 0 0 0 0, 0 0 0 1 0, 0 1 1 1 0, 0 0 1 1 0
0 0 0 0 0, 0 0 1 0 1, 1 0 0 0 1, 1 0 0 0 1
0 0 0 0 0, 0 0 1 0 1, 0 0 0 0 0, 1 0 0 0 1
0 0 0 0 0, 0 0 0 1 0, 1 1 0 0 0, 0 1 0 0 1
0 0 0 0 0, 0 0 0 0 1, 0 0 1 1 0, 0 0 1 1 1
0 0 0 0 0, 0 0 0 0 0, 1 1 0 0 1, 0 0 0 0 0
0 1 1 1 0, 0 1 1 1 0, 0 0 1 1 0, 1 0 0 0 0
0 1 0 0 1, 1 0 0 0 1, 0 0 0 1 0, 1 0 0 0 0

0 1 0 0 0, 0 0 0 0 1, 1 1 1 0 1, 0 0 0 0 0
0 1 0 0 0, 0 0 0 0 1, 0 0 0 1 0, 0 0 0 0 0
1 0 1 0 0, 0 1 0 0 1, 0 0 0 0 1, 0 0 0 0 0
1 0 0 1 0, 1 0 0 0 1, 0 0 0 0 1, 1 0 0 0 0
1 0 1 1 0, 1 1 0 0 1, 1 1 0 0 1, 0 1 0 0 0
1 0 0 0 0, 0 0 0 0 1, 0 0 1 1 1, 0 0 1 0 0
0 1 0 0 0, 0 0 0 1 0, 1 1 0 0 0, 1 1 1 0 0
0 0 1 1 1, 1 1 1 0 0, 0 0 0 0 0, 0 0 0 0 0

### Gastly

0 0 0 0 0, 1 1 1 0 0, 0 0 0 1 1, 0 0 1 1 0
0 0 0 1 1, 0 0 0 1 1, 1 0 1 0 0, 1 0 1 1 1
0 0 1 0 0, 0 1 1 1 1, 0 1 0 0 0, 0 1 0 0 0
0 0 1 0 1, 1 0 0 0 0, 1 1 0 0 0, 0 1 0 0 0
0 1 0 1 0, 0 0 0 0 0, 0 0 1 0 0, 1 0 0 0 0
1 1 1 0 0, 0 0 0 0 0, 0 0 0 1 0, 1 0 1 1 0
1 1 1 0 0, 0 0 0 0 0, 0 0 0 1 0, 0 1 0 0 1
1 1 1 1 0, 0 0 0 0 0, 0 1 0 0 1, 0 0 0 0 1

1 1 0 1 0, 0 0 0 0 1, 1 1 0 0 1, 0 0 0 1 0
1 1 0 1 0, 0 0 1 1 1, 1 1 1 0 1, 0 0 1 0 1
0 1 1 0 0, 0 1 0 1 1, 1 1 1 0 1, 0 0 1 0 1
0 0 1 0 0, 1 1 0 1 1, 1 1 0 1 0, 0 0 0 1 0
0 0 1 0 0, 0 1 1 1 1, 0 0 0 1 0, 0 0 0 1 0
0 0 0 1 0, 0 0 0 0 0, 0 0 1 0 0, 0 0 1 0 0
0 0 0 0 1, 1 0 0 0 0, 1 1 0 1 0, 0 1 0 0 0
0 0 0 0 0, 0 1 1 1 1, 1 0 1 0 1, 1 0 0 0 0

### Tipo Normal

0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 1 0, 0 0 0 0 1, 0 0 0 0 0, 1 0 0 0 0
0 0 1 0 0, 0 0 0 0 1, 0 0 0 0 0, 0 1 0 0 0
0 0 1 0 0, 0 0 0 1 1, 1 0 0 0 0, 0 1 0 0 0
0 1 0 0 1, 0 0 0 1 1, 1 0 0 0 1, 0 0 1 0 0
0 1 0 0 0, 1 1 1 1 1, 1 1 1 1 0, 0 0 1 0 0
0 1 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 1 0 0

0 1 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 1 0 0
0 1 0 0 0, 1 1 1 1 1, 1 1 1 1 0, 0 0 1 0 0
0 1 0 0 1, 0 0 0 1 1, 1 0 0 0 1, 0 0 1 0 0
0 0 1 0 0, 0 0 0 1 1, 1 0 0 0 0, 0 1 0 0 0
0 0 1 0 0, 0 0 0 0 1, 0 0 0 0 0, 0 1 0 0 0
0 0 0 1 0, 0 0 0 0 1, 0 0 0 0 0, 1 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0

### Tipo Lutador

0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 1 0, 0 0 1 1 0, 1 1 0 0 0, 1 0 0 0 0
0 0 1 0 0, 1 0 1 1 0, 1 1 0 1 0, 0 1 0 0 0
0 0 1 0 1, 1 0 1 1 0, 1 1 0 1 1, 0 1 0 0 0
0 1 0 0 1, 1 0 1 1 0, 1 1 0 1 1, 0 0 1 0 0
0 1 0 0 1, 1 0 1 1 0, 1 1 0 1 1, 0 0 1 0 0
0 1 0 0 0, 0 0 0 0 0, 0 0 0 0 0, 0 0 1 0 0

0 1 0 0 1, 1 1 1 1 0, 1 1 1 1 1, 0 0 1 0 0
0 1 0 0 1, 1 1 1 1 0, 1 1 1 1 1, 0 0 1 0 0
0 1 0 0 1, 1 1 1 0 1, 1 1 1 1 1, 0 0 1 0 0
0 0 1 0 0, 1 1 0 1 1, 1 1 1 1 0, 0 1 0 0 0
0 0 1 0 0, 0 0 1 1 1, 1 1 0 0 0, 0 1 0 0 0
0 0 0 1 0, 0 0 1 1 1, 1 1 0 0 0, 1 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0

### Tipo Água

0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 1 0, 0 0 0 0 0, 0 1 0 0 0, 1 0 0 0 0
0 0 1 0 0, 0 0 0 0 1, 1 0 0 0 0, 0 1 0 0 0
0 0 1 0 0, 0 0 0 1 1, 1 0 0 0 0, 0 1 0 0 0
0 1 0 0 0, 0 0 1 1 1, 1 1 0 0 0, 0 0 1 0 0
0 1 0 0 0, 0 1 1 1 1, 1 1 0 0 0, 0 0 1 0 0
0 1 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 1 0 0

0 1 0 0 0, 1 1 1 1 1, 1 1 1 1 0, 0 0 1 0 0
0 1 0 0 0, 1 1 1 1 1, 1 1 1 1 0, 0 0 1 0 0
0 1 0 0 0, 1 1 0 1 1, 1 1 1 1 0, 0 0 1 0 0
0 0 1 0 0, 0 1 0 0 1, 1 1 1 1 0, 0 1 0 0 0
0 0 1 0 0, 0 0 1 0 0, 1 1 1 0 0, 0 1 0 0 0
0 0 0 1 0, 0 0 0 1 1, 1 1 0 0 0, 1 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0

### Tipo Fogo

0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 1 0, 0 0 0 0 1, 0 0 0 0 0, 1 0 0 0 0
0 0 1 0 0, 0 0 0 0 1, 1 0 0 0 0, 0 1 0 0 0
0 0 1 0 0, 0 0 0 0 1, 1 1 0 0 0, 0 1 0 0 0
0 1 0 0 0, 0 0 0 1 1, 1 1 0 0 0, 0 0 1 0 0
0 1 0 0 0, 0 0 1 1 1, 1 1 1 0 0, 0 0 1 0 0
0 1 0 0 1, 0 1 1 1 1, 0 1 1 0 1, 0 0 1 0 0

0 1 0 0 1, 1 1 1 1 0, 1 1 1 1 1, 0 0 1 0 0
0 1 0 0 0, 1 1 1 0 0, 1 0 1 0 0, 0 0 1 0 0
0 1 0 1 1, 0 1 1 1 0, 0 0 1 1 1, 1 0 1 0 0
0 0 1 0 1, 1 1 0 0 0, 0 0 1 1 1, 0 1 0 0 0
0 0 1 0 0, 1 1 1 0 0, 0 1 1 1 0, 0 1 0 0 0
0 0 0 1 0, 0 0 1 1 1, 1 1 0 0 0, 1 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0

### Tipo Psíquico

0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 1 0, 0 0 0 0 0, 0 0 0 0 0, 1 0 0 0 0
0 0 1 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 1 0 0 0
0 0 1 0 1, 1 1 1 1 1, 1 1 1 1 1, 0 1 0 0 0
0 1 0 1 1, 1 0 1 1 1, 1 1 0 1 1, 1 0 1 0 0
0 1 1 1 0, 0 1 1 1 0, 0 0 1 0 0, 1 1 1 0 0
0 1 1 0 0, 0 1 1 1 0, 0 0 1 0 0, 0 1 1 0 0

0 1 1 0 0, 0 1 0 0 0, 0 0 1 0 0, 0 1 1 0 0
0 1 1 1 0, 0 0 1 1 1, 1 1 0 0 0, 1 1 1 0 0
0 1 0 1 1, 1 0 0 0 0, 0 0 0 1 1, 1 0 1 0 0
0 0 1 0 1, 1 1 1 1 1, 1 1 1 1 1, 0 1 0 0 0
0 0 1 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 1 0 0 0
0 0 0 1 0, 0 0 0 0 0, 0 0 0 0 0, 1 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0

### Tipo Fantasma

0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 0 0 0 1 1, 0 0 0 0 0
0 0 0 1 0, 0 0 1 1 1, 1 1 0 0 0, 1 0 0 0 0
0 0 1 0 0, 1 1 1 1 1, 1 1 1 1 0, 0 1 0 0 0
0 0 1 0 1, 1 1 0 0 1, 0 0 1 1 1, 0 1 0 0 0
0 1 0 0 1, 1 1 0 0 1, 0 0 1 1 1, 0 0 1 0 0
0 1 0 1 1, 1 0 0 1 1, 1 0 0 1 1, 1 0 1 0 0
0 1 0 1 1, 0 0 1 1 1, 1 1 0 0 1, 1 0 1 0 0

0 1 0 0 1, 1 1 1 1 1, 1 1 1 1 1, 1 0 1 0 0
0 1 0 0 1, 1 1 1 1 1, 1 1 1 1 1, 1 0 1 0 0
0 1 0 0 0, 0 1 1 1 1, 1 1 1 1 1, 0 0 1 0 0
0 0 1 0 0, 0 1 1 1 1, 1 1 1 1 1, 0 1 0 0 0
0 0 1 0 0, 0 0 1 1 1, 1 1 1 1 0, 0 1 0 0 0
0 0 0 1 0, 0 0 0 1 1, 1 1 1 0 0, 1 0 0 0 0
0 0 0 0 1, 1 0 0 0 0, 1 1 0 1 1, 0 0 0 0 0
0 0 0 0 0, 0 1 1 1 1, 1 1 1 0 0, 0 0 0 0 0