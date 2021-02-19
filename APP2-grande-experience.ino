#include <SPI.h>
#include <SD.h>
 #include <LiquidCrystal.h>
#include <TinkerKit.h>


TKThermistor therm(A0);
int delai = 1800000; // delai de temps de mesure temperature en s .
int h = 0; // temps en heure 


int Vin = 5; //tension d'arduino en v
int R1 =  10000; //resistance en ohm
float V;// valeur brute du Pin A5 
float R;// photoresistance en ohm
float lux; // eclairement en lux
float lux1;
float moy_lux;
float Vout;// tension au borne de le photoresistance

float C;	// valeur de temperature en degre celsius
float C1;
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
  pinMode(A5,INPUT);// pin de la photorésistance initialisation

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

C = therm.readCelsius();      // Reading the temp in Celsius degrees and store in the C variable
C1 = C;

///fonction lumière 
V = analogRead(A5);
Vout =((V*5)/1023);
R = ((R1*Vout)/(Vin-Vout));
lux = pow((R/2784.9),(1/0.5317));// L = racine^0.5317(R/Ro)  --- Ro = 2784.9
lux1 = lux;

// boucle incrémentant la variable i de 0 à delai, de 1 en 1
for (int i=0; i <= delai; i++){ 
  
  C = therm.readCelsius();      // Reading the temp in Celsius degrees and store in the C variable

///fonction lumière 
V = analogRead(A5);
Vout =((V*5)/1023);
R = ((R1*Vout)/(Vin-Vout));
lux = pow((R/860.82),(1/0.5317));

lux1 = lux1+ lux;
C1 = C1 +C;


lcd.print("T : ");lcd.print(C);lcd.print(" C");lcd.setCursor(0,1);lcd.print("E : ");lcd.print(lux);lcd.print(" lux    ");lcd.setCursor(0,0);
Serial.print("moylux:");Serial.print(moy_lux);Serial.print("\t");Serial.print("moytempe");Serial.println(moy_C);
delay(1000);

}

      
 moy_lux = lux1 /delai;
moy_C = C1/delai;
   myFile = SD.open("temp.csv", FILE_WRITE);
                  h = h + 30;
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


 
