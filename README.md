# exam01

  Equipment List
1. PC or notebook (or an optional VM copy just in case your notebook fails)
2. USB Stick to transfer codes and backup data (Recommended but optional)
3. A phone (to take a picture of your hardware setup)
4. B_L4S5I_IOT01A
5. Bread board
6. Buttons * 3 (Please keep the same connection as HW2)
7. Picoscope
8. uLCD display
9. Wires


   Setup and run program
1. Plugin 3 buttons and wire to mbed(A0:selet, A1:UP, A2:DOWN)

2. connected D7(output signal) with A5(input signal for sampling)

3. Compile the program.
  $ sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f

4. Polt FFT 
  $ sudo python3 FFT.py

