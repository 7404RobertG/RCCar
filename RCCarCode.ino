/*
  Program: RC Motor Driver Code
  By:      Robert J. Guziec
  Written: 09/30/25
  Edited:  09/30/2025
  I/O Pins
  A0: 
  A1: 
  A2: 
  A3: 
  A4: 
  A5: 
  D0:
  D1:
  D2:
  D3: 
  D4: 
  D5: Motor Reverse     [TCNT0 OC0B] [Pin 7 H-Bridge]
  D6: Motor Forward     [TCNT0 OC0A] [Pin 2 H-Bridge]
  D7: 
  D8: 
  D9:  
  D10: Servo Steering
  D11: 
  D12: 
  D13: 

*/


void setup() {
  cli();

  // * * * * MOTOR SETUP * * * *
  //Timer Counters
  TCCR0A = 0xA1;
  TCCR0B = 0x01;
  // Output
  DDRD = 0x60;   // D5, D6: motor control

  // * * * * SERVO SETUP * * * * 
  // Timer Counters
  TCCR1A = 0x23; // Non-inverting, phase shift
  TCCR1B = 0x12; // Set prescaler to 8
  OCR1A = 20000;
  // Output
  DDRB = 0x04; // Set output to D10

  // * * * * PINCHANGE INT SETUP * * * *
  PCICR = 0x04;
  PCMSK2 = 0X0C; 


  // TESTING PURPOSES
  Serial.begin(9600);

  sei();
}


// Move farward values
void moveForward() {
  OCR0A = 237; OCR0B = 0;
}

void loop() {

}
ISR(PCINT2_vect){
  if (PIND & 0x08){
    OCR1B = 500;
    Serial.println("LEFT");
  }
  else if (PIND & 0x04){
  OCR1B = 1400;
  Serial.println("RIGHT");
  }
  else{
    OCR1B = 950;
  }
}