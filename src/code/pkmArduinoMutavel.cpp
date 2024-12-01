#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int saveButton = 2;
const int closeButton = 4;
const int leftAxis = 7;
const int rightAxis = 8;
const int upAxis = 12;
const int downAxis = 13;
int save = 0;
int close = 0;
int left = 0;
int right = 0;
int up = 0;
int down = 0;

const int DIST_SENSOR_TRIG = 3;
const int DIST_SENSOR_ECHO = 5;
#define RAIN_SENSOR A3
#define TEMPERATURE_SENSOR A2
#define INFRA_SENSOR A1
const int PRESENCE_SENSOR = 7;

const int ledRed = 11;
const int ledGreen = 9;
const int ledBlue = 10;
const int buzzer = 6;

int firstIteration = 0;
int turn = 0;
int count = 0;
int player = 1;
int atkType = 1;
int damage = 2;
String command = "null";

int playerActivePkm = 1;
int playerActualPkm = 0;
int playerPkm[6] = {1, 2, 3, 4, 5, 6};
int playerPkmHp[6] = {5, 5, 5, 5, 5, 5};

int player2ActivePkm = 1;
int player2ActualPkm = 0;
int player2Pkm[6] = {1, 2, 3, 4, 5, 6};
int player2PkmHp[6] = {5, 5, 5, 5, 5, 5};

int actualPkm = playerActivePkm;

