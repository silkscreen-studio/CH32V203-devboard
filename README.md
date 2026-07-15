# CH32V203 devboard
A simple CH32V203C8U6 devboard, with a 7x8 charlieplexed matrix and a 12P FPC for IOs, beside the more common 2.54 headers for breadboard compatibility.

# Key features 
 - CH32V203C8U6 MCU:
    - FLASH: 64k
    - SRAM: 20k
    - 144MHz CPU max clock speed
    - 37 GPIOs
    - Many peripherals (4x USART, 2x SPI, 2x I2C, 1x CAN, USB (FS))
    - 9 analog capable GPIOs
    - 12 PWM capable GPIOs
 - 7x8 charlieplexed LED matrix (8 GPIOs)
 - 23x 2.54mm header pins
 - 12P .5mm FPC for breaking out 9 more IOs
 - Boot and Reset Button
 - On board 3.3V LDO `TLV75733PDBVR`, 1A max current
<br></br>
<br></br>
<p align="center">
<img width="96.3%" alt="Render 1" src="IMGs/R1.png" />
</p>
<p align="center">
  <img width="52.3%" alt="Render 2" src="IMGs/R2.png" />
  <img width="44%" alt="Render 3" src="IMGs/R3.png" />
</p>
<br></br>

# Schematic
<img width="2533" alt="SCHEMATIC" src="CH32V203 devboard schematic.svg" />
<br></br>

# PCB layout
<p align="center">
  <img width="46%" alt="Layout F" src="IMGs/CH32V203 devboard layout Front.png" />
  <img width="45%" alt="Layout B" src="IMGs/CH32V203 devboard layout Back.png" />
</p>
<br></br>

# Pinout

<img alt="Pinout" src="IMGs/Pinout CH32V203.png" />
<br></br>

# BOM

| Qty | Type | Part | Value | Extended description | Unit price | Price [MOQ]| LCSC part number | Link |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 7 | MLCC | CL05B104KB54PNC | 100nF | 0402 | $0.014 | $1.40 [100] | C307331 | https://www.lcsc.com/product-detail/C307331.html |
| 3 | MLCC | CL10A106MA8NRNC | 10µF | 0603 | $0.14 | $2.80 [20] | C96446 | https://www.lcsc.com/product-detail/C96446.html |
| 1 | Ideal Diode | CH213K | |  | $0.074 | $0.74 [10] | C5456874 | https://www.lcsc.com/product-detail/C5456874.html |
| 1 | FPC connector 12P | FPC-05F-12PH20 | |  | $0.11 | $0.57 [5] | C2856799 | https://www.lcsc.com/product-detail/C2856799.html |
| 56 | LED | XL-1005UOC | | Orange 0402 LED | $0.014 | $1.42 [100] | C965791 | https://www.lcsc.com/product-detail/C965791.html |
| 3 | Resistor | RC0402JR-7W10KL | 10k | 0402 SMD resistor | $0.004 | $0.45 [100] | C851859 | https://www.lcsc.com/product-detail/C851859.html |
| 2 | Resistor | RC-02K512JT | 5.1k | 0402 SMD resistor | $0.0033 | $0.33 [100] | C453708 | https://www.lcsc.com/product-detail/C453708.html |
| 8 | Resistor | RC0402FR-07680RL | 680 | 0402 SMD resistor | $0.0014 | $0.14 [100] | C137948 | https://www.lcsc.com/product-detail/C137948.html |
| 2 | Push button | TS-1075S-A1B2-D4 | | | $0.066 | $0.66 [10] | C492872 | https://www.lcsc.com/product-detail/C492872.html |
| 1 | MCU | CH32V203C8U6 | | | $0.85 | $0.85 [1] | C6407762 | https://www.lcsc.com/product-detail/C6407762.html |
| 1 | LDO | TLV75733PDBVR | | 3.3V LDO | $0.18 | $0.92 [5] | C485517 | https://www.lcsc.com/product-detail/C485517.html |
| 1 | ESD protection | USBLC6-2P6 | | | $0.28 | $1.39 [5] | C15999 | https://www.lcsc.com/product-detail/C15999.html |
| 1 | PCB | | | | $5 |  |  | https://jlcpcb.com/quote |
|  |  |  |  |  |  |  |  |  |
|  | TOTAL (price per board) | | | | $7.96 |  |  |  |
|  | TOTAL (price due to MOQ) | | | | $16.67 |  |  |  |
