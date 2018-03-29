float sinVAl;
int toneVal;
unsigned long tepTimer;

void setup() {
      pinMode(8,OUTPUT);     // 蜂鸣器引脚设置
      Serial.begin(9600);   // 设置波特率为9600 bps
}

void loop() {
      int val;        //用于存储LM35温度传感器读到的值
      double data;    //用于存储已转换的温度值
      val = analogRead(0);  //LM35连到模拟口，并从模拟口读值
      data = (double) val * (5/10.24);  //得到电压值，通过公式换成温度

       if(data>27){       //如果温度大于27，蜂鸣器响
             for(int x=0; x<180; x++){
                  sinVal = (sin(x*(3.1412/180)));       //将角度转化成弧度
                  toneVal = 2000+(int(sinVal*1000));    //产生声音的频率
                  tone(8, toneVal);                     //从引脚8输出
                  delay(2);    
             }
       }
       else{              //如果温度小于27，关闭蜂鸣器
          noTone(8);      //关闭蜂鸣器
       }

       if(millis() - tepTimer > 500){   //每500ms,串口输出一次温度值
              tepTimer = millis();
              Serial.print("现在的温度是：");
              Serial.print(data);
              Serial.prinntln("C");
       }
}
