#include <DHT11.h>
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
DHT11 TEMPERATURE_SENSOR_DHT11(TEMPERATURE_SENSOR);
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

int playerActivePkm = 3;
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

void printPokemon(int pokemon, String command)
{
  byte pkmSprite[8][8];
  String pkmName;
  String pkmType;
  int pkmHpPrint;
  if (pokemon == 1)
  {
    byte eevee[8][8] = {
        {B10010, B11011, B11110, B01100, B01100, B10000, B10010, B10101},
        {B11111, B00000, B00000, B00000, B00000, B00000, B00000, B00001},
        {B01000, B10000, B01101, B00010, B00000, B00000, B10001, B01000},
        {B01000, B10011, B00111, B11110, B11000, B00011, B11100, B10000},
        {B10111, B10010, B10000, B01000, B01000, B00100, B00011, B00000},
        {B00001, B00000, B01000, B10000, B01110, B00000, B00000, B11111},
        {B11000, B10000, B00000, B00001, B00001, B00010, B11100, B00000},
        {B11000, B10100, B10010, B00001, B00011, B00010, B00010, B00010}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        pkmSprite[j][i] = eevee[j][i];
      };
    };
    pkmName = "Eevee";
    pkmType = "Normal";
  }
  else if (pokemon == 2)
  {
    byte machop[8][8] = {
        {B00000, B00000, B00000, B00001, B00001, B00000, B00001, B00011},
        {B00111, B01010, B10101, B01010, B01010, B11011, B01100, B00001},
        {B11000, B10100, B00010, B01110, B10011, B00001, B11001, B11001},
        {B00000, B00000, B00000, B00000, B00000, B00000, B10000, B10000},
        {B00101, B00100, B00100, B00011, B00000, B00000, B00000, B00000},
        {B00000, B10010, B01110, B00010, B11001, B01101, B01001, B01101},
        {B01010, B00010, B00111, B00000, B10000, B10011, B10010, B10010},
        {B01000, B00100, B00100, B00010, B11000, B00000, B00000, B00000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        pkmSprite[j][i] = machop[j][i];
      };
    };
    pkmName = "Machop";
    pkmType = "Fight";
  }
  else if (pokemon == 3)
  {
    byte magikarp[8][8] = {
        {B00000, B00001, B00010, B00010, B00100, B00111, B01111, B01100},
        {B11111, B00000, B00110, B00101, B00111, B00011, B10000, B11001},
        {B11100, B00001, B00001, B00001, B00001, B01100, B10000, B10000},
        {B00000, B00010, B00010, B10010, B10011, B10000, B10000, B10001},
        {B00100, B01100, B10110, B01011, B01001, B10100, B01010, B00101},
        {B11010, B01101, B01100, B10000, B11000, B00110, B00001, B00000},
        {B11000, B10101, B01010, B01011, B11011, B00100, B01011, B10100},
        {B11111, B10111, B10000, B00000, B00000, B10000, B00000, B10000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        pkmSprite[j][i] = magikarp[j][i];
      };
    };
    pkmName = "Magikarp";
    pkmType = "Water";
  }
  else if (pokemon == 4)
  {
    byte charmander[8][8] = {
        {B00001, B00010, B00100, B00100, B01000, B10001, B10001, B10000},
        {B11100, B00010, B00001, B00001, B00000, B11000, B01000, B11000},
        {B00000, B00000, B00000, B00000, B10000, B10000, B01000, B01000},
        {B00100, B01010, B01001, B01001, B10010, B10110, B10110, B01111},
        {B01000, B00110, B00001, B00000, B00000, B00001, B00000, B00000},
        {B00000, B00000, B11001, B10010, B10001, B11000, B11100, B00000},
        {B00100, B00010, B00011, B00001, B11001, B00001, B00011, B00000},
        {B01010, B10010, B00100, B00100, B01000, B10000, B00000, B00000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        pkmSprite[j][i] = charmander[j][i];
      };
    };
    pkmName = "Charmander";
    pkmType = "Fire";
  }
  else if (pokemon == 5)
  {
    byte mew[8][8] = {
        {B00000, B00000, B00000, B00000, B00000, B00000, B01110, B01001},
        {B00010, B00101, B00101, B00010, B00001, B00000, B01110, B10001},
        {B01110, B10001, B00000, B11000, B00110, B11001, B00110, B00010},
        {B00110, B10001, B10001, B01001, B00111, B00000, B10000, B10000},
        {B01000, B01000, B10100, B10010, B10110, B10000, B01000, B00111},
        {B00001, B00001, B01001, B10001, B11001, B00001, B00010, B11100},
        {B11101, B00010, B00001, B00001, B11001, B00111, B11000, B00000},
        {B00000, B00000, B00000, B10000, B01000, B00000, B11100, B00000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        pkmSprite[j][i] = mew[j][i];
      };
    };
    pkmName = "Mew";
    pkmType = "Psychic";
  }
  else if (pokemon == 6)
  {
    byte gastly[8][8] = {
        {B00000, B00011, B00100, B00101, B01010, B11100, B11100, B11110},
        {B11100, B00011, B01111, B10000, B00000, B00000, B00000, B00000},
        {B00011, B10100, B01000, B11000, B00100, B00010, B00010, B01001},
        {B00110, B10111, B01000, B01000, B10000, B10110, B01001, B00001},
        {B11010, B11010, B01100, B00100, B00100, B00010, B00001, B00000},
        {B00001, B00111, B01011, B11011, B01111, B00000, B10000, B01111},
        {B11001, B11101, B11101, B11010, B00010, B00100, B11010, B10101},
        {B00010, B00101, B00101, B00010, B00010, B00100, B01000, B10000}};
    for (int j = 0; j < 8; j++)
    {
      for (int i = 0; i < 8; i++)
      {
        pkmSprite[j][i] = gastly[j][i];
      };
    };
    pkmName = "Gastly";
    pkmType = "Gho/Poi";
  };
  if (command == "right")
  {
    if (turn == 0)
    {
      pkmHpPrint = playerPkmHp[pokemon - 1];
      player = 1;
    }
    else if (turn == 1)
    {
      pkmHpPrint = player2PkmHp[pokemon - 1];
      player = 2;
    };
  }
  else if (command == "left")
  {
    if (turn == 1)
    {
      pkmHpPrint = playerPkmHp[pokemon - 1];
      player = 1;
    }
    else if (turn == 0)
    {
      pkmHpPrint = player2PkmHp[pokemon - 1];
      player = 2;
    };
  };
  lcd.createChar(0, pkmSprite[0]);
  lcd.createChar(1, pkmSprite[1]);
  lcd.createChar(2, pkmSprite[2]);
  lcd.createChar(3, pkmSprite[3]);
  lcd.createChar(4, pkmSprite[4]);
  lcd.createChar(5, pkmSprite[5]);
  lcd.createChar(6, pkmSprite[6]);
  lcd.createChar(7, pkmSprite[7]);
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
  lcd.setCursor(5, 0);
  lcd.print(pkmName);
  lcd.setCursor(15, 0);
  lcd.print(player);
  lcd.setCursor(5, 1);
  lcd.print(pkmType);
  lcd.setCursor(13, 1);
  lcd.print("HP");
  lcd.print(pkmHpPrint);
  delay(2000);
};

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
  delay(2000);
};

