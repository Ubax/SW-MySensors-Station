# MySensors network

Before running the project, first check if all the values in configuration files are correct.

## Arduino Mega Connections 

Connections shown below are default connections which are currently saved in configuration files

### Radio - nRF24l01

nRF24l01 pins numbers

Name | Num | Num | Name
-----|-----|-----|-----
GND|1|2|3.3V
CE|3|4|CS
SCK|5|6|MOSI
MISO|7|8|IRQ

SPI Connections

nRF24l01|Mega
--------|----
1|GND
2|3.3V
3|49
4|53
5|52
6|51
7|50
8|

### Display - TFT HY - 1.8 SPI

TFT|Mega
---|----
1|GND
2|5V
⋮|
6|6
7|7
8|31
9|32
10|33
⋮|
15|2
16|GND

### Buttons

Button|Mega
------|----
Next|21
Prev|20
Enter|18
Back|19
