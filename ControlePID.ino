#define enable1 9
#define enable2 10
#define pot A1
// #define pwm x
// min 34 || max 835

int potenciometro = 0;
int erro = 0;
int ierro = 0;
int derro = 0;
int lasterro = 0;
int ang = 45;
int kp = 100;
int kd = 3;
int ki = 3;
int pwm = 0;
int sp = 0;
int byteRead = 0;

void setup() {
    pinMode(enable1, OUTPUT);
    pinMode(enable2, OUTPUT);
    pinMode(pot, INPUT);
    Serial.begin(9600);
    Serial.print("Insira o angulo: ");
    
}

void loop() {
  if(Serial.available()){
    byteRead= Serial.parseInt();
  }

  if (byteRead != 0){
    ang = byteRead;
    Serial.println(byteRead);
  }
      
  sp = map(ang, 0, 180, 17, 795);
  potenciometro = analogRead(pot);


  erro = (sp - potenciometro);    
  ierro += (erro);
  derro = (lasterro - erro);
  lasterro = erro;
  pwm = (kp*erro + ki*ierro + kd*derro);
    
  if(erro > 0){      
    analogWrite(enable1, pwm);
    analogWrite(enable2, 0);

  }else{
    
    analogWrite(enable1, 0);
    analogWrite(enable2, pwm);
      
  }      
    
}
