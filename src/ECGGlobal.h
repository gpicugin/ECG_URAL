#ifndef ECGGLOBAL_H
#define ECGGLOBAL_H

enum enumModeECG
{
    Graph3Wire  = 0,
    Graph5Wire  = 1
};

enum enumPositionGraph
{
    GraphECG                = 0,
    GraphECG_SPO2           = 1,
    GraphECG_IBP            = 2,
    GraphECG_SPO2_IBP       = 3,
    SizeEnumPositionGraph   = 4
};

enum enumTypeGraph
{
    GraphI          = 0,
    GraphII         = 1,
    GraphIII        = 2,
    GraphAVR        = 3,
    GraphAVL        = 4,
    GraphAVF        = 5,
    GraphV          = 6,
    GraphSPO2       = 7
};

enum enumVSweepECG
{
    VSweep2_5       = 0,
    VSweep5         = 1,
    VSweep10        = 2,
    VSweep20        = 3,
    VSweep40        = 4,
    SizeVSweepECG   = 5
};

enum enumHSweepECG
{
    HSweep12        = 0,
    HSweep25        = 1,
    HSweep50        = 2,
    HSweep100       = 3,
    SizeHSweepECG   = 4
};

enum enumOperatingMode
{
    ModeDiagnostics     = 0,
    ModeMonitoring      = 1,
    ModeSurgical        = 2,
    SizeOperatingMode   = 3
};

#define PULSE_VOLUME_MAX 5

enum enumPulseTone
{
    PulseToneMono = 0,
    PulseToneSPO2 = 1,
    SizePulseTone = 2
};

enum enumNumSettingsECG_SPO2
{
    SettingECGMode          = 0,
    SettingECGGraph1        = 1,
    SettingECGGraph2        = 2,
    SettingECGGraph3        = 3,
    SettingVSweepECG        = 4,
    SettingHSweepECG        = 5,
    SettingECGOperatingMode = 6,
    SettingECG50HzFilter    = 7,
    SettingSPO2PulseVolume  = 8,
    SettingSPO2PulseTone    = 9,
    SizeSettingECG_SPO2     = 10
};

#endif // ECGGLOBAL_H
