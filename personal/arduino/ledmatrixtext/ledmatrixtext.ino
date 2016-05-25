#include <avr/pgmspace.h>

const byte ALPHABET[28][8][8] PROGMEM = {
{ //A
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0}
}, 
{ //B
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 0, 0}
}, 
{ //C
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0}
}, 
{ //D
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0}
}, 
{ //E
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0}
}, 
{ //F
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0}
}, 
{ //G
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0}
}, 
{ //H
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0}
}, 
{ //I
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0}
}, 
{ //J
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 1, 1, 1, 0, 0, 0}
}, 
{ //K
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0}
}, 
{ //L
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0}
}, 
{ //M
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0, 1, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {1, 0, 0, 1, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0}
}, 
{ //N
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 0, 0, 0, 1, 0},
    {1, 0, 0, 1, 0, 0, 1, 0},
    {1, 0, 0, 0, 1, 0, 1, 0},
    {1, 0, 0, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0}
}, 
{ //O
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0}
}, 
{ //P
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0}
}, 
{ //Q
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 1, 0, 1, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 1, 1, 1, 0, 1, 0}
}, 
{ //R
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0}
}, 
{ //S
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 1, 1, 0, 0}
}, 
{ //T
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0}
}, 
{ //U
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0}
}, 
{ //V
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0}
}, 
{ //W
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 1, 0, 0, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0},
    {1, 1, 0, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 1, 0}
}, 
{ //X
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0}
}, 
{ //Y
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0}
}, 
{ //Z
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0}
},
{ //SPACE
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
},
{ //.
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0}
}
};

int r[] = {0, 1, 2, 3, 4, 5, 6, 7};
int c[] = {8, 9, 10, 11, 12, 13, A0, A1};

int *msg_char_to_int(char *msg) {
  int *val = new int[strlen(msg) + 2];
  val[0] = 26;
  val[strlen(msg)] = 26;
  for (int i = 1; i < strlen(msg) + 1; i++){
    switch (msg[i - 1]) {
      case 'A':
      case'a':
        val[i] = 0;
        break;
      case 'B':
      case 'b':
        val[i] = 1;
        break;
      case 'C':
      case 'c':
        val[i] = 2;
        break;
      case 'D':
      case 'd':
        val[i] = 3;
        break;
      case 'E':
      case 'e':
        val[i] = 4;
        break;
      case 'F':
      case 'f':
        val[i] = 5;
        break;
      case 'G':
      case 'g':
        val[i] = 6;
        break;
      case 'H':
      case 'h':
        val[i] = 7;
        break;
      case 'I':
      case 'i':
        val[i] = 8;
        break;
      case 'J':
      case 'j':
        val[i] = 9;
        break;
      case 'K':
      case 'k':
        val[i] = 10;
        break;
      case 'L':
      case 'l':
        val[i] = 11;
        break;
      case 'M':
      case 'm':
        val[i] = 12;
        break;
      case 'N':
      case 'n':
        val[i] = 13;
        break;
      case 'O':
      case 'o':
        val[i] = 14;
        break;
      case 'P':
      case 'p':
        val[i] = 15;
        break;
      case 'Q':
      case 'q':
        val[i] = 16;
        break;
      case 'R':
      case 'r':
        val[i] = 17;
        break;
      case 'S':
      case 's':
        val[i] = 18;
        break;
      case 'T':
      case 't':
        val[i] = 19;
        break;
      case 'U':
      case 'u':
        val[i] = 20;
        break;
      case 'V':
      case 'v':
        val[i] = 21;
        break;
      case 'W':
      case 'w':
        val[i] = 22;
        break;
      case 'X':
      case 'x':
        val[i] = 23;
        break;
      case 'Y':
      case 'y':
        val[i] = 24;
        break;
      case 'Z':
      case 'z':
        val[i] = 25;
        break;
      case ' ':
        val[i] = 26;
        break;
      case '.':
        val[i] = 27;
        break;
      default:
        val[i] = -1;
    }
  }
  return val;
}

void zeroRows() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(r[i], 0);
  }
}

void zeroColumns() { 
  for (int j = 0; j < 8; j++) {
    digitalWrite(c[j], 0);
  }
}

int *msg;
int msgSize;
int lambda;
int scroll;

void setup() {
  scroll = 0;
  lambda = 1500;
  char message[] = "Hello world.";
  msgSize = strlen(message) + 1;
  msg = msg_char_to_int(message);
  for (int i = 0; i < 8; i++) {
    pinMode(r[i], OUTPUT);
    pinMode(c[i], OUTPUT);
  }
  zeroRows();
  zeroColumns();
}

void loop() {
  if (scroll < msgSize * 8) {
    for (int blit = 0; blit < 5; blit++) {
      if (scroll%8 == 0) {
        for (int i = 0; i < 8; i++) {
          for (int j = 0; j < 8; j++) {
            if (pgm_read_byte((&ALPHABET[msg[scroll/8]][i][j])) == 1) {
              digitalWrite(r[i], 1);
              digitalWrite(c[j], 1);
            }
          }
          delayMicroseconds(lambda);
          digitalWrite(r[i], 0);
          zeroColumns();
        }
      } else {
        int k0 = floor(scroll/8);
        int k1 = k0 + 1;
        int border = scroll%8;
        
        for (int i = 0; i < 8; i++) {
          for (int p = border; p < 8; p++) {
            if (pgm_read_byte((&ALPHABET[msg[k0]][i][p])) == 1) {
              digitalWrite(r[i], 1);
              digitalWrite(c[p - border], 1);
            }
          }
          for (int q = 0; q < border; q++) {
            if (pgm_read_byte((&ALPHABET[msg[k1]][i][q])) == 1) {
              digitalWrite(r[i], 1);
              digitalWrite(c[8 - border + q], 1);
            }
          }
          delayMicroseconds(lambda);
          digitalWrite(r[i], 0);
          zeroColumns();
        }
      }
    }
    scroll++;
  } else {
    scroll = 0;
  }
}
