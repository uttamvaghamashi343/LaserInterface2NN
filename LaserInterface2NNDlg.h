// LaserInterface2NNDlg.h : header file
//

#pragma once

#include "AKGHWCDummy6Axis.h"       

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
	uint16_t fpgaHardwareRevMajor;
	uint16_t fpgaHardwareRevMinor;
	uint16_t fpgaHardwareRelease;
	uint16_t fpgaFirmwareRevMajor;
	uint16_t fpgaFirmwareRevMinor;
	uint16_t fpgaFirmwareRelease;
	uint32_t stellarisFirmwareVersion;
	uint16_t driverFirmware;
};

struct LaserDescription
{
	uint16_t ratedPowerLevel; 
	uint16_t maxPulseRate;    
	uint16_t ratedEnergy;     
	uint32_t features;        
};

// CLaserInterface2NNDlg dialog
class CLaserInterface2NNDlg : public CDialogEx
{
	// Construction
public:
	CLaserInterface2NNDlg(CWnd* pParent = nullptr); // standard constructor
	~CLaserInterface2NNDlg(); // destructor
	CAKGHWCDummy6Axis m_cAKGHWCDummy6Axis;

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LASERINTERFACE2NN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	DECLARE_MESSAGE_MAP()

public:
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

	// Initialize RAL ON/OFF state
	bool m_bRalOn = false;  // Assuming the initial state is RAL OFF

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
	BOOL getCheckSumValidation();
	UINT getLaserInterfaceControlMode();
	UINT getLaserControlSignals();
	UINT getAnalogOrActiveSimmerCurrent(BOOL bType);
	UINT32 getPulseWaveform(UINT16& selectedWaveform);
	UINT getPulseRate();
	UINT getPulseBurstLength();
	UINT getPumpDutyFactor();

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
	
	bool SetLaserInterfaceControlMode(UCHAR mode);
	void HandleLaserInterfaceControlModeResponse(BYTE response);
	
	bool setLaserControlSignals(uint16_t controlSignals);
	void HandleLaserControlSignalsResponse(BYTE response);
	
	bool setAnalogActiveCurrent(uint16_t currentValue);
	bool setAnalogSimmerCurrent(uint16_t currentValue);
	void HandleAnalogCurrentSetPointResponse(BYTE response);
	
	bool setPulseWaveform(uint16_t waveformNumber);
	void HandlePulseWaveformResponse(BYTE response);
	
	bool setPulseRate(uint32_t pulseRate);
	void HandlePulseRateResponse(BYTE response);
	
	bool setPulseBurstLength(uint32_t burstLength);
	void HandlePulseBurstLengthResponse(BYTE response);
	
	bool setPumpDutyFactor(uint16_t dutyFactor);
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
	afx_msg void OnBnClickedButtonStandby();
	afx_msg void OnBnClickedButtonEnable();
	afx_msg void OnBnClickedButtonTrigger();
	afx_msg void OnBnClickedButtonRalOn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual void OnOK();
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
};
