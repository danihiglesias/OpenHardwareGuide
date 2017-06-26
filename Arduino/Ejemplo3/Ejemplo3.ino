/*
Aquí se definen algunas constantes para ser utilizadas a lo largo del código. 
En este caso los pines analógico y digital utilizados para las entradas del programa
*/
#define ANALOG_SENSOR_PIN A0 
#define DIGITAL_SENSOR_PIN 7
#define DIGITAL_RELAY_PIN 2


int digitalValue; /* Variable para el ultimo valor leído de la entrada digital */
int lightAnalogValue; /* Variable para el último valor analógico leído */

void setup() 
{
   // Inicializamos el puerto serie del arduino (en este caso el USB al PC) a 9600 baudios. La consola deberá configurarse a esta velocidad también
   Serial.begin(9600);
   Serial.println("Lectura (LDR) + Actuador (Relé) Ejemplo 3"); //Imprimimos un mensaje de bienvenida del programa
   pinMode(DIGITAL_SENSOR_PIN, INPUT);
   pinMode(DIGITAL_RELAY_PIN, OUTPUT);
}


void loop(){

  digitalValue = digitalRead(DIGITAL_SENSOR_PIN); 
 
  //Escribimos el valor de la señal
  Serial.println("Valor digital:"+ String(digitalValue));
  
  lightAnalogValue = analogRead(ANALOG_SENSOR_PIN); //Leemos el voltaje del sensor
  Serial.print("Valor analógico de (0 to 1023)"); 
   
  Serial.println(lightAnalogValue,DEC); // Escribimos en el puerto serie

  //Añadimos este código para encender o apagar el rele en función de la luminusidad

  if(digitalValue == LOW){
    Serial.println("Relay OFF");
    digitalWrite(DIGITAL_RELAY_PIN,LOW);
  }else{
    Serial.println("Relay ON");
    digitalWrite(DIGITAL_RELAY_PIN,HIGH);
  }
  
  delay(100); //Esperamos

}
