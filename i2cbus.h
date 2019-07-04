#ifndef I2CBUS_H
#define I2CBUS_H

#include <string>

#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>

using namespace std;

class I2cBus
{
private:
    string i2cDev;
    int fichierI2c;

public:
    I2cBus(string _i2cDev);
    ~I2cBus();
    int i2c_smbus_access(char _mode, unsigned char _registre, int _taille, i2c_smbus_data *_data);
    void CommencerTransmission(unsigned char _adresse);
    unsigned char LireRegistre(unsigned char _registre);
    int EcrireRegistre(unsigned char _registre, unsigned char _valeur);
};

class I2cException
{
  private:
    int code;
    string message;
  public:
    I2cException(int _codeErreur, string _message);
    string ObtenirErreur() const;
};

#endif // I2CBUS_H
