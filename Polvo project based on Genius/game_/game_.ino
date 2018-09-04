#include <Tone.h>

/*

Simon Says game. Now with sound effects. 
Originaly made by Robert Spann
Code trimmed and sound effects added by digimike


Os botões devem ser configurados para pinos designados sem resistores de pull down
 e conectados ao terra ao invés do +5. 
*/

#include <Tone.h>
Tone speakerpin; // gerador de tom para pino do speaker
// música de início
int starttune[] = {NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4};
int duration2[] = {100, 200, 100, 200, 100, 400, 100, 100, 100, 100, 200, 100, 500};
// música de acerto 
int note[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5};
int duration[] = {100, 100, 100, 300, 100, 300};

boolean button[] = {2, 3, 4, 5}; // pinos dos botões
boolean ledpin[] = {8, 9, 10, 11};  // pinos dos LEDs
int turn = 0;  // contador de vez
int buttonstate = 0;  // checagem do estado do botão
int randomArray[100]; //matriz para armazenar sequencia de acertos (longa..., ninguém chegou tão longe)
int inputArray[100];  


// na inicialização do Arduino
void setup() 
{
  Serial.begin(9600);
  speakerpin.begin(12); // speaker no pino 12

  for(int x=0; x<4; x++)  // pinos dos LEDs como saída
  {
    pinMode(ledpin[x], OUTPUT);
  }
  
  for(int x=0; x<4; x++) 
  {
    pinMode(button[x], INPUT);  // pinos dos botões como entradas
    digitalWrite(button[x], HIGH);  // habilita pull up interno; botões iniciam em estado alto; lógica reversa
  }

  randomSeed(analogRead(0)); // adicionado para gerar "mais aleatoreidade" 
                                                // com a matriz randomicapara a  função de saída
  for (int thisNote = 0; thisNote < 13; thisNote ++) { // toca música de início
     // toca a próxima nota
     speakerpin.play(starttune[thisNote]);
     // mantém a nota:
     if (thisNote==0 || thisNote==2 || thisNote==4 || thisNote== 6) // se estas notas?
     {
       digitalWrite(ledpin[0], HIGH);  // acende o LED vermelho (índice 0 da matriz, primeiro LED)
     }
     if (thisNote==1 || thisNote==3 || thisNote==5 || thisNote== 7 || thisNote==9 || thisNote==11) 
     // se estas notas?
     {
       digitalWrite(ledpin[1], HIGH); // acende o LED amarelo (índice 1 da matriz, segundo LED)
     }
     if (thisNote==8 || thisNote==12)
     // se estas notas?
     {
       digitalWrite(ledpin[2], HIGH); // acende o LED verde (índice 2 da matriz, segundo LED)
     }  
     if (thisNote==10) // se esta nota
     {   
       digitalWrite(ledpin[3], HIGH); // acende o LED azul (índice 3 da matriz, segundo LED)
     }
     delay(duration2[thisNote]); // pausa de cada nota
     // finaliza para iniciar a próxima nota
     speakerpin.stop();
     digitalWrite(ledpin[0], LOW); // apaga todos os LEDs
     digitalWrite(ledpin[1], LOW);
     digitalWrite(ledpin[2], LOW);
     digitalWrite(ledpin[3], LOW);
     delay(25); // pausa
    }
  delay(1000); // pausa
}


