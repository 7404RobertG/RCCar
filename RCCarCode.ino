/*
  Program: RC Motor Driver Code
  By:      Robert J. Guziec
  Written: 09/30/25
  Edited:  10/06/2025
  I/O Pins
  A0: Motor FORWARD (PUSH BUTTONS)
  A1: Motor BACKWARD (PUSH BUTTONS) 
  A2: 
  A3: 
  A4: 
  A5: 
  D0:
  D1: Servo RIGHT (PUSH BUTTONS)
  D2: Servo LEFT  (PUSH BUTTONS)
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
  PCICR = 0x06;
  PCMSK2 = 0X0C; // Servo control
  PCMSK1 = 0x03; // Motor Control


  // TESTING PURPOSES
  Serial.begin(9600);

  sei();
}

void loop() {
  // Nothing to see here! :D
}

// Servo Control
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

// Motor Control
ISR(PCINT1_vect){
  if (PINC & 0x01){
    OCR0A = 150; 
    OCR0B = 0;
  }
  else if (PINC & 0x02){
    OCR0A = 0; 
    OCR0B = 150;
  }
  else{
    OCR0A = 0; 
    OCR0B = 0;
  }
}