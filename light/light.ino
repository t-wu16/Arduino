int LED = 13;         //设置LED灯为数字引脚13
int val = 0;          //设置模拟引脚0读取光敏二极管的电压值

void setup() {
  pinMode(LED,OUTPUT);    //LED为输出模式
  Serial.begin(9600);     //串口波特率设置为9600
}

void loop() {
  val = analogRead(0);    //读取电压值0~1023
  Serial.println(val);    //串口查看电压值的变化
  if(val<1000){
        digitalWrite(LED,LOW);
    }
  else{
        digitalWrite(LED,HIGH);   //如果外界太暗，感光灯就亮起
    }
  delay(10);        //延时10ms
}