void visualAndSoundEffects(int red, int green, int blue)
{
  digitalWrite(ledRed, red);
  digitalWrite(ledGreen, green);
  digitalWrite(ledBlue, blue);
};

void atkExecution()
{
  int attacker;
  int deffender;
  String attackerName;
  String deffenderName;
  int red;
  int green;
  int blue;
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
    visualAndSoundEffects(255, 255, 255);
    if (deffender == 6)
    {
      damage = 0;
    };
  }
  else if (count == 2)
  {
    float DIST_SENSOR_time = 0.0;
    float DIST_SENSOR_distance = 0.0;
    for (int i = 0; i < 100; i++)
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
      else if (i == 99)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        return;
      };
    };
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
    float RAIN_SENSOR_umidity;
    for (int i = 0; i < 100; i++)
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
        return;
      };
    };
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
    int TEMPERATURE_SENSOR_temperature;
    for (int i = 0; i < 100; i++)
    {
      TEMPERATURE_SENSOR_temperature = TEMPERATURE_SENSOR_DHT11.readTemperature();
      Serial.println(TEMPERATURE_SENSOR_temperature);
      if (TEMPERATURE_SENSOR_temperature > 30)
      {
        break;
      }
      else if (i == 99)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        return;
      };
    };
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
        return;
      };
    };
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
    int PRESENCE_SENSOR_presence = 0;
    for (int i = 0; i < 100; i++)
    {
      PRESENCE_SENSOR_presence = digitalRead(PRESENCE_SENSOR);
      Serial.println(PRESENCE_SENSOR_presence);
      if (PRESENCE_SENSOR_presence == 1)
      {
        break;
      }
      else if (i == 99)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        return;
      };
    };
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
  delay(2500);
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
    sensor = "de Distância";
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
    sensor = "de Presença";
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
    lcd.print("Rápido!!!");
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