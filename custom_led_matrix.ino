// Code by Tanuj
//  ___________                       __
//  \__    ___/____    ____  __ __   |__|
//     |    |  \__  \  /    \|  |  \  |  |
//     |    |   / __ \|   |  \  |  /  |  |
//     |____|  (____  /___|  /____/\__|  |
//                  \/     \/     \______|

#define D_PIN 3
#define RCLK 5
#define SRCLK 6
#define SRCLR 9
#define DELAY_TIME 300


                   //             g          end 
                   //1      8b    -     r    _      32 
uint32_t ledBits = 0b00000000000000000000000000000000;
uint32_t *ptr_ledBits = &ledBits;

uint32_t emptyBits = 0b00000000000000000000000000000000;
uint32_t *ptr_emptyBits = &emptyBits;

char buffer[100];

typedef struct {
  char color[50];
  int row;
  int col;
} _instruction_per_led;

void writeOut(uint32_t *binaryValue) {

  digitalWrite(RCLK, LOW);

  for(int i = 8; i <= 31; ++i) {

    uint8_t data = (*binaryValue >> i) & 1;

    digitalWrite(D_PIN, data);
    digitalWrite(SRCLK, HIGH);
    digitalWrite(SRCLK, LOW);

  }

  digitalWrite(RCLK, HIGH);
  digitalWrite(SRCLK, LOW);
  
}

void lightWrite(uint8_t lrow, uint8_t lcol, char lcolor, char state) {
  /* Green Starts from 13 - 18;
   * Blue Starts from 7 - 12;
   * Red Starts from 19 - 24;
   *
  */

  switch (lcolor) {

      case 'R':
      (state == 'H') ? bitSet(*ptr_ledBits, 31- (19 + (lcol - 1))) & bitSet(*ptr_ledBits, 31-lrow) : bitClear(*ptr_ledBits, 31 - (19 + lcol - 1)) & bitClear(*ptr_ledBits,31-lrow);
     // bitSet(NullD, 31-lrow);
      writeOut(ptr_ledBits);
      break;

    case 'G':
      (state == 'H') ? bitSet(*ptr_ledBits, 31 -(13 + (lcol - 1))) && bitSet(*ptr_ledBits, 31-lrow) : bitClear(*ptr_ledBits, 31 - (13 + (lcol - 1))) && bitClear(*ptr_ledBits, 31-lrow);

      writeOut(ptr_ledBits);
      break;

    case 'B':
      (state == 'H') ? bitSet(*ptr_ledBits, 31 - ( 7 + (lcol - 1))) & bitSet(*ptr_ledBits, 31-lrow) : bitClear(*ptr_ledBits, 31 - (7 + (lcol - 1))) & bitClear(*ptr_ledBits, 31-lrow);

      writeOut(ptr_ledBits);
      break;

    case 'W':

      lightWrite(lrow, lcol, 'R', state);
      sprintf(buffer,"Took the red high at row %d , col %d", lrow, lcol);
      Serial.println(buffer);
      lightWrite(lrow, lcol, 'G', state);

      sprintf(buffer, "Took the green high at row %d, col %d", lrow, lcol);
      Serial.println(buffer);
      lightWrite(lrow, lcol, 'B', state);
      sprintf(buffer ,"Took the blue high at row %d, col %d", lrow, lcol);
      Serial.println(buffer);

      break;
}
}

/* void lightOff(uint8_t lrow, uint8_t lcol) {

   * for the row control, only first 7 digits need be set or unset
   * & for individual led contorl, only columns need be controlled
   * But I sense something is off here.
   * For lightOff , I will set and unset depending upon the color or not
   
   * Now, If I want to turn off 3rd row, 3rd column - It does point to one led ...
   * I cannot turn off 3rd row entirely, because in that way, the whole row will go off.
   * So i have to target the specific led, which is at position (3,3).

   -- Cancelled Now, .....
  
}
*/

void clearData() {
  for (uint8_t i = 0 ; i < 32; i++) {
    bitClear(*ptr_ledBits, i);
  }
  writeOut(ptr_ledBits);
}

void initRegisters() {

  digitalWrite(D_PIN, LOW);
  digitalWrite(RCLK, LOW);
  digitalWrite(SRCLK, LOW);
  delay(50);
  digitalWrite(SRCLR, LOW);
  delay(50);
  digitalWrite(SRCLR, HIGH);
}

void setup() {

  Serial.begin(115200);

  pinMode(D_PIN, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
  pinMode(SRCLR, OUTPUT);
 
  initRegisters(); 

  writeOut(ptr_emptyBits);
  clearData();

  // bitSet(NullD, 31);
  // bitSet(NullD, 31-7);
  // writeOut(NullD);

}


/* There are 6 columns, 7 rows 
 * 
 * I would like to command only to light up 1st col and 1st row, which
 * corresponds to 31-0, 31-7
 *
 *
*/


void loop() {

  /*  lightWrite(0, 2, 'R', 'H');
  delay(DELAY_TIME);
  lightWrite(0, 2, 'R', 'L');
  delay(DELAY_TIME);
  lightWrite(1, 1, 'R' , 'H');
  delay(DELAY_TIME);
  lightWrite(1, 1, 'R', 'L');
  delay(DELAY_TIME);
  lightWrite(1, 3, 'R', 'H');
  delay(DELAY_TIME);
  lightWrite(1, 3, 'R', 'L');
  delay(DELAY_TIME);
  lightWrite(2, 1, 'R', 'H');
  delay(DELAY_TIME);
  lightWrite(2, 1, 'R', 'L');
  delay(DELAY_TIME);
  lightWrite(3, 2, 'R', 'H');
  delay(DELAY_TIME);
  lightWrite(3, 2, 'R', 'L');
  delay(DELAY_TIME);
  lightWrite(2, 3, 'R', 'H');
  delay(DELAY_TIME);
  lightWrite(2, 3, 'R', 'L');

*/

  for(uint8_t i=0; i < 7; i++) {
    for (uint8_t j = 1; j < 6; j++) {
      lightWrite(i, j, 'G','H');
    }
    delay(DELAY_TIME);
  }

  clearData();
  
  delay(700);
}
