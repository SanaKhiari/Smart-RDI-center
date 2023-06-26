
#include<SoftwareSerial.h>
#include<LiquidCrystal_I2C.h>
int  flame=0;

LiquidCrystal_I2C lcd(0x27, 20 ,4);

char data; // variable contenant le caractère lu

void setup (){
  
  pinMode (8, OUTPUT);
  //pinMode (A0, INPUT);
  lcd.init();
  Serial.begin(9600);
}



void loop (){

  //*****
  lcd.backlight();
  lcd.clear();
  lcd.print("hello");
  //***
  Serial.println("D");
  flame = analogRead(A0);

   Serial.print("Flame Sensor - ");

  Serial.println(flame);

   if (flame <100){
    Serial.println("Fire detected");
    Serial.println("buzzer");

    Serial.write('1');//envoyer 1 au pc 
    
      tone (8, 600); // allume le buzzer actif arduino
     delay(500);
     tone(8, 900); // allume le buzzer actif arduino
     delay(500);
     noTone(8);  // désactiver le buzzer actif arduino
     delay(500);


//********************************************
      if (Serial.available()){ 
             
    //Si un message a été reçu  faire ceci
     data=Serial.read();  
     // controler la lampe 1 reliée à la broche 13
     //récuperer le caractère reçu
     if(data=='1') //si le caractère lu est égale à 1
    {
    
       tone (8, 600); // allume le buzzer actif arduino
     delay(500);
     tone(8, 900); // allume le buzzer actif arduino
     delay(500);
     noTone(8);  // désactiver le buzzer actif arduino
     delay(500);
     }  
     else if(data=='0') //si le caractère lu est égale à 0

     {
        noTone(8); //éteindre la lampe
     
     }   

     
     } 
   }
   //********************************************************
  
}
