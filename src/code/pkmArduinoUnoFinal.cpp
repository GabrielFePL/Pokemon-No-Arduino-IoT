#ifndef Geekble_Note2Freq_h
#define Geekble_Note2Freq_h
class Geekble_Note2Freq
{
public:
  Geekble_Note2Freq();
  unsigned long NoteLength(float _duration);
  void Set_BPM_QuarterNote(uint16_t _BPM);
};
#endif
#define _dottedbreve 12.0
#define _dotteddoubleWhole 12.0
#define _breve 8.0
#define _doubleWhole 8.0
#define _dottedsemibreve 6.0
#define _dottedwhole 6.0
#define _semibreve 4.0
#define _whole 4.0
#define _dottedminim 3.0
#define _dottedhalf 3.0
#define _minim 2.0
#define _half 2.0
#define _dottedcrotchet 1.5
#define _dottedquarter 1.5
#define _crotchet 1.0
#define _quarter 1.0
#define _dottedquaver 0.75
#define _dottedeighth 0.75
#define _quaver 0.5
#define _eighth 0.5
#define _dottedsemiquaver 0.375
#define _dottedsixteenth 0.375
#define _semiquaver 0.25
#define _sixteenth 0.25
#define _dotteddemisemiquaver 0.1875
#define _dottedthirtysecond 0.1875
#define _demisemiquaver 0.125
#define _thirtysecond 0.125
#define _dottedhemidemisemiquaver 0.09375
#define _dottedsixtyfourth 0.09375
#define _hemidemisemiquaver 0.0625
#define _sixtyfourth 0.0625
#define n_C5 3138.69
#define n_E5 3955.5
#define n_G5 4703.94
#define n_A5 5280.00
uint16_t bpm_QuarterNote = 120;
Geekble_Note2Freq::Geekble_Note2Freq() {}
unsigned long Geekble_Note2Freq::NoteLength(float _duration)
{
  return (unsigned long)((60000.0 * _duration) / bpm_QuarterNote);
}
void Geekble_Note2Freq::Set_BPM_QuarterNote(uint16_t _BPM)
{
  bpm_QuarterNote = _BPM;
}
Geekble_Note2Freq note2freq;

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
#define PRESENCE_SENSOR A0

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
int playerPkmHp[6] = {5, 5, 5, 5, 5, 5};

int player2ActivePkm = 1;
int player2ActualPkm = 0;
int player2PkmHp[6] = {5, 5, 5, 5, 5, 5};

int actualPkm = playerActivePkm;

// Geekble_Note2Freq function that needs buzzer declaration
void playNote(float frequency, float duration)
{
  unsigned long noteDuration = note2freq.NoteLength(duration);
  tone(buzzer, frequency, noteDuration);
  delay(noteDuration * 1.3);
  noTone(buzzer);
}

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

void executionVisualEffects(int redNum, int greenNum, int blueNum)
{
  analogWrite(ledRed, redNum);
  analogWrite(ledGreen, greenNum);
  analogWrite(ledBlue, blueNum);
};

void printPokemon(int pokemon, String command)
{
  byte pkmSprite[8][8];
  String pkmName;
  String pkmType;
  int pkmHpPrint;
  executionVisualEffects(0, 0, 0);
  int red = 0;
  int green = 0;
  int blue = 0;
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
    red = 255;
    green = 255;
    blue = 255;
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
    red = 255;
    green = 10;
    blue = 0;
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
    red = 0;
    green = 100;
    blue = 255;
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
    red = 255;
    green = 0;
    blue = 0;
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
    red = 255;
    green = 0;
    blue = 255;
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
    red = 20;
    green = 0;
    blue = 255;
  };
  executionVisualEffects(red, green, blue);
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
};

