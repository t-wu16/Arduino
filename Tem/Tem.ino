#include<IRremote.h>
unsigned long tepTimer; //娑撴彃褰�
int RED = 2;      //缁俱垹鍘滈敍姘穿閼达拷0閿涙稒淇惔锟�
//int GREEN = 3;    //缂佸灝鍘滈敍姘穿閼达拷3閿涙稒绠嶆惔锕佺翻閸戯拷
int YELLOW = 4;   //姒涘嫬鍘滈敍姘穿閼达拷2閿涙稓鍎梿锟�
int VOICE = 7;    //閾氬倿绂忛崳顭掔窗瀵洝鍓�7閿涙稑锛愰棅锟�
//int SOUND = 9;    //婢逛即鐓舵导鐘冲妳閸ｎ煉绱板鏇″壖5
int RECV_PIN = 8; //缁俱垹顦婚幒褍鍩楅敍姘穿閼达拷8
//int SHIDU = 6;    //濠�鍨鏉堟挸鍙嗛敍姘穿閼达拷6


IRrecv irrecv(RECV_PIN);
decode_results results;
boolean state = LOW;
boolean voice_state = LOW;

float sinVal;
int toneVal;

//闂婂厖绠�
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
//閹跺﹥鐦℃稉顏堢叾缁楋箑鎷版０鎴犲芳閸婄厧顕惔鏃囨崳閺夛拷,閸欘垯浜掗梾蹇斿壈缂傛牕鍟揇鐠嬪啰娈戦崥鍕潚濮濆矉绱�
//閻⑩垷OTE_D+閺佹澘鐡х悰銊с仛闂婂磭顑侀敍瀛∣TE_DH+閺佹澘鐡х悰銊с仛娑撳﹪娼伴張澶屽仯閻ㄥ嫰鍋呯粔宥夌叾缁楋讣绱漀OTE_DL+閺佹澘鐡х悰銊с仛娑撳娼伴張澶屽仯閻ㄥ嫰鍋呯粔宥夌叾缁楋负锟斤拷
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625
//閻€劏瀚抽弬鍥ь嚠鎼存柧绨￠幏宥呯摍閿涘矁绻栭弽宄版倵闂堫澀绡冨В鏃囩窛婵傜晫婀�

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
  NOTE_D6,  
};//鏉╂瑩鍎撮崚鍡楁皑閺勵垱鏆ｆ＃鏍ㄦ锤鐎涙劗娈戦棅宕囶儊闁劌鍨庨敍宀�鏁ゆ禍鍡曠娑擃亜绨崚妤�鐣炬稊澶夎礋tune閿涘本鏆ｉ弫锟�

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
};//鏉╂瑩鍎撮崚鍡樻Ц閺佹挳顩婚弴鎻掔摍閻ㄥ嫭甯撮幏宥夊劥閸掑棴绱濇稊鐔风暰娑斿閲滄惔蹇撳灙duration閿涘本璇為悙鐧哥礄閺佹壆绮嶉惃鍕嚋閺佹澘鎷伴崜宥夋桨闂婂磭顑侀惃鍕嚋閺佺増妲告稉锟介弽椋庢畱閿涘奔绔存稉锟界�电懓绨查敍锟�

int length;//鏉╂瑩鍣风�规矮绠熸稉锟芥稉顏勫綁闁插骏绱濋崥搴ㄦ桨閻€劍娼电悰銊ュ彙閺堝顦跨亸鎴滈嚋闂婂磭顑�

void setup() {
  Serial.begin(9600);  
  irrecv.enableIRIn();
  pinMode(RED,OUTPUT);
  //pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  //pinMode(VOICE,OUTPUT);
  length = sizeof(tune)/sizeof(tune[0]);//鏉╂瑩鍣烽悽銊ょ啊娑擄拷娑撶尰izeof閸戣姤鏆熼敍灞藉讲娴犮儲鐓￠崙绨峯ne鎼村繐鍨柌灞炬箒婢舵艾鐨稉顏堢叾缁楋拷
}

void loop() {
  //鐠囪褰囧〒鈺佸娴肩姵鍔呴崳銊ワ拷锟�
  int tem;      
  double tem_data;  
  tem = analogRead(0);  
  tem = -tem;
  tem_data = (double) tem / 19.12+50;
  //鐠囪褰囬崗澶嬫櫛閻㈢敻妯�
  int light;
  light = analogRead(1);  //鐠囪褰囬悽闈涘竾閸婏拷0~1023

  //鐠囪褰囬悜鐔兼禈娴肩姵鍔呴崳锟�
//  int smoke;
//  smoke = analogRead(2);

  //缁俱垹顦婚幒褍鍩楅敍灞肩喘閸忓牏楠囨锟�
  if(irrecv.decode(&results)){
      Serial.println(results.value,HEX);

      if(results.value == 0xFD00FF){
          state = !state;
          digitalWrite(RED,state);
          //digitalWrite(GREEN,state);
          digitalWrite(YELLOW,state);
        }
      if(results.value == 0xFDA05F){
          voice_state = !voice_state;
          if(voice_state == HIGH){
              BuzzerDI();
            }
          if(voice_state == LOW){
              noTone(VOICE);
            }
        }
      irrecv.resume();
    }
  //閼奉亜濮╅幒褍鍩楅敍灞肩喘閸忓牏楠囨担锟�
  else{
       if(tem_data > 21){
          digitalWrite(RED,HIGH);
        } 
//       if(digitalRead(SOUND) == HIGH){
//          BuzzerDI();
//        }
//       if(digitalRead(SHIDU) == HIGH){
//          digitalWrite(GREEN,HIGH);
//        } 
//       if(smoke > 30){
//          digitalWrite(YELLOW,HIGH);
//        }
       
    }
  if(millis() - tepTimer > 500){ 
      tepTimer = millis();
      Serial.println(tem_data);
      if(tem_data>25){
            Serial.print(1,HEX);
        }
    }   
}
void BuzzerDI(){
//    for(int x=0; x<180; x++)
//    {
//        //鐏忓敄in閸戣姤鏆熺憴鎺戝鏉烆剙瀵叉稉鍝勫К鎼达拷9
//        sinVal = (sin(x*(3.1412/180)));
//       //閻⑩暞in閸戣姤鏆熼崐闂撮獓閻㈢喎锛愰棅宕囨畱妫版垹宸�
//       toneVal = 2000+(int(sinVal*1000));
//      //缂佹瑥绱╅懘锟�8娑擄拷娑擄拷
//       tone(VOICE,toneVal);
//       delay(2); 
//    }
  for(int x=0;x<length;x++)
  {
    tone(VOICE,tune[x]);
    delay(400*duration[x]);
    noTone(VOICE);
  }
}


