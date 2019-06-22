# 5. The Production of Electronic Boards

Goal(s):

- Group assignment:
  - Characterize the design rules for your PCB production process

- Individual assignment:
  - Make an in-circuit programmer by milling the PCB, program it, then optionally try other PCB processes

## PCB
A printed circuit board (PCB) mechanically supports and electrically connects electronic components using conductive tracks, pads and other features etched/milled from copper sheets laminated onto a non-conductive substrate. A basic building block of the PCB is an FR-4 panel with a thin layer of copper foil laminated to one or both sides.There are multiple ways of making the PCB. The most common techniques being etching and milling.

There are two ways of mounting the parts to the PCB. The Trough Hole Mounting:mounting technique involves different components which have lead wires that are led to the board through holes, hence the name. And in Surface Mount Technology(SMT), the leads are soldered on PCB surface directly rather than using hole mounting

## PCB Milling

In the lab, we used a router for the PCB milling. We had the following tools for milling the PCB

SVP Laser CNC Router
Single-Sided Copper Clad Circuit PCB Board (FR1)
Double sided tape
Engraving bits

## Sacrificial Layer

We need a sacrificial layer here because in case something goes wrong and the milling bit goes further than expected, we might just end up damaging the base plate. The sacrificial layer as the name suggests sacrifices itself for saving the base plate from any damage.To do this we apply the dual sided tape onto a copper clad board, about the same or of greater size to that of the plate we are going to mill.

## Setting the PCB

A PCB board of suitable size could be fixed on the sacrficial layer using double side tape. Care should be taken to evenly place the board, as any variations may cause cutting tool breakage. If the milling surface is not level then need to apply pressure gently on the raised areas, if that doesn’t work we need to redo the adhesive part, making sure that its level and uniformly distributed.

## Attaching the milling bit

First we need to raise the milling head by using the ‘Tool-UP’ button on the Modela control panel. Using the Allen key, gently loosen the hex nut on the rotating part on the milling head, and gently remove the existing bit. Depending on the type of cut we need to select from 2 available bits. 1/64 for the traces and 1/32 for the border cut. While storing, we need to ensure that the bits should be placed in its appropriate container with the cap on. It is also a good idea to place a sponge(soft cloth) beneath the tool holder to ensure that the bit is not damage in case it falls while being removed.

The board layout, need to be available as an image (.png) file, having black and white coloring. The black portion of the board is removed by the miller and the white portion remains as the circuit trace. The layout used for this assignments are available here

## Setting the orgin

We need to set the origin so that the machine knows from where it should start the operation. This is also vital in order to select the desired area on the copper board on which to mill the PCB. First we need to select the ‘move to xmin, ymin’ option. This would move the milling head to the Zero (20,20 by default). Then by changing the values we could locate the orgin to the desired area. In my assignment, I shifted the orgin to (2,79), so as to mill on the available space at the top left corner. Then move the milling head down by using the ‘Tool-Down’ button on the front panel, till we reach about 0.5 cms above the milling surface. Now with the Allen key, gently loosen the hex-nut holding the bit such that the bit drops to the milling surface. Then fasten the nut. Now the milling bit should be resting just on the top of the milling surface, as seen in the image.

## Milling the board

Select the ‘PCB traces’ option under the ‘process’ drop down. Adjust the cut depth to 0.1mm, which will mill away the copper. Then select the ‘calculate’ option.This will generate the tool path for the device.Go through the tool paths and see if all traces are available. It is interesting to note that if we give -1 as the offset value, then all the copper except the traces will be removed. Finally click the ‘send’ button to send the tool path to the device. And it will start cutting. A status window will be displayed, showing the time elapsed and remaining, and mine took about 10mins to mill the traces.

If so redo the entire traces with a little more cut depth. Once the traces are ready, replace the bit with the 1/32 bit and repeat the same process with the border for cutting the board out. Be sure to use the ‘Cut out board’ option in the process dropdown. We have to use another .png file that looks like the one below to do the border cutting

Once this cutting is finished, we can remove the cut board from the mill.

## Stuffing and Soldering

Once the board is milled the next task is stuff the boards with the parts. This could be done in the following steps.

Identify the parts that goes into the board
Place them in a markable tray/sheet
Solder them to the board

The fabTinyISP needs the following parts:

1x ATtiny45 or ATtiny85
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
The ATtiny45 marks pin 1 with a dot laser-etched into the corner of the package. Pin 1 is marked in the drawing with a dot as well. This should be pointing to bottom left when the USB is on the left side.
And its better to start soldering with the ATtiny45 as it will be more accessible when other parts not around. Once the parts are all soldered in then need to use solder to create a bridge on the jumper near the ISP header (J1). This temporarily connects VCC to the Vprog pin on the ISP header so that the header can be used to program the tiny45.

Once the soldering is done, we need to inspect it against the schematic and PCB layout image, and also check if the parts are all placed correctly and connection are soldered properly.

## Useful links

- [Jekyll](http://jekyll.org)
- [Google](http://google.com)
- [Markdown](https://en.wikipedia.org/wiki/Markdown)