void setup()
{
  pinMode(saveButton, INPUT);
  pinMode(closeButton, INPUT);
  pinMode(leftAxis, INPUT);
  pinMode(rightAxis, INPUT);
  pinMode(upAxis, INPUT);
  pinMode(downAxis, INPUT);
  pinMode(DIST_SENSOR_TRIG, OUTPUT);
  pinMode(DIST_SENSOR_ECHO, INPUT);
  pinMode(RAIN_SENSOR, INPUT);
  pinMode(PRESENCE_SENSOR, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  Serial.begin(9600);
};

// MUTÁVEL // MUTÁVEL // MUTÁVEL

void printPokemon(int pokemon, String command)
{
  lcd.print("pokemon");
  delay(500);
};

// MUTÁVEL // MUTÁVEL // MUTÁVEL

void changeActualPokemon(int player, String command)
{
  int listPkm[6];
  if (player == 0)
  {
    actualPkm = playerActualPkm;
    for (int i = 0; i < 6; i++)
    {
      listPkm[i] = playerPkm[i];
    };
  }
  else if (player == 1)
  {
    actualPkm = player2ActualPkm;
    for (int i = 0; i < 6; i++)
    {
      listPkm[i] = player2Pkm[i];
    };
  };
  actualPkm++;
  if (actualPkm > 6)
  {
    actualPkm = 1;
  };
  if (player == 0)
  {
    playerActualPkm = actualPkm;
  }
  else if (player == 1)
  {
    player2ActualPkm = actualPkm;
  };
  if (actualPkm != listPkm[actualPkm - 1])
  {
    changeActualPokemon(player, command);
  }
  else
  {
    return;
  };
};

void printAtk()
{
  lcd.clear();
  byte typeSprite[8][8];
  String typeAtk;
  String effectiveness = "x1";
  int enemyActivePkm;
  if (turn == 0)
  {
    enemyActivePkm = player2ActivePkm;
  }
  else if (turn == 1)
  {
    enemyActivePkm = playerActivePkm;
  };
  if (count == 1)
  {
    byte normalType[8][8] = {
        {B00000, B00011, B00100, B01000, B01000, B10010, B10001, B10000},
        {B11111, B00000, B00010, B00010, B00111, B00111, B11111, B11111},
        {B11000, B00110, B00001, B00000, B00000, B00010, B11100, B11000},
        {B00000, B00000, B00000, B10000, B10000, B01000, B01000, B01000},
        {B10000, B10001, B10010, B01000, B01000, B00100, B00011, B00000},
        {B11111, B11111, B00111, B00111, B00010, B00010, B00000, B11111},
        {B11000, B11100, B00010, B00000, B00000, B00001, B00110, B11000},
        {B01000, B01000, B01000, B10000, B10000, B00000, B00000, B00000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        typeSprite[j][i] = normalType[j][i];
      };
    };
    typeAtk = "Normal Atk";
    if (enemyActivePkm == 6)
    {
      effectiveness = "x0";
    };
  }
  else if (count == 2)
  {
    byte fightType[8][8] = {
        {B00000, B00001, B00010, B00100, B00101, B01001, B01001, B01000},
        {B01111, B10000, B00110, B10110, B10110, B10110, B10110, B00000},
        {B11100, B00011, B11000, B11010, B11011, B11011, B11011, B00000},
        {B00000, B00000, B10000, B01000, B01000, B00100, B00100, B00100},
        {B01001, B01001, B01001, B00100, B00100, B00010, B00001, B00000},
        {B11110, B11110, B11101, B11011, B00111, B00111, B10000, B01111},
        {B11111, B11111, B11111, B11110, B11000, B11000, B00011, B11100},
        {B00100, B00100, B00100, B01000, B01000, B10000, B00000, B00000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        typeSprite[j][i] = fightType[j][i];
      };
    };
    typeAtk = "Fighting Atk";
    if (enemyActivePkm == 1)
    {
      effectiveness = "x2";
    }
    else if (enemyActivePkm == 5)
    {
      effectiveness = "x1/2";
    }
    else if (enemyActivePkm == 6)
    {
      effectiveness = "x0";
    };
  }
  else if (count == 3)
  {
    byte waterType[8][8] = {
        {B00000, B00001, B00010, B00100, B00100, B01000, B01000, B01000},
        {B01111, B10000, B00000, B00001, B00011, B00111, B01111, B01111},
        {B11100, B00011, B01000, B10000, B10000, B11000, B11000, B11100},
        {B00000, B00000, B10000, B01000, B01000, B00100, B00100, B00100},
        {B01000, B01000, B01000, B00100, B00100, B00010, B00001, B00000},
        {B11111, B11111, B11011, B01001, B00100, B00011, B10000, B01111},
        {B11110, B11110, B11110, B11110, B11100, B11000, B00011, B11100},
        {B00100, B00100, B00100, B01000, B01000, B10000, B00000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        typeSprite[j][i] = waterType[j][i];
      };
    };
    typeAtk = "Water Atk";
    if (enemyActivePkm == 3)
    {
      effectiveness = "x1/2";
    }
    else if (enemyActivePkm == 4)
    {
      effectiveness = "x2";
    };
  }
  else if (count == 4)
  {
    byte fireType[8][8] = {
        {B00000, B00001, B00010, B00100, B00100, B01000, B01000, B01001},
        {B01111, B10000, B00001, B00001, B00001, B00011, B00111, B01111},
        {B11100, B00011, B00000, B10000, B11000, B11000, B11100, B01101},
        {B00000, B00000, B10000, B01000, B01000, B00100, B00100, B00100},
        {B01001, B01000, B01011, B00101, B00100, B00010, B00001, B00000},
        {B11110, B11100, B01110, B11000, B11100, B00111, B10000, B01111},
        {B11111, B10100, B00111, B00111, B01110, B11000, B00011, B11100},
        {B00100, B00100, B10100, B01000, B01000, B10000, B00000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        typeSprite[j][i] = fireType[j][i];
      };
    };
    typeAtk = "Fire Atk";
    if (enemyActivePkm == 3)
    {
      effectiveness = "x1/2";
    }
    else if (enemyActivePkm == 4)
    {
      effectiveness = "x1/2";
    };
  }
  else if (count == 5)
  {
    byte psychicType[8][8] = {
        {B00000, B00001, B00010, B00100, B00101, B01011, B01110, B01100},
        {B01111, B10000, B00000, B01111, B11111, B10111, B01110, B01110},
        {B11100, B00011, B00000, B11100, B11111, B11011, B00100, B00100},
        {B00000, B00000, B10000, B01000, B01000, B10100, B11100, B01100},
        {B01100, B01110, B01011, B00101, B00100, B00010, B00001, B00000},
        {B01000, B00111, B10000, B11111, B01111, B00000, B10000, B01111},
        {B00100, B11000, B00011, B11111, B11100, B00000, B00011, B11100},
        {B01100, B11100, B10100, B01000, B01000, B10000, B00000, B00000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        typeSprite[j][i] = psychicType[j][i];
      };
    };
    typeAtk = "Psychic Atk";
    if (enemyActivePkm == 2)
    {
      effectiveness = "x2";
    }
    else if (enemyActivePkm == 5)
    {
      effectiveness = "x1/2";
    }
    else if (enemyActivePkm == 6)
    {
      effectiveness = "x2";
    };
  }
  else if (count == 6)
  {
    byte ghostType[8][8] = {
        {B00000, B00001, B00010, B00100, B00101, B01001, B01011, B01011},
        {B01111, B10000, B00111, B11111, B11001, B11001, B10011, B00111},
        {B11100, B00011, B11000, B11110, B00111, B00111, B10011, B11001},
        {B00000, B00000, B10000, B01000, B01000, B00100, B10100, B10100},
        {B01001, B01001, B01000, B00100, B00100, B00010, B00001, B00000},
        {B11111, B11111, B01111, B01111, B00011, B00011, B10000, B01111},
        {B11111, B11111, B11111, B11111, B11111, B11100, B01111, B11100},
        {B10100, B10100, B00100, B01000, B01000, B10000, B00000, B00000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        typeSprite[j][i] = ghostType[j][i];
      };
    };
    typeAtk = "Ghost Atk";
    if (enemyActivePkm == 1)
    {
      effectiveness = "x0";
    }
    else if (enemyActivePkm == 5)
    {
      effectiveness = "x2";
    }
    else if (enemyActivePkm == 6)
    {
      effectiveness = "x2";
    };
  };
  lcd.createChar(0, typeSprite[0]);
  lcd.createChar(1, typeSprite[1]);
  lcd.createChar(2, typeSprite[2]);
  lcd.createChar(3, typeSprite[3]);
  lcd.createChar(4, typeSprite[4]);
  lcd.createChar(5, typeSprite[5]);
  lcd.createChar(6, typeSprite[6]);
  lcd.createChar(7, typeSprite[7]);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.setCursor(1, 0);
  lcd.write(byte(1));
  lcd.setCursor(2, 0);
  lcd.write(byte(2));
  lcd.setCursor(3, 0);
  lcd.write(byte(3));
  lcd.setCursor(0, 1);
  lcd.write(byte(4));
  lcd.setCursor(1, 1);
  lcd.write(byte(5));
  lcd.setCursor(2, 1);
  lcd.write(byte(6));
  lcd.setCursor(3, 1);
  lcd.write(byte(7));
  lcd.setCursor(4, 0);
  lcd.print(typeAtk);
  lcd.setCursor(4, 1);
  lcd.print("Multi: ");
  lcd.print(effectiveness);
  delay(500);
};

void attackExecutionVisualEffects(int redNum, int greenNum, int blueNum)
{
  analogWrite(ledRed, redNum);
  analogWrite(ledGreen, greenNum);
  analogWrite(ledBlue, blueNum);
};

void attackExecutionSound()
{
  if (count == 1)
  {
    int quickAttack = 400;
    for (int i = 0; i < 15; i++)
    {
      quickAttack += 200;
      tone(buzzer, quickAttack, 50);
      delay(30);
    }
    noTone(buzzer);
  }
  else if (count == 2)
  {
    tone(buzzer, 800, 200);
    delay(220);
    for (int i = 800; i >= 400; i -= 35)
    {
      tone(buzzer, i, 50);
      delay(50);
    };
    tone(buzzer, 0, 1);
    noTone(buzzer);
  }
  else if (count == 3)
  {
    for (int i = 0; i < 50; i++)
    {
      int waterFreq = 450 + 100 * sin(0.1 * i);
      tone(buzzer, waterFreq, 30);
      delay(20);
    };
    noTone(buzzer);
  }
  else if (count == 4)
  {
    for (int i = 0; i < 50; i++)
    {
      int flameFreq = random(400, 800);
      tone(buzzer, flameFreq, 30);
      delay(20);
    };
    noTone(buzzer);
  }
  else if (count == 5)
  {
    for (int i = 0; i < 15; i++)
    {
      int psychicFreq = 600 + (i % 2 == 0 ? 200 : -200);
      tone(buzzer, psychicFreq, 100);
      delay(100);
    };
    for (int i = 800; i >= 400; i -= 50)
    {
      tone(buzzer, i, 50);
      delay(50);
    };
    noTone(buzzer);
  }
  else if (count == 6)
  {
    for (int i = 0; i < 20; i++)
    {
      int shadowFreq = 400 + (i % 3) * 100;
      tone(buzzer, shadowFreq, 50);
      delay(60);
    };
    for (int i = 800; i >= 300; i -= 100)
    {
      tone(buzzer, i, 70);
      delay(70);
    };
    for (int i = 0; i < 10; i++)
    {
      int impactFreq = random(300, 700);
      tone(buzzer, impactFreq, 50);
      delay(50);
    };
    noTone(buzzer);
  };
};

void atkExecution()
{
  int attacker;
  int deffender;
  String attackerName;
  String deffenderName;
  int red = 0;
  int green = 0;
  int blue = 0;
  if (turn == 0)
  {
    attacker = playerActivePkm;
    deffender = player2ActivePkm;
  }
  else if (turn == 1)
  {
    attacker = player2ActivePkm;
    deffender = playerActivePkm;
  };
  if (attacker == 1)
  {
    attackerName = "Eevee";
  }
  else if (attacker == 2)
  {
    attackerName = "Machop";
  }
  else if (attacker == 3)
  {
    attackerName = "Magikarp";
  }
  else if (attacker == 4)
  {
    attackerName = "Charmander";
  }
  else if (attacker == 5)
  {
    attackerName = "Mew";
  }
  else if (attacker == 6)
  {
    attackerName = "Gastly";
  };
  if (deffender == 1)
  {
    deffenderName = "Eevee";
  }
  else if (deffender == 2)
  {
    deffenderName = "Machop";
  }
  else if (deffender == 3)
  {
    deffenderName = "Magikarp";
  }
  else if (deffender == 4)
  {
    deffenderName = "Charmander";
  }
  else if (deffender == 5)
  {
    deffenderName = "Mew";
  }
  else if (deffender == 6)
  {
    deffenderName = "Gastly";
  };
  if (attacker == count)
  {
    damage++;
  };
  if (count == 1)
  {
    red = 255;
    green = 255;
    blue = 255;
    if (deffender == 6)
    {
      damage = 0;
    };
  }
  else if (count == 2)
  {
    red = 15;
    float DIST_SENSOR_time = 0.0;
    float DIST_SENSOR_distance = 0.0;
    for (int i = 0; i < 80; i++)
    {
      digitalWrite(DIST_SENSOR_TRIG, LOW);
      digitalWrite(DIST_SENSOR_TRIG, HIGH);
      delayMicroseconds(1);
      digitalWrite(DIST_SENSOR_TRIG, LOW);
      DIST_SENSOR_time = pulseIn(DIST_SENSOR_ECHO, HIGH);
      DIST_SENSOR_distance = float(DIST_SENSOR_time * 0.0343) / 2;
      if (DIST_SENSOR_distance > 20 && DIST_SENSOR_distance < 100)
      {
        break;
      }
      else if (i == 79)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        attackExecutionVisualEffects(0, 0, 0);
        return;
      };
      red += 3;
      analogWrite(ledRed, red);
    };
    red = 255;
    green = 10;
    blue = 0;
    if (deffender == 1)
    {
      damage = damage * 2;
    }
    else if (deffender == 5)
    {
      damage = damage / 2;
    }
    else if (deffender == 6)
    {
      damage = 0;
    };
  }
  else if (count == 3)
  {
    red = 15;
    float RAIN_SENSOR_umidity;
    for (int i = 0; i < 80; i++)
    {
      RAIN_SENSOR_umidity = analogRead(RAIN_SENSOR);
      RAIN_SENSOR_umidity = map(RAIN_SENSOR_umidity, 0, 1023, 0, 100);
      if (RAIN_SENSOR_umidity > 50)
      {
        break;
      }
      else if (i == 99)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        attackExecutionVisualEffects(0, 0, 0);
        return;
      };
      red += 3;
      analogWrite(ledRed, red);
    };
    red = 0;
    green = 100;
    blue = 255;
    if (deffender == 3)
    {
      damage = damage / 2;
    }
    else if (deffender == 4)
    {
      damage = damage * 2;
    };
  }
  else if (count == 4)
  {
    red = 255;
    green = 0;
    blue = 0;
    if (deffender == 3)
    {
      damage = damage / 2;
    }
    else if (deffender == 4)
    {
      damage = damage / 2;
    };
  }
  else if (count == 5)
  {
    red = 15;
    int INFRA_SENSOR_signal = 0;
    for (int i = 0; i < 100; i++)
    {
      INFRA_SENSOR_signal = analogRead(INFRA_SENSOR);
      if (INFRA_SENSOR_signal > 0)
      {
        break;
      }
      else if (i == 99)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        attackExecutionVisualEffects(0, 0, 0);
        return;
      };
      red += 3;
      analogWrite(ledRed, red);
    };
    red = 200;
    green = 0;
    blue = 255;
    if (deffender == 2)
    {
      damage = damage * 2;
    }
    else if (deffender == 5)
    {
      damage = damage / 2;
    }
    else if (deffender == 6)
    {
      damage = damage * 2;
    };
  }
  else if (count == 6)
  {
    red = 15;
    int PRESENCE_SENSOR_presence = 0;
    for (int i = 0; i < 150; i++)
    {
      PRESENCE_SENSOR_presence = digitalRead(PRESENCE_SENSOR);
      if (PRESENCE_SENSOR_presence == 1)
      {
        break;
      }
      else if (i == 149)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        attackExecutionVisualEffects(0, 0, 0);
        return;
      };
      red += 3;
      analogWrite(ledRed, red);
    };
    red = 100;
    green = 0;
    blue = 255;
    if (deffender == 1)
    {
      damage = 0;
    }
    else if (deffender == 5)
    {
      damage = damage * 2;
    }
    else if (deffender == 6)
    {
      damage = damage * 2;
    };
  };
  lcd.clear();
  lcd.print(attackerName);
  lcd.print(" Ataca!");
  attackExecutionVisualEffects(red, green, blue);
  attackExecutionSound();
  delay(4000);
  attackExecutionVisualEffects(0, 0, 0);
  lcd.clear();
  lcd.print(deffenderName);
  lcd.print(" Levou");
  lcd.setCursor(0, 1);
  lcd.print(damage);
  lcd.print(" Pontos de Dano");
  delay(2500);
  if (turn == 0)
  {
    player2PkmHp[deffender - 1] = player2PkmHp[deffender - 1] - damage;
  }
  else if (turn == 1)
  {
    playerPkmHp[deffender - 1] = playerPkmHp[deffender - 1] - damage;
  };
};

