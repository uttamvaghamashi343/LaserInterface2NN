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
		bool setLaserInterfaceControlMode(UINT16 mode);
		bool setLaserControlSignals(UINT16 controlSignals);
		bool setPulseWaveform(UINT16 waveformNumber);
		bool setPulseRate(UINT32 pulseRate);
		bool setAnalogActiveCurrent(UINT16 currentValue);
		bool setAnalogSimmerCurrent(UINT16 currentValue);
		bool setPumpDutyFactor(UINT16 dutyFactor);
		bool setPulseBurstLength(UINT32 burstLength);
		
		bool restartPulseGenerator(UINT16 waveform);

		UINT getBaudRate();
		UINT getLaserInterfaceControlMode();
		UINT getLaserControlSignals();
		UINT getPulseWaveform(UINT& selectedWaveform);
		UINT getPulseRate();
		UINT getAnalogOrActiveSimmerCurrent(BOOL bType);
		UINT getPumpDutyFactor();
		UINT getPulseBurstLength();
		
		void setStandby();
		void setEnable();
		void setTrigger();
		void setRalOn();
};

