![Wokwi](./Wokwi.png)

This project has four main parts to implement, and the user is definitely in one of these four parts: turning on the device, lock screen, home screen, and menu. These four parts can be controlled using variables that only have one phase available to the user, and the rest of the phases can be moved in response to the user.

Initially, the keypad, Adafruit_SSD1306, DHT, RTC_DS3231, TM1637, and Timer1 values ​​have been set so that we can access the hardware using these values.

In the loop section, the user first goes to the device power-on mode. In this mode, the user must hold the power button for about 3 seconds to turn on the device, then we go to the animation display mode, in this mode, each animation step is equal to every 8 music steps because we have 40 song notes and 5 animation frames, and in this way, music is played throughout the entire animation.

Then a display logo is played that is accompanied by an animation. Animation using the SSD130 library rectangle is drawn in black and white from the sides and comes to the edge of the logo. Then after reaching the edge, the number of internal rectangles is reduced to 2 so that in the end there is no rectangle left and only the logo is displayed.

After turning on the device, by pressing any key, we go to the login screen. On this screen, a password is entered, which is equal to 10203040 by default. By pressing any key, an asterisk is displayed on the screen so that the user can see the number of characters in the password. A comparison is made between the entered password and the correct password, and the user can confirm his password using the hashtag or if it reaches 8 digits, it is automatically checked and the appropriate message is displayed, and if the password is incorrect, it returns to this page.

After entering the password, the user goes to the main screen, where a background image is displayed, and the user goes to the menu screen by pressing any button.

On the menu page, the same menu page is displayed according to the index and we are waiting for the user to press a button. The user can also move between pages or return to the main page. Depending on the user's choice, the following modes can be used:
1. Locking the device: In this mode, the user is sent to the lock screen using variables and exits the logged-in user mode.

1. Distance finding program: By sending and receiving a pulse, we calculate the pulse return time and then the distance and display it. Then we wait for the user to see the value or return to the menu and after 1 second we perform the measurement again.

2. Calculator: First, we take the value of the first number from the user and until he enters the number, we record it as the first number until he selects an operand and designates it as the operation operand. Then the user enters the second number and until he does not select the equal operand, we consider it as the unit and finally perform the operation. If none is recorded, we consider it as zero. In the second case, if the operand is selected, we consider the first number as the result of the previous operation.

3. Temperature and Humidity: Using the sensor and library, we read and display the information including temperature and humidity. Then we wait for the user's command and read the new information again after 2 seconds.

4. Game: In this game, we first defined a hundredth of a second counter using the Timer 4 library. Then we saved the steps as seconds and hundredths of a second. The user is shown one second and hundredths of a second, and he must keep the timer at that second (in the first 3 steps), second and tenths of a second (the second 3 steps), and second and hundredths of a second (the third 3 steps), and if correct, he gets points, otherwise he loses.

5. Clock Display: In this mode, the user sees the clock in 7 segments, which is read using the system's world clock information, and the hours and minutes are updated every 6 seconds. The user can also see the date of the day on the OLED display.

6. Gallery: Images are displayed in dimensions of 100 by 64 and there are icons on both sides of the image to go to the previous and next image. The last image shows the back button, but in all images it is possible to go back and the images return in a loop from the last to the first.

7. Stopwatch: In this mode, using the Timer 4 interrupt, each hundredth of a second is counted. And after counting 100 centiseconds, it counts one second and continues. The user has the ability to select 4 modes: stop, continue, start and reset the stopwatch, all of which are implemented using a flag and two variables, seconds and centiseconds. Also, if we exceed 100 seconds, we display it on the screen in minutes and seconds.

in wokwi website :  [click here](https://wokwi.com/projects/418606710099402753)
