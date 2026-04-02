/*
 * PROYECTO: Sistema de Supervisión de Planta - ACME S.A.
 * MÓDULO: Nodo de Control Principal (Clasificación y Ambiente)
 * HARDWARE: Arduino Mega 2560, LCD I2C 20x4, HC-SR04, DHT22, LDR.
 */

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- Definición de Pines (Hardware Map) ---
#define DHTPIN 2
#define DHTTYPE DHT22
#define ECHO_PIN 3   
#define TRIG_PIN 4   
#define LDR_PIN A0

// --- Instancias de Componentes ---
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

// --- Variables de Estado del Proceso ---
int contadorCajas = 0;
String clasificacion = "ESPERANDO...";

void setup() {
  // Inicialización de comunicaciones
  Serial.begin(9600);
  dht.begin();
  
  // Inicialización de HMI (Pantalla)
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print("  ACME SMART PLANT  ");
  
  // Configuración de E/S del sensor ultrasónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Secuencia de arranque
  Serial.println("--- INICIANDO SISTEMA DE SUPERVISIÓN ACME ---");
  delay(2000);
  lcd.clear();
}

void loop() {
  // ==========================================
  // 1. CAPTURA DE DATOS Y CLASIFICACIÓN (HC-SR04)
  // ==========================================
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duracion = pulseIn(ECHO_PIN, HIGH);
  int distancia = duracion * 0.034 / 2; // Cálculo de distancia en cm

  // Lógica de detección de caja en la cinta
  if (distancia >= 2 && distancia <= 30) {
    contadorCajas++;
    clasificacion = (distancia < 15) ? "ASCENSOR (ALTA)" : "ESCALERA (BAJA)";
    delay(800); // Retardo para evitar el "doble conteo" de la misma caja
  }

  // ==========================================
  // 2. LECTURA AMBIENTAL (DHT22 y LDR)
  // ==========================================
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();
  int luz = analogRead(LDR_PIN);

  // Verificación de seguridad del sensor DHT22
  String estadoDHT = "OK";
  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("[ALERTA] Falla de lectura en nodo DHT22");
    estadoDHT = "FALLO";
    // Asignamos valores a 0 para que la LCD no muestre basura
    temperatura = 0.0;
    humedad = 0.0;
  }

  // ==========================================
  // 3. ACTUALIZACIÓN DE HMI (LCD 20x4)
  // ==========================================
  lcd.setCursor(0, 0); //Columna Fila
  lcd.print("TIPO: "); 
  lcd.print(clasificacion);
  
  lcd.setCursor(0, 1);
  lcd.print("CONTEO TOTAL: "); 
  lcd.print(contadorCajas);
  
  lcd.setCursor(0, 2);
  lcd.print("--------------------");
  
  lcd.setCursor(0, 3); 
  lcd.print(temperatura, 1); lcd.print("C  ");
  lcd.print(humedad, 0); lcd.print("%H  ");
  lcd.print("L:"); lcd.print(luz);
  // Limpiar caracteres residuales si la luz baja de 4 a 3 cifras
  lcd.print(" "); 

  // ==========================================
  // 4. REGISTRO DE DATOS (LOG INDUSTRIAL)
  // ==========================================
  Serial.print("[ACME_LOG] ");
  Serial.print("Cajas: "); Serial.print(contadorCajas);
  Serial.print(" | Ultima: "); Serial.print(clasificacion);
  Serial.print(" | Temp: "); Serial.print(temperatura, 1); Serial.print("C");
  Serial.print(" | Hum: "); Serial.print(humedad, 0); Serial.print("%");
  Serial.print(" | Luz(ADC): "); Serial.print(luz);
  Serial.print(" | Sensor_Ambiente: "); Serial.println(estadoDHT);

  delay(2000); // Frecuencia de muestreo del sistema
}