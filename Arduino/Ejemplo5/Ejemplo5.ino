/*
 * En este ejemplo leeremos comandos enviados desde la consola
 * del IDE de Arduino y encenderemos o apagaremos un LED según el mensaje recibido.
 * 
 * 
 */

#include <SoftwareSerial.h> //Incluimos los archivos de cabecera de la biblioteca SoftwareSerial para configurar un puerto serie

#define SIZE_BUFFER 200 //Tamaño del buffer

String inputString = "";         // cadena que utilizaremos de buffer para los mensajes recibidos
boolean stringComplete = false;  // variable que utilizaremos para saber si la cadena está completa. Comunmente se le suele llamar bandera o flag en inglés

SoftwareSerial bluetooth(2, 4); // RX, TX  
//  Conexión HM10               Arduino Uno
//     Pin 1/TXD     <---->     Pin 2 RX
//     Pin 2/RXD     <---->     Pin 4 TX

void setup() {

  // Inicializamos el puerto serie del Arduino a 9600 baudios y esperamos a que esté conectado
  // En este caso lo utilizaremos como debugger, es decir, todo las comunicaciones serán retrasmitidas también por este puerto para que sean visible en la consola.
  // Esto permitirá detectar si todo está funcionando correctamente.
  Serial.begin(9600);
  while (!Serial) {
    ; // bucle esperando por la conexion USB
  }

  // Configuramos el baud rate a 9600. El HM-10 debería venir por defecto con 9600. De no ser así deberá modificarse este valor o bien el del módulo mediante comandos AT (ver la wiki)
  bluetooth.begin(9600);

  // Reservamos 200 bytes de memoria para la cadena que utilizaremos de buffer
  inputString.reserve(SIZE_BUFFER);

  // Mensaje de bienvenida
  Serial.println("##### Ejemplo 5 Transmitiendo datos por Bluetooth ####");

}

void loop() {
  
  // Leemos del puerto serie hasta que se llene el buffer o haya un salto de linea

  // Mientras haya datos disponibles leemos caracter a caracter del puerto serie
  // Hemos sustituido el objeto Serial por el creado con anterioridad bluetooth
  while (bluetooth.available() && !stringComplete) {
    // Leemos un nuevo caracter:
    char inChar = (char)bluetooth.read();
    // lo concatenamos a inputString:
    inputString += inChar;
    // comprobamos si es un salto de linea o se ha llenado el buffer, si es asi seteamos la bandera a true
    if (inChar == '\n' || inputString.length() == SIZE_BUFFER) {
      stringComplete = true;
    }
    Serial.print(inChar);
  }

  /*
   * Si se trata de una cadena válida actuamos en consecuencia y vaciamos el buffer
   */
  if(stringComplete){
  
    //Eliminamos el salto de linea si lo hubiese
    inputString.replace("\n", "");
    
    if(inputString.equals("Hola")){
      Serial.println("Recibido por bluetooth:" + inputString);
      Serial.println("Saludos");
      //Enviamos sin salto de linea esta vez. Un detalle inportante a tener en cuenta es que los mensajes en BLE tiene un tamaño 20. Se se envían mensajes más grandes estos se fraccionarán
      bluetooth.print("Saludos");
    }else{
      Serial.println("No entiendo tu mensaje: "+inputString);
      bluetooth.print("No entiendo");
    }

    // Limpiamos el buffer
    inputString = "";
    // Seteamos la bandera a false
    stringComplete = false;
  }

  delay(500);
 
}
