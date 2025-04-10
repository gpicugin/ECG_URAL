#ifndef SERIALPORTGLOBAL_H
#define SERIALPORTGLOBAL_H

#include <stdint.h>

//ECG
#define SIZE_PACKAGE_ECG_ALTONICA       16          //размер пакета по протоколу

#define MASK_ALTONICA_R_BREAK           0x01        // RN-line break
#define MASK_ALTONICA_L_BREAK           0x02        // L-line Break
#define MASK_ALTONICA_F_BREAK           0x04        // F-line break
#define MASK_ALTONICA_C_BREAK           0x08        // C-line break
#define MASK_ALTONICA_LN_BI             0x10        // LN-line zero impedance
#define MASK_ALTONICA_LR_BI             0x20        // LR-line high impedance
#define MASK_ALTONICA_FR_BI             0x40        // FR-line high impedance
#define MASK_ALTONICA_CR_BI             0x80        // CR-line high impedance

//COMMON
#define SIZE_PACKAGE_COMMON             2           //размер пакета по протоколу

enum NumSerialPort
{
    COMMON      = 3,
    ECG         = 4
};

#endif // SERIALPORTGLOBAL_H
