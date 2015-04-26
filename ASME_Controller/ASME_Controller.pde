import processing.serial.*;
import vsync.*;
import controlP5.*;

Serial bluetooth;
boolean upPressed, downPressed, leftPressed, rightPressed, qPressed, aPressed, wPressed, sPressed, pPressed, oPressed;

/***************************************************************************************
// vsync objects
// Create a sender and a receiver for incoming and outgoing synchronization.
****************************************************************************************/
ValueReceiver receiver;
ValueSender sender;

// vsync public variables for passing to Arduino
public int up;
public int down;
public int left;
public int right;
public int front;
public int back;
public int servo;

/********************************************************
/ Misc variables for displaying text to graphics window.
/********************************************************/
ControlP5 cp5;
Textlabel title;
Textlabel authors;
Textlabel tcnj;

/********************************************************
/ setup function 
/********************************************************/
void setup() {
  size(800, 360);
  noStroke();
  background(0);
  upPressed = false;
  downPressed = false;
  leftPressed = false;
  rightPressed = false;
  qPressed = false;
  aPressed = false;
  wPressed = false;
  sPressed = false;
  pPressed = false;
  oPressed = false;
  up = 0;
  down = 0;
  left = 0;
  right = 0;
  front = 0;
  back = 0;
  servo = 0;
  //Text
  cp5 = new ControlP5(this);
  title = cp5.addTextlabel("label")
        .setText("ASME Student Design Competition 2015: Robots for Relief ")
        .setPosition(5,50)
        .setColorValue(0xffffff00)
        .setFont(createFont("Times New Roman",30))
        ;
  authors = cp5.addTextlabel("authors")
        .setText("by Richard Levenson, Chris deRocco, Julian Daum, Charlie Gordon, and Justin Cheng")
        .setPosition(5,100)
        .setColorValue(0xffffffff)
        .setFont(createFont("Times New Roman",16))
        ;
  tcnj = cp5.addTextlabel("tcnj")
        .setText("The College of New Jersey")
        .setPosition(5,130)
        .setColorValue(0x241170FF)
        .setFont(createFont("Times New Roman",20))
        ;
  //Controller "buttons"
  triangle(40,200, 50,180, 60,200);
  triangle(40,240, 50,260, 60,240);
  triangle(30,210, 10,220, 30,230);
  triangle(70,210, 90,220, 70,230);
  
  triangle(120,210 ,130,180, 140,210);
  triangle(120,230 ,130,260, 140,230);
  triangle(150,210 ,160,180, 170,210);
  triangle(150,230 ,160,260, 170,230);
  // List out and setup the Serial com port interface
  print("Serial Com Ports Available: ");
  println(Serial.list());
  println();
  bluetooth = new Serial(this, Serial.list()[0], 9600);
  
  // setup for vSync control. Receiver object takes in data from Arduino. Sender object sends data to Arduino
  // the number of objects and the order of these must match between Processing and Arduino.
  sender = new ValueSender(this, bluetooth).observe("up").observe("down").observe("left").observe("right").observe("front").observe("back").observe("servo");
}


/********************************************************
/ draw function 
/********************************************************/
void draw() {

}

void keyPressed() {
  if (key == CODED){
      if (keyCode == UP && upPressed == false) { 
        println("Up"); 
        fill(0,255,0);
        triangle(40,200, 50,180, 60,200);
        up = 1;
        upPressed = true; 
      } else
      if (keyCode == DOWN && downPressed == false) { 
        println("Down"); 
        fill(0,255,0);
        triangle(40,240, 50,260, 60,240);
        down = 1;
        downPressed = true; 
      } else
      if (keyCode == LEFT && leftPressed == false) { 
        println("Left"); 
        fill(0,255,0);
        triangle(30,210, 10,220, 30,230);
        left = 1;
        leftPressed = true; 
      } else
      if (keyCode == RIGHT && rightPressed == false) { 
        println("Right"); 
        fill(0,255,0);
        triangle(70,210, 90,220, 70,230);
        right = 1;
        rightPressed = true; 
      }
  } else
  if(key == 'a' && aPressed == false) {
    println("Front forward spin");
    fill(0,255,0);
    triangle(120,210 ,130,180, 140,210);
    front = 1;
    aPressed = true;
  } else
  if(key == 'q' && qPressed == false) {
    println("Front backward spin");
    fill(0,255,0);
    triangle(120,230 ,130,260, 140,230);
    front = 2;
    qPressed = true;
  } else
  if(key == 's' && sPressed == false) {
    println("Back forward spin");
    fill(0,255,0);
    triangle(150,210 ,160,180, 170,210);
    back = 1;
    sPressed = true;
  } else
  if(key == 'w' && wPressed == false) {
    println("Back backward spin");
    fill(0,255,0);
    triangle(150,230 ,160,260, 170,230);
    back = 2;
    wPressed = true;
  } else
  if(key == 'o' && oPressed == false) {
    println("Open pulley");
    servo = 1;
    oPressed = true;
  } else
  if(key == 'p' && pPressed == false) {
    println("Close pulley");
    servo = 2;
    pPressed = true;
  }
  
}

void keyReleased() {
  if (key == CODED){
      if (keyCode == UP && upPressed == true) { 
        println("Up Released");
        fill(255,255,255);
        triangle(40,200, 50,180, 60,200);
        up = 0;
        upPressed = false; 
      } else
      if (keyCode == DOWN && downPressed == true) { 
          println("Down Released");
          fill(255,255,255);
          triangle(40,240, 50,260, 60,240);
         down = 0; 
          downPressed = false; 
      } else
      if (keyCode == LEFT && leftPressed == true) { 
        println("Left Released"); 
        fill(255,255,255);
        triangle(30,210, 10,220, 30,230);
        left = 0;
        leftPressed = false; 
      } else
      if (keyCode == RIGHT && rightPressed == true) { 
        println("Right Released"); 
        fill(255,255,255);
        triangle(70,210, 90,220, 70,230);
        right = 0;
        rightPressed = false; 
      }
  } else
  if(key == 'a' && aPressed == true) {
    println("Front forward spin stopped");
    fill(255,255,255);
    triangle(120,210 ,130,180, 140,210);
    front = 0;
    aPressed = false;
  } else
  if(key == 'q' && qPressed == true) {
    println("Front backward spin stopped");
    fill(255,255,255);
    triangle(120,230 ,130,260, 140,230);
    front = 0;
    qPressed = false;
  } else
  if(key == 's' && sPressed == true) {
    println("Back forward spin stopped");
    fill(255,255,255);
    triangle(150,210 ,160,180, 170,210);
    back = 0;
    sPressed = false;
  } else
  if(key == 'w' && wPressed == true) {
    println("Back backward spin stopped");
    fill(255,255,255);
    triangle(150,230 ,160,260, 170,230);
    back = 0;
    wPressed = false;
  } else
  if(key == 'o' && oPressed == true) {
    println("Stop opening pulley");
    servo = 0;
    oPressed = false;
  } else
  if(key == 'p' && pPressed == true) {
    println("Stop closing pulley");
    servo = 0;
    pPressed = false;
  }
}
