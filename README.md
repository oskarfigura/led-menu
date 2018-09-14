# led-menu

Comparison of a code size for the same 8 option led menu written using switch and if statements

Atmega16 has 16 KB programmable flash memory

Atmega16 - if statements (menu_if.c)
618bytes (2.8% full)

Atmega16 - switch case statements (menu_switch.c)
1058bytes (6.5% full)

Conclusion: 
Code written using if statements will take significantly less memory than code written using switch case statements. 
For a microcontroller such as Atmega16 this can have a major impact on the structure of your code. However there are cases where this massive difference in memory doesn't occur and it's simply better to use switch case.

Demo of menu - <br />
https://youtu.be/TvDNxFKiiDQ<br />
https://youtu.be/KFQCP3L45aE<br />
Please note that this is some of my first code written in C hence it's not of the highest quality.<br />

Updated version of led menu which used functions and left the main loop clean, which showed my progress in understanding C.<br />
Unfortunately at that time I didn't use git and most of my code has been lost.
However if I have some spare time I will try to recreate this effect.<br />
https://youtu.be/JEekTwN7cDs
