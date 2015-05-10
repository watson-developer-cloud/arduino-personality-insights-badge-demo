/*
  IBM Watson Twitter Personality Insights Badge
  
  By Nathan Friedly <nfriedly@us.ibm.com>
 */
 
#include <Process.h>
#include <TFT.h>  // Arduino LCD library
#include <SPI.h>

// pin definition for the Uno
//#define cs   10
//#define dc   9
//#define rst  8

// pin definition for the Yun
#define cs   2
#define dc   4
#define rst  3

#define NO_LINUX

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

char twitter_username[] = "@nfriedly";
const String categories[] = {"Openness", "Conscientiousness", "Extraversion", "Agreeablemess", "Neuroticism"};
const int numCategories = 5;
String values[] = {"", "", "", "", ""};

void setup() {

  // Put this line at the beginning of every sketch that uses the GLCD:
  TFTscreen.begin();

  // clear the screen with a black background
  TFTscreen.background(0, 0, 0);

  // write the static text to the screen
  // set the font color to white
  TFTscreen.stroke(255, 255, 255);
  
  #if ndef NO_LINUX
  TFTscreen.text("Connectiong to Linux...", 0, 0);
  Bridge.begin();
  #endif
  
  TFTscreen.background(0, 0, 0);
  TFTscreen.text("Serial monitor", 0, 0);
  // Initialize Serial
  Serial.begin(9600);
  // Wait until a Serial Monitor is connected.
  //while (!Serial);
  
  TFTscreen.background(0, 0, 0);
  TFTscreen.text("Loading...", 0, 0);
  
  getDisplayText();
  
  
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(3);
  TFTscreen.text(twitter_username, 0, 0);
}

void loop() {
  
  static int i = numCategories-1;
  
  
  Serial.println("blacking out " + String(i));
  
  // black out the previous text
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.setTextSize(2);
  drawString(categories[i], 0, 35);
  TFTscreen.setTextSize(5);
  drawString(values[i], 4, 70);

  i++;
  if (i >= numCategories) {
    i = 0;
  }
  
  Serial.println("drawing " + String(i));

  // draw the current text in white
  TFTscreen.stroke(255, 255, 255);
  
  TFTscreen.setTextSize(2);
  drawString(categories[i], 0, 35);
  
  TFTscreen.setTextSize(5);
  drawString(values[i], 4, 70);
  
  
  delay(1500);
}

void drawString(const String str, const int x, const int y) {
  const unsigned int len = str.length() +1; // +1 for null terminator
  char chars[len];
  str.toCharArray(chars, len);
  Serial.println(chars);
  TFTscreen.text(chars, x, y);
}

void getDisplayText() {
  // return value is line of CSV numbers representing % scores for:
  // Openness, Conscientiousness, Extraversion, Agreeablemess, & Neuroticism
  String cur = "";
  int i = 0;
  const char seperator = ',';
  
  #if ndef NO_LINUX
  Process p;		// Create a process and call it "p"
  p.runShellCommand("cd /mnt/sda1/twitter-personality-insights/ && python index.py " + String(twitter_username) + "  2>&1");
  p.run(); // todo: run asyc
  
  while (p.running()); 
   
  Serial.println(p.available());
  Serial.println(p.exitValue());

  while (p.available() > 0) {
    char c = p.read();
  #else
    char fakeReturn[] = "10.2,20.2,30.3,40.4,50.5,"; // end in a comma so that we can ignore the last section
    int len = sizeof(fakeReturn);
  for(int j = 0; j<len; j++) {
    char c = fakeReturn[j];
  #endif
    if (c == seperator) {
      values[i] = cur + "%";
      Serial.print("got value: "); Serial.println(values[i]);
      i++;
      cur = "";
    } else {
      cur.concat(c);
    }
  }
  Serial.println("done reading from linux");
}

