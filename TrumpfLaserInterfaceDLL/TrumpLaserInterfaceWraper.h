#pragma once


#ifdef TRUMP_LASER_INTERFACE_DLL
#define exportTrumpLaserInterfaceDll _declspec(dllexport)
#else
#define exportTrumpLaserInterfaceDll _declspec(dllimport)
#endif

class exportTrumpLaserInterfaceDll CTrumpLaserInterfaceWraper
{
	public:

		void CreateLaserInterfaceDlg(CWnd* pParent, CRect cDlgRect);
		void ShowSetingDlg();
		bool setBaudRate(UINT32 baudRate);
		bool SetLaserInterfaceControlMode(UINT16 mode);
		bool setLaserControlSignals(UINT16 controlSignals);
		bool setAnalogActiveCurrent(UINT16 currentValue);
		bool setAnalogSimmerCurrent(UINT16 currentValue);
		bool setPulseWaveform(UINT16 waveformNumber);
		bool setPulseRate(UINT32 pulseRate);
		bool setPulseBurstLength(UINT32 burstLength);
		bool setPumpDutyFactor(UINT16 dutyFactor);
		bool restartPulseGenerator(UINT16 waveform);
		UINT getBaudRate();
		UINT getLaserInterfaceControlMode();
		UINT getLaserControlSignals();
		UINT getAnalogOrActiveSimmerCurrent(BOOL bType);
		UINT getPulseWaveform(UINT& selectedWaveform);
		UINT getPulseRate();
		UINT getPulseBurstLength();
		UINT getPumpDutyFactor();
		void setStandby();
		void setEnable();
		void setTrigger();
		void setRalOn();

};

