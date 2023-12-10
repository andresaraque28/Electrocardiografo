
#include <LiquidCrystal.h>


const int pin2 = 2;          // Pin de entrada para medir el periodo
volatile unsigned long tiempoInicio = 0;    // Almacena el tiempo de inicio del pulso
volatile unsigned long tinicio = 0; 
volatile unsigned long periodo = 0;         // Almacena el periodo de la señal
float frecuencia = 0; 

volatile boolean flancoAscendente = false;  // Indica si se detectó un flanco ascendente
volatile unsigned long contador = 0;        // Contador de periodos
const unsigned long duracionConteo = 60000;  // Duración del conteo en milisegundos
unsigned long duracion;
const int pin7 = 7;      // Pin de salida para generar el pulso led bradicardia
const int pin8 = 8;      // Pin de salida para generar el pulso led normal
const int pin13 = 13;    // Pin de salida para generar el pulso led taquicardia
const int pinLED = 10;


//pines lcd
const int rs = 12;  // Pin de Registro de Selección
const int en = 11;  // Pin de Habilitación
const int d4 = 5;  // Pin de Datos 4
const int d5 = 4;  // Pin de Datos 5
const int d6 = 3; // Pin de Datos 6
const int d7 = 6; // Pin de Datos 7

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  pinMode(pin2, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin2), medirPeriodo, RISING);
  Serial.begin(9600);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin13, OUTPUT);
  pinMode(pinLED, OUTPUT);
  lcd.begin(16, 2);
  
 

}

void loop() {
  
  tinicio = millis();

  if (duracion < duracionConteo) {
  lcd.setCursor(0, 0);
  lcd.print("FC:" );
  lcd.setCursor(3, 0);
  lcd.print(frecuencia);

  lcd.setCursor(10, 0);
  lcd.print("T:" );
  lcd.setCursor(12, 0);
  lcd.print(duracion);

  
  
  lcd.setCursor(0, 1);
  lcd.print("Pulsos:" );
  lcd.setCursor(8, 1);
  lcd.print(contador);
    
    }
    

  if(tinicio > duracionConteo){
    lcd.clear();
    delay(200);
    
    if (contador < 60) {
    lcd.setCursor(0, 0);
    lcd.print("FC:" );
    lcd.setCursor(4, 0);
    lcd.print(contador);

    lcd.setCursor(0, 1);
    lcd.print("Bradicardia");
    delay(5000);


    } else if (contador >= 60 && contador <= 120) {
    lcd.setCursor(0, 0);
    lcd.print("FC:" );
    lcd.setCursor(4, 0);
    lcd.print(contador);
    lcd.setCursor(0, 1);
    lcd.print("Normal");
    delay(5000);
   } else {
    lcd.setCursor(0, 0);
    lcd.print("FC:" );
    lcd.setCursor(4, 0);
    lcd.print(contador);
    lcd.setCursor(0, 1);
    lcd.print("taquicardia");
    delay(5000);
    }
  }
  
 
}

void medirPeriodo() {
  if (!flancoAscendente) {
    // Primer flanco ascendente, inicia el pulso
    tiempoInicio = millis();
    digitalWrite(pinLED, HIGH);
    delay(50);  // Puedes ajustar el tiempo de encendido del LED si es necesario
    digitalWrite(pinLED, LOW);
    flancoAscendente = true;
  } else {
    // Segundo flanco ascendente, calcula el periodo
    periodo = millis() - tiempoInicio;

    // Calcula la frecuencia
    frecuencia = 1000.0 / periodo;
    
      // Convierte el periodo a frecuencia en Hz

  
    Serial.print("Frecuencia:");
    Serial.print(frecuencia);
    Serial.println(" Hz");


    contador++;  // Incrementa el contador de periodos
    
    Serial.print("Contador: ");
    Serial.println(contador);

    digitalWrite(pinLED, HIGH);
    delay(50);  // Puedes ajustar el tiempo de encendido del LED si es necesario
    digitalWrite(pinLED, LOW);

    flancoAscendente = false;  // Reinicia para esperar el próximo flanco ascendente
  }
  unsigned long tiempoActual = millis();
  duracion = (duracionConteo - tiempoActual)/1000 ;
  Serial.print("Duración: ");
  Serial.println(duracion);
  if (contador < 60) {
    digitalWrite(pin7, HIGH);
    digitalWrite(pin8, LOW);
    digitalWrite(pin13, LOW);

    } else if (contador >= 60 && contador <= 120) {
      digitalWrite(pin8, HIGH);
      digitalWrite(pin7, LOW);
      digitalWrite(pin13, LOW);
   } else {
      digitalWrite(pin13, HIGH);
      digitalWrite(pin8, LOW);
      digitalWrite(pin7, LOW);
    }
  // Detiene el bucle loop después de un minuto
 if (duracion >= duracionConteo) {
    while (true) {
      // el bucle se detendrá aquí
    }
  }
  

}

