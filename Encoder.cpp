#define ENCODER_A_PIN 2  // Pin untuk Encoder A
#define ENCODER_B_PIN 3  // Pin untuk Encoder B
#define RPWM_PIN 9       // Pin untuk RPWM
#define LPWM_PIN 10      // Pin untuk LPWM
#define ENABLE_PIN 11    // Pin untuk Enable motor

volatile int encoderPos = 0;    // Variabel untuk posisi encoder
volatile bool directionCW = true; // Arah putaran motor (CW/CCW)

void setup() {
  // Set pin mode
  pinMode(ENCODER_A_PIN, INPUT);
  pinMode(ENCODER_B_PIN, INPUT);
  pinMode(RPWM_PIN, OUTPUT);
  pinMode(LPWM_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  // Attach interrupts for encoder pins
  attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_B_PIN), readEncoder, CHANGE);

  Serial.begin(9600);
}

void loop() {
  // Maju 2 detik
  maju();
  delay(2000);
  
  // Stop 1 detik
  stopMotor();
  delay(1000);

  // Mundur 2 detik
  mundur();
  delay(2000);

  // Stop 1 detik
  stopMotor();
  delay(1000);

  // Tampilkan arah pergerakan motor dan nilai encoder
  if (directionCW) {
    Serial.print("Motor Direction: CW | ");
  } else {
    Serial.print("Motor Direction: CCW | ");
  }
  
  // Tampilkan nilai posisi encoder
  Serial.print("Encoder Position: ");
  Serial.println(encoderPos);

  //delay(500);  // Tunda untuk debugging
}

// Fungsi yang dipanggil saat terjadi perubahan sinyal encoder
void readEncoder() {
  int A = digitalRead(ENCODER_A_PIN);
  int B = digitalRead(ENCODER_B_PIN);

  // Tentukan arah pergerakan berdasarkan sinyal dari Encoder A dan B
  if (A == B) {
    encoderPos++;           // Menambah posisi encoder (CW)
    directionCW = true;      // Motor bergerak CW
  } else {
    encoderPos--;           // Mengurangi posisi encoder (CCW)
    directionCW = false;     // Motor bergerak CCW
  }
}

// Fungsi untuk menggerakkan motor maju
void maju() {
  digitalWrite(ENABLE_PIN, HIGH);  // Aktifkan motor
  analogWrite(RPWM_PIN, 255);      // RPWM penuh (motor maju)
  analogWrite(LPWM_PIN, 0);        // LPWM 0
}

// Fungsi untuk menggerakkan motor mundur
void mundur() {
  digitalWrite(ENABLE_PIN, HIGH);  // Aktifkan motor
  analogWrite(RPWM_PIN, 0);        // RPWM 0
  analogWrite(LPWM_PIN, 255);      // LPWM penuh (motor mundur)
}

// Fungsi untuk menghentikan motor
void stopMotor() {
  digitalWrite(ENABLE_PIN, LOW);   // Matikan motor
  analogWrite(RPWM_PIN, 0);        // Set RPWM 0
  analogWrite(LPWM_PIN, 0);        // Set LPWM 0
}