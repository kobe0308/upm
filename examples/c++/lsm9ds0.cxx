/*
 * Author: Jon Trulson <jtrulson@ics.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include <signal.h>

#include "lsm9ds0.hpp"
#include "upm_utilities.h"

using namespace std;

int shouldRun = true;

void
sig_handler(int signo)
{
    if (signo == SIGINT)
        shouldRun = false;
}

int
main(int argc, char** argv)
{
    signal(SIGINT, sig_handler);
    //! [Interesting]

    // Instantiate an LSM9DS0 using default parameters (bus 1, gyro addr 6b,
    // xm addr 1d)
    upm::LSM9DS0 sensor;

    sensor.init();

    while (shouldRun) {
        sensor.update();

        float x, y, z;

        sensor.getAccelerometer(&x, &y, &z);
        cout << "Accelerometer: ";
        cout << "AX: " << x << " AY: " << y << " AZ: " << z << endl;

        sensor.getGyroscope(&x, &y, &z);
        cout << "Gryoscope:     ";
        cout << "GX: " << x << " GY: " << y << " GZ: " << z << endl;

        sensor.getMagnetometer(&x, &y, &z);
        cout << "Magnetometer:  ";
        cout << "MX = " << x << " MY = " << y << " MZ = " << z << endl;

        cout << "Temperature:   " << sensor.getTemperature() << endl;
        cout << endl;

        upm_delay_us(500000);
    }

    //! [Interesting]

    cout << "Exiting..." << endl;

    return 0;
}