void changeActualPokemon(int player, String command)
{
  if (player == 0)
  {
    actualPkm = playerActualPkm;
  }
  else if (player == 1)
  {
    actualPkm = player2ActualPkm;
  };
  if (actualPkm < 0)
  {
    actualPkm = 0;
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
};

void printAtk()
{
  lcd.clear();
  executionVisualEffects(0, 0, 0);
  byte typeSprite[8][8];
  String typeAtk;
  String effectiveness = "x1";
  int enemyActivePkm;
  int red = 0;
  int green = 0;
  int blue = 0;
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
    red = 255;
    green = 255;
    blue = 255;
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
    red = 255;
    green = 10;
    blue = 0;
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
    red = 0;
    green = 100;
    blue = 255;
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
    red = 255;
    green = 0;
    blue = 0;
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
    red = 255;
    green = 0;
    blue = 255;
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
    red = 20;
    green = 0;
    blue = 255;
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
  executionVisualEffects(red, green, blue);
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

void cryPokemon(int pokemon)
{
  if (pokemon == 1)
  {
    playNote(n_E5, _sixteenth);
    playNote(n_C5, _quarter);
  }
  else if (pokemon == 2)
  {
    playNote(n_E5, _sixteenth);
    playNote(n_G5, _eighth);
    playNote(n_C5, _sixteenth);
  }
  else if (pokemon == 3)
  {
    playNote(n_E5, _sixteenth);
    playNote(n_G5, _sixteenth);
    playNote(n_E5, _eighth);
    playNote(n_C5, _sixteenth);
  }
  else if (pokemon == 4)
  {
    playNote(n_E5, _sixteenth);
    playNote(n_C5, _sixteenth);
    playNote(n_G5, _eighth);
    playNote(n_C5, _sixteenth);
  }
  else if (pokemon == 5)
  {
    playNote(n_E5, _eighth);
    playNote(n_C5, _sixteenth);
  }
  else if (pokemon == 6)
  {
    playNote(n_E5, _eighth);
    playNote(n_G5, _sixteenth);
    playNote(n_E5, _sixteenth);
    playNote(n_C5, _sixteenth);
  };
  delay(1500);
};

void attackExecutionSound()
{
  if (count == 1)
  {
    int quickAttack = 3600;
    for (int i = 0; i < 15; i++)
    {
      quickAttack += 150;
      tone(buzzer, quickAttack, 50);
      delay(30);
    }
    noTone(buzzer);
  }
  else if (count == 2)
  {
    tone(buzzer, 3200, 200);
    delay(220);
    for (int i = 3200; i >= 800; i -= 50)
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
      int waterFreq = 3600 + 100 * sin(0.1 * i);
      tone(buzzer, waterFreq, 30);
      delay(20);
    };
    noTone(buzzer);
  }
  else if (count == 4)
  {
    for (int i = 0; i < 50; i++)
    {
      int flameFreq = random(3600, 2700);
      tone(buzzer, flameFreq, 30);
      delay(20);
    };
    noTone(buzzer);
  }
  else if (count == 5)
  {
    for (int i = 0; i < 15; i++)
    {
      int psychicFreq = 3600 + (i % 2 == 0 ? 400 : -400);
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
      int shadowFreq = 3600 + (i % 12) * 100;
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
      int impactFreq = random(2700, 3600);
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
    for (int i = 0; i < 300; i++)
    {
      digitalWrite(DIST_SENSOR_TRIG, LOW);
      digitalWrite(DIST_SENSOR_TRIG, HIGH);
      delayMicroseconds(1);
      digitalWrite(DIST_SENSOR_TRIG, LOW);
      DIST_SENSOR_time = pulseIn(DIST_SENSOR_ECHO, HIGH);
      DIST_SENSOR_distance = float(DIST_SENSOR_time * 0.0343) / 2;
      Serial.println(DIST_SENSOR_distance);
      if (DIST_SENSOR_distance > 20 && DIST_SENSOR_distance < 100)
      {
        break;
      }
      else if (i == 299)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        executionVisualEffects(0, 0, 0);
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
    for (int i = 0; i < 300; i++)
    {
      RAIN_SENSOR_umidity = analogRead(RAIN_SENSOR);
      RAIN_SENSOR_umidity = map(RAIN_SENSOR_umidity, 1023, 0, 0, 100);
      Serial.println(RAIN_SENSOR_umidity);
      Serial.println(i);
      if (RAIN_SENSOR_umidity > 50.0)
      {
        break;
      }
      else if (i == 299)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        executionVisualEffects(0, 0, 0);
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
    red = 15;
    int TEMPERATURE_SENSOR_temperature;
    for (int i = 0; i < 300; i++)
    {
      TEMPERATURE_SENSOR_temperature = TEMPERATURE_SENSOR_DHT11.readTemperature();
      Serial.println(TEMPERATURE_SENSOR_temperature);
      if (TEMPERATURE_SENSOR_temperature >= 25)
      {
        break;
      }
      else if (i == 299)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        return;
      };
      red += 3;
      analogWrite(ledRed, red);
    };
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
    for (int i = 0; i < 300; i++)
    {
      INFRA_SENSOR_signal = analogRead(INFRA_SENSOR);
      if (INFRA_SENSOR_signal > 0)
      {
        break;
      }
      else if (i == 299)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        executionVisualEffects(0, 0, 0);
        return;
      };
      red += 3;
      analogWrite(ledRed, red);
    };
    red = 255;
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
    for (int i = 0; i < 300; i++)
    {
      PRESENCE_SENSOR_presence = analogRead(PRESENCE_SENSOR);
      Serial.println(PRESENCE_SENSOR_presence);
      if (PRESENCE_SENSOR_presence != 0)
      {
        break;
      }
      else if (i == 299)
      {
        lcd.clear();
        lcd.print("O Ataque Falhou!");
        executionVisualEffects(0, 0, 0);
        return;
      };
      red += 3;
      analogWrite(ledRed, red);
    };
    red = 20;
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
  executionVisualEffects(red, green, blue);
  attackExecutionSound();
  delay(2000);
  executionVisualEffects(0, 0, 0);
  lcd.clear();
  lcd.print(deffenderName);
  lcd.print(" Levou");
  lcd.setCursor(0, 1);
  lcd.print(damage);
  lcd.print(" Pontos de Dano");
  delay(2000);
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
    int hp = 0;
    if (turn == 0)
    {
      hp = playerPkmHp[playerActivePkm - 1];
      if (hp > 0)
      {
        playerActualPkm = playerActivePkm;
        player2ActualPkm = player2ActivePkm - 1;
        player = 1;
        lcd.clear();
        printPokemon(playerActivePkm, "right");
        cryPokemon(playerActivePkm);
        firstIteration = 1;
      }
      else
      {
        firstIteration = 0;
        playerActivePkm++;
        if (playerActivePkm > 6)
        {
          playerActivePkm = 1;
        };
      };
    }
    else if (turn == 1)
    {
      hp = player2PkmHp[player2ActivePkm - 1];
      if (hp > 0)
      {
        playerActualPkm = playerActivePkm - 1;
        player2ActualPkm = player2ActivePkm;
        player = 2;
        lcd.clear();
        printPokemon(player2ActivePkm, "right");
        cryPokemon(player2ActivePkm);
        firstIteration = 1;
      }
      else
      {
        firstIteration = 0;
        player2ActivePkm++;
        if (player2ActivePkm > 6)
        {
          player2ActivePkm = 1;
        };
      };
    };
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
      if (count > 6)
      {
        count = 1;
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
      cryPokemon(actualPkm);
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
      else if (count > 6)
      {
        count = 0;
        return;
      };
      command = "right";
      changeActualPokemon(turn, command);
      lcd.clear();
      printPokemon(actualPkm, command);
      cryPokemon(actualPkm);
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
        int hp = 0;
        if (turn == 0)
        {
          hp = playerPkmHp[playerActualPkm - 1];
          if (hp > 0)
          {
            playerActivePkm = playerActualPkm;
          }
          else
          {
            tone(buzzer, 1000, 100);
          };
        }
        else if (turn == 1)
        {
          hp = player2PkmHp[player2ActualPkm - 1];
          if (hp > 0)
          {
            player2ActivePkm = player2ActualPkm;
          }
          else
          {
            tone(buzzer, 1000, 100);
          };
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
      int hp = 0;
      hp = player2PkmHp[player2ActivePkm - 1];
      if (turn == 0)
      {
        hp = playerPkmHp[playerActivePkm - 1];
        if (hp > 0)
        {
          playerActualPkm = playerActivePkm;
          player2ActualPkm = player2ActivePkm - 1;
          player = 1;
          lcd.clear();
          printPokemon(playerActivePkm, "right");
          cryPokemon(playerActivePkm);
        }
        else
        {
          firstIteration = 0;
          playerActivePkm++;
          if (playerActivePkm > 6)
          {
            playerActivePkm = 1;
          };
        };
      }
      else if (turn == 1)
      {
        hp = player2PkmHp[player2ActivePkm - 1];
        if (hp > 0)
        {
          playerActualPkm = playerActivePkm - 1;
          player2ActualPkm = player2ActivePkm;
          player = 2;
          lcd.clear();
          printPokemon(player2ActivePkm, "right");
          cryPokemon(player2ActivePkm);
        }
        else
        {
          firstIteration = 0;
          player2ActivePkm++;
          if (player2ActivePkm > 6)
          {
            player2ActivePkm = 1;
          };
        };
      };
    };
  };
};