 #define SHIFT_CLK_PIN 0
 #define LATCH_CLK_PIN 1
 #define DATA_PIN 2
 #define BUTTON_PIN 3
 #define BYTE_SIZE 8
 #define TIME_EVENT_MILLIS 1500
typedef enum 
{ 
    OFF,
    ON,  
    PAFUERA,
    DESTELLO 
} modos;
 
 void sendOneByteSpi(bool data[BYTE_SIZE]);
 
void setup() {
  pinMode(SHIFT_CLK_PIN,OUTPUT);//configuro los pines del spi como salida
  pinMode(LATCH_CLK_PIN,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
  pinMode(BUTTON_PIN,INPUT);
  
  // put your setup code here, to run once:

}

modos modoActual=OFF;
int i=0;
int destello=0;
bool dest=true;
bool paUnLado=true;
bool once=false;
bool edgeDet=false;
unsigned long currTime=0;
bool lastOff=false;
modos lastMode;
void loop() {
  
  bool allOff[8]={0,0,0,0,0,0,0,0};
  bool allOn[8]={1,1,1,1,1,1,1,1};
  bool patronDestello[]={1,1,0,0,0,1,1,0,0,0,0,0,0};
  bool t4[8];

  switch (modoActual){
  case OFF:
    if(!once){
      sendOneByteSpi(allOff);
      once=true;
    }
        break;
     case ON:
    if(!once){
      sendOneByteSpi(allOn);
      once=true;
    }
        break;
        case PAFUERA:
          
    for(int j=0;j<8;j++){
      t4[j]=false;
    }
    if(paUnLado){
      t4[i]=true;
    t4[7-i]=true;
    }else{
      t4[3-i]=true;
    t4[i+4]=true;
    }
    
    sendOneByteSpi(t4);
    i++;
    if(i>3){
      i=0;
      paUnLado=!paUnLado;
    }
    
       break;

      case DESTELLO:

      if(patronDestello[destello]){
        sendOneByteSpi(allOn);
      }else{
        sendOneByteSpi(allOff);
      }

      destello++;
      if(destello>12){
      destello=0; 
    }
      break;
}

if(digitalRead(BUTTON_PIN)){
  if(!edgeDet){
    currTime=millis()+TIME_EVENT_MILLIS;
  }
  
  edgeDet=true;
  
}else{
  if(edgeDet){
    if(millis()>currTime){
      lastMode=modoActual;
      modoActual=OFF;
      lastOff=true;
    }else{
     
    
    modoActual=modoActual+1;
    if(lastOff){
      lastOff=false;
      modoActual=lastMode;
    }
  if(modoActual>DESTELLO){
    modoActual=ON;
  }
    }
    once=false;
   edgeDet=false; 
  }
  
}
delay(50);

}



void sendOneByteSpi(bool data[BYTE_SIZE]){
  
  for (int i=0;i<BYTE_SIZE;i++){
    digitalWrite(DATA_PIN,data[i]);
    //Serial.println();
    digitalWrite(SHIFT_CLK_PIN,HIGH);
    delay(1);
    digitalWrite(SHIFT_CLK_PIN,LOW);
  }
  digitalWrite(LATCH_CLK_PIN,HIGH);
  delay(1);
 digitalWrite(LATCH_CLK_PIN,LOW);
}
