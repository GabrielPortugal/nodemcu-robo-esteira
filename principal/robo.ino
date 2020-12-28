//////////////////////////////////////////
//
void MoverCabecaNao() {
  Serial.println("CABECA");
  servo_cabeca.write(cab_zero);
  delay(500);
  servo_cabeca.write(cab_esquerda);
  delay(500);
  servo_cabeca.write(cab_zero);
  delay(500);
  servo_cabeca.write(cab_esquerda);
  delay(500);
  servo_cabeca.write(cab_zero);
}
//////////////////////////////////////////
//
void ParadaTotal() {
  servo_esteira_dir.detach();
  servo_esteira_esq.detach();
  digitalWrite(pDireita, LOW);
  digitalWrite(pEsquerda, LOW);
}
//////////////////////////////////////////
//
void VirarDireita() {
  servo_esteira_dir.attach(pDireita);
  servo_esteira_esq.attach(pEsquerda);
  servo_esteira_dir.write(dir_max_antihorario);
  servo_esteira_esq.write(esq_max_horario);
}
//////////////////////////////////////////
//
void VirarEsquerda() {
  servo_esteira_dir.attach(pDireita);
  servo_esteira_esq.attach(pEsquerda);
  servo_esteira_dir.write(dir_max_horario);
  servo_esteira_esq.write(esq_max_antihorario);
}
//////////////////////////////////////////
//
void AndarFrente() {
  servo_esteira_dir.attach(pDireita);
  servo_esteira_esq.attach(pEsquerda);
  servo_esteira_dir.write(dir_max_horario);
  servo_esteira_esq.write(esq_max_horario);
}
//////////////////////////////////////////
//
void AndarTras() {
  servo_esteira_dir.attach(pDireita);
  servo_esteira_esq.attach(pEsquerda);
  servo_esteira_dir.write(dir_max_antihorario);
  servo_esteira_esq.write(esq_max_antihorario);
}
