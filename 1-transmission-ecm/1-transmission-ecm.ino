#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// =======================
// CONFIGURACIÓN DE PINES
// =======================

// GPS
#define GPS_RX 4       // GPS recibe datos del Arduino (TX)
#define GPS_TX 5       // GPS envía datos al Arduino (RX)
SoftwareSerial gpsSerial(GPS_TX, GPS_RX); // RX, TX invertidos para SoftwareSerial

// Comunicación serial adicional
SoftwareSerial mySerial(7, 8); // Pin 7 (RX), Pin 8 (TX)

// Sensores de RPM
#define MotorPin 2       // Pin D2: interrupción externa INT0
#define GearboxPin 3     // Pin D3: interrupción externa INT1

// =======================
// VARIABLES GLOBALES
// =======================

TinyGPSPlus gps;

const int pulse_per_rev = 8;
const int sample_time = 200;

int rpm_motor_count = 0;
int rpm_gearbox_count = 0;
int ten_ms_counter = 0;

float rpm_motor = 0;
float rpm_gearbox = 0;

bool ten_ms_counter_flag = false;
bool motor_sim = false;

// =======================
// CONFIGURACIÓN INICIAL
// =======================

void setup() {
  // Pines de simulación
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);


  // Pines de entrada
  pinMode(MotorPin, INPUT);
  pinMode(GearboxPin, INPUT);

  // Inicializar comunicaciones
  Serial.begin(9600);       // USB
  mySerial.begin(9600);     // Comunicación por pin 8
  gpsSerial.begin(9600);    // GPS

  // Configurar Timer2
  SREG &= 0b01111111; // Deshabilitar interrupciones
  TIMSK2 |= 0b00000001; // Habilita la interrupción por desbordamiento
  TCCR2B = 0b00000011; // Preescala para que FT2 sea de 250 kHz
  SREG |= 0b10000000; // Habilitar interrupciones

  // Interrupciones externas
  attachInterrupt(digitalPinToInterrupt(MotorPin), rpm_motor_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(GearboxPin), rpm_gearbox_interrupt, RISING);
}

// =======================
// BUCLE PRINCIPAL
// =======================

void loop() {
  // Leer datos del GPS
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // Si se cumplió el tiempo de muestreo
  if (ten_ms_counter_flag) {
    float lat = gps.location.isValid() ? gps.location.lat() : 0.0;
    float lng = gps.location.isValid() ? gps.location.lng() : 0.0;

    // Enviar por USB
    Serial.print(millis());
    Serial.print(",");
    Serial.print(rpm_motor);
    Serial.print(",");
    Serial.print(rpm_gearbox);
    Serial.print(",");
    Serial.print(lat, 6);
    Serial.print(",");
    Serial.println(lng, 6);

    // Enviar por pin 8
    mySerial.print(millis());
    mySerial.print(",");
    mySerial.print(rpm_motor);
    mySerial.print(",");
    mySerial.print(rpm_gearbox);
    mySerial.print(",");
    mySerial.print(lat, 6);
    mySerial.print(",");
    mySerial.println(lng, 6);

    ten_ms_counter_flag = false;
  }
}

// =======================
// INTERRUPCIONES DE RPM
// =======================

void rpm_motor_interrupt() {
  rpm_motor_count++;
}

void rpm_gearbox_interrupt() {
  rpm_gearbox_count++;
}

// =======================
// INTERRUPCIÓN DEL TIMER
// =======================

ISR(TIMER2_OVF_vect) {
  motor_sim = !motor_sim;
  digitalWrite(9, motor_sim);
  digitalWrite(10, motor_sim);

  ten_ms_counter++;
  if (ten_ms_counter > 195) {
    rpm_motor = (float(rpm_motor_count) / pulse_per_rev) * (1000.0 / sample_time) * 60.0;
    rpm_gearbox = (float(rpm_gearbox_count) / pulse_per_rev) * (1000.0 / sample_time) * 60.0;

    rpm_motor_count = 0;
    rpm_gearbox_count = 0;
    ten_ms_counter_flag = true;
    ten_ms_counter = 0;
  }
}