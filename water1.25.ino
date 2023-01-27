//8266 esp12E完成20230124大年初三成品完工
/*在water1.24.ino
加入魚池花園水閥的控制
詳細程式說明在water1.24.ino
/********程式說明******
手機控制水池幫浦分別往山坡及溪埔兩個方向的水管

1.BLYNK APP 介面設定BLYNK APP 安裝完註冊 blynk.mixly.org及water1.24.ino介面設定
2.線路:D1幫浦，D2溪埔水閥，D5魚池花園水閥，D6山坡水閥。
接 底位觸發的4路繼電器模組。

3.程式程式
*使手機程式連上blynk伺服器
連上成功後虛擬顯示器V0顯示出
"瑞龍鳳梨 連線成功 等待指示"
虛擬顯示器V10顯示出
" 網路連結了機板  等待手機的指示 "
delay(DELAY);
(V0," ");延遲一些時間後清除顯示器字幕
*等待按下手機v1或者v2按鍵

*當按下虛擬pinv1  
顯示V0,"溪埔 正要澆水")
delay(DELAY2);
(V0,"溪埔澆水 開幫浦")

控制LED1=gp4 //(D2)溪埔水閥溪埔水閥打開,
 Blynk.virtualWrite(V10, " 幫浦開始運轉", nis,"分鐘  ")

或者按下虛擬pinv2控制LED4 =gp12 //(D6)山坡網室水閥打開,
V0,"山坡網室 正要澆水");
delay(DELAY2);


DELAY10秒後,
打開LED3=gp5 //(D1)魚池幫浦,
 Blynk.virtualWrite(V10, " 幫浦開始運轉", nis,"分鐘  ")
持續(15)分鐘，然後關掉魚池幫浦,
最後關掉LED1=gp4 //(D2)溪埔水閥，
或者LED4 =gp12 //(D6)山坡網室水閥。
  注意:int buttonStatel;必須在  void setup()之前*/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] ="H1-qfyt140OthpaPB05Dqbw4NDQogEFM";
char ssid[] = "IOT";
char pass[] = "0939201239";
// char ssid[] = "USR-LG220-L-F600";
// char pass[] = "www.usr.cn";


int buttonStatel;//虛擬pinv1要用到
int buttonState2;//虛擬pinv2要用到
int buttonState3;//虛擬pinv3要用到
int buttonState4;
long nis =1L;//虛擬pinv11要用到

void pineapple();

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass,"blynk.mixly.org",8080);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);
  Blynk.virtualWrite(V3, 0);
  Blynk.virtualWrite(V11, 0);

#define LED1 4  //(D2)溪埔水閥
#define LED2 14//(D5)魚池花園水閥
#define LED3 5  //(D1)魚池幫浦
#define LED4 12 //(D6)山坡網室

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);

#define DELAY  1000//設定延長時間
#define DELAY1 3000 //3秒
#define DELAY2 10*1000//10秒
#define DELAY3 15*60*1000//

#define DELAY4  nis*60L*1000L//





}
void loop() {
  Blynk.run();

  Blynk.virtualWrite(V0, "瑞龍鳳梨 連線成功 ");
  Blynk.virtualWrite(V10, "網路連結機板~等待手機指示");
  delay(DELAY);
  Blynk.virtualWrite(V0, " ");
  Blynk.virtualWrite(V10, " ");
  delay(DELAY);

  //***********************************
  //宣告函數瑞龍鳳梨連線成功


  if (buttonStatel == 1) {
    delay(DELAY1);  //防止v1按鍵誤觸
  }

  if (buttonStatel == 1) {
    digitalWrite(LED1,LOW);//打開溪埔水閥10秒
    Blynk.virtualWrite(V0, "溪埔要澆水了");
    Blynk.virtualWrite(V10, "打開溪埔方向的水閥10秒 ");
    delay(DELAY2);
    digitalWrite(LED3,LOW);//開始幫浦運轉 15分鐘
    Blynk.virtualWrite(V0, "溪埔澆水 溪埔方向的水閥開");
    Blynk.virtualWrite(V10, "幫浦開始運轉", nis,"分鐘");
    delay(DELAY4);
   digitalWrite(LED3, HIGH);//停止幫浦運轉
    digitalWrite(LED1, HIGH);//關閉溪埔水閥
    Blynk.virtualWrite(V1, 0); //關閉手機v1按鈕
    buttonStatel = 0; //誤動作解決方法
  } else
  {
    digitalWrite(LED1, HIGH);
    Blynk.virtualWrite(V1, 0); //關閉手機v1按鈕
  }
  if (buttonState2 == 1) {
    delay(DELAY1);  //防止v2按鍵誤觸
  }
  if (buttonState2 == 1) {
    digitalWrite(LED4, LOW); //打開山坡網室水閥
    Blynk.virtualWrite(V0, "山坡或網室要澆水");
    Blynk.virtualWrite(V10, "打開山坡和網室方向的水閥10秒 ");
    delay(DELAY2);
    digitalWrite(LED3, LOW);//開始幫浦運轉
    Blynk.virtualWrite(V0, "山坡網室澆水 打開往山坡網室水閥,");
    Blynk.virtualWrite(V10, "幫浦開始運轉", nis,"分鐘");
    delay(DELAY4);
    digitalWrite(LED3, HIGH);//停止幫浦運轉
    digitalWrite(LED4, HIGH);//關閉山坡網室水閥
    Blynk.virtualWrite(V2, 0); //關閉手機v2按鈕
    buttonState2 = 0; //誤動作解決方法
  } else {
    digitalWrite(LED4, HIGH);
    Blynk.virtualWrite(V2, 0); //關閉手機v2按鈕
  }
  if (buttonState3 == 1) {
    delay(DELAY1);  //防止v2按鍵誤觸
  }
  if (buttonState3 == 1) {
    digitalWrite(LED2, LOW); //打開魚池花園水閥
    Blynk.virtualWrite(V0, "魚池花園要澆水");
    Blynk.virtualWrite(V10, "打開魚池花園的水閥10秒 ");
    delay(DELAY2);
    digitalWrite(LED3, LOW);//開始幫浦運轉
    Blynk.virtualWrite(V0, "魚池花園澆水 打開魚池花園水閥,");
    Blynk.virtualWrite(V10, "幫浦開始運轉", nis,"分鐘");
    delay(DELAY4);
    digitalWrite(LED3, HIGH);//停止幫浦運轉
    digitalWrite(LED2, HIGH);//關閉魚池花園水閥
    Blynk.virtualWrite(V3, 0); //關閉手機v3按鈕
    buttonState3 = 0; //誤動作解決方法
  } else {
    digitalWrite(LED2, HIGH);
    Blynk.virtualWrite(V3, 0); //關閉手機v3按鈕
  }
}
//下面程式需在loop } 之後
BLYNK_WRITE(V1) {
  buttonStatel = param.asInt();
}
BLYNK_WRITE(V2) {
  buttonState2 = param.asInt();
}
BLYNK_WRITE(V3) {
  buttonState3 = param.asInt();  
}
 BLYNK_WRITE(V11) {
nis = param.asInt();  }
