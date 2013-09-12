##Arduino Yún Examples

#####This repository is a collection of Arduino Yún sketches that make use of the Bridge library to create web servers, combined with visual interfaces and experiments with JS.

![screenshot](/pictures/color_picker.jpg)

To start with these examples, you need to **prepare a micro-SD card**. Make an empty "www" folder at the following path:

**sd/arduino/www**

Then insert the SD card in your Arduino Yún.

Once the board is configured to connect to a WiFi network ([follow this tutorial](http://arduino.cc/en/Guide/ArduinoYun#toc13)), in the **Tools->Port** menu of your Arduino IDE, select the WiFi version of your board (the one with an IP address).

Now when you upload, all the content is uploaded on your board via WiFi, included the "www" subfolder of your sketch. It is placed in a subfolder of the previously created folder on your SD car, named after your sketch.

Now from any browser (pc, mobile, ecc), you can access the content of this folder on your Yún by typing the following URL:

*192.168.0.1/sd/mysketch*

Where 192.168.0.1 is your Arduino local IP address and "mysketch" is your sketch name. 


Eventually you can try the following:

*arduino.local/sd/mysketch*

where "arduino" is your Arduino Yún board name

#####These examples are still a work in progress, most of them are incomplete but they can be a good starting point. They were tested successfully with Google Chrome, some of them don't work with Firefox (the color_picker in FF has a strange bug where it shows the previously selected color instead of the current).

Realized by Matteo Loglio ([matlo.me](http://matlo.me)) and Angelo Scialabba

*	*	*	*	*	*	*	*	*	*	*	

### Led Slider Input

![screenshot](/pictures/ledSliderInput.jpg)

HTML slider that controls a LED hooked up to pin 11

*	*	*	*	*	*	*	*	*	*	*	

### Led Pin

![screenshot](/pictures/ledPin.jpg)

HTML slider that controls any PWM pin, slectable from a dropdown menu.

*	*	*	*	*	*	*	*	*	*	*	

### Color Picker

![screenshot](/pictures/color_picker.jpg)

HTML color picker interface used to set the color of an RGB led

*	*	*	*	*	*	*	*	*	*	*	

### Analog Inputs

![screenshot](/pictures/analogInputs.jpg)

A pure HTML / SVG dashboard to visualize the analog input pins values.

*	*	*	*	*	*	*	*	*	*	*	

### Viual Bridge

![screenshot](/pictures/visualBridge.jpg)

A viusal interface based on the Bridge example. It uses Flat UI elements. It's still a draft, it requires heavy improvements.

*	*	*	*	*	*	*	*	*	*	*	

### Noise Field

![screenshot](/pictures/noiseField.jpg)

Interaction between processing.js and Yún Server. The amount of light perceived by an LDR changes the size of a noise field particles.

*	*	*	*	*	*	*	*	*	*	*	

### Noise Field Fullscreen

![screenshot](/pictures/noiseFieldFull.jpg)

Same as above, but full screen

*	*	*	*	*	*	*	*	*	*	*	

### paper.js circle

![screenshot](/pictures/paperCircle.jpg)

Interaction between paper.js and Yún Server. The amount of light perceived by an LDR changes the size of a circle.

*	*	*	*	*	*	*	*	*	*	*	

### three.js box resize

![screenshot](/pictures/three.jpg)

Interaction between three.js and Yún Server. The amount of light perceived by an LDR changes the Z-scale of a textured box, rendered using webGL.

