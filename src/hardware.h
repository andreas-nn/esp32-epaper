//read battery voltage
float read_battery_voltage(uint8_t bat_pin)
{
  float voltageRaw = 0;
  for (int i = 0; i < 10; i++)
  {
    voltageRaw += analogRead(bat_pin);
    delay(1);
  }
  voltageRaw /=EPD_BAT_DIVIDER;
  return voltageRaw;
}

void set_builtin_led(int8_t led_pin, bool on_off) {
    int8_t led_pin2 = led_pin;
    bool on_off2    = on_off;
    if (led_pin<0) {led_pin2 = 0-led_pin; on_off2 = !on_off;}
    pinMode(led_pin2, OUTPUT);
    digitalWrite(led_pin2,on_off2);
}