# AstroTool

## Description

The device is intended for keeping the telescope in RA axis by a stepper motor (to compensate for the Earth's rotation).

Also, the device can control the DSLR camera equipped with an external shutter cable connector.

The device uses the following elements:

- Stepper motor 28BYJ48-5 (2048 steps per turn, the motor power is weak, so the gear unit 1:12.5 was used to connect it to the mount EQ1)
- Monochrome display 122*32 WG12232E

The other elements shown in the circuit diagram.

## Circuit diagram

Circuit diagram and PCB located in the Misc folder:

- [Misc/schematic.svg](Misc/schematic.svg) - circuit diagram
- [Misc/top.png](Misc/top.png) - drawing the top PCB layer
- [Misc/bottom.png](Misc/bottom.png) - drawing the bottom PCB layer
- [Misc/assembly.png](Misc/assembly.png) - position of elements on the PCB

## Program source description

Target MCU - Atmega8, system clock - internal RC oscilator 8 MHz. Fuse bits - 0xD9 (high), 0xE4 (low).

Object `Interval` allows one hardware timer call several listeners (introduced because of the lack of hardware timers).

`Keyboard` object is responsible for reading the keyboard data.

`Display` object contains methods of interaction in the display.

Object `Drive` controls stepper motor.

Object `Shutter` controls the DSLR camera shutter.

`Battery` object allows to read the voltage battery.

`Application` object contains the logic of the program.

## Configuring program for hardware

Basic program configuration located in configuration.h file

| Parameter                   | Description                                                             |
| --------------------------- | ----------------------------------------------------------------------- |
| INTERVAL_LISTENERS_COUNT \* | The maximum number of listeners for `Interval` class                    |
| INTERVAL_FREQ \*            | The operating frequency of the hardware timer for `Interval` class (Hz) |
| KEYBOARD_BOUNCE_FILTER \*\* | Keyboard bounce filter                                                  |
| KEYBOARD_LONG_TIME          | Time of a long press on the keyboard (ms)                               |
| DISPLAY_OSC_FREQ \*\*       | Display generator frequency (Hz)                                        |
| DISPLAY_LIGHT_TIME          | Display backlight time (ms)                                             |
| BATTERY_DEVIDER \*\*        | Battery voltage divider coefficient                                     |
| DRIVE_DIRECTION             | Stepper motor direction (either 0 or 1)                                 |
| DRIVE_REDUCTION             | Motor steps count per axis RA turn                                      |
| DRIVE_MAXSPEED \*\*         | The maximum speed of the stepper motor (pps)                            |

When the APPLICATION_DEBUG is defined, you can test the screen and keyboard. Exit is carried by four long-pressing the S3 button (Enter).

\* For correct operation of the program, these settings are not recommended to change

\*\* These parameters are matched to the current hardware (stepping motor, mount, display)

## User instruction

The main screen is as follows:

```
 1.0x = 107A 8.3v
> 0 / 20x10s + 2s
```

The first line displays:

- The relative speed of the engine (in this example - 1.0x)
- The current value is loaded into the timer (in this example - 107A)
- The battery voltage (in this example - 8.3v)

The second line displays:

- DSLR shutter mode as icons stop, pause or play (in the example - >)
- The current frame (in this example - 0)
- The number of frames to shoot (in this example - 20)
- Exposure time (in the example - 10s)
- Pause time between frames (in this example - 2s)

In the main mode, the current line is highlighted by reverse background.
Selection of the current line is done by pressing the S3 button (Enter).

If the cursor is on the first line, then pressing the button S1 (Left) and S2 (Right) stepper motor will spin at maximum speed in the appropriate direction.
If the cursor is on the second line, then pressing the S1 button (Left) and S2 (Right) changing DSLR shutter mode.

When long-pressing the S3 button (Enter) to any of the lines application will go to the parameter edit mode.
Selecting by pressing the S3 button (Enter).
Changing the setting is carried by buttons S1 (Left) and S2 (Right).
Exit is carried by long-pressing the S3 button (Enter).

