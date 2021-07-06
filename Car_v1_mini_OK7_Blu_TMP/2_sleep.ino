/*

void sleepNow ()
{
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);   
  noInterrupts ();          // make sure we don't get interrupted before we sleep
  sleep_enable ();          // enables the sleep bit in the mcucr register
  EIFR = bit (INTF0);       // clear flag for interrupt 0
  attachInterrupt (0, wake, RISING);  // wake up on rising edge  //RISING ขอบขาขึ้น , FALLING ขอบขาลง
  interrupts ();           // interrupts allowed now, next instruction WILL be executed
  sleep_cpu ();            // here the device is put to sleep
  detachInterrupt (0);      // stop this interrupt until next time
}  // end of sleepNow


*/
