typedef unsigned		u1;
typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned long int	u32;

int settemp = 20;           //settemperatur, den temperatur vi gerne vil have

// constants won't change.
const int analogport = 0;   //porten der skal måles fra
const int blaeserport = 8;  //porten blæseren sidder på
const int varmeport = 9;    //porten varmelegme sidder på

const int buttonPin = 2;     // the number of the pushbutton pin
const int button2Pin = 3;     // the number of the pushbutton pin

const int ledPin =  10;      // the number of the LED pin used in millisblink

// variables will change:
unsigned char ButtonState = 0;
unsigned char Button2State = 0;


u16 counter = 0; //(maks 65535) //til loop/os


int temp = 0;               //nuværende temperatur
int i;                       //til tælle løkke (loop) i måling
int samples[8];             // variabler for at få en bedre præsition

int ledState = LOW;             // ledState used to set the LED in millisblink
long previousMillis = 0;        // will store last time LED was updatedin millisblink

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 50;           // interval at which to blink (milliseconds) in millis 

void setup()
{
Serial.begin(9600); // opret forbindelse til pcen via arduino. (setup)
  
pinMode(analogport, INPUT);
pinMode(blaeserport, OUTPUT);
pinMode(varmeport, OUTPUT);
pinMode(10, OUTPUT);
pinMode(buttonPin, INPUT);   
pinMode(button2Pin, INPUT);   

}

void millisblinkled()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;  

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}



void startblaeser()
{
digitalWrite(blaeserport,HIGH);

}

void stopblaeser()
{
digitalWrite(blaeserport,LOW);

}

void startvarme()
{
digitalWrite(varmeport,HIGH);

}

void stopvarme()
{
digitalWrite(varmeport,LOW);

}

void maaltemperatur()
{
  for(int i = 0; i<=7; i++) //mål temperatur 8 gange for at få et bedre resultat
  { 
  samples[i] = ( 5.0 * analogRead(analogport) * 100.0) / 1024.0; //mål temperatur
  temp = temp + samples[i];
  
  }
}


void loop()
{
counter++;

if (counter == 16383)//1/4 to max of counter
    {

    }


if (counter == 32767)//halfway to max of counter (sprintf/uart laver overflow med xc8 == -32737)
    {
     stopvarme(); 
      maaltemperatur();
      temp = temp/8.0;

  
  if (temp >= settemp || temp == 26)
  
    {
    startblaeser();
    stopvarme(); 
     }
  
  if (temp <= settemp)
    {
    startvarme();
    startblaeser();
     }

Serial.print(temp,DEC); //udskrive temp / formatering decimal
Serial.println(" Grader, ");

temp = 0;

    }

if (counter == 49151)// 3/4 to max of counter
    {
   
    }

if (counter == 65534) //almost at max
        {

        }
        
if (counter == 65535) //counter has reached max
        {
        counter = 0;
        }        
        
// read the state of the pushbutton value:
ButtonState = digitalRead(buttonPin);
Button2State = digitalRead(button2Pin);


  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (ButtonState == HIGH) {     

    Serial.println(" Button 1 pressed ");
    
  } 
  else {
    // turn LED off:
    
  }

  if (Button2State == HIGH) {     

    Serial.println(" Button 2 pressed ");
    
  } 
  else {
    // turn LED off:
    
  }



}
