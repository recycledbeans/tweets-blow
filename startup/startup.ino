
// The pin used for PWM of the fan
int const fan_pin = 9;

// Potentiometer
int const pot_pin = A0;

// Slowest fan speed
int fan_speed = 0;

// Approximate minimum voltage need just to spin the blades slowly
int base_fan_voltage = 155;

// Potentiometer voltage in percentage
int pot_percent = 0;

void setup() {

  analogWrite(fan_pin, fan_speed);

  Serial.begin(9600);

}

void loop() {

  // Get the potentiometer voltage as a percentage
  pot_percent = potPercentage();

  // Just add the percentage (0-100) to the base_fan_voltage to determine PWM (0-255)
  fan_speed = base_fan_voltage + pot_percent;

  // Set fan to GO!
  analogWrite(fan_pin, fan_speed);

  // Slight delay in between shifts in speed
  delay(400);
    
}

int potPercentage() {

  // Read value of potentiometer (needs to be float instead of integer to calculate next part)
  float pot_val = analogRead(pot_pin);

  // Calculate percentage by deviding potentiometer value by max pot. value (1023)
  // Multiply by 100 and round up to get a whole number between 0 and 100.
  int pot_percentage = ceil((pot_val / 1023) * 100);

  // For reference. Can comment out.
  Serial.println(pot_percentage);

  // return the percentage
  return pot_percentage;
    
}