// loop principal do programa
void loop() 
{   
  for (int y=0; y<=99; y++)
  {
    // função para gerar a matriz a ser seguida pelo jogador
    digitalWrite(ledpin[0], HIGH); // acende todos os LEDs na inicialização
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
  
    for (int thisNote = 0; thisNote < 6; thisNote ++) {
     // toca a próxima nota
     speakerpin.play(note[thisNote]);
     // mantém a nota; duração
     delay(duration[thisNote]);
     // finaliza para a próxima nota
     speakerpin.stop();
     delay(25); // pausa
    }
    
    digitalWrite(ledpin[0], LOW); // apaga todos os LEDs
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    delay(1000); // pausa
  
// imprime o turno a sequência gerada, e a sequência do jogador
    for (int y=turn; y <= turn; y++)
    { // limitado pela variável de turno
      Serial.println(""); //saída serial com a sequência a ser seguida durante o jogo
      Serial.print("Turn: ");
      Serial.print(y);
      Serial.println("");
      randomArray[y] = random(1, 5); // designa um número randômico serial de (1-4) para um
                                                        //  randomArray[y], y inicia a contagem de turno
      for (int x=0; x <= turn; x++)
      {
        Serial.print(randomArray[x]);
      
        for(int y=0; y<4; y++)
        {
      
          if (randomArray[x] == 1 && ledpin[y] == 8) 
          {  // se está na matriz o que foi mostrado na posição 1?
            digitalWrite(ledpin[y], HIGH); // acende o LED
            speakerpin.play(NOTE_G3, 100); // toca nota
            delay(400); // pausa
            digitalWrite(ledpin[y], LOW); // apaga o LED
            delay(100); // pausa
          }

          if (randomArray[x] == 2 && ledpin[y] == 9) 
          { // se está na matriz o que foi mostrado na posição 2?
            digitalWrite(ledpin[y], HIGH);
            speakerpin.play(NOTE_A3, 100);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }
  
          if (randomArray[x] == 3 && ledpin[y] == 10) 
          { // se está na matriz o que foi mostrado na posição 3?
            digitalWrite(ledpin[y], HIGH);
            speakerpin.play(NOTE_B3, 100);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }

          if (randomArray[x] == 4 && ledpin[y] == 11) 
          { // se está na matriz o que foi mostrado na posição 4?
            digitalWrite(ledpin[y], HIGH);
            speakerpin.play(NOTE_C4, 100);
            delay(400);
            digitalWrite(ledpin[y], LOW);
            delay(100);
          }
        }
      }
    }
    input(); // chama função
  }
}



void input() { // funão para verificar as entradas do jogador contra a matriz gerada

  for (int x=0; x <= turn;)
  { // isto é controlado pelo contador de turno

    for(int y=0; y<4; y++)
    {
      
      buttonstate = digitalRead(button[y]);
    
      if (buttonstate == LOW && button[y] == 2)
      { // verifica se botão pressionado
        digitalWrite(ledpin[0], HIGH); // liga LED
        speakerpin.play(NOTE_G3, 100); // toca nota
        delay(200); // pausa
        digitalWrite(ledpin[0], LOW); // apaga LED
        inputArray[x] = 1; // 1 na variável do lugar da matriz (foi botão 1)
        delay(250); // pausa
        Serial.print(" "); 
        Serial.print(1);
        if (inputArray[x] != randomArray[x]) { // verifica valor de entrada do jogador e bate contra
          fail();                              // o valor no mesmo indice da matriz gerada
        }                                      // chama a função de falhou se não bater
        x++; // próximo
      }
       if (buttonstate == LOW && button[y] == 3) // se botão não pressionado e chegou a 3
      {
        digitalWrite(ledpin[1], HIGH); 
        speakerpin.play(NOTE_A3, 100); 
        delay(200); // pausa
        digitalWrite(ledpin[1], LOW); 
        inputArray[x] = 2;
        delay(250);
        Serial.print(" ");
        Serial.print(2);
        if (inputArray[x] != randomArray[x]) {
          fail();
        }
        x++;
      }

      if (buttonstate == LOW && button[y] == 4)
      {
        digitalWrite(ledpin[2], HIGH);
        speakerpin.play(NOTE_B3, 100);
        delay(200);
        digitalWrite(ledpin[2], LOW);
        inputArray[x] = 3;
        delay(250);
        Serial.print(" ");
        Serial.print(3);
        if (inputArray[x] != randomArray[x]) {
          fail();
        }
        x++;
      }

      if (buttonstate == LOW && button[y] == 5)
      {
        digitalWrite(ledpin[3], HIGH);
        speakerpin.play(NOTE_C4, 100);
        delay(200);
        digitalWrite(ledpin[3], LOW);
        inputArray[x] = 4;
        delay(250);
        Serial.print(" ");
        Serial.print(4);
        if (inputArray[x] != randomArray[x]) 
        {
          fail();
        }
        x++;
      }
    }
  }
  delay(500);
  turn++; // incrementa o contador de turno, 
          // como ultima ação antes chamar novamente a função de saída
}

void fail() { // função usada quando o jogador falha na sequência

  for (int y=0; y<=2; y++)
  { // pisca os LEDs para indicação de falha
    
    digitalWrite(ledpin[0], HIGH); // acende o LED
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
    speakerpin.play(NOTE_G3, 300); // toca nota
    delay(200); // pausa
    digitalWrite(ledpin[0], LOW); // apaga LED
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    speakerpin.play(NOTE_C3, 300); // toca nota
    delay(200); // pausa
  }
  delay(500); // pausa
  turn = -1; // reinicia o valor do turno então o jogo começa 
             // novamente sem necessidade de reset pelo botão
}

// Fim da Compilação
