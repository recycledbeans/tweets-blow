
/**
 * PARTS LIST:
 *  
 *  1 - MOSFET
 *  1 - 9v battery terminal (and 9v battery)
 *  1 - Diode IN4007 1A 1000v
 *  1 - PC Fan (12v) with PWM (4 wires)
 *  1 - Potentiometer
 *  
 */

// MOSFET GPIO pin
int const mosfet_pin = 9;

// Potentiometer
int const pot_pin = A0;

// Slowest fan speed
int fan_speed = 0;

// Approximate minimum voltage need just to spin the blades slowly
int base_fan_voltage = 155;

// Potentiometer voltage in percentage
int pot_percent = 0;

// Seconds since last check for status
int time_since_last_check = 1;

// Time (in seconds) that fan should run for a tweet
int max_fan_time = 5;

void setup() 
{

  pinMode(mosfet_pin, OUTPUT);
  Serial.begin(9600);

}

bool check = false;

void loop() 
{

  Serial.println(time_since_last_check);    

  if(time_since_last_check >= max_fan_time)
  {

    fan("stop");
    check = checkForUpdate();

    if(check == true)
    {
      fan("start");
    }

    time_since_last_check = 0;
    
  }

  delay(1000);

  time_since_last_check++;

  
}

void fan(String status)
{
  if(status == "start")
  {
    beforeFanStart();
    Serial.println("Starting Fan...");
    digitalWrite(mosfet_pin, HIGH);
    afterFanStart();
  }
  else
  {
    beforeFanStop();
    Serial.println("Fan Stopped.");
    digitalWrite(mosfet_pin, LOW);
    afterFanStop();
  }
}

/**
 * Add some more custom actions if you want in the events below.
 */

void beforeFanStart()
{
  
}

void afterFanStart()
{
  
}

void beforeFanStop()
{
  
}

void afterFanStop()
{
  
}

bool checkForUpdate()
{

  // WiFi-related logic would go here;

  // Simulated wait time
  delay(3000);

  // Temp random on or off
  int r = rand();

  if(r%2 != 0)
  {
    return true;
  }

    return false;
  
}

int potPercentage() 
{

  // Read value of potentiometer (needs to be float instead of integer to calculate next part)
  float pot_val = analogRead(pot_pin);

  // Calculate percentage by deviding potentiometer value by max pot. value (1023)
  // Multiply by 100 and round up to get a whole number between 0 and 100.
  int pot_percentage = ceil((pot_val / 1023) * 100);

  // For reference. Can comment out.
//  Serial.println(pot_percentage);

  // return the percentage
  return pot_percentage;
    
}

