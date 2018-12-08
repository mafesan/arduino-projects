// Original code from https://www.luisllamas.es/medir-sonido-con-arduino-y-microfono-amplificado-max9812/

const int sensorPIN = A0;
const int sampleWindow = 50; // Window width in ms (50 ms = 20Hz)

void setup()
{
   Serial.begin(9600);
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
}
