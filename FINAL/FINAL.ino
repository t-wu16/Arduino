#include<IRremote.h>
unsigned long tepTimer; 
int RED = 2;      
int GREEN = 3;    
int YELLOW = 4;   
int VOICE = 7;    
int SOUND = 12;    
int RECV_PIN = 8;
int SHIDU = 6; 

IRrecv irrecv(RECV_PIN);
decode_results results;
boolean state = LOW;
boolean voice_state = LOW;

float sinVal;
int toneVal;


#define NOTE_D0 -1
#define NOTE_D1 262
#define NOTE_D2 293
#define NOTE_D3 329
#define NOTE_D4 349
#define NOTE_D5 392
#define NOTE_D6 440
#define NOTE_D7 494

#define NOTE_DL1 147
#define NOTE_DL2 165
#define NOTE_DL3 175
#define NOTE_DL4 196
#define NOTE_DL5 221
#define NOTE_DL6 248
#define NOTE_DL7 278

#define NOTE_DH1 523
#define NOTE_DH2 586
#define NOTE_DH3 658
#define NOTE_DH4 697
#define NOTE_DH5 783
#define NOTE_DH6 879
#define NOTE_DH7 987

#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625

int tune[] = 
{
  NOTE_DH1,NOTE_D6,NOTE_D5,NOTE_D6,NOTE_D0,
  NOTE_DH1,NOTE_D6,NOTE_D5,NOTE_DH1,NOTE_D6,NOTE_D0,NOTE_D6,
  NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D6,NOTE_D0,NOTE_D6,
  NOTE_DH1,NOTE_D6,NOTE_D5,NOTE_DH1,NOTE_D6,NOTE_D0,
  NOTE_D1,NOTE_D1,NOTE_D3,
  NOTE_D1,NOTE_D1,NOTE_D3,NOTE_D0,
  NOTE_D6,NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D6,
  NOTE_D5,NOTE_D1,NOTE_D3,NOTE_D0,
  NOTE_DH1,NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D6,
  NOTE_D5,NOTE_D1,NOTE_D2,NOTE_D0,
  NOTE_D7,NOTE_D7,NOTE_D5,NOTE_D3,
  NOTE_D5,
  NOTE_DH1,NOTE_D0,NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D5,NOTE_D6,NOTE_D6,
  NOTE_D0,NOTE_D5,NOTE_D1,NOTE_D3,NOTE_D0,
  NOTE_DH1,NOTE_D0,NOTE_D6,NOTE_D6,NOTE_D5,NOTE_D5,NOTE_D6,NOTE_D6,
  NOTE_D0,NOTE_D5,NOTE_D1,NOTE_D2,NOTE_D0,
  NOTE_D3,NOTE_D3,NOTE_D1,NOTE_DL6,
  NOTE_D1,
  NOTE_D3,NOTE_D5,NOTE_D6,NOTE_D6,
  NOTE_D3,NOTE_D5,NOTE_D6,NOTE_D6,
  NOTE_DH1,NOTE_D0,NOTE_D7,NOTE_D5,
  NOTE_D6
};

float duration[]=
{
  1,1,0.5,0.5,1,
  0.5,0.5,0.5,0.5,1,0.5,0.5,
  0.5,1,0.5,1,0.5,0.5,
  0.5,0.5,0.5,0.5,1,1,
  1,1,1+1,
  0.5,1,1+0.5,1,
  1,1,0.5,0.5,1,
  0.5,1,1+0.5,1,
  0.5,0.5,0.5,0.5,1+1,
  0.5,1,1+0.5,1,
  1+1,0.5,0.5,1,
  1+1+1+1,
  0.5,0.5,0.5+0.25,0.25,0.5+0.25,0.25,0.5+0.25,0.25,
  0.5,1,0.5,1,1,
  0.5,0.5,0.5+0.25,0.25,0.5+0.25,0.25,0.5+0.25,0.25,
  0.5,1,0.5,1,1,
  1+1,0.5,0.5,1,
  1+1+1+1,
  0.5,1,0.5,1+1,
  0.5,1,0.5,1+1,
  1+1,0.5,0.5,1,
  1+1+1+1
};

int length;

void setup() {
  Serial.begin(9600);  
  irrecv.enableIRIn();
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(VOICE,OUTPUT);
  length = sizeof(tune)/sizeof(tune[0]);
}

void loop() {
  int tem;      
  double tem_data;  
  tem = analogRead(0);  
  tem = -tem;
  tem_data = (double) tem / 19.12+50;
  int light;
  light = analogRead(1); 
  int smoke;
  smoke = analogRead(2);

  if(irrecv.decode(&results)){
      Serial.println(results.value,HEX);

      if(results.value == 0xFD00FF){
          state = !state;
          digitalWrite(RED,LOW);
           digitalWrite(GREEN,LOW);
          digitalWrite(YELLOW,LOW);
        }
      if(results.value == 0xFDA05F){
          voice_state = !voice_state;
          if(voice_state == HIGH){
              noTone(VOICE);
              digitalWrite(VOICE,LOW);
            }
        }
      irrecv.resume();
    }

    if(state == LOW & voice_state == LOW){
       if(tem_data > 27){
          digitalWrite(RED,HIGH);
          BuzzerDI();
        } 
       if(digitalRead(SHIDU) == LOW){
          digitalWrite(GREEN,HIGH);
        }
        if(smoke > 30){
          digitalWrite(YELLOW,HIGH);
        }
     }

     if(millis() - tepTimer > 2000){ 
      tepTimer = millis();
      if(tem_data>26){
            if(light > 1000){
                Serial.print(3,HEX);
              }
            else{
                Serial.print(1,HEX);
              }
       }
       else{
            if(light > 1000){
                Serial.print(2,HEX);
              }
            else{
                Serial.print(0,HEX);
              }
       }
    }   
}


void BuzzerDI(){
  for(int x=0;x<10;x++)
  {
    tone(VOICE,tune[x]);
    delay(400*duration[x]);
    noTone(VOICE);
  }
}
