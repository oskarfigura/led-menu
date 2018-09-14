# led-menu

Comparison of a code size for the same 8 option led menu written using switch and if statements

Atmega16 has 16 KB programmable flash memory

Atmega16 - if statements (menu_if.c)
618bytes (2.8% full)

Atmega16 - switch case statements (menu_switch.c)
1058bytes (6.5% full)

Conclusion: 
Code written using if statements will take significantly less memory than code written using switch case statements. 
For a microcontroller such as Atmega16 this can have a major impact on the structure of your code.

Demo of menu - https://youtu.be/TvDNxFKiiDQ
Please note that this is some of my first code written in C hence it's not of the highest quality.
