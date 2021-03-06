#define trig_pin 13
#define echo_pin 12
#define led_1 7
#define led_2 6
#define piezo 3
#define quick_button 9

//GLOBAL VARIABLES
char input_array[] = {'1','2','3','4','5','6','7','8','9','q','w','e','r','t'};
int myarray[] = {0,50,100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000};
short myarraysize = 21;
char input;
char  goback_input;
//bool checker = true;
char while_loop_breaker;
int counter = 0;
//delay variables
int ascend_descend_delay = 50;
int beats_delay = 50;
int bell_delay = 1000;
int bump_delay = 100;
int oh_biscuits_delay = 20;


//MAKE SURE YOU UPDATE myarraysize WHEN YOU CHANGE MYARRAY ELEMENTS SIZE
//MAKE SURE WHEN YOU UPDATE input_array YOU CHANGE INPUT_ARRAY ELEMENT SIZE

//LED GOES ON WHEN DISTANCE IS LESS THAN 20
//YOU CAN CHECK EXACT DISTANCE IN THE SERIAL MONITOR AS WELL


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  //randomSeed(random(0,200000)); 
  //pinmode for pins for the piezo, led, and sound sensor
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  pinMode(led_1,OUTPUT);
  pinMode(led_2,OUTPUT);
  pinMode(piezo,OUTPUT);
  pinMode(quick_button,INPUT);
  //inputs for music selection
  Serial.println("Welcome to the Laptop Security Program!");
  Serial.println("Which alarm do you what?");
  Serial.println("1. Ascending 2. Descending 3. Single Low  4. Single High 5.Single Mid 6. Beats 7. Beats_2 ");
  Serial.println("8.Bells 9.Bells_2 q.Bump_Low w.Bump_Mid e.Bump_High r.Normal Alarm(Low To High) t.OhBiscuits ");
  Serial.println();
  Serial.println("If you want to go back to change your music selection just press R when the programs running!");
  input = '?';
  while(input == '?') {
  if(Serial.available() > 0){
    input = Serial.read();
    delay(500);
    //end of input reading in loop
    }
  if (digitalRead(quick_button) == HIGH){
    delay(300);
    digitalWrite(led_2,HIGH);
    delay(1000);
    digitalWrite(led_2,LOW);
    counter ++;
    if (counter > 13){
      counter = 0;
    }
    input = input_array[counter];
  }
  //end of while loop
  }
  //end of setup function
}

//Music functions
void ascending(){
for (int x = 0; x < myarraysize; ++x){
  tone(3,myarray[x]);
  delay(ascend_descend_delay);
  }
}

void descending(){
 for(int x = myarraysize; x >= 0; --x){
  tone(3,myarray[x]);
  delay(ascend_descend_delay);
 }
}

void single_low(){
  tone(3,myarray[0]);
}

void single_high(){
  tone(3,myarray[20]);
}

void single_mid(){
  tone(3,myarray[10]);
}

void beats(){
  tone(3,myarray[10]);
  delay(beats_delay);
  tone(3,myarray[5]);
  delay(beats_delay);
  tone(3,myarray[7]);
  delay(beats_delay);
  tone(3,myarray[3]);
  delay(beats_delay);
}

void beats_2(){
  tone(3,myarray[3]);
  delay(beats_delay);
  tone(3,myarray[5]);
  delay(beats_delay);
  tone(3,myarray[7]);
  delay(beats_delay);
  tone(3,myarray[10]);
  delay(beats_delay);
}

void bells(){
  tone(3,myarray[20]);
  delay(bell_delay);
  tone(3,myarray[10]);
  delay(bell_delay);
  tone(3,myarray[0]);
  delay(bell_delay);
}

void bells_2(){
  tone(3,myarray[0]);
  delay(bell_delay);
  tone(3,myarray[10]);
  delay(bell_delay);
  tone(3,myarray[20]);
  delay(bell_delay);
}

void bump_low(){
  tone(3,myarray[0]);
  delay(bump_delay);
  noTone(3);
  delay(bump_delay);
}


void bump_mid(){
  tone(3,myarray[10]);
  delay(bump_delay);
  noTone(3);
  delay(bump_delay);
}


void bump_high(){
  tone(3,myarray[20]);
  delay(bump_delay);
  noTone(3);
  delay(bump_delay);
}


void normal_alarm(){
  tone(3,myarray[0]);
  tone(3,myarray[20]);
}

void oh_biscuits(){
  tone(3,myarray[random(0,21)]);
  delay(random(0,2000));
  tone(3,myarray[random(0,21)]);
  delay(random(0,2000));
  tone(3,myarray[random(0,21)]);
  delay(random(0,2000));
  tone(3,myarray[random(0,21)]);
}

//end of music selections8
void nomusic(){
  digitalWrite(led_1,LOW);
  digitalWrite(led_2,LOW);
  noTone(3);
}


void loop() {

  long duration;
  long distance;
  digitalWrite(trig_pin,LOW);
  delay(10);
  digitalWrite(trig_pin,HIGH);
  delay(10);
  digitalWrite(trig_pin,LOW);
  duration = pulseIn(echo_pin,HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
  
  if (distance<30){
    digitalWrite(led_1,HIGH);
    digitalWrite(led_2,HIGH);

    //input music choices
    if (input == '1'){
      ascending();
    }
    else if(input == '2'){
      descending();
    }
    else if(input == '3'){
      single_low();
    }
    else if(input == '4'){
      single_high();
    }
    else if(input == '5'){
      single_mid();
    }
    else if (input == '6'){
      beats();
    }
    else if (input == '7'){
      beats_2();
    }
    else if (input == '8'){
      bells();
    }
    else if (input == '9'){
      bells_2();
    }
    else if (input == 'q'){
      bump_low();
    }

    else if (input == 'w'){
      bump_mid();
    }

    else if(input == 'e'){
      bump_high();
    }

    else if(input == 'r'){
      normal_alarm();
    }

    else if(input == 't'){
      oh_biscuits();
    }

    else{
      ascending();
    }
  //end of distance alarm if conditions
   }

  else{
    nomusic();
    //end of no alarm else statement
  }
if (Serial.available()> 0){
    goback_input = Serial.read();
    delay(500);

if (goback_input == 'R'){
  nomusic();
  setup();
   }
  }

//end of go back input checker
if (digitalRead(quick_button) == HIGH){
  nomusic();
  setup();
  }

//end of void loop
}
