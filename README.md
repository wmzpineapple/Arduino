/********water1.24.ino程式說明******
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
