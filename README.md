# RC Car with Obstacle Avoidance

An Arduino-based RC car with **Bluetooth control** and **ultrasonic obstacle avoidance**.

The car can be controlled wirelessly through Bluetooth and can automatically detect and avoid obstacles using an **HC-SR04 ultrasonic sensor** mounted on an **SG90 servo**.

## Features

* Bluetooth remote control
* Automatic obstacle detection
* Ultrasonic distance measurement using HC-SR04
* Servo-mounted sensor for left/right scanning
* Automatic reverse and direction selection when an obstacle is detected
* 4-wheel drive using four DC motors

## Hardware

* Arduino Uno
* Adafruit Motor Shield V1
* HC-05 Bluetooth module
* HC-SR04 ultrasonic sensor
* SG90 servo motor
* 4 × DC motors
* 4-wheel chassis
* Battery
* Jumper wires

## How It Works

In normal mode, the car receives movement commands through Bluetooth.

When obstacle avoidance is enabled, the HC-SR04 continuously measures the distance in front of the car.

If an obstacle is detected within the set distance:

1. The car stops.
2. It reverses briefly.
3. The ultrasonic sensor scans the left and right sides.
4. The car compares the available space.
5. It turns toward the clearer direction.
6. Normal movement resumes.

```text
Bluetooth Command
       │
       ▼
    Arduino
       │
       ├──► Motor Shield ──► DC Motors
       │
       └──► HC-SR04
              │
              ▼
          Obstacle?
          /       \
        No         Yes
        │           │
        ▼           ▼
     Continue    Stop → Reverse
                    │
                    ▼
               Scan Left/Right
                    │
                    ▼
              Choose Direction
                    │
                    ▼
                   Turn
```

## Pin Connections

### HC-SR04

| HC-SR04 | Arduino |
| ------- | ------- |
| VCC     | 5V      |
| GND     | GND     |
| TRIG    | D4      |
| ECHO    | D5      |

### HC-05

| HC-05 | Arduino |
| ----- | ------- |
| VCC   | 5V      |
| GND   | GND     |
| TX    | A2      |
| RX    | A3      |

The motors are controlled through the **Adafruit Motor Shield V1**.

## Software

The project uses the following Arduino libraries:

* `AFMotor`
* `Servo`
* `SoftwareSerial`

## Getting Started

1. Assemble the chassis and connect the motors to the Motor Shield.
2. Connect the HC-SR04 and SG90 servo.
3. Connect the HC-05 Bluetooth module.
4. Open the Arduino sketch.
5. Install the required libraries.
6. Upload the code to the Arduino Uno.
7. Pair your phone/controller with the HC-05.
8. Send movement commands to control the car.

## Project Status

Completed and tested on Arduino Uno.

## Future Improvements

* Add speed control
* Improve obstacle detection
* Add autonomous navigation
* Replace Bluetooth control with a longer-range RF system
* Add battery voltage monitoring

## License

This project is open source. Feel free to modify and build upon it.
