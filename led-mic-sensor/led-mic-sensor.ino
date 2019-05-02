// Audio sensor: MAX-9812L
// LED RGB Strip 5V, 4 pins: Vcc, G, R, B

const int sensorPIN = A0;
const int sampleWindow = 50; // Window width in ms (50 ms = 20Hz)
int redPin = 6;
int greenPin = 7;
int bluePin = 5;

float low_sound = 0.035;
float medium_sound = 0.085;
float high_sound = 0.15;

void setup()
{
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
   unsigned long startMillis= millis();

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   // Get samples during window
   unsigned int sample;
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(sensorPIN);
      if (sample < 1024)
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // Update max. value
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // Update min. value
         }
      }
   }
   unsigned int peakToPeak = signalMax - signalMin;  // Sound amplitude
   double volts = (peakToPeak * 5.0) / 1024;  // Convert to voltage
   Serial.println(volts);
    
   if (volts < low_sound){
      setColor(HIGH, HIGH, HIGH);  // Turn off LEDs
   } else if (volts <= medium_sound){ 
      setColor(HIGH, LOW, HIGH);  // Turn on green LEDs
   } else if (volts <= high_sound){
      setColor(HIGH, LOW, LOW);  // Turn on green+blue LEDs
   } else {
      setColor(LOW, LOW, LOW);  // Turn on all LEDs (red+green+blue)
   }
  
}

void setColor(int redValue, int greenValue, int blueValue) {
  digitalWrite(redPin, redValue);
  digitalWrite(greenPin, greenValue);
  digitalWrite(bluePin, blueValue);
}
