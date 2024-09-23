#include "pch.h"
#include "TrumpLaserInterfaceDll.h"
#include "TrumpLaserInterfaceWraper.h"


CTrumpLaserInterfaceDll glbTrumpLaserInterfaceDll;

void CTrumpLaserInterfaceWraper::CreateLaserInterfaceDlg(CWnd* pParent, CRect cDlgRect)
{
    glbTrumpLaserInterfaceDll.CreateDlg(pParent, cDlgRect);
}

void CTrumpLaserInterfaceWraper::ShowSetingDlg()
{
    glbTrumpLaserInterfaceDll.ShowWindow(SW_SHOW);
}

bool CTrumpLaserInterfaceWraper::setBaudRate(UINT32 baudRate)
{
    return glbTrumpLaserInterfaceDll.setBaudRate(baudRate);
}

bool CTrumpLaserInterfaceWraper::setLaserInterfaceControlMode(UINT16 mode)
{
    return glbTrumpLaserInterfaceDll.setGetLaserInterfaceControlMode(mode);
}

bool CTrumpLaserInterfaceWraper::setLaserControlSignals(UINT16 controlSignals)
{
    return glbTrumpLaserInterfaceDll.setLaserControlSignals(controlSignals);
}

bool CTrumpLaserInterfaceWraper::setPulseWaveform(UINT16 waveformNumber)
{
    return glbTrumpLaserInterfaceDll.setGetPulseWaveform(waveformNumber);
}

bool CTrumpLaserInterfaceWraper::setPulseRate(UINT32 pulseRate)
{
    return glbTrumpLaserInterfaceDll.setGetPulseRate(pulseRate);
}

bool CTrumpLaserInterfaceWraper::setAnalogActiveCurrent(UINT16 currentValue)
{
    return glbTrumpLaserInterfaceDll.setGetAnalogActiveCurrent(currentValue);
}

bool CTrumpLaserInterfaceWraper::setAnalogSimmerCurrent(UINT16 currentValue)
{
    return glbTrumpLaserInterfaceDll.setGetAnalogSimmerCurrent(currentValue);
}

bool CTrumpLaserInterfaceWraper::setPumpDutyFactor(UINT16 dutyFactor)
{
    return glbTrumpLaserInterfaceDll.setGetPumpDutyFactor(dutyFactor);
}

bool CTrumpLaserInterfaceWraper::setPulseBurstLength(UINT32 burstLength)
{
    return glbTrumpLaserInterfaceDll.setGetPulseBurstLength(burstLength);
}

bool CTrumpLaserInterfaceWraper::restartPulseGenerator(UINT16 waveform)
{
    return glbTrumpLaserInterfaceDll.restartPulseGenerator(waveform);
}

UINT CTrumpLaserInterfaceWraper::getBaudRate()
{
    return glbTrumpLaserInterfaceDll.getBaudRate();
}

UINT CTrumpLaserInterfaceWraper::getLaserInterfaceControlMode()
{
    return glbTrumpLaserInterfaceDll.getLaserInterfaceControlMode();
}

UINT CTrumpLaserInterfaceWraper::getLaserControlSignals()
{
    return glbTrumpLaserInterfaceDll.getLaserControlSignals();
}

UINT CTrumpLaserInterfaceWraper::getPulseWaveform(UINT& selectedWaveform)
{
    return glbTrumpLaserInterfaceDll.getPulseWaveform(selectedWaveform);
}

UINT CTrumpLaserInterfaceWraper::getPulseRate()
{
    return glbTrumpLaserInterfaceDll.getPulseRate();
}

UINT CTrumpLaserInterfaceWraper::getAnalogOrActiveSimmerCurrent(BOOL bIsSetSimmerCurrent)
{
    return glbTrumpLaserInterfaceDll.getAnalogOrActiveSimmerCurrent(bIsSetSimmerCurrent);
}

UINT CTrumpLaserInterfaceWraper::getPumpDutyFactor()
{
    return glbTrumpLaserInterfaceDll.getPumpDutyFactor();
}

UINT CTrumpLaserInterfaceWraper::getPulseBurstLength()
{
    return glbTrumpLaserInterfaceDll.getPulseBurstLength();
}

void CTrumpLaserInterfaceWraper::setStandby()
{
    glbTrumpLaserInterfaceDll.setStandby();
}

void CTrumpLaserInterfaceWraper::setEnable()
{
    glbTrumpLaserInterfaceDll.setEnable();
}

void CTrumpLaserInterfaceWraper::setTrigger()
{
    glbTrumpLaserInterfaceDll.setTrigger();
}

void CTrumpLaserInterfaceWraper::setRalOn()
{
    glbTrumpLaserInterfaceDll.setRalOn();
}

