
#include <IRremote.h>





/*
* SERIAL COMMANDS
* Send commands as ASCII within greater and less than symbols. Ie: <8>.
* 1-8: light n candles (including shamash, if off)
* 9: kill all lights
* 10: light shamash only
* 0: reset
*/

// Define shamash RGB LED if used. i'm using 10 for the shamash as an output.
const int shamash_r = 10;
const int shamash_g = 11;
const int shamash_b = 9;
//IR Read pin and setup
const int ir_in = 13;
IRrecv irrecv(ir_in);
decode_results results;

// Define pins for other candle LEDs
int candles[] = {2, 3, 4, 5, 6, 7, 8, 12};

// Keep track of current IR command / night of chag
int serial_command = 0;

// Are the candles lit?
int candles_lit = 0;

// Serial variables
char inData[10];
int index;
boolean started = false;
boolean ended = false;
char output_buffer[50];
int ir_value = 0;

void setup() {
  
  irrecv.enableIRIn(); // Start the receiver
  // Set up pin modes
  pinMode(shamash_r, OUTPUT);
  pinMode(shamash_g, OUTPUT);
  pinMode(shamash_b, OUTPUT);
  pinMode(candles[0], OUTPUT);
  pinMode(candles[1], OUTPUT);
  pinMode(candles[2], OUTPUT);
  pinMode(candles[3], OUTPUT);
  pinMode(candles[4], OUTPUT);
  pinMode(candles[5], OUTPUT);
  pinMode(candles[6], OUTPUT);
  pinMode(candles[7], OUTPUT);
  
  // Open the serial port
  Serial.begin(9600);
  //Serial.println("Setting up Menorah");
}

int irButton(){ //map IR result to remote key

 switch(ir_value)
 {

 case 16724175:
   //Serial.println("1");
   return 1;
   break;

 case 16718055:
   //Serial.println("2");
   return 2;
   break;

 case 16743045:
   //Serial.println("3");
   return 3;
   break;

 case 16716015:
   //Serial.println("4");
   return 4;
   break;

case 16726215:
   //Serial.println("5");
   return 5;
   break;
   
case 16734885:
   //Serial.println("6");
   return 6;
   break;

case 16728765:
   //Serial.println("7");
   return 7;
   break;

case 16730805:
   //Serial.println("8");
   return 8;
   break;
 
case 16738455:
   ///Serial.println("9");
   return 9;
   break;

case 16753245:
  //Serial.println("Power On - Light the Shamash");
  return 10;
  break;

case 4294967295:
   //Serial.println("multiPress");
   break;

default:
   //Serial.println("Default returns 0");
    return 0;
 }// end case
 //Delay from original loop is not needed in my case as the loop delay worked better and quicker, 20 vs 500.
 //delay(500); // Ignore immediate repeat
}



void loop() {
  if (irrecv.decode(&results)){
      ir_value = results.value;
      serial_command = irButton();
      //Serial.println("The IR Value is:" + results.value);
      irrecv.resume();
  }
  //delay to keep the IR read clean.
  delay(20);  
  if (serial_command != 9 && serial_command != 0 && serial_command > 0 ) {
    lightCandles(serial_command);
    serial_command = 0;
  } else if (serial_command == 9) {
    extinguishCandles();
    serial_command = 0;
  }
}

void reset() {
  candles_lit = 0;
  serial_command = 0;
  index = 0;
  started = false;
  ended = false;
  extinguishCandles();
}

void lightCandles(int night) {
  if (candles_lit == 1) {
    extinguishCandles();
  }
  lightShamash();
  for(int i = 0; i < night; i++) {
    digitalWrite(candles[i], HIGH);
  }
  candles_lit = 1;
  serial_command = 0;
}

void extinguishCandles() {
  //Serial.println("<MSG:Extinguishing candles.>");
  for (int i = 8; i >= 0; i--) {
    digitalWrite(candles[i], LOW);
  }
  analogWrite(shamash_r, 0);
  analogWrite(shamash_g, 0);
  analogWrite(shamash_b, 0);
  candles_lit = 0;
  serial_command = 0;
}

void lightShamash() {
  //Serial.println("<MSG:Lighting smahash.>");
  analogWrite(shamash_r, 255);
  analogWrite(shamash_g, 255);
  analogWrite(shamash_b, 255);
}
