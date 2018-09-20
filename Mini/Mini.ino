// 遥控器控制
#include <IRremote.h>
int RECV_PIN = 10;              
int Pin2 = 11;                // LED – digital 11
int Pin1 = 12;
int Pin0 = 13;
boolean ledState2 = LOW;         // ledstate用来存储LED的状态
boolean ledState1 = LOW;
boolean ledState0 = LOW;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
     Serial.begin(9600);
     irrecv.enableIRIn(); 
     pinMode(Pin2,OUTPUT);       // 设置LED为输出状态
     pinMode(Pin1,OUTPUT);
     pinMode(Pin0,OUTPUT);
}

void loop() {
      if (irrecv.decode(&results)) {     
              Serial.println(results.value, HEX);

              //一旦接收到电源键的代码, LED翻转状态，HIGH变LOW，或者LOW变HIGH
         if(results.value == 0xFD00FF){
                 ledState2 = !ledState2;             //取反      
                 digitalWrite(Pin2,ledState2);    //改变LED相应状态        
            }
         if(results.value == 0xFD807F){
                 ledState1 = !ledState1;             //取反      
                 digitalWrite(Pin1,ledState1);    //改变LED相应状态        
            }
         if(results.value == 0xFD40BF){
                 ledState0 = !ledState0;             //取反      
                 digitalWrite(Pin0,ledState0);    //改变LED相应状态        
            }
         irrecv.resume();  
        }
}

