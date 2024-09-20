#pragma once
#include "resource.h"
#include "AKGHWCDummy6Axis.h"    
#include "afxdialogex.h"
#include "INI.h"

enum class COMMAND
{
	// For show Status (Temp, Currents, Voltages)
	L_LTV = 0,
	L_BTV,
	L_PACV,
	L_MACV,
	L_LPVV,
	L_APVV,

	// For Active Parameter Set
	L_CM,
	L_CWP,
	L_WAVEFORM,
	L_PRF,
	L_PRF0,
	L_ACTIVE,
	L_SIMMER,
	L_DF,
	L_BL,
};

struct FirmwareDetails
{
	UINT16 fpgaHardwareRevMajor;
	UINT16 fpgaHardwareRevMinor;
	UINT16 fpgaHardwareRelease;
	UINT16 fpgaFirmwareRevMajor;
	UINT16 fpgaFirmwareRevMinor;
	UINT16 fpgaFirmwareRelease;
	UINT32 stellarisFirmwareVersion;
	UINT16 driverFirmware;
};

struct LaserDescription
{
	UINT16 ratedPowerLevel;
	UINT16 maxPulseRate;
	UINT16 ratedEnergy;
	UINT32 features;
};

class CTrumpLaserInterfaceDll : public CDialogEx
{
	DECLARE_DYNAMIC(CTrumpLaserInterfaceDll)

public:
	CTrumpLaserInterfaceDll(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTrumpLaserInterfaceDll();
	CAKGHWCDummy6Axis m_cAKGHWCDummy6Axis;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LASER_INTERFACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	HICON m_hIcon;
	DECLARE_MESSAGE_MAP()
public:
	CIniReader m_IniReadWritePrm;
	
	CToolTipCtrl m_ToolTip;

	CBitmap m_bmpGrey, m_bmpRed, m_bmpYellow;

	CStatic m_ctrlLaserOn;
	CStatic m_ctrlLaserEnabled;
	CStatic m_ctrlLaserDisabled;
	CStatic m_ctrlLaserEmissionGate;
	CStatic m_ctrlLaserEmission;
	CStatic m_ctrlMonitor;
	CStatic m_ctrlCW;
	CStatic m_ctrlAlarm;
	CStatic m_ctrlSystemFault;
	CStatic m_ctrlTaskActive;
	CStatic m_ctrlLaserBodyTemp;
	CStatic m_ctrlBeamDeliveryTemp;
	CStatic m_ctrlPowerSupplyFault;
	CStatic m_ctrlFanFault;
	CStatic m_ctrlEmergencyStopFault;

	CEdit m_EditLaserIPAdd;
	CString m_csLaserIPAddress;
	int m_iPort;
	bool m_bConnectResponce = false;

	// Initialize RAL ON/OFF state
	bool m_bRalOn = false;  // Assuming the initial state is RAL OFF

	// Initialize Enable ON/OFF state
	bool m_bEnableOn = false;  // Assuming the initial state is Enable OFF

	UINT_PTR m_nTimerID;

	CString m_csLaserControl;
	CStatic m_csPulseGeneration;
	CString m_csCurrentControl;
	CString m_csFPE;
	CString m_csWaveformSelection;
	CString m_csLaserTemp;
	CString m_csBDOTemp;
	CString m_csPreAmpCurrent;
	CString m_csMainAmpCurrent;
	CString m_csLogicPSUVoltages;
	CString m_csAmpPSUVoltages;

	CComboBox m_ctrlControlMode;
	CComboBox m_ctrlCWPulse;
	CComboBox m_ctrlWaveform;
	CString m_csSetControlMode;
	CString m_csSetCWPulse;
	CString m_csSetWaveform;
	CString m_csSetPRF;
	CString m_csSetActive;
	CString m_csSetSimmer;
	CString m_csSetDutyFactor;
	CString m_csSetBurstLength;
	CString m_csGetControlMode;
	CString m_csGetCWPulse;
	CString m_csGetWaveform;
	CString m_csGetPRF;
	CString m_csGetPRF0;
	CString m_csGetActive;
	CString m_csGetSimmer;
	CString m_csGetDutyFactor;
	CString m_csGetBurstLength;

	CSpinButtonCtrl m_ctrlSpinPRF;
	CSpinButtonCtrl m_ctrlSpinActive;
	CSpinButtonCtrl m_ctrlSpinSimmer;
	CSpinButtonCtrl m_ctrlSpinDutyFactor;
	CSpinButtonCtrl m_ctrlSpinBurstLength;

	CBrush m_brushRed;
	CBrush m_brushGreen;
	CFont m_fontLarge;

	UINT getBaudRate();
	UINT getLaserInterfaceControlMode();
	UINT getLaserControlSignals();
	UINT getAnalogOrActiveSimmerCurrent(BOOL bType);
	UINT getPulseWaveform(UINT& selectedWaveform);
	UINT getPulseRate();
	UINT getPulseBurstLength();
	UINT getPumpDutyFactor();
	BOOL getCheckSumValidation();

	void setLEDLaserOn(bool val);
	void setLEDLaserEnabled(bool val);
	void setLEDLaserDisabled(bool val);
	void setLEDLaserEmissionGate(bool val);
	void setLEDLaserEmission(bool val);
	void setLEDMonitor(bool val);
	void setLEDCW(bool val);
	void setLEDAlarm(bool val);
	void setLEDSystemFault(bool val);
	void setLEDTaskActive(bool val);
	void setLEDLaserBodyTemp(bool val);
	void setLEDBeamDeliveryTemp(bool val);
	void setLEDPowerSupplyFault(bool val);
	void setLEDFanFault(bool val);
	void setLEDEmergencyStopFault(bool val);
	void setLED(CStatic& ctrlLED, bool val, HBITMAP hBitmapOn, HBITMAP hBitmapOff);

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void CreateDlg(CWnd* pParent, CRect cDlgRect);
	void fillComboBoxAndControlBox();
	void setTooltipForControl();
	afx_msg void OnBnClickedButtonIlmTestEthernetSetupConnect();
	void UpdateLaserData();
	afx_msg void OnBnClickedButtonIlmTestEthernetSetupDisconnect();
	void connectAsTCPIPClient(CString csIpAdress, int iPortNum);
	void disconnectFromTCPIPClient();

	bool setBaudRate(UINT32 baudRate);
	void HandleBaudRateResponse(BYTE response);

	bool SetLaserInterfaceControlMode(UINT16 mode);
	void HandleLaserInterfaceControlModeResponse(BYTE response);

	bool setLaserControlSignals(UINT16 controlSignals);
	void HandleLaserControlSignalsResponse(BYTE response);

	bool setAnalogActiveCurrent(UINT16 currentValue);
	bool setAnalogSimmerCurrent(UINT16 currentValue);
	void HandleAnalogCurrentSetPointResponse(BYTE response);

	bool setPulseWaveform(UINT16 waveformNumber);
	void HandlePulseWaveformResponse(BYTE response);

	bool setPulseRate(UINT32 pulseRate);
	void HandlePulseRateResponse(BYTE response);

	bool setPulseBurstLength(UINT32 burstLength);
	void HandlePulseBurstLengthResponse(BYTE response);

	bool setPumpDutyFactor(UINT16 dutyFactor);
	void HandlePumpDutyFactorResponse(BYTE response);

	bool setPulseGeneratorParameters(UINT16 waveform, UINT32 pulseRate, UINT32 burstLength, UINT16 dutyFactor);
	bool restartPulseGenerator(UINT16 waveform);
	bool setLaserDiagnosisState();

	bool WaitForData(int timeoutMilliseconds);
	void DoEvent(int iDelay);
	void setReceivedDataFromTheAPS(COMMAND iCommandType, UINT iVal);
	void setReceivedDataFromTheLaserStatus(COMMAND iCommandType, double iVal);
	UINT32 getLaserSerialNumber();
	CString getLaserPartNumber();
	FirmwareDetails getLaserFirmwareDetails();
	LaserDescription getLaserDescription();
	bool getLaserTemperatures(UINT16& laserTemperature, UINT16& beamDeliveryTemperature);
	bool getLaserCurrents(UINT16& preAmplifierCurrent, UINT16& powerAmplifierCurrent);
	bool getPowerSupplyVoltages(UINT16& logicVoltage, UINT16& diodeVoltage);
	bool getLaserCurrents(UINT16& preAmplifierCurrent, UINT16& powerAmplifierCurrent1, UINT16& powerAmplifierCurrent2, UINT16& powerAmplifierCurrent3);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnDeltaposSpinPrf(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinActive(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSimmer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinDutyFactor(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinBurstLength(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCbnSelchangeComboControlMode();
	afx_msg void OnCbnSelchangeComboCwPulse();
	afx_msg void OnCbnSelchangeComboWaveform();
	afx_msg void OnEnKillfocusEditPrf();
	afx_msg void OnEnKillfocusEditActive();
	afx_msg void OnEnKillfocusEditSimmer();
	afx_msg void OnEnKillfocusEditDutyFactor();
	afx_msg void OnEnKillfocusEditBurstLength();
	void setStandby();
	afx_msg void OnBnClickedButtonStandby();
	void setEnable();
	afx_msg void OnBnClickedButtonEnable();
	void setTrigger();
	afx_msg void OnBnClickedButtonTrigger();
	void setRalOn();
	afx_msg void OnBnClickedButtonRalOn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual void OnOK();
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void readWriteLaserActiveParameterSet(BOOL bIsReading);

};
