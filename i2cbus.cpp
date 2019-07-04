#include "i2cbus.h"



I2cBus::I2cBus(string _i2cDev):
    i2cDev(_i2cDev)
{
    if ((fichierI2c = open(i2cDev.c_str(), O_RDWR)) < 0)
        throw I2cException(errno, " Erreur d'ouverture de " + i2cDev);
}

I2cBus::~I2cBus()
{
    close(fichierI2c);
}

int I2cBus::i2c_smbus_access(char _mode, unsigned char _registre, int _taille, i2c_smbus_data *_data)
{
    struct i2c_smbus_ioctl_data args;
    args.read_write = _mode;
    args.command = _registre;
    args.size = _taille;
    args.data = _data;
    return ioctl(fichierI2c, I2C_SMBUS, &args);
}

void I2cBus::CommencerTransmission(unsigned char _adresse)
{
    if (ioctl(fichierI2c, I2C_SLAVE, _adresse) < 0)
        throw I2cException(errno, " Erreur affectation adresse " + to_string(_adresse));
}

unsigned char I2cBus::LireRegistre(unsigned char _registre)
{
    union i2c_smbus_data data;
    if (i2c_smbus_access(I2C_SMBUS_READ, _registre, I2C_SMBUS_BYTE_DATA, &data) < 0)
        throw I2cException(errno, " Erreur Lecture registre 8 bits n° " + to_string(_registre));
    return data.byte & 0xFF;
}

int I2cBus::EcrireRegistre(unsigned char _registre, unsigned char _valeur)
{
    int retour;
    union i2c_smbus_data data;
    data.byte = _valeur;
    if ((retour = i2c_smbus_access(I2C_SMBUS_WRITE, _registre, I2C_SMBUS_BYTE_DATA, &data)) < 0)
        throw I2cException(errno, " Erreur Ecriture registre 8 bits n° "+ to_string(_registre));
    return retour;
}

I2cException::I2cException(int _codeErreur, string _message):
    code(_codeErreur),
    message(_message)
{
}

string I2cException::ObtenirErreur() const
{
    string erreur = "Code erreur : ";
    erreur += to_string(code);
    erreur += " ";
    erreur += message;
    return erreur;
}
