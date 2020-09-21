#include <U8glib.h>
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE); 

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <Event.h>
#include <Timer.h>

const int b1 = 2, b2 = 3, b3 = 4, b4 = 5;
Timer t0;
Timer t30;
int firstButton=2;
int i = 0;
int b1state = 1, b2state = 1, b3state = 1, b4state = 1;
int firstOn = 1;
int ranNum[8] = {0};
int gameState = 0;
int heart = 3;
int stage = 1;

void draw(void);
void draw2(void);
void draw3(void);
void draw4(void);
void draw5(void);

void ledOn(); // LED 랜덤으로 킴 값은 j에 저장

void setup() {

  pinMode(13, OUTPUT);
  
  for(i=6; i<10; i++){
  pinMode(i, OUTPUT);
  }

  for(i=2; i<6; i++){
   pinMode(i, INPUT_PULLUP);
  }

  t0.every(1000, ledOn);
   Serial.begin(9600);

   randomSeed(analogRead(0));

 if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }








   
}

void loop() {
 

 
  b1state = digitalRead(b1);
  b2state = digitalRead(b2);
  b3state = digitalRead(b3);
  b4state = digitalRead(b4);
  //버튼 상태 주기

while (gameState == 0){
  
   u8g.firstPage();  
  do {
    draw2();
  } while( u8g.nextPage() );
  
 t0.update();
 stage = 1;
 
  b1state = digitalRead(b1);
  b2state = digitalRead(b2);
  b3state = digitalRead(b3);
  b4state = digitalRead(b4);
  
 if (b1state == 0 || b2state == 0 || b3state == 0 || b4state == 0)
  gameState = 7;
  }

if(gameState == 7){
for(i=1; i<4; i++){
digitalWrite(9-i, HIGH);
digitalWrite(13, HIGH);

firstButton = 4 - i;
   u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );

  
delay(50);
digitalWrite(13, LOW);
delay(950);
digitalWrite(9-i, LOW);
}

   u8g.firstPage();  
  do {
    draw4();
  } while( u8g.nextPage() );

   digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(50);
          digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(50);
          digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);

  gameState = 1;
  delay(2000);

}

if(gameState == 1){
for(i=0; i<8; i++){
  ranNum[i] = random(4)+1;
  if(i>=1 && ranNum[i] == ranNum[i-1])
    ranNum[i] = random(4)+1;
    
  digitalWrite(ranNum[i]+5, HIGH);
  digitalWrite(13, HIGH);
  firstButton = ranNum[i];
    u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  delay(50);
   digitalWrite(13, LOW);
  delay(450);
   digitalWrite(ranNum[i]+5, LOW);
  }

gameState = 2;
i = 0;
heart = 3;
}

while (gameState == 2){

  b1state = digitalRead(b1);
  b2state = digitalRead(b2);
  b3state = digitalRead(b3);
  b4state = digitalRead(b4);
  
  if ((b1state == 0 || b2state == 0 || b3state == 0 || b4state == 0) && i != 8 ){
    switch (ranNum[i]){
      case 1:
      if(b1state == 0){
        i++;
        digitalWrite(6, HIGH);
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(200);
        digitalWrite(6, LOW);
        break;
      }
      else{
        i = 0;
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        heart--;
        break;
      }

      case 2:
      if(b2state == 0){
        i++;
        digitalWrite(7, HIGH);
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(200);
        digitalWrite(7, LOW);
        break;
      }
      else{
        i = 0;
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        heart--;
        break;
      }

        case 3:
      if(b3state == 0){
        i++;
        digitalWrite(8, HIGH);
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(200);
        digitalWrite(8, LOW);
        break;
      }
      
      else{
        i = 0;
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        heart--;
        break;
      }

        case 4:
      if(b4state == 0){
        i++;
        digitalWrite(9, HIGH);
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(200);
        digitalWrite(9, LOW);
        break;
      }
      else{
        i = 0;
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        heart--;
        break;
      }
      }

     
    }

    if(i == 8)
    gameState = 3;

    if(heart <= 0)
      gameState = 0;
  }

  if(gameState == 3){
    
       for(i=6; i<10; i++)
    digitalWrite(i, HIGH);

    u8g.firstPage();  
  do {
    draw3();
  } while( u8g.nextPage() );

     digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(50);
          digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(3000);

         
   for(i=6; i<10; i++)
    digitalWrite(i, LOW);

    if(++stage >= 4){
      
    u8g.firstPage();  
  do {
    draw5();
  } while( u8g.nextPage() );
  
       digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(50);
          digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(300);
          digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(300);
          digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
         delay(50);
          digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
       delay(50);
          digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
  
      delay(3000);
    gameState = 0;
    }

    else{
    gameState = 1;
    }
    }

  

 
}




   

 

  
 

  void draw(void) {
  u8g.setFont(u8g_font_unifont);
  char buf[2];
  sprintf (buf,"%d", firstButton);
   
  u8g.drawStr( 60, 22, buf);
  //u8g.drawStr( 52, 22, "Team");
}

 void draw2(void) {
  u8g.setFont(u8g_font_unifont);
  char buf[2];
  //sprintf (buf,"%d", firstButton);
   u8g.drawStr( 40, 22, "New Game");
}

 void draw3(void) {
  u8g.setFont(u8g_font_unifont);
  char buf[2];
  //sprintf (buf,"%d", firstButton);
   u8g.drawStr( 40, 22, "Success");
}

 void draw4(void) {
  u8g.setFont(u8g_font_unifont);
  char buf[2];
  //sprintf (buf,"%d", firstButton);
   u8g.drawStr( 40, 22, "Start !");
}

 void draw5(void) {
  u8g.setFont(u8g_font_unifont);
  char buf[2];
  //sprintf (buf,"%d", firstButton);
   u8g.drawStr( 40, 22, "Great !!!");
}

 void ledOn(){
  for(i=6; i<10; i++)
    digitalWrite(i, HIGH);
    
    delay(1000);

  for(i=6; i<10; i++)
    digitalWrite(i, LOW);
    
    delay(1000);
 
  //Serial.print(j);
  //Serial.println("켜짐");
  }
