//完成
/*虛擬pinv1控制gp4(D2)溪埔水閥打開,DELAY10秒,
  打開gp5(D1)魚池幫浦,持續15分鐘
  關掉魚池幫浦,關掉gp4(D2)溪埔水閥

  注意:int buttonStatel;必須在  void setup()之前*/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = " kX7M_4IVR4EM2gFIClDyHIIX6Pwvtnbg";
char ssid[] = "IOT";
char pass[] = "0939201239";
// char ssid[] = "USR-LG220-L-F600";
// char pass[] = "www.usr.cn";


int buttonStatel;//虛擬pinv1要用到
int buttonState2;
int buttonState3;
int buttonState4;
long nis =1L;

void pineapple();

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V1, 0);
  Blynk.virtualWrite(V2, 0);

#define LED1 4  //(D2)溪埔水閥
#define LED2 14//(D5)設定LED第幾PIN(D5)
#define LED3 5  //(D1)魚池幫浦
#define LED4 12 //(D6)山坡網室

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);

#define DELAY  1000//設定延長時間
#define DELAY1 3000 //1秒
#define DELAY2 10*1000//10秒
#define DELAY3 15*60*1000//

#define DELAY4  nis*60L*1000L//


Blynk.virtualWrite(V11, 0);


}
void loop() {
  Blynk.run();

  Blynk.virtualWrite(V0, "瑞龍鳳梨 連線成功 ");
  Blynk.virtualWrite(V10, " 網路連結了機板  等待手機的指示 ");
  delay(DELAY);
  Blynk.virtualWrite(V0, " ");
  Blynk.virtualWrite(V10, " ");
  delay(DELAY);

  //***********************************
  //宣告函數瑞龍鳳梨連線成功


  if (buttonStatel == 1) {
    delay(DELAY);  //防止v1按鍵誤觸
  }

  if (buttonStatel == 1) {
    digitalWrite(LED1,LOW);//打開溪埔水閥10秒
    Blynk.virtualWrite(V0, "溪埔要澆水了");
    Blynk.virtualWrite(V10, " 打開溪埔方向的水閥10秒 ");
    delay(DELAY2);
    digitalWrite(LED4,LOW);//開始幫浦運轉 15分鐘
    Blynk.virtualWrite(V0, "溪埔澆水 溪埔方向的水閥全開");
    Blynk.virtualWrite(V10, " 幫浦開始運轉", nis,"分鐘  ");
    delay(DELA);
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
}
//下面程式需在loop } 之後
BLYNK_WRITE(V1) {
  buttonStatel = param.asInt();
}
BLYNK_WRITE(V2) {
  buttonState2 = param.asInt();
}
 BLYNK_WRITE(V11) {
nis = param.asInt();  }
