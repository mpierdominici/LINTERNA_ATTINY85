 #define SHIFT_CLK_PIN 8
 #define LATCH_CLK_PIN 9
 #define DATA_PIN 10
 #define BYTE_SIZE 8
 void sendOneByteSpi(bool data[BYTE_SIZE]);
 
void setup() {
  pinMode(SHIFT_CLK_PIN,OUTPUT);//configuro los pines del spi como salida
  pinMode(LATCH_CLK_PIN,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  bool t1[8]={1,1,1,1,0,0,1,0};
  bool t2[8]={1,0,1,0,1,0,1,0};
  bool t3[8]={1,1,1,1,1,1,1,1};
  bool t4[8];
  //sendOneByteSpi(t1);
  //delay(1500);
  //sendOneByteSpi(t2);
  //delay(1500);
  
  //sendOneByteSpi(t3);
 // delay(1500);

//  for(int i=0;i<7;i++){ //pa un lado
//    for(int j=0;j<8;j++){
//      t4[j]=false;
//    }
//    t4[i]=true;
//    t4[i+1]=true;
//    sendOneByteSpi(t4);
//    delay(50);
//  }
  for(int i=0;i<4;i++){ //pa adentro
    for(int j=0;j<8;j++){
      t4[j]=false;
    }
    t4[i]=true;
    t4[7-i]=true;
    sendOneByteSpi(t4);
    delay(50);
  }
   for(int i=0;i<4;i++){ //pa afuera
    for(int j=0;j<8;j++){
      t4[j]=false;
    }
    t4[3-i]=true;
    t4[i+4]=true;
    sendOneByteSpi(t4);
    delay(50);
  }

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
