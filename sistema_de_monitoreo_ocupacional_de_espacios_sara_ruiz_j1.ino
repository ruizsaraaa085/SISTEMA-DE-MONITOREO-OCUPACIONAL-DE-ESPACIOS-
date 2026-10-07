// Pines de los Sensores (Entradas)
const int trigEntrada = 12;
const int echoEntrada = 11;
const int trigSalida = 10;
const int echoSalida = 9;
const int pinBoton = 8;

// Pines de los Actuadores (Salidas)
const int ledVerde = 7;
const int ledAmarillo = 6;
const int ledRojo = 4;
const int buzzer = 5;

// Variables de Control
int personasEnSalon = 0;
const int capacidadMaxima = 15; // Límite máximo del salón

// Variables para evitar que un solo cruce cuente mil veces
bool personaEntrando = false;
bool personaSaliendo = false;
bool botonPresionado = false;

void setup() {
  // Configurar Entradas
  pinMode(echoEntrada, INPUT);
  pinMode(echoSalida, INPUT);
  pinMode(pinBoton, INPUT);
  
  // Configurar Salidas
  pinMode(trigEntrada, OUTPUT);
  pinMode(trigSalida, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("=========================================");
  Serial.println("SISTEMA DE AFORO - MONITOREO EN TIEMPO REAL");
  Serial.println("=========================================");
}

void loop() {
  // Leer distancias con un tiempo de espera (timeout) muy corto para velocidad ultra rápida
  long distEntrada = obtenerDistancia(trigEntrada, echoEntrada);
  long distSalida = obtenerDistancia(trigSalida, echoSalida);
  int estadoBoton = digitalRead(pinBoton);

  // --- LÓGICA DEL SENSOR DE ENTRADA ---
  if (distEntrada > 0 && distEntrada < 60) {
    if (!personaEntrando) { 
      // NUEVO CAMBIO: Solo suma si NO ha llegado a la capacidad máxima (15)
      if (personasEnSalon < capacidadMaxima) {
        personasEnSalon++;
        Serial.print("[ENTRADA AUTO] -> Persona detectada. Total en salon: ");
        Serial.println(personasEnSalon);
      } else {
        Serial.println("[ALERTA] -> Intento de entrada RECHAZADO: Salon lleno (Limite 15).");
      }
      personaEntrando = true;
      delay(150); 
    }
  } else {
    personaEntrando = false; 
  }

  // --- LÓGICA DEL SENSOR DE SALIDA ---
  if (distSalida > 0 && distSalida < 60) {
    if (!personaSaliendo) {
      if (personasEnSalon > 0) { // No podemos tener personas negativas
        personasEnSalon--;
      }
      personaSaliendo = true;
      
      Serial.print("[SALIDA AUTO]  -> Persona detectada. Total en salon: ");
      Serial.println(personasEnSalon);
      delay(150);
    }
  } else {
    personaSaliendo = false;
  }

  // --- LÓGICA DEL BOTÓN MANUAL ---
  if (estadoBoton == HIGH) {
    if (!botonPresionado) {
      // NUEVO CAMBIO: Solo suma si NO ha llegado a la capacidad máxima (15)
      if (personasEnSalon < capacidadMaxima) {
        personasEnSalon++;
        Serial.print("[BOTON MANUAL] -> Registro manual.   Total en salon: ");
        Serial.println(personasEnSalon);
      } else {
        Serial.println("[ALERTA] -> Intento de boton manual RECHAZADO: Salon lleno (Limite 15).");
      }
      botonPresionado = true;
      delay(150);
    }
  } else {
    botonPresionado = false;
  }

  // --- CONTROL DE OCUPACIÓN (LEDs Y BUZZER) ---
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, LOW);
  digitalWrite(ledRojo, LOW);
  noTone(buzzer);

  if (personasEnSalon == 0) {
    // Salon Vacio
  }
  else if (personasEnSalon > 0 && personasEnSalon <= 5) {
    digitalWrite(ledVerde, HIGH);
  } 
  else if (personasEnSalon >= 6 && personasEnSalon <= 14) {
    digitalWrite(ledAmarillo, HIGH);
  } 
  else if (personasEnSalon >= 15) {
    digitalWrite(ledRojo, HIGH);
    tone(buzzer, 800); 
  }

  delay(30); 
}

long obtenerDistancia(int pinTrig, int pinEcho) {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  
  long duracion = pulseIn(pinEcho, HIGH, 4000); 
  if (duracion == 0) return 999; 
  return duracion * 0.034 / 2;
}




