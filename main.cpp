#include <iostream>
#include "i2cbus.h"

using namespace std;

#define PCF8574_W 0x40
#define PCF8574_R 0x41

int main()
{
    try
    {
        I2cBus busI2c("/dev/i2c-1");
        busI2c.CommencerTransmission(PCF8574_R);
        cout << "Valeur du capteur : " << busI2c.LireRegistre(0);
    }
    catch(I2cException const &e)
    {
        cout << e.ObtenirErreur() << endl;
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
