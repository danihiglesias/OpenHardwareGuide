/*
 * En este ejemplo leeremos comandos enviados desde la consola
 * del IDE de Arduino y encenderemos o apagaremos un LED según el mensaje recibido.
 * 
 * 
 */

#define SIZE_BUFFER 200 //Tamaño del buffer

String inputString = "";         // cadena que utilizaremos de buffer para los mensajes recibidos
boolean stringComplete = false;  // variable que utilizaremos para saber si la cadena está completa. Comunmente se le suele llamar bandera o flag en inglés

void setup() {

  // Inicializamos el puerto serie del Arduino a 9600 baudios y esperamos a que esté conectado
  Serial.begin(9600);
  while (!Serial) {
    ; // bucle esperando por la conexion USB
  }

  // Reservamos 200 bytes de memoria para la cadena que utilizaremos de buffer
  inputString.reserve(SIZE_BUFFER);

  // Mensaje de bienvenida
  Serial.println("##### Ejemplo 4 Transmitiendo datos ####");

}

void loop() {
  
  // Leemos del puerto serie hasta que se llene el buffer o haya un salto de linea

  // Seteamos la bandera a false
  stringComplete = false;

  // Mientras haya datos disponibles leemos caracter a caracter del puerto serie
  while (Serial.available() && !stringComplete) {
    // Leemos un nuevo caracter:
    char inChar = (char)Serial.read();
    // lo concatenamos a inputString:
    inputString += inChar;
    // comprobamos si es un salto de linea o se ha llenado el buffer, si es asi seteamos la bandera a true
    if (inChar == '\n' || inputString.length() == SIZE_BUFFER) {
      stringComplete = true;
    }
  }

  /*
   * Si se trata de una cadena válida actuamos en consecuencia y vaciamos el buffer
   */
  if(stringComplete){
  
    //Eliminamos el salto de linea si lo hubiese
    inputString.replace("\n", "");
    
    if(inputString.equals("Hola")){
      Serial.println("Saludos");
    }else{
      Serial.println("No entiendo tu mensaje: "+inputString);
    }

    // Limpiamos el buffer
    inputString = "";
  }

  delay(500);
 
}
