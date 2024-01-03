#include <GyverJoy.h>

#define LED_PIN (13) // Pin for the LED

#define JOY1_X_PIN A1
GyverJoy joy1X(JOY1_X_PIN);

#define JOY1_B_PIN A2

#define LEFT_DIRECTION_PIN 4
#define LEFT_PWM_PIN 5

void resetTrusters();

void setup()
{
    Serial.begin(9600);
    Serial.println("starting..");
    pinMode(LED_PIN, OUTPUT); // LED Visual Output

    resetTrusters();

    joy1X.invert(true);
    joy1X.calibrate();        // калибровка нуля при запуске
    joy1X.deadzone(30);       // мёртвая зона
    joy1X.exponent(GJ_CUBIC); // экспонента для плавности
}

void resetTrusters()
{
    Serial.println("resetting...");
    digitalWrite(LED_PIN, LOW);

    pinMode(LEFT_PWM_PIN, OUTPUT);
    pinMode(LEFT_DIRECTION_PIN, OUTPUT);

    delay(3000);
    digitalWrite(LED_PIN, HIGH); // LED High Once Armed
}

void loop()
{
    int z10 = analogRead(JOY1_B_PIN);
    Serial.println(z10);
    if (z10 > 1000)
    {
        resetTrusters();
    }

    Serial.print("now ");
    int v = analogRead(1);
    if (joy1X.tick())
    {
        v = joy1X.value();
    }

    Serial.println(v);

    int speedLeft = 0;
    int dirrection = 0;
    if (v >= 0)
    {
        dirrection = 0;
        speedLeft = v;
    }
    else
    {
        dirrection = 1;
        speedLeft = 255 - abs(v);
    }

    Serial.print("dirrection / speedLeft = ");
    Serial.print(dirrection);
    Serial.print(" / ");
    Serial.println(speedLeft);

    digitalWrite(LEFT_DIRECTION_PIN, dirrection);
    analogWrite(LEFT_PWM_PIN, abs(speedLeft)); // value 0.. 255
}