void atkSelection()
{
  String atkType;
  String sensor;
  if (count == 1)
  {
    atkType = "Normal";
  }
  else if (count == 2)
  {
    atkType = "Fight";
    sensor = "de Distancia";
  }
  else if (count == 3)
  {
    atkType = "Water";
    sensor = "de Chuva";
  }
  else if (count == 4)
  {
    atkType = "Fire";
    sensor = "de Temperatura";
  }
  else if (count == 5)
  {
    atkType = "Psychic";
    sensor = "de Infravermelho";
  }
  else if (count == 6)
  {
    atkType = "Ghost";
    sensor = "de Presenca";
  };
  lcd.clear();
  lcd.print("Ataque ");
  lcd.print(atkType);
  lcd.setCursor(0, 1);
  lcd.print("Selecionado!");
  delay(2000);
  if (count != 1)
  {
    lcd.clear();
    lcd.print("Rapido!!!");
    delay(2000);
    lcd.clear();
    lcd.print("Acione o Sensor");
    lcd.setCursor(0, 1);
    lcd.print(sensor);
  };
};

void changeTurn()
{
  if (turn == 0)
  {
    turn = 1;
  }
  else if (turn == 1)
  {
    turn = 0;
  };
  lcd.clear();
  lcd.print("Troca de Turnos!");
  lcd.setCursor(0, 1);
  lcd.print("Vez do Player ");
  lcd.print(turn + 1);
  delay(2000);
};

