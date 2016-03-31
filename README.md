# CurtinPrime
The Library Driver for Transformer CurtinPrime

** To begin
Copy the two folder into your arduino libraries folder (Usually at  Documents/Arduino/libraries)
- DS3231
- Tlc5940

Adn you are ready to make the pattern code for the transformer!

Put your code inside the **Main Fucntion** Quotation

Function to use
/********
Head Functions
**********/
- headup(steps)
- headdown(steps)
- neckleft(steps)
- neckright(steps)
- leftup(steps)
- leftdown(steps)
- rightup(steps)
- rightdown(steps)

/***************
Eye Functions
*************/
P/s: To set a LED, first use the Clear function, then Set function, then Update. After update be sure to use delay function.

- Tlc.clear()
- Tlc.update()
- Tlc.set(LED_Position, Intensity)

**The LED Position Map

       (0)(1)
  (2) (3)  (4) (5)
(6)(7)         (8)(9)
   (10)(11)(12)(13)
       (14)(15)
