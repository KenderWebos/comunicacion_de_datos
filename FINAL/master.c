// MAESTRO

#include <Wire.h>
#include <LiquidCrystal.h>
//libreria de servo
#include <Servo.h>

int pos = 0;
Servo servo_9;
float humedad = 0;
int signal = 0;
int lectura3=0, cm=0, cm1=0, cm2=0;

float newHum;

void movimientoServo()
{
  for (pos = 0; pos <= 90; pos += 1) 
  {
    servo_9.write(pos);
    delay(10);
  }
  
  for (pos = 90; pos >= 0; pos -= 1) 
  {
    servo_9.write(pos);
    delay(5);
  }
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  
  //MOTORES
  servo_9.attach(9); //, 500, 2500
}

void loop(){
  //enviamos la peticion de informacion al esclavo
  Wire.requestFrom(3,4);//aca sera para recibir. 3,2
  
  //FORMATEOS
  cm1 = Wire.read();
  cm2 = Wire.read();
  cm = (cm2 << 8) + cm1;
  
  humedad = Wire.read();
  signal = Wire.read();
  
  //para cambiar entre modo bluethoot y modo escribir por consola
  //comentar el while ya que bluethoot usa el puerto serial para comunicarse
  // while(true){
  //   Serial.println(humedad);
  //   delay(1000);
  // }

  // bluethoot
  // printOnlyWater(); 
  // console
  printData();
  
  //esperamos 1 segundo
  delay(250);
}

void printOnlyWater(){
  // Serial.print("Distancia: ");
  // Serial.print(cm);
  // Serial.println(" cm ");
  // Serial.print("Humedad: ");

  // humedad 
  // 65 mojado mojado
  // 100 seco

  humedad = ((humedad-65)/35)*100;
  
  humedad = humedad-100;
  // if(humedad<0){
  //   humedad = 0;
  // }
  humedad = fabs(humedad);
  
  Serial.println(int(humedad));

  // Serial.println(" humedad");

  // Serial.print("Signal: ");
  // Serial.print(signal, DEC);
  // Serial.println(" luminocidad");
}

void printData(){
  Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  
  //IMPRIMIR INFORMACION VITAL DE LA PLANTA
  Serial.print("Distancia: ");
  Serial.print(cm);
  Serial.println(" cm ");
  
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.println(" humedad");

  Serial.print("Signal: ");
  Serial.print(signal, DEC);
  Serial.println(" luminocidad");
  
  Serial.println("");
  Serial.println("< ESTADO DE LA PLANTA >");
  //cm alguien cerca // humedad > 85 falta agua // humedad < 50 mucha agua // poca luz
  if(cm < 50 && humedad > 85 && humedad < 50 && signal<100)
  {
    Serial.print(" :) -> OPTIMO");
  }
  else
  {
    Serial.println(" :( -> AYUDA!!");
    if(humedad > 85)
    {
      Serial.println("Falta agua");
    }
    if(humedad < 50)
    {
      Serial.println("Mucha agua");
    }
    if(cm < 50)
    {
      Serial.println("Objeto demasiado cerca");
    }
    if(signal < 70)
    {
      Serial.println("Poca luz");
    }
    
    Serial.print("              __/)\n           .-(__(=:\n        |\ |    \)\n        \ ||\n         \||\n          \|\n           |\n");

    movimientoServo();
  }
}


