
#include <ArduinoBLE.h>


BLEService DeviceInformation("0000180a-0000-1000-8000-00805f9b34fb");
BLECharCharacteristic Weight("00002a98-0000-1000-8000-00805f9b34fb", BLEWrite | BLERead | BLENotify);  
BLECharCharacteristic WeightMeasurement("00002a9d-0000-1000-8000-00805f9b34fb", BLEWrite | BLERead | BLENotify); 

int Reed[3] = {7,8,9}; //리드스위치1,2,3
#define relay 12
#define PUSH_PIN 5
#define R_PIN 2
#define G_PIN 3
#define B_PIN 4

const int RED = 22;
const int GREEN = 23;
const int BLUE = 24;


int count=0;
char cB='0';
unsigned long ti;
unsigned long ti2;
int current_Button=HIGH;
int last_Button=HIGH;

 

void setup() {
  Serial.begin(9600);
  while (!Serial);
  for(int i=0;i<3;i++) pinMode(Reed[i], INPUT); //리드스위치
  pinMode(LED_BUILTIN, OUTPUT); //내장 led 끔
 
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode( PUSH_PIN, INPUT_PULLUP );
  pinMode(relay, OUTPUT);
  pinMode(R_PIN, OUTPUT); 
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  


   if (!BLE.begin()) 
  {
  Serial.println("starting BLE failed!");
  while (1);
  }
  BLE.setLocalName("pillitee");
  BLE.setAdvertisedService(DeviceInformation); 
  DeviceInformation.addCharacteristic(Weight); 
  DeviceInformation.addCharacteristic(WeightMeasurement); 
  BLE.addService(DeviceInformation);
  Weight.writeValue(NULL);
  WeightMeasurement.writeValue(NULL);
  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");
}
void displayColor(String color, int r, int g, int b, unsigned long mills)
{ //Serial.println(color);
  setColor(r, g, b);
  
}
void setColor(int red, int green, int blue)
{ analogWrite(R_PIN, red); 
  analogWrite(G_PIN, green); 
  analogWrite(B_PIN, blue);
}
char checkBlank(){
  int i;
  
  for(i=0;i<3;i++){ //////////////////////////고장난거 바꾸고 3으로바꾸기
    if(digitalRead(Reed[i])==HIGH){
      cB='a'+i;
      return cB;
    }
  }
  cB='0';
  return cB;//아무것도 빼지않음
}
void sentApp(char cB){
  if(cB=='0') return ;
  WeightMeasurement.writeValue(cB);
  Weight.writeValue(cB);
  //Weight.writeValue('');
  Serial.println(cB);
  cB='0';
  
  sentApp(cB);
  
}


  
  
  


long debounce=100;
void loop() {
  //sentApp(cB);
   int Button = digitalRead( PUSH_PIN );
  int doflag=0;

BLEDevice central = BLE.central();
   digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  
    if(Button==LOW) 
  { 
      Serial.println("dd");
    
    ti=millis();
    digitalWrite(relay,HIGH);
  

     if (central) {
    
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
    displayColor("green", 0, 255, 0, 1000);
    while(central.connected())
    {
       if(checkBlank()!='0')
       {
        sentApp(cB);
        
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, HIGH);
        digitalWrite(BLUE, LOW);
        Serial.println(cB);
        unsigned long ti2=millis();
        while(millis()-ti2<3000){
           displayColor("blue", 0, 0, 255, 1000);
        }
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, HIGH);
        displayColor("green", 0, 255, 0, 1000);
          Serial.print(F("Disconnected from central: "));
        Serial.println(central.address());
         digitalWrite(relay,LOW);
         displayColor("none", 0, 0, 0, 0); 
  
       }
        if(millis()-ti>100000) break;//1분 30초동안 블투 연결안되면 return
    } 
   
   }
 }
  displayColor("none", 0, 0, 0, 0); 
  digitalWrite(relay,LOW);
  
  
}
