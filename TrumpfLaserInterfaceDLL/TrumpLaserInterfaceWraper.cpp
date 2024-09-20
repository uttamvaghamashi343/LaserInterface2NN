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

bool CTrumpLaserInterfaceWraper::SetLaserInterfaceControlMode(UINT16 mode)
{
    if (!glbTrumpLaserInterfaceDll.SetLaserInterfaceControlMode(mode))
        return false;

    UINT iBR = glbTrumpLaserInterfaceDll.getLaserInterfaceControlMode();
    glbTrumpLaserInterfaceDll.setReceivedDataFromTheAPS(COMMAND::L_CM, iBR);
}

bool CTrumpLaserInterfaceWraper::setLaserControlSignals(UINT16 controlSignals)
{
    return glbTrumpLaserInterfaceDll.setLaserControlSignals(controlSignals);
}

bool CTrumpLaserInterfaceWraper::setAnalogActiveCurrent(UINT16 currentValue)
{
    if (!glbTrumpLaserInterfaceDll.setAnalogActiveCurrent(currentValue))
        return false;

    UINT iBR = glbTrumpLaserInterfaceDll.getAnalogOrActiveSimmerCurrent(0);
    glbTrumpLaserInterfaceDll.setReceivedDataFromTheAPS(COMMAND::L_ACTIVE, iBR);
}

bool CTrumpLaserInterfaceWraper::setAnalogSimmerCurrent(UINT16 currentValue)
{
    if (!glbTrumpLaserInterfaceDll.setAnalogSimmerCurrent(currentValue))
        return false;

    UINT iBR = glbTrumpLaserInterfaceDll.getAnalogOrActiveSimmerCurrent(1);
    glbTrumpLaserInterfaceDll.setReceivedDataFromTheAPS(COMMAND::L_SIMMER, iBR);
}

bool CTrumpLaserInterfaceWraper::setPulseWaveform(UINT16 waveformNumber)
{
    if (!glbTrumpLaserInterfaceDll.setPulseWaveform(waveformNumber))
        return false;

    UINT selectedWaveform;
    UINT iBR = glbTrumpLaserInterfaceDll.getPulseWaveform(selectedWaveform);
    glbTrumpLaserInterfaceDll.setReceivedDataFromTheAPS(COMMAND::L_WAVEFORM, selectedWaveform);
    glbTrumpLaserInterfaceDll.setReceivedDataFromTheAPS(COMMAND::L_PRF0, iBR);
}

bool CTrumpLaserInterfaceWraper::setPulseRate(UINT32 pulseRate)
{
    if (!glbTrumpLaserInterfaceDll.setPulseRate(pulseRate))
        return false;

    UINT iBR = glbTrumpLaserInterfaceDll.getPulseRate();
    glbTrumpLaserInterfaceDll.setReceivedDataFromTheAPS(COMMAND::L_PRF, iBR);
}

bool CTrumpLaserInterfaceWraper::setPulseBurstLength(UINT32 burstLength)
{
    if (!glbTrumpLaserInterfaceDll.setPulseBurstLength(burstLength))
        return false;

    UINT iBR = glbTrumpLaserInterfaceDll.getPulseBurstLength();
    glbTrumpLaserInterfaceDll.setReceivedDataFromTheAPS(COMMAND::L_BL, iBR);
}

bool CTrumpLaserInterfaceWraper::setPumpDutyFactor(UINT16 dutyFactor)
{
    if (!glbTrumpLaserInterfaceDll.setPumpDutyFactor(dutyFactor*10))
        return false;

    UINT iBR = glbTrumpLaserInterfaceDll.getPumpDutyFactor();
    glbTrumpLaserInterfaceDll.setReceivedDataFromTheAPS(COMMAND::L_DF, iBR);
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

UINT CTrumpLaserInterfaceWraper::getAnalogOrActiveSimmerCurrent(BOOL bIsSetSimmerCurrent)
{
    return glbTrumpLaserInterfaceDll.getAnalogOrActiveSimmerCurrent(bIsSetSimmerCurrent);
}

UINT CTrumpLaserInterfaceWraper::getPulseWaveform(UINT& selectedWaveform)
{
    return glbTrumpLaserInterfaceDll.getPulseWaveform(selectedWaveform);
}

UINT CTrumpLaserInterfaceWraper::getPulseRate()
{
    return glbTrumpLaserInterfaceDll.getPulseRate();
}

UINT CTrumpLaserInterfaceWraper::getPulseBurstLength()
{
    return glbTrumpLaserInterfaceDll.getPulseBurstLength();
}

UINT CTrumpLaserInterfaceWraper::getPumpDutyFactor()
{
    return glbTrumpLaserInterfaceDll.getPumpDutyFactor();
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

