# Teatimer2.0
English

What's better in the morning than a hot cup of tea?
You should keep to the brewing time so that the tea tastes the way you want it to.
Unfortunately, there's always a lot to do and the timer beeps when you're somewhere else.
So we need an automatic "tea extraction machine".....

As always, there are already a few things on the net.
But they didn't really fulfill all my wishes.

What are the main differences to other approaches?
Teatimer2.0 is robust and easy to use for a daily use.

Here are the requirements first:
- the height of the arm should be easily adjustable for different sized cups and pots
- also suitable for heavy tea filters
- the brewing time should be flexibly adjustable
- the remaining brewing time should be displayed

Later (after trials with the customer (my wife)) a few more wishes were added.
- interruption of the brewing process
- adjustability of the brewing time during the brewing process
- sound for welcoming and when the tea is ready

Teatimer 2.0 in use

To show how Teatimer2.0 works - here is a small video.

Connect Arduino to power - it will display the welcome screen and sound the MP3 greeting.
Press or turn the rotary encoder once.
The height adjustment of the arm will be displayed.
Insert the tea strainer or tea bag and fill in tea
Move the arm to the desired brewing position.
Press the rotary encoder
The time setting is displayed
set the time and brew the tea
Press the rotary encoder
The time counts down
During the brewing process, the time can be adjusted and thus the brewing process can be aborted.
When it reaches zero, the arm slowly rises and the message "tea is ready" (or whatever you have recorded) occurs.
After pressing the encoder, the greeting is displayed again.
After 15 minutes (can be adjusted in the sketch under #define INTERVALL_SHUTDOWN) the Arduino goes into a "half" standby - the display goes dark and the servo is turned off.
This reduces the power consumption considerably - a real shutdown was too much work for me here ...
If you press the encoder for two seconds the standby is initiated immediately.

Prerequisites
- General tinkering experience (sawing, drilling, ...)
- If possible some previous knowledge in Arduino & electronics
- Optional soldering

Material
- Arduino Leonardo (UNO works too - but then you have to use software serial)
- USB power supply with Micro-USB connector
- LCD Display 1602 IC2
- Rotary Encoder KY-040
- Servo motor MG995 180?? (or 270?? - NOT 360??)
- small breadboard
- Jumper wires
- wooden boards for the case e.g. 
	2 x 15mm x 150mm x 150mm (solid wood, multiplex, plywood, ...)
	2 x 15mm x 150mm x 200mm (solid wood, multiplex, plywood, ...)
	2 x 5mm x 150mm x 230mm (= 200mm + 2 x thickness of boards - here 2 x 15mm) (plywood)
- Wooden strip for the arm e.g. 
	5mm x 15mm x 230mm (plywood)
- Wooden blocks for mounting the servo e.g.
	4 x 15mm x 20mm x 20mm (solid wood, multiplex, plywood, ...)
- PVC hard foam (alternatively cardboard, plywood, ...)
	2mm x 35mm x 100mm mounting servo
	2mm x frame LCD
- screws 
	12 x 4,5mm x 30mm (housing)
	2 x 3mm x 15mm (mounting plate of the servo)
- wire / cord
- optional 
	- MP3 module DFPlayer mini
	- resistor 1kOhm
	- Loudspeaker (e.g. 8 Ohm / 2 Watt)
	- micro SD card

Tool
- Drill
- Saw
- File
- Sandpaper
- hot glue gun
- optional soldering iron

Wiring diagram

KY-040 <-> Arduino
CLK <-> 11
DT <-> 10
SW <-> 3
+ <-> 5V
GND <-> GND

LCD <-> Arduino
GND <-> GND
VCC <-> 5V
SDA <-> SDA
SCL <-> SCL

Servo <-> Arduino
GND (brown cable) <-> GND
+ (red cable) <-> 5V
Control (orange cable) <-> 8

DFP MP3 module <-> Arduino Leonardo (different for UNO)
RX <-> TX - Attention! Use resistor 1kOhm 
TX <-> RX
VCC <-> 5V
GND <-> GND
SPK1 <-> Speaker
SPK2 <-> Speaker

MP3 Sound
If you want, you can be greeted at the beginning and let you know when the tea is ready.
But you don't have to do this to use the TeaNik's function.
You can then simply leave out the MP3 player and the speaker and don't have to change anything.
- Format Micro SD card (FAT32)
- Record soundfiles (greeting & message that the tea is ready) e.g. with a cell phone.
- If necessary convert soundfiles to .wav or .mp3 (SW on the internet)
- Save soundfiles
- Save greeting under 0001.mp3 and message under 0002.mp3
- Insert micro SD card into DFP MP3 module
- Start system - adjust volume if necessary - under #define MP3_VOLUME

Assembly & startup

Housing 1/2
- Saw hole in front panel for LCD
- Saw hole in front panel for arm
- Drill hole in front panel for encoder
- Drill holes in front panel for loudspeaker
- Pre-drill first side panel and screw to bottom panel (4.5mm x 30mm screws)
- Fix front side with hot glue

LCD display
- Cut out frame from rigid PVC
- Fix LCD display on frame with hot glue
- Fix frame on front panel with hot glue

Arm
- Drill holes in the wooden strip - once for a hook and once for the mounting screw on the servo
- Glue arm of servo to arm with hot glue - pay attention to the fixing hole

Servo on plate
- Screw servo to wooden block 
- Cut out mounting plate from hard PVC
- Fix the blocks to the plate with hot glue
- glue the blocks in the box under and over the display

Install electronics
- Cut out hard PVC plate for Arduino, glue Arduino with little hot glue, glue plate in bottom part so that Arduino is flush with rear edge
- Measure the position of the USB port and drill a hole in the back panel at this position.
- Glue breadboard to bottom part
- Glue loudspeaker to front panel
- Plug DFP MP3 module into breadboard (Attention: the breadboard has tracks in one direction - each connection must have its own track)
- Connection diagram of DFP MP3 module - from above - pay attention to the indentation
- connect 1kOhm resistor to RX of DFP MP3 module so that the second pole is on the other side of the breadboard (see photo)
- Connect all electronics one after the other as shown in the wiring diagram
- Attention - with LCD displays a common mistake is that the contrast is not set correctly, adjust it by potentiometer on the backside after everything is wired.
- Connect the servo - but do not install it yet

Power supply
- Apparently the built-in voltage regulator is not very powerful.
- When using a 9V power supply, the display kept failing.
- I recommend to use a USB power supply. 

Adjusting & installing the servo
- A servo always moves to the center position as soon as it is connected to voltage.
- Therefore, before installation, connect the servo once, connect the Arduino briefly to voltage so that the servo moves to the center position.
- In this position, attach the arm so that it points to the desired start position (this can be adjusted later with the knob).
- Screw the plate with the servo onto the blocks (with 3mm x 15mm screws).
- It is still important to set the max / min positions of the servo correctly.
- If they do not fit, the servo may hit the limits in the box and it or the bracket may be damaged.
- Therefore set the max / min values to the center position first if necessary.
- #define MIN_HEIGHT 60 // maximum height of the arm
- #define MAX_HEIGHT 60 // minimum height of the arm
- Insert the servo with the arm into the housing and screw it tight.
- Then adjust the position by turning the encoder to the end positions and note the values.
- Adjust values max / min
- #define MIN_HEIGHT 85 // maximum height of the arm
- #define MAX_HEIGHT 20 // minimum height of the arm
- #define START_HEIGHT 20 // start height of the arm - usefull if set to the maximum height

Housing 2/2
- Pre-drill second side part and screw to top part and bottom part (4,5mm x 30mm screws)
- Pre-drill back side and screw together with side parts (4,5mm x 30mm screws)

Conclusion
Teatimer2.0 is in daily use with us and has proven itself well.

Acknowledgements
To the many ideas and instructions on the Internet.
To my wife for the good customer feedback and optimization suggestions.
To my son for the good tinkering and developing together.
To my daughter for the voice output.
To deepl for the translation.


Deutsch
Was gibt's besseres am Morgen als eine hei??e Tasse Tee?
Dabei sollte man die Ziehzeit einhalten, damit der Tee auch so schmeckt, wie man es gerne h??tte.
Leider ist immer viel zu tun und der Timer piept wenn man gerade woanders ist.
Also muss eine automatische "Tee-Rausnehm-Maschine" her....

Wie immer gibt's schon einige Dinge im Netz.
Aber so richtig haben die nicht alle meine W??nsche erf??llt.

Was sind die Hauptunterschiede zu anderen Approaches?
Teatimer2.0 ist robust und einfach bedienbar f??r einen t??glichen Einsatz.

Hier zun??chst die Anforderungen:
- die H??he des Arms soll einfach f??r verschieden gro??e Tassen und Kannen eingestellt werden k??nnen
- auch f??r schwere Teefilter geeignet
- die Ziehzeit flexibel einstellbar sein
- die verbleibende Ziehzeit soll angezeigt werden

Sp??ter (nach Versuchen mit dem Kunden (meiner Frau)) kamen noch ein paar W??nsche dazu.
- Abbruch des Br??hvorgangs
- Verstellbarkeit der Ziehzeit w??hrend des Ziehens
- Sound zur Begr????ung und wenn der Tee fertig ist

Teatimer 2.0 im Einsatz

Um zeigen, wie Teatimer2.0 funktioniert - hier ein kleines Video.

Arduino an Spannung anschlie??en - es wird der Begr????ungsbildschirm angezeigt werden und die MP3-Begr????ung ert??nen.
Einmal den Drehgeber dr??cken oder drehen.
Es wird die H??henverstellung des Arms angezeigt.
Teesieb oder Teebeutel einh??ngen und Tee einf??llen
Den Arm in die gew??nschte Br??hposition bringen.
Drehgeber dr??cken
Es wird die Zeiteinstellung angezeigt
die Zeit einstellen und den Tee aufbr??hen
den Drehgeber dr??cken
Die Zeit z??hlt runter
W??hrend des Br??hvorgangs kann die Zeit angepasst und damit auch der Br??hvorgang abgebrochen werden.
Bei null angekommen f??hrt der Arm langsam hoch und die Meldung "Tee ist fertig" (oder was immer man aufgenommen hat) erfolgt.
Nach dem Dr??cken des Drehgebers wird wieder die Begr????ung angezeigt.
Nach 15 Minuten (kann im Sketch unter #define INTERVALL_SHUTDOWN angepasst werden) geht der Arduino in einen "halben" Standby - das Display wird dunkel und der Servo wird abgeschaltet.
Dies reduziert den Stromverbrauch erheblich - ein echter Shutdown war mir hier zu aufw??ndig ...
Wenn man den Drehgeber zwei Sekunden lang dr??ckt wird der Standby sofort eingeleitet.

Voraussetzungen
- Allgemeine Bastelerfahrung (S??gen, Bohren, ...)
- M??glichst einige Vorkenntnisse in Arduino & Elektronik
- Optional L??ten

Material
- Arduino Leonardo (UNO works too - but then you have to use software serial)
- USB Netzteil mit Micro-USB-Stecker
- LCD Display 1602 IC2
- Rotary Encoder KY-040
- Servomotor MG995 180?? (oder 270?? - NICHT 360??)
- kleines Breadboard
- Jumper wires
- Holzbretter f??r das Geh??use bspw. 
	2 x 15mm x 150mm x 150mm (Vollholz, Multiplex, Sperrholz, ...)
	2 x 15mm x 150mm x 200mm (Vollholz, Multiplex, Sperrholz, ...)
	2 x 5mm x 150mm x 230mm (= 200mm + 2 x St??rke der Bretter - hier 2 x 15mm) (Sperrholz)
- Holzleiste f??r den Arm bspw. 
	5mm x 15mm x 230mm (Sperrholz)
- Holzkl??tzchen zur Befestigung des Servo bspw.
	4 x 15mm x 20mm x 20mm (Vollholz, Multiplex, Sperrholz, ...)
- PVC Hartschaum (alternativ Pappe, Sperrholz, ...)
	2mm x 35mm x 100mm Befestigung Servo
	2mm x Rahmen LCD
- Schrauben 
	12 x 4,5mm x 30mm (Geh??use)
	2 x 3mm x 15mm (Befestigung Platte des Servo)
- Draht / Schnur
- optional 
	- MP3 Modul DFPlayer mini
	- Widerstand 1kOhm
	- Lautsprecher (bspw. 8 Ohm / 2 Watt)
	- Micro-SD-Karte

Werkzeug
- Bohrmaschine
- S??ge
- Feile
- Sandpapier
- Hei??klebepistole
- optional L??tkolben

Verkabelungsplan

KY-040 <-> Arduino
CLK <-> 11
DT <-> 10
SW <-> 3
+ <-> 5V
GND <-> GND

LCD <-> Arduino
GND <-> GND
VCC <-> 5V
SDA <-> SDA
SCL <-> SCL

Servo <-> Arduino
GND (brown cable) <-> GND
+ (red cable) <-> 5V
Control (orange cable) <-> 8

DFP MP3 module <-> Arduino Leonardo (different for UNO)
RX <-> TX - Attention! Widerstand 1kOhm benutzen 
TX <-> RX
VCC <-> 5V
GND <-> GND
SPK1 <-> Speaker
SPK2 <-> Speaker

MP3 Sound
Wenn man m??chte, kann man sich zu Beginn begr????en lassen und Bescheid geben lassen, wenn der Tee fertig ist.
Dies muss man aber nicht umsetzen, um die Funktion des TeaNik nutzen zu k??nnen.
Man kann dann einfach den MP3-Player und den Lautsprecher weglassen und muss nichts ??ndern.
- Micro-SD-Karte formatieren (FAT32)
- Soundfiles (Begr????ung & Meldung, dass der Tee fertig ist) aufnehmen bspw. mit dem Handy
- Ggf. Soundfiles in .wav oder .mp3 umwandeln (SW im Internet)
- Soundfiles abspeichern
- Begr????ung unter 0001.mp3 und Meldung unter 0002.mp3 abspeichern
- Micro-SD-Karte in das DFP MP3 Modul stecken
- System starten - ggf. Lautst??rke anpassen - unter #define MP3_VOLUME

Zusammenbau & Inbetriebnahme

Geh??use 1/2
- Loch in Frontplatte f??r LCD s??gen
- Loch in Frontplatte f??r Arm s??gen
- Loch in Frontplatte f??r Drehgeber bohren
- L??cher in Frontplatte f??r Lautsprecher bohren
- Erstes Seitenteil vorbohren und mit Unterteil verschrauben (4,5mm x 30mm Schrauben)
- Vorderseite mit Hei??kleber befestigen

LCD Display
- Rahmen aus Hart-PVC ausschneiden
- LCD Display mit Hei??kleber auf Rahmen befestigen
- Rahmen auf Frontplatte mit Hei??kleber befestigen

Arm
- L??cher in die Holzleiste bohren - einmal f??r einen Haken und einmal f??r die Befestigungsschraube am Servo
- Arm des Servo mit Hei??kleber an Arm kleben - dabei auf das Befestigungsloch achten

Servo auf Platte
- Servo an Holzkl??tzchen schrauben 
- Befestigungsplatte aus Hart-PVC ausschneiden
- Kl??tzchen mit Hei??kleber auf Platte befestigen
- Kl??tzchen in Box unter und ??ber das Display kleben

Elektronik einbauen
- Platte aus Hart-PVC f??r Arduino ausschneiden, Arduino mit wenig Hei??kleber aufkleben, Platte in Unterteil kleben, so dass der Arduino mit der Hinterkante b??ndig abschlie??t
- Position des USB-Anschlusses abmessen und in R??ckwand an dieser Stelle ein Loch bohren.
- Breadboard auf Unterteil kleben
- Lautsprecher an Frontplatte kleben
- DFP MP3 Modul in Breadboard stecken (Achtung das Breadboard hat in eine Richtung Leiterbahnen - jeder Anschluss muss eine eigene Leiterbahn haben)
- Anschlussbild von DFP MP3 Modul - von oben - auf die Einkerbung achten
- 1kOhm Widerstand an RX von DFP MP3 Modul so anschlie??en, dass der zweite Pol auf der anderen Seite des Breadboards ist (siehe Foto)
- Nacheinander alle Elektronik wie im Verkabelungsplan angegeben anschlie??en
- Achtung - bei den LCD Displays ist ein h??ufiger Fehler, dass der Kontrast nicht richtig eingestellt ist, diesen per Poti auf der R??ckseite einstellen, nachdem alles verkabelt ist.
- Servo anschlie??en - aber noch nicht einbauen

Stromversorgung
- Scheinbar ist der eingebaute Spannungsregler nicht besonders leistungsf??hig.
- Beim Betrieb mit einem 9V-Netzteil kam es immer wieder zu Ausf??llen beim Display.
- Ich empfehle ein USB-Netzteil zu verwenden. 

Servo einstellen & einbauen
- Ein Servo f??hrt immer in die Mittelposition, sobald er an Spannung angeschlossen ist.
- Daher vor dem Einbau einmal den Servo anschlie??en, den Arduino kurz an Spannung anschlie??en, so dass der Servo in die Mittelposition f??hrt.
- In dieser Position den Arm anbringen, so dass er in die gew??nschte Startposition zeigt (diese kann sp??ter mit dem Drehregler angepasst werden).
- Die Platte mit dem Servo auf den Kl??tzchen festschrauben (mit 3mm x 15mm Schrauben)
- Wichtig ist weiterhin eine korrekte Einstellung der max / min Positionen des Servos.
- Wenn diese nicht passen, f??hrt der Servo unter Umst??nden an die Begrenzungen in der Box und er oder die Halterung k??nnen Schaden nehmen.
- Daher die max / min Werte ggf. zun??chst auf die Mittelposition setzen.
- #define MIN_HEIGHT 60 // maximum height of the arm
- #define MAX_HEIGHT 60 // minimum height of the arm
- Der Servo mit dem Arm in das Geh??use einsetzen und festschrauben
- Dann die Position durch Drehen des Drehgebers in die Endpositionen einstellen und die Werte notieren.
- Werte max / min anpassen
- #define MIN_HEIGHT 85 // maximum height of the arm
- #define MAX_HEIGHT 20 // minimum height of the arm
- #define START_HEIGHT 20 // start height of the arm - usefull if set to the maximum height

Geh??use 2/2
- Zweites Seitenteil vorbohren und mit Oberteil Unterteil und verschrauben (4,5mm x 30mm Schrauben)
- R??ckseite vorbohren mit Seitenteilen verschrauben (4,5mm x 30mm Schrauben)

Fazit
Teatimer2.0 ist bei uns im t??glichen Einsatz und hat sich gut bew??hrt.

Danksagung
An die vielen Ideen und Anleitungen im Internet.
An meine Frau f??r das gute Kundenfeedback und die Optimierungsvorschl??ge.
An meinen Sohn f??r das gute zusammen basteln und entwickeln.
An meine Tochter f??r die Sprachausgabe.
An deepl f??r die ??bersetzung.
