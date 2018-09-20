#include<Servo.h>
Servo myservo;    //创建一个舵机对象
int potpin = 0;   //连接到模拟口0
int val;          //变量val用来存储从模拟口0读到的值0。
double ptr;
void setup() {
  myservo.attach(9);  //将引脚9  上的舵机与声明的舵机对象连接起来
}

void loop() {
  val = analogRead(potpin);         //从模拟口0读值，并通过val记录
  ptr = (double)val * (5/10.24);
  ptr = map(ptr, 25, 30, 0, 179);  //通过map函数进行数值转换
  myservo.write(ptr);               //给舵机写入角度
  delay(500);
}       
