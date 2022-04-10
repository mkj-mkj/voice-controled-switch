#include <ld3320.h>

VoiceRecognition Voice;                         //聲明一個語音辨識對象

#define Led 8                                   //定義LED控制接腳

void setup(){
    pinMode(Led,OUTPUT);                        //設定輸出腳位
    digitalWrite(Led,LOW);                      //LED接腳低電位
    
    Voice.init();                               //初始化VoiceRecognition模組   
    Voice.addCommand("kai deng",0);             //輸入控制指令,開燈,將變數設為0
    Voice.addCommand("guan deng",2);            //輸入控制指令,關燈,將變數設為2
                                                //數字可以隨意設定,只要下面switch對應動作設定好就好了
                                                //控制指令為羅馬拼音
    Voice.start();//開始辨識
}
void loop() {
    switch(Voice.read()){                           //判斷辨識
        case 0:                                     //若是指令“kai deng”
	      digitalWrite(Led,HIGH);                     //點亮LED
        break;
    
        case 2:                                     //若是指令“guan deng”
	      digitalWrite(Led,LOW);                      //熄滅LED
        break;  
    
        default:                                    //如果都不是
        break;
    }
}
