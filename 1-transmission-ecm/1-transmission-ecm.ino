// Ya sirven las interrupciones con freq de sampleo maxima de 90 hz
// Probado con un simulador embedido: motor_sim
// Hay que probar con el verdadero motor
// Crear una rutina de guardado en una memoria sim mientras llega el radiofrequencia

unsigned int ten_ms_sample = 0;
int rpm_motor_count;
int pulse_per_rev = 8;
int ten_ms_counter = 0;
const int sample_time = 200; //200 ms
float rpm_motor;
bool ten_ms_counter_flag = false;
bool motor_sim = false;
bool rpm_motor_interrflag;



#define MotorPin 2



void setup() {

  pinMode(9, OUTPUT);

  Serial.begin(9600);

  SREG = (SREG & 0b01111111); //Desabilitar interrupciones
  TIMSK2 = TIMSK2 | 0b00000001; //Habilita la interrupcion por desbordamiento
  TCCR2B = 0b00000011; //Configura preescala para que FT2 sea de 250 khz
  SREG = (SREG & 0b01111111) | 0b10000000; //Habilitar interrupciones //Desabilitar interrupciones

  attachInterrupt(digitalPinToInterrupt(MotorPin), rpm_motor_interrumpt, RISING);

}


void loop() {

  if (ten_ms_counter_flag == true) {
    Serial.println(rpm_motor);
    Serial.println("y");
    ten_ms_counter_flag = false;
    }
}

void rpm_motor_interrumpt() {
  rpm_motor_interrflag = true;
  rpm_motor_count++;

}

// Timer2 cuenta de 0 a 255, 250E+3/255 = 980.39 -> Por lo tanto cuenta > 9
ISR(TIMER2_OVF_vect) {

  motor_sim = !motor_sim;
  digitalWrite(9, motor_sim);

  ten_ms_counter++;
  if (ten_ms_counter > 195) { // Sample time would be 100 ms
    rpm_motor = (float (rpm_motor_count)/float(pulse_per_rev)) * (1000/float(sample_time))*60; //Resolution = 13.64 RPM
    rpm_motor_count = 0;
    ten_ms_counter_flag = true;
    ten_ms_counter = 0;
  }




}
