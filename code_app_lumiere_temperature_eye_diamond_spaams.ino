#include <SPI.h>
#include <SD.h>
 #include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
#define ONE_WIRE_BUS 8 // On branche le capteur de temÃ©rature Ã©tanche sur le port D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature celsius(&oneWire);

int delai = 10; // delai de temps de mesure temperature en s .
int h = 0; // temps en seconde 

int Vin = 5; //tension d'arduino en v
int R1 =  10000; //resistance en ohm
float V;// valeur brute du Pin A5 
float R;// photoresistance en ohm
float lux; // eclairement en lux
float moy_lux;
float Vout;// tension au borne de le photoresistance

float C;  // valeur de temperature en degre celsius
float moy_C;

File myFile;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int inputPin = A0;  // buttons array analog input 
const int ledPin =  9;    // backlight control
float temp;
uint16_t inputValue = 0;   // value read from buttons array


void setup()
{

    Serial.begin(9600);
    pinMode(A4,INPUT);// pin de la photorésistance initialisation
    celsius.begin(); // initialisation du lecteur de temperature
   pinMode(ledPin, OUTPUT); //lcd initialisation
    digitalWrite(ledPin, HIGH);
    lcd.begin(16, 2); 

    while (!Serial) {// carte sd initialisation
    }
    Serial.print("Initializing SD card...");
    if (!SD.begin(10)) {
      Serial.println("initialization failed!");
     lcd.print("   Insere SD "); lcd.setCursor(0,1);lcd.print(" et reset");
      while (1);
    } Serial.println("initialization done.");
    
  myFile = SD.open("temp.csv", FILE_WRITE);
  if (myFile) {
  Serial.print("temperature");
  myFile.print("temperature");myFile.print(";");myFile.print("eclairement");myFile.print(";");myFile.println("temps");
  lcd.setCursor(0,0);lcd.print("initialisation");lcd.setCursor(0,1); lcd.print("   reussi");
  myFile.close();
    } else {
      Serial.println("error opening temp.csv");
      lcd.print("error SD");
    }
    lcd.clear();
  }

void loop(){
  
  float C1 = 0; 
  float lux1 = 0;


  // boucle incrémentant la variable i de 0 à delai, de 1 en 1
  for (int i=1; i <= delai; i++){ 
    
       // fonction temperature
       celsius.requestTemperatures(); 
       C = celsius.getTempCByIndex(0);     
      
      ///fonction lumière 
      V = analogRead(A3);
      Vout =((V*5)/1023);
      R = ((R1*Vout)/(Vin-Vout));
      lux = pow((R/860.82),(1/0.6838));
      lux1 = lux1+ lux;
      C1 = C1 +C;

     
            if (lux <= 100 and C >=27){
          lcd.print("T : ");lcd.print(C);lcd.print(" C");lcd.setCursor(0,1);lcd.print("LIGHT : OFF");;lcd.print(lux);lcd.setCursor(0,0);
  digitalWrite(4, HIGH);
delay(1000);
}
  else if (lux <= 100 and C<= 23){
    lcd.print("T : ");lcd.print(C);lcd.print(" C");lcd.setCursor(0,1);lcd.print("LIGHT : OFF");;lcd.print(lux);lcd.setCursor(0,0);
     digitalWrite(4, LOW);
      delay(1000);
          }
          else if (lux > 100 and C>= 27){
            lcd.print("T : ");lcd.print(C);lcd.print(" C");lcd.setCursor(0,1);lcd.print("LIGHT : ON");;lcd.print(lux);lcd.setCursor(0,0);
  digitalWrite(4, HIGH);
  delay(1000);
}
  else if ( lux > 100 and  C<= 23){
     digitalWrite(4, LOW);
  }
          lcd.print("T : ");lcd.print(C);lcd.print(" C");lcd.setCursor(0,1);lcd.print("LIGHT : ON  ");;lcd.print(lux);lcd.setCursor(0,0);
          delay(1000);
          }

  
   celsius.requestTemperatures(); 
     C = celsius.getTempCByIndex(0);     
    if  (C>= 27){   
  digitalWrite(4, HIGH);
    }
     else if (C<= 23){
     digitalWrite(4, LOW);
     }
            
  int hasard = random(3);
  moy_lux = lux1 /delai;
  moy_C = C1/delai;
  if(hasard == 1){
      lcd.clear();
      lcd.print("  EYE DIAMOND");lcd.setCursor(0,1);lcd.print("     SPAAMS");lcd.setCursor(0,0);
      delay(5000);
      lcd.clear();}
  else if(hasard == 2){
      lcd.clear();
      lcd.print("  APP L2 2019");lcd.setCursor(0,1);lcd.print("PBR SPATIAL GRP4");lcd.setCursor(0,0);
      delay(5000);
      lcd.clear();}

   myFile = SD.open("temp.csv", FILE_WRITE);
                  h +=  delai + 5;
                  if(myFile){
                   
                      myFile.print(moy_C);myFile.print(";");myFile.print(moy_lux);myFile.print(";");myFile.println(h);
                     lcd.print("prise mesure");
                     lcd.clear();
                      myFile.close();
                     }else{
                      Serial.println("error opening temp.csv");
                      lcd.clear();
                      lcd.print("error SD"); 
 }
  }