void loop()
{
  if (firstIteration == 0)
  {
    if (turn == 0)
    {
      playerActualPkm = playerActivePkm;
      player2ActualPkm = player2ActivePkm - 1;
      printPokemon(playerActivePkm, "right");
    }
    else if (turn == 1)
    {
      playerActualPkm = playerActivePkm - 1;
      player2ActualPkm = player2ActivePkm;
      printPokemon(player2ActivePkm, "right");
    };
    firstIteration = 1;
  };
  save = digitalRead(saveButton);
  close = digitalRead(closeButton);
  left = digitalRead(leftAxis);
  right = digitalRead(rightAxis);
  up = digitalRead(upAxis);
  down = digitalRead(downAxis);
  if (save == 1 || close == 1 || left == 1 || right == 1 || up == 1 || down == 1)
  {
    if (left == 1)
    {
      if (command != "left")
      {
        count = 0;
        if (turn == 0)
        {
          playerActualPkm = playerActivePkm;
          player2ActualPkm = player2ActivePkm - 2;
        }
        else if (turn == 1)
        {
          playerActualPkm = playerActivePkm - 1;
          player2ActualPkm = player2ActivePkm;
        };
      };
      count++;
      if (count == 6)
      {
        count = 0;
      };
      int tempTurn = turn;
      if (turn == 0)
      {
        tempTurn = 1;
      }
      else if (turn == 1)
      {
        tempTurn = 0;
      };
      command = "left";
      changeActualPokemon(tempTurn, command);
      lcd.clear();
      printPokemon(actualPkm, command);
    }
    else if (right == 1)
    {
      if (command != "right")
      {
        count = 0;
        if (turn == 0)
        {
          playerActualPkm = playerActivePkm;
          player2ActualPkm = player2ActivePkm - 2;
        }
        else if (turn == 1)
        {
          playerActualPkm = playerActivePkm - 1;
          player2ActualPkm = player2ActivePkm;
        };
      };
      count++;
      if (count == 1)
      {
        count++;
      }
      else if (count == 6)
      {
        count = 0;
      };
      command = "right";
      changeActualPokemon(turn, command);
      lcd.clear();
      printPokemon(actualPkm, command);
    }
    else if (up == 1)
    {
      if (command != "up" && command != "down")
      {
        count = 0;
      };
      count++;
      if (count == 7)
      {
        count = 1;
      };
      command = "up";
      printAtk();
    }
    else if (down == 1)
    {
      if (command != "down" && command != "up")
      {
        count = 7;
      };
      count--;
      if (count == 0)
      {
        count = 6;
      };
      command = "down";
      printAtk();
    }
    else if (close == 1)
    {
      lcd.clear();
      command = "null";
      count = 0;
    }
    else if (save == 1)
    {
      if (command == "right")
      {
        if (turn == 0)
        {
          playerActivePkm = playerActualPkm;
        }
        else if (turn == 1)
        {
          player2ActivePkm = player2ActualPkm;
        };
        count = 0;
        command = "null";
        lcd.clear();
        lcd.print("Player ");
        lcd.print(turn + 1);
        lcd.print(" Trocou");
        lcd.setCursor(0, 1);
        lcd.print("de Pokemon!");
        delay(2000);
        changeTurn();
      }
      else if (command == "up" || command == "down")
      {
        atkSelection();
        atkExecution();
        damage = 2;
        count = 0;
        command = "null";
        changeTurn();
      };
    };
    if (count == 0)
    {
      if (turn == 0)
      {
        playerActualPkm = playerActivePkm;
        player2ActualPkm = player2ActivePkm - 1;
        player = 1;
        lcd.clear();
        printPokemon(playerActivePkm, "right");
      }
      else if (turn == 1)
      {
        playerActualPkm = playerActivePkm - 1;
        player2ActualPkm = player2ActivePkm;
        player = 2;
        lcd.clear();
        printPokemon(player2ActivePkm, "right");
      };
    };
  };
};