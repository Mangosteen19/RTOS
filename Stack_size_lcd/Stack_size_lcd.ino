#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal.h> //Thu vien cho LCD



#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // baudrate 9600
  lcd.begin(16, 2);               // Dùng LCD 16, 2
  lcd.setCursor(0,0);            //Thiết lập vị trí con trỏ
  lcd.print("  DIEN TU 3M !");   // In ra cái mình muốn ghi
  xTaskCreate(task1,"LCD",192,NULL,2,&task1_t); 
}

void loop() {
  // put your main code here, to run repeatedly:

}


TaskHandle_t task1_t;
void task1(){
   UBaseType_t uxHighWaterMark;// Khai báo biến 
    uxHighWaterMark = uxTaskGetStackHighWaterMark(task1_t); //Gán giá trị stack còn lại vào biến  uxHighWaterMark
  while(1){
    LCD();  //Hàm hiển thị LCD
    uxHighWaterMark = uxTaskGetStackHighWaterMark(task1_t);  //Gán giá trị stack còn lại vào biến  uxHighWaterMark
    Serial.println("lcd on");   
    Serial.print("Stack_size con lai: ");
    Serial.println(uxHighWaterMark);  //in ra màn hình Serial lượng stack còn lại
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // Đọc giá trị các nút nhấn

 if (adc_key_in > 1000) return btnNONE; // Giá trị lớn hơn 1000 là không có nút nào được nhấn
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT; 
 

 return btnNONE;  // Nếu không nằm trong khoảng trên thì cũng có nghĩa là không có nút nào được nhấn
}

void LCD(){

   lcd.setCursor(0,1);            //Thiết lập vị trí con trỏ
 lcd.print("Phim An :"); // In ra cái mình muốn ghi

 lcd.setCursor(11,1);       
 lcd_key = read_LCD_buttons();  // Đọc nút nhấn

 switch (lcd_key)               // Phần lập trình hiển thị nút được nhấn
 {
   case btnRIGHT:
     {
     lcd.print("RIGHT ");
     break;
     }
   case btnLEFT:
     {
     lcd.print("LEFT   ");
     break;
     }
   case btnUP:
     {
     lcd.print("UP    ");
     break;
     }
   case btnDOWN:
     {
     lcd.print("DOWN  ");
     break;
     }
   case btnSELECT:
     {
     lcd.print("SELECT");
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE  ");
     break;

     }
     //delay(20);
 }   
}