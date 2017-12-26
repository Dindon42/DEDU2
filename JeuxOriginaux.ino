void Delay_Fraudeur()
{
  //Debut DELAY et TESTFRAUDEUR --------------------------------------
  r = 50 + (12 - vitesse) * random(100) + 5000;
//r = 50 + (12 - vitesse) * random(100);
  x = 0;

  for (int a = 1; a <= r; a++) {
    for (int i = 1; i <= nbj; i++) {
      y = 22 + (2 * i);
      if (digitalRead(y) == HIGH) {
        z = y + 7;
        digitalWrite(z, HIGH);
        x = 1;
      }
      if (x > 0) {
        tone(Tone_Pin, 1500, 1000);
        myservo.write(70);
        delay(1000);
        myservo.write(Servo_LowPos);
        delay(500);
        loop();
      }
    }  
    delay(40);
  }
  //Fin DELAY et TESTFRAUDEUR --------------------------------------
}
