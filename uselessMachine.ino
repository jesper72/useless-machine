// UselessMachine
// by svejes <http://svenssonskod.se> 

#include <Servo.h> 
 
Servo myservo;              
const int buttonPin = 3;
const int ledPin =  13;
int buttonState = 0;
int initiated = 0;
int pos = 0; 
long randNumber;
long randTimeout;

void setup() 
{ 
  myservo.attach(9); 
  myservo.write(0);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);  
  randomSeed(analogRead(0));
} 
 
 
void loop() 
{   
  // Read the button state
  buttonState = digitalRead(buttonPin);
   
  if (buttonState == 1) {
    // OK, button is switched on - lets randomize which sequence to run and 
    // the delay to use for some of the sequences
    randNumber = random(4);
    randTimeout = random(1000, 5000);
    delay(10);            
    digitalWrite(ledPin, HIGH);  
    
    switch (randNumber) {       
      case 0:
        // Simply up - wait 500ms and back down again
        for(pos = 0; pos < 90; pos += 1) {                               
          myservo.write(pos);           
          delay(5);                                 
        }       
        delay(500);

        for(pos = 90; pos > 0; pos -= 1) {
          myservo.write(pos);                       
          delay(5);                      
        }    
        break;
        
      case 1:
        // Half way up - wait 500ms - back again - half way up again - excelerate the last 45 degrees - wait 100ms and back down at full speed
        for(pos = 0; pos < 45; pos += 1) {                            
          myservo.write(pos);
          delay(50); 
        }       
        delay(500);
        myservo.write(0);
        delay(randTimeout);
        
        for(pos = 0; pos < 45; pos += 1) {                                
          myservo.write(pos);            
          delay(50);                     
        }
        
        for(pos = 45; pos < 90; pos += 1) {                                 
          myservo.write(pos);             
          delay(5);                       
        }
        delay(100);
        myservo.write(0);          
        break;
        
      case 2:
        // Wait a bit - slowly up to 50degrees - fast up to 90 and full speed back to 0
        delay(randTimeout);
        for(pos = 0; pos < 50; pos += 1) {
          myservo.write(pos);             
          delay(100);                     
        }       
        myservo.write(90);                 
        myservo.write(0);         
        break;
          
      case 3:
        // Full speed up to 90 - slowly back to 40 - jump to 50 - back to 0
        myservo.write(90);
        for(pos = 90; pos > 40; pos -= 1) {
          myservo.write(pos);                         
          delay(70);                      
        }    

        myservo.write(50);
        for(pos = 50; pos > 0; pos -= 1) {
          myservo.write(pos);            
          delay(30);                     
        }    
        break;  
    }
          
  } else {
    digitalWrite(ledPin, LOW);   
    myservo.write(0);
  }
} 
