#include <SoftwareSerial.h>

// Ya sirven las interrupciones con freq de sampleo maxima de 90 hz
// Probado con un simulador embedido: motor_sim
// Hay que probar con el verdadero motor
// Crear una rutina de guardado en una memoria sim mientras llega el radiofrequencia

unsigned int ten_ms_sample = 0;
int rpm_motor_count = 0;
int rpm_gearbox_count = 0;
int pulse_per_rev = 8;
int ten_ms_counter = 0;
const int sample_time = 200; // 200 ms
float rpm_motor = 0;
float rpm_gearbox = 0;
bool ten_ms_counter_flag = false;
bool motor_sim = false;
bool rpm_motor_interrflag = false;
bool rpm_gearbox_interrflag = false;

#define MotorPin 2
#define GearboxPin 3

// Create SoftwareSerial object on pin 8 (TX), pin 7 (RX not used)
SoftwareSerial mySerial(7, 8); // RX, TX

void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(MotorPin, INPUT);
  pinMode(GearboxPin, INPUT);

  Serial.begin(9600);      // USB serial
  mySerial.begin(9600);    // Software serial on pin 8

  // Configurar Timer2
  SREG &= 0b01111111; // Deshabilitar interrupciones
  TIMSK2 |= 0b00000001; // Habilita la interrupción por desbordamiento
  TCCR2B = 0b00000011; // Preescala para que FT2 sea de 250 kHz
  SREG |= 0b10000000; // Habilitar interrupciones

  // Interrupciones externas
  attachInterrupt(digitalPinToInterrupt(MotorPin), rpm_motor_interrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(GearboxPin), rpm_gearbox_interrupt, RISING);
}

void loop() {
  if (ten_ms_counter_flag) {
    // Print to USB serial
    Serial.print(millis());
    Serial.print(",");
    Serial.print(rpm_motor);
    Serial.print(",");
    Serial.println(rpm_gearbox); 

    // Print to pin 8 serial
    mySerial.print(millis());
    mySerial.print(",");
    mySerial.print(rpm_motor);
    mySerial.print(",");
    mySerial.println(rpm_gearbox); 

    ten_ms_counter_flag = false;
  }
}

void rpm_motor_interrupt() {
  rpm_motor_interrflag = true;
  rpm_motor_count++;
}

void rpm_gearbox_interrupt() {
  rpm_gearbox_interrflag = true;
  rpm_gearbox_count++;
}

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
