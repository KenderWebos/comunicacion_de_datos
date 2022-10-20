// ESCLAVO

#include <Wire.h>
// informacion para enviar por serializacion
char b[4]={0, 0, 0, 0};

//VARIABLES GLOBALES para el doc
int cm = 0;
int signal = 0;
int humedad = 0;
float tiempo;//tiempo en que demora en regresar el pulso
int distancia;//Calcula la distancia (viaje de ida y vuelta) que recorre el pulso

 //<PARA EL SENSOR DE PROXIMIDAD>
 int Echo=3;
 int Trig=4;

 //Constantes
 const float VEL_SONIDO=29.2;//Velocidad del sonido cm/us(depende de variables ambientales)
 const float espera=4;//Espera en microsegundos, puede elegir cualqueir valor que desee
 const float esperaUS=10;//El sensor necesita como minimo 10us en alto

//</PARA EL SENSOR DE PROXIMIDAD>

//<sensorLuz y humedad>
int SensorPin = A0; // humedad
int port_signal = A1; // luz
//</sensorLuz y humedad>

// >> SETUP <<
void setup()
{
  Serial.begin(9600);
  Wire.begin(3);
  Wire.onRequest(peticion);
  setupSensorProximidad();
}

//>> FUNCIONES <<
void inputSensorProximidad()
{
    digitalWrite(Trig,LOW);
    delayMicroseconds(espera);
    digitalWrite(Trig,HIGH);
    delayMicroseconds(esperaUS);
    digitalWrite(Trig,LOW);

    tiempo=pulseIn(Echo,HIGH);//se mantiene en HIGH hasta recibir el pulso
    tiempo=tiempo/2;//se divide el tiempo total (ida+regreso) por la mitad
    distancia=tiempo/29.2;
    //Serial.println(distancia);
    delay(50);
}

void setupSensorProximidad()
{
    pinMode(Trig,OUTPUT);
    pinMode(Echo,INPUT);
}

int inputSensorHumedad(){
    humedad = analogRead(SensorPin);
    return humedad;
}

int inputSensorLuz(){
    signal = analogRead(port_signal);
    return signal;
}

//SETUPS
void peticion()
{
  b[0] = lowByte(distancia);//cm
  b[1] = highByte(distancia);//cm
  
  b[2] = (humedad/10); // para enviarlo como byte
  b[3] = (signal/10); // para enviarlo como byte
  //signal

  Wire.write(b, 8); //2
}

// >> LOOP <<
void loop()
{
  inputSensorProximidad();
  inputSensorHumedad();
  inputSensorLuz();

  mostrarInformacion();

  delay(500);
}

void mostrarInformacion(){
  Serial.print("\n\n\n\n\n\n\n\n");
  Serial.println("-----( ͡❛ ‿ ͡❛)-------");
  Serial.print("Proximidad: ");
  Serial.println(distancia); // antes cm
  Serial.print("Humedad: ");
  Serial.println(humedad);
  Serial.print("Luminocidad: ");
  Serial.println(signal, DEC);
  Serial.println("----------------------");
}

