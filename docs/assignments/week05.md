# 5. The Production of Electronic Boards

Goal(s):

- Group assignment:
  - Characterize the design rules for your PCB production process

- Individual assignment:
  - Make an in-circuit programmer by milling the PCB, program it, then optionally try other PCB processes

## Basics

The electronics side of Fab Academy was quite new to me and this has been a steep learning curve for me.

The main idea is to build an In-System Programmer which can then be used to program other boards needed later during the course.

For this purpose, an ATTiny Microchip is used as the chip for programming

From the many tutorials out there, the main chips used for this are listed below and the main type of components used are SMD Packages

- [ATTiny44](https://www.microchip.com/wwwproducts/en/ATtiny44#datasheet-toggle)
- [ATTiny45](https://www.microchip.com/wwwproducts/en/ATtiny45)
- [ATTiny85](https://www.microchip.com/wwwproducts/en/ATtiny85)

For this exercise, I decided to use the PCB Etching Workflow using the laser cutter as this was a familiar process and simple enough to achieve

## PCB Production Process

I used the following [image](http://www.theparsley.com/arduino/diy/pattern.jpg) as shared in this [Instructable](https://www.instructables.com/id/DIY-Arduino-or-The-DIY-Duino/)

This image was opened in Corel Draw and the negative was laser engraved on to a Copper clad plate with a sticker attached leaving the postive side of the circuit present on the board

The engraved board was removed, cut and cleaned with Iso-Propyl alcohol to remove glue traces.

The board was then placed in an etching solution of Hydrochloric acid and Hydrogen peroxide and agitated continuously for 7 minutes until all the copper was removed.

The final board was then cleaned with Acetone to remove all the glue and the stickers from the board

The other machining processes for the PCB Board were also tried, but they did not yield satisfactory results and hence the chemical process was used.

## Making the Programmer Board

After using the same Workflow for the FabISP Tiny Star, the final board is shown here

The rest of the steps are followed as per Brians's page and Jim Seelan's page

### Stuffing and Soldering

The FabISP Tiny Star needs the following parts:

1x ATtiny45 or ATtiny85 (This was the one available)
2x 1kΩ resistors
2x 499Ω resistors
2x 49Ω resistors
2x 3.3v zener diodes
1x red LED
1x green LED
1x 100nF capacitor
1x 2x3 pin header

It is important to note the orientation of the parts,

The zener diodes are marked, both in the drawing and on the packages, with a line on the cathode side.

The LED cathodes on the PCB drawing are marked with dots and thicker lines. The one in our lab has a green line visible on the cathode side of the epoxy lens.
The ATtiny85 marks pin 1 with a dot laser-etched into the corner of the package. Pin 1 is marked in the drawing with a dot as well. This should be pointing to bottom left when the USB is on the left side.
And its better to start soldering with the ATtiny85 as it will be more accessible when other parts not around. Once the parts are all soldered in then need to use solder to create a bridge on the jumper near the ISP header (J1). This temporarily connects VCC to the Vprog pin on the ISP header so that the header can be used to program the board.

Once the soldering is done, we need to inspect it against the schematic and PCB layout image, and also check if the parts are all placed correctly and connection are soldered properly.

### Programming the board

First we need to setup the enviorment. We used AVRDUDE, which is a utility to download/upload/manipulate the ROM and EEPROM contents of AVR microcontrollers using the in-system programming technique (ISP). For setting up the following command is entered on the terminal on Ubuntu.

"sudo apt install avrdude gcc-avr avr-libc make"

Then we need to download the firmware source code and extract and cd that path on a terminal window. Then we need to Run make. This will build the hex file that will get programmed onto the ATtiny85. When the command completes, we should have a file called fts_firmware.hex.

Then we need to connect another programmer, I have used the AVRISP Programmer in our lab, to load the program to my fabISP. The Blue LED will glow now. It should be noted that the boards are oriented in the same direction. Then we need to enter "make flash" on the terminal. This will erase the target chip, and program its flash memory with the contents of the .hex file we built before. We should see several progress bars while avrdude erases, programs, and verifies the chip.

But I got the following message.

```
WARNING: Unable to detect MCU

avrdude.exe: set SCK frequency to 1000 Hz
avrdude.exe: warning: cannot set sck period. please check for usbasp firmware update.
avrdude.exe: error: program enable: target doesn't answer. 1 
avrdude.exe: initialization failed, rc=-1
             Double check connections and try again, or use -F to override
             this check.


avrdude.exe done.  Thank you.
```

After going through the problem in detail, I found the following text at the top of the Makefile within the firmware downloaded

I then checked the [Gitbook](http://fabacademy.org/2018/docs/FabAcademy-Tutorials/week4_electronic_production/fabtinyisp_english.html) for troubleshooting the problem and was able to resolve it after checkng all connections and solder joints and plugging the FabISP properly into the USB port.

```
# Generic AVR Makefile - Adapted for FabTinyStar
# Brian Mayton <bmayton@media.mit.edu>
#
# 'make' builds the .hex file.
# 'make flash' uses the programmer to load it onto the target chip.
# 'make fuses' programs the fuse bits on the target chip.
# 'make rstdisbl' blows the reset fuse.
# 'make clean' removes all autogenerated files.

# OBJECTS should list all of the object files for the program (e.g. for each
# .c file, list a corresponding .o file here.)  APPLICATION just specifies the
# name of the hex/elf files, and can be whatever you want.
``` 

After flashing we need to set the configuration fuses, which is done by entering "make fuses" on the terminal. This will set up all of the fuses except the one that disables the reset pin. Next we need to check the USB connectivity. This is done by typing lsusb in the terminal, which will list USB devices. And if we should see a "Multiple Vendors USBtiny" device, it worked correctly.

Now there are two final steps left to turn your board into a programmer that can program other boards. First, we need to change the bit that will turn the ATtiny85's reset pin into a GPIO pin. Once again, this will disable our ability to reprogram this ATtiny85 in the future, which is why we wanted to make sure everything was working before doing this. Connect the ISP programmer to the board one more time, and run "make rstdisbl". This does the same thing as the make fuses command, but this time it's going to include that reset disable bit as well. We should see some progress bars, and with that, avrdude will never be able to talk to this chip again through the ISP header. And it has begun its life as a programmer alone.



## Useful links

- [Gitbook](http://fabacademy.org/2018/docs/FabAcademy-Tutorials/week4_electronic_production/fabtinyisp_english.html)
- [AVR Programming](https://sites.google.com/a/simpleavr.com/simpleavr/avr/vusbtiny)
- [AVR Programmer](https://www.instructables.com/id/VUSBTiny-AVR-SPI-Programmer/)
- [Fab TinyStar](http://fabacademy.org/archives/2015/doc/projects/FabTinyStar/)
- [DIY Programmer](http://sheekgeek.org/2016/adamsheekgeek/how-to-fabtinystar-programmer)
- [Hookup Guide](https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/all)
- [Fab Archive](http://fabacademy.org/archives/2015/doc/FabTinyIsp/index.html)