// TrumpLaserInterfaceDll.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "TrumpLaserInterfaceDll.h"
#include "afxdialogex.h"
#include <chrono>   // For std::chrono functions
#include <thread> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const CString ACTIVEPARAMETERSET_FILE_PATH = _T("C:\\SLTCard\\LaserActiveParameterSet.ini");
#define READ_SETTING TRUE
#define WRITE_SETTING FALSE

IMPLEMENT_DYNAMIC(CTrumpLaserInterfaceDll, CDialogEx)


CTrumpLaserInterfaceDll::CTrumpLaserInterfaceDll(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LASER_INTERFACE, pParent)
	, m_csLaserIPAddress(_T("192.168.101.22"))
	, m_iPort(58174)
	, m_csLaserControl(_T(""))
	, m_csCurrentControl(_T(""))
	, m_csFPE(_T(""))
	, m_csWaveformSelection(_T(""))
	, m_csLaserTemp(_T(""))
	, m_csBDOTemp(_T(""))
	, m_csPreAmpCurrent(_T(""))
	, m_csMainAmpCurrent(_T(""))
	, m_csLogicPSUVoltages(_T(""))
	, m_csAmpPSUVoltages(_T(""))
	, m_csSetControlMode(_T(""))
	, m_csSetCWPulse(_T(""))
	, m_csSetWaveform(_T(""))
	, m_csSetPRF(_T("0"))
	, m_csSetActive(_T("0"))
	, m_csSetSimmer(_T("0"))
	, m_csSetDutyFactor(_T("0"))
	, m_csSetBurstLength(_T("0"))
	, m_csGetControlMode(_T(""))
	, m_csGetCWPulse(_T("PULSE"))
	, m_csGetWaveform(_T(""))
	, m_csGetPRF(_T(""))
	, m_csGetPRF0(_T(""))
	, m_csGetActive(_T(""))
	, m_csGetSimmer(_T(""))
	, m_csGetDutyFactor(_T(""))
	, m_csGetBurstLength(_T(""))
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTrumpLaserInterfaceDll::~CTrumpLaserInterfaceDll()
{
}

void CTrumpLaserInterfaceDll::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TRUPULSENANO_SETUP_LASER_IP, m_EditLaserIPAdd);
	DDX_Text(pDX, IDC_EDIT_TRUPULSENANO_SETUP_LASER_IP, m_csLaserIPAddress);
	DDX_Text(pDX, IDC_EDIT_TRUPULSENANO_SETUP_PORT, m_iPort);
	DDX_Text(pDX, IDC_STATIC_LASER_CONTROL_VALUE, m_csLaserControl);
	DDX_Control(pDX, IDC_STATIC_PULSE_GENERATION_VALUE, m_csPulseGeneration);
	DDX_Text(pDX, IDC_STATIC_CURRENT_CONTROL_VALUE, m_csCurrentControl);
	DDX_Text(pDX, IDC_STATIC_FPE_VALUE, m_csFPE);
	DDX_Text(pDX, IDC_STATIC_WAVEFORM_SELECTION_VALUE, m_csWaveformSelection);
	DDX_Text(pDX, IDC_STATIC_LASER_TEMP_VALUE, m_csLaserTemp);
	DDX_Text(pDX, IDC_STATIC_BDO_TEMP_VALUE, m_csBDOTemp);
	DDX_Text(pDX, IDC_STATIC_PRE_AMP_CURR_VALUE, m_csPreAmpCurrent);
	DDX_Text(pDX, IDC_STATIC_MAIN_AMP_CURR_VALUE, m_csMainAmpCurrent);
	DDX_Text(pDX, IDC_STATIC_LOGIC_PSU_VOLT_VALUE, m_csLogicPSUVoltages);
	DDX_Text(pDX, IDC_STATIC_AMP_PSU_VOLT_VALUE, m_csAmpPSUVoltages);
	DDX_Control(pDX, IDC_COMBO_CONTROL_MODE, m_ctrlControlMode);
	DDX_Control(pDX, IDC_COMBO_CW_PULSE, m_ctrlCWPulse);
	DDX_Control(pDX, IDC_COMBO_WAVEFORM, m_ctrlWaveform);
	DDX_CBString(pDX, IDC_COMBO_CONTROL_MODE, m_csSetControlMode);
	DDX_CBString(pDX, IDC_COMBO_CW_PULSE, m_csSetCWPulse);
	DDX_CBString(pDX, IDC_COMBO_WAVEFORM, m_csSetWaveform);
	DDX_Text(pDX, IDC_EDIT_PRF, m_csSetPRF);
	DDX_Text(pDX, IDC_EDIT_ACTIVE, m_csSetActive);
	DDX_Text(pDX, IDC_EDIT_SIMMER, m_csSetSimmer);
	DDX_Text(pDX, IDC_EDIT_DUTY_FACTOR, m_csSetDutyFactor);
	DDX_Text(pDX, IDC_EDIT_BURST_LENGTH, m_csSetBurstLength);
	DDX_Text(pDX, IDC_CONTROL_MODE_VALUE, m_csGetControlMode);
	DDX_Text(pDX, IDC_CW_PULSE_VALUE, m_csGetCWPulse);
	DDX_Text(pDX, IDC_WAVEFORM_VALUE, m_csGetWaveform);
	DDX_Text(pDX, IDC_PRF_VALUE, m_csGetPRF);
	DDX_Text(pDX, IDC_PRF0_VALUE, m_csGetPRF0);
	DDX_Text(pDX, IDC_ACTIVE_VALUE, m_csGetActive);
	DDX_Text(pDX, IDC_SIMMER_VALUE, m_csGetSimmer);
	DDX_Text(pDX, IDC_DUTY_FACTOR_VALUE, m_csGetDutyFactor);
	DDX_Text(pDX, IDC_BURST_LENGTH_VALUE, m_csGetBurstLength);
	DDX_Control(pDX, IDC_SPIN_TRUPULSENANO_PRF, m_ctrlSpinPRF);
	DDX_Control(pDX, IDC_SPIN_TRUPULSENANO_ACTIVE, m_ctrlSpinActive);
	DDX_Control(pDX, IDC_SPIN_TRUPULSENANO_SIMMER, m_ctrlSpinSimmer);
	DDX_Control(pDX, IDC_SPIN_TRUPULSENANO_DUTY_FACTOR, m_ctrlSpinDutyFactor);
	DDX_Control(pDX, IDC_SPIN_TRUPULSENANO_BURST_LENGTH, m_ctrlSpinBurstLength);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_LASER_ON, m_ctrlLaserOn);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_LASER_ENABLED, m_ctrlLaserEnabled);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_LASER_DISABLED, m_ctrlLaserDisabled);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_LASER_EMISSION_GATE, m_ctrlLaserEmissionGate);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_LASER_EMISSION, m_ctrlLaserEmission);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_MONITOR, m_ctrlMonitor);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_CW, m_ctrlCW);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_ALARM, m_ctrlAlarm);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_SYSTEM_FAULT, m_ctrlSystemFault);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_TASK_ACTIVE, m_ctrlTaskActive);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_LASER_BODY_TEMP, m_ctrlLaserBodyTemp);
	DDX_Control(pDX, IDC_STATIC_PICTURE_TRUPULSENANO_BEAM_DELIVERY_TEMP, m_ctrlBeamDeliveryTemp);
	DDX_Control(pDX, IDC_STATIC_ALARM_POWER_FAULT_VALUE, m_ctrlPowerSupplyFault);
	DDX_Control(pDX, IDC_STATIC_ALARM_FAN_FAULT_VALUE, m_ctrlFanFault);
	DDX_Control(pDX, IDC_STATIC_ALARM_EMERGENCY_STOP_VALUE, m_ctrlEmergencyStopFault);
}

BEGIN_MESSAGE_MAP(CTrumpLaserInterfaceDll, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TRUPULSENANO_SETUP_CONNECT, &CTrumpLaserInterfaceDll::OnBnClickedButtonTruPulseNanoSetupConnect)
	ON_BN_CLICKED(IDC_BUTTON_TRUPULSENANO_SETUP_DISCONNECT, &CTrumpLaserInterfaceDll::OnBnClickedButtonTruPulseNanoSetupDisconnect)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TRUPULSENANO_PRF, &CTrumpLaserInterfaceDll::OnDeltaposSpinPrf)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TRUPULSENANO_ACTIVE, &CTrumpLaserInterfaceDll::OnDeltaposSpinActive)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TRUPULSENANO_SIMMER, &CTrumpLaserInterfaceDll::OnDeltaposSpinSimmer)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TRUPULSENANO_DUTY_FACTOR, &CTrumpLaserInterfaceDll::OnDeltaposSpinDutyFactor)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TRUPULSENANO_BURST_LENGTH, &CTrumpLaserInterfaceDll::OnDeltaposSpinBurstLength)
	ON_CBN_SELCHANGE(IDC_COMBO_CONTROL_MODE, &CTrumpLaserInterfaceDll::OnCbnSelchangeComboControlMode)
	ON_CBN_SELCHANGE(IDC_COMBO_CW_PULSE, &CTrumpLaserInterfaceDll::OnCbnSelchangeComboCwPulse)
	ON_CBN_SELCHANGE(IDC_COMBO_WAVEFORM, &CTrumpLaserInterfaceDll::OnCbnSelchangeComboWaveform)
	ON_EN_KILLFOCUS(IDC_EDIT_PRF, &CTrumpLaserInterfaceDll::OnEnKillfocusEditPrf)
	ON_EN_KILLFOCUS(IDC_EDIT_ACTIVE, &CTrumpLaserInterfaceDll::OnEnKillfocusEditActive)
	ON_EN_KILLFOCUS(IDC_EDIT_SIMMER, &CTrumpLaserInterfaceDll::OnEnKillfocusEditSimmer)
	ON_EN_KILLFOCUS(IDC_EDIT_DUTY_FACTOR, &CTrumpLaserInterfaceDll::OnEnKillfocusEditDutyFactor)
	ON_EN_KILLFOCUS(IDC_EDIT_BURST_LENGTH, &CTrumpLaserInterfaceDll::OnEnKillfocusEditBurstLength)
	ON_BN_CLICKED(IDC_BUTTON_STANDBY, &CTrumpLaserInterfaceDll::OnBnClickedButtonStandby)
	ON_BN_CLICKED(IDC_BUTTON_ENABLE, &CTrumpLaserInterfaceDll::OnBnClickedButtonEnable)
	ON_BN_CLICKED(IDC_BUTTON_TRIGGER, &CTrumpLaserInterfaceDll::OnBnClickedButtonTrigger)
	ON_BN_CLICKED(IDC_BUTTON_RAL_ON, &CTrumpLaserInterfaceDll::OnBnClickedButtonRalOn)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTrumpLaserInterfaceDll message handlers

BOOL CTrumpLaserInterfaceDll::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	//SetIcon(m_hIcon, TRUE);			// Set big icon
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	//m_cAKGHWCDummy6Axis.m_CTrumpLaserInterfaceDll = this;

	m_bmpGrey.LoadBitmap(IDB_BITMAP_LEDGRAY);
	m_bmpRed.LoadBitmap(IDB_BITMAP_LEDRED);
	m_bmpYellow.LoadBitmap(IDB_BITMAP_LEDYELLOW);

	setLEDLaserOn(0);
	setLEDLaserEnabled(0);
	setLEDLaserDisabled(0);
	setLEDLaserEmissionGate(0);
	setLEDLaserEmission(0);
	setLEDMonitor(0);
	setLEDCW(0);
	setLEDAlarm(0);
	setLEDSystemFault(0);
	setLEDTaskActive(0);
	setLEDLaserBodyTemp(0);
	setLEDBeamDeliveryTemp(0);
	setLEDPowerSupplyFault(0);
	setLEDFanFault(0);
	setLEDEmergencyStopFault(0);

	fillComboBoxAndControlBox();
	setTooltipForControl();

	readWriteLaserActiveParameterSet(READ_SETTING);

	// Disable "Disconnect" button
	GetDlgItem(IDC_BUTTON_TRUPULSENANO_SETUP_DISCONNECT)->EnableWindow(FALSE);

	// Initialize brushes
	m_brushRed.CreateSolidBrush(RGB(255, 0, 0));   // Red color
	m_brushGreen.CreateSolidBrush(RGB(0, 255, 0)); // Green color

	// Create a larger font
	m_fontLarge.CreatePointFont(160, _T("Arial")); // Font size 16

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrumpLaserInterfaceDll::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrumpLaserInterfaceDll::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTrumpLaserInterfaceDll::CreateDlg(CWnd* pParent, CRect cDlgRect)
{
	// Create the dialog
	Create(IDD_DIALOG_LASER_INTERFACE, pParent);

	// Get parent window size if needed for auto-resizing
	CRect parentRect;
	pParent->GetClientRect(parentRect);

	// Calculate width and height based on the parent (optional)
	int width = cDlgRect.Width();
	int height = cDlgRect.Height();

	// Set the position and size of the dialog
	SetWindowPos(NULL, 0, 0, width, height, SWP_SHOWWINDOW);
}

void CTrumpLaserInterfaceDll::fillComboBoxAndControlBox()
{
	// Add values for Control Mode
	for (int i = 0; i <= 7; ++i)
	{
		CString csValue;
		csValue.Format(_T("%d"), i);
		m_ctrlControlMode.AddString(csValue);
	}
	//m_ctrlControlMode.AddString(_T("Unread"));
	m_ctrlControlMode.SetCurSel(0);

	// Add values for CW/PULSE
	//m_ctrlCWPulse.AddString(_T("CW"));
	m_ctrlCWPulse.AddString(_T("PULSE"));

	// Add values for Waveform
	for (int i = 0; i <= 63; ++i)
	{
		CString csValue;
		csValue.Format(_T("%d"), i);
		m_ctrlWaveform.AddString(csValue);
	}
	m_ctrlCWPulse.SetCurSel(0);
	m_ctrlWaveform.SetCurSel(33);

	// Add Spin Control for PRF
	m_ctrlSpinPRF.SetRange(0, 1000000); // Set range (min, max)
	m_ctrlSpinPRF.SetPos(0); // Set initial position

	CString strValuePRF = _T("");
	strValuePRF.Format(_T("%d"), m_ctrlSpinPRF.GetPos());
	GetDlgItem(IDC_EDIT_ACTIVE)->SetWindowText(strValuePRF);

	// Add Spin Control for Active
	m_ctrlSpinActive.SetRange(0, 1000); // Set range (min, max)
	m_ctrlSpinActive.SetPos(0); // Set initial position

	CString strValueActive = _T("");
	strValueActive.Format(_T("%d"), m_ctrlSpinActive.GetPos());
	GetDlgItem(IDC_EDIT_ACTIVE)->SetWindowText(strValueActive);

	// Add Spin Control for Simmer
	m_ctrlSpinSimmer.SetRange(0, 100); // Set range (min, max)
	m_ctrlSpinSimmer.SetPos(0); // Set initial position

	CString strValueSimmer = _T("");
	strValueSimmer.Format(_T("%d"), m_ctrlSpinSimmer.GetPos());
	GetDlgItem(IDC_EDIT_SIMMER)->SetWindowText(strValueSimmer);

	// Add Spin Control for Duty Factor
	m_ctrlSpinDutyFactor.SetRange(0, 100); // Set range (min, max)
	m_ctrlSpinDutyFactor.SetPos(0); // Set initial position

	CString strValueDutyFactor = _T("");
	strValueDutyFactor.Format(_T("%d"), m_ctrlSpinDutyFactor.GetPos());
	GetDlgItem(IDC_EDIT_DUTY_FACTOR)->SetWindowText(strValueDutyFactor);

	// Add Spin Control for Burst Length
	m_ctrlSpinBurstLength.SetRange(0, 1000000); // Set range (min, max)
	m_ctrlSpinBurstLength.SetPos(0); // Set initial position

	CString strValueBurstLength = _T("");
	strValueBurstLength.Format(_T("%d"), m_ctrlSpinBurstLength.GetPos());
	GetDlgItem(IDC_EDIT_BURST_LENGTH)->SetWindowText(strValueBurstLength);
}

void CTrumpLaserInterfaceDll::setTooltipForControl()
{
	// Initialize the tooltip control
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);

	// Associate the tooltip with the control (e.g., an edit control)
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_PRF), _T("Max = 1000000, Min = 1000"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_ACTIVE), _T("Max = 1000, Min = 0"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_SIMMER), _T("Max = 100, Min = 0"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_DUTY_FACTOR), _T("Max = 100%, Min = 0%"));
	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_BURST_LENGTH), _T("Max = 1000000, Min = 0"));
}

void CTrumpLaserInterfaceDll::OnBnClickedButtonTruPulseNanoSetupConnect()
{
	UpdateData(TRUE);
	connectAsTCPIPClient(m_csLaserIPAddress, m_iPort);
	Sleep(50);

	m_bConnectResponce = setBaudRate(115200);

	if (m_bConnectResponce)
	{
		// Disable "Connect" button
		GetDlgItem(IDC_BUTTON_TRUPULSENANO_SETUP_CONNECT)->EnableWindow(FALSE);
	}

	// Enable "Disconnect" button
	GetDlgItem(IDC_BUTTON_TRUPULSENANO_SETUP_DISCONNECT)->EnableWindow(TRUE);


	if (m_bConnectResponce)
	{
		GetDlgItem(IDC_EDIT_TRUPULSENANO_SETUP_CONNECTION_STATUS)->SetWindowText(_T("Connected"));

		readWriteLaserActiveParameterSet(READ_SETTING);

		// Start a timer to periodically update the data
		m_nTimerID = SetTimer(1, 500, nullptr);  // Timer ID = 1, Interval = 500 ms (0.5 second)

		// Initial data fetch
		UpdateLaserData();

		setLEDLaserEmission(1);

		if (m_bEnableOn)
		{
			OnBnClickedButtonEnable();
		}
		else
		{
			OnBnClickedButtonStandby();
		}

		setGetActiveParameterSet();

	}
	else
	{
		GetDlgItem(IDC_EDIT_TRUPULSENANO_SETUP_CONNECTION_STATUS)->SetWindowText(_T("Connection Fail"));

		// Stop the timer if the connection fails
		if (m_nTimerID != 0)
		{
			KillTimer(m_nTimerID);
			m_nTimerID = 0;
		}
	}

}

void CTrumpLaserInterfaceDll::UpdateLaserData()
{
	if (m_cAKGHWCDummy6Axis.m_bTimerPause == 1)
		return;
	UINT16 ilaserTemperature = 0;
	UINT16 ibeamDeliveryTemperature = 0;
	if (!getLaserTemperatures(ilaserTemperature, ibeamDeliveryTemperature))
		return;
	// Convert Kelvin to Celsius
	double dlaserTemperatureCelsius = (ilaserTemperature / 100.0) - 273.15;
	double dbeamDeliveryTemperatureCelsius = (ibeamDeliveryTemperature / 100.0) - 273.15;
	setReceivedDataFromTheLaserStatus(COMMAND::L_LTV, dlaserTemperatureCelsius);
	setReceivedDataFromTheLaserStatus(COMMAND::L_BTV, dbeamDeliveryTemperatureCelsius);

	if (m_cAKGHWCDummy6Axis.m_bTimerPause == 1)
		return;
	UINT16 ipreAmplifierCurrent = 0;
	UINT16 ipowerAmplifierCurrent = 0;
	if (!getLaserCurrents(ipreAmplifierCurrent, ipowerAmplifierCurrent))
		return;
	// Convert mA to A
	double dpreAmplifierCurrent = (ipreAmplifierCurrent / 1000.0);
	double dpowerAmplifierCurrent = (ipowerAmplifierCurrent / 1000.0);
	setReceivedDataFromTheLaserStatus(COMMAND::L_PACV, dpreAmplifierCurrent);
	setReceivedDataFromTheLaserStatus(COMMAND::L_MACV, dpowerAmplifierCurrent);

	if (m_cAKGHWCDummy6Axis.m_bTimerPause == 1)
		return;
	UINT16 ilogicVoltage = 0;
	UINT16 idiodeVoltage = 0;
	if (!getPowerSupplyVoltages(ilogicVoltage, idiodeVoltage))
		return;
	// Convert mV to V
	double dlogicVoltage = (ilogicVoltage / 1000.0);
	double ddiodeVoltage = (idiodeVoltage / 1000.0);
	setReceivedDataFromTheLaserStatus(COMMAND::L_LPVV, dlogicVoltage);
	setReceivedDataFromTheLaserStatus(COMMAND::L_APVV, ddiodeVoltage);
}

void CTrumpLaserInterfaceDll::connectAsTCPIPClient(CString csIpAdress, int iPortNum)
{
	m_cAKGHWCDummy6Axis.ConnectToServer(csIpAdress, iPortNum, FALSE);
}

void CTrumpLaserInterfaceDll::OnBnClickedButtonTruPulseNanoSetupDisconnect()
{
	readWriteLaserActiveParameterSet(WRITE_SETTING);

	m_bConnectResponce = false;

	// Disable "Disconnect" button
	GetDlgItem(IDC_BUTTON_TRUPULSENANO_SETUP_DISCONNECT)->EnableWindow(FALSE);

	// Enable "Connect" button
	GetDlgItem(IDC_BUTTON_TRUPULSENANO_SETUP_CONNECT)->EnableWindow(TRUE);


	// Stop the periodic timer if it's running
	if (m_nTimerID != 0)
	{
		KillTimer(m_nTimerID);  // Stop the timer
		m_nTimerID = 0;
	}

	// Disconnect the TCP/IP client
	disconnectFromTCPIPClient();

	// Update UI to show disconnection
	GetDlgItem(IDC_EDIT_TRUPULSENANO_SETUP_CONNECTION_STATUS)->SetWindowText(_T("Disconnected"));

	// Optional: Set any LED or state indicators to off
	setLEDLaserOn(0);
	setLEDLaserEnabled(0);
	setLEDLaserEmission(0);
	setLEDMonitor(0);
	setLEDTaskActive(0);

	// Additional cleanup tasks (resetting any UI or internal variables if necessary)
	GetDlgItem(IDC_STATIC_TRUPULSENANO_LASER_LABEL)->SetWindowText(_T(""));

	GetDlgItem(IDC_STATIC_LASER_TEMP_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_BDO_TEMP_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_PRE_AMP_CURR_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_MAIN_AMP_CURR_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_LOGIC_PSU_VOLT_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_STATIC_AMP_PSU_VOLT_VALUE)->SetWindowText(_T(""));

	GetDlgItem(IDC_CONTROL_MODE_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_CW_PULSE_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_WAVEFORM_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_PRF_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_PRF0_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_ACTIVE_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_SIMMER_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_DUTY_FACTOR_VALUE)->SetWindowText(_T(""));
	GetDlgItem(IDC_BURST_LENGTH_VALUE)->SetWindowText(_T(""));

}

void CTrumpLaserInterfaceDll::disconnectFromTCPIPClient()
{
	m_cAKGHWCDummy6Axis.DisconnectFromServer();  // Call the disconnection function in the CAKGHWCDummy6Axis class
}


UINT CTrumpLaserInterfaceDll::getBaudRate()
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	UINT iBr = 0;

	// Prepare command and arguments
	unsigned char command = 0x11; // Command byte for setting RS-232 baud rate
	std::vector<unsigned char> arguments; // Array to hold the baud rate arguments
	arguments.clear();

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			iBr = m_cAKGHWCDummy6Axis.m_cBuff[5] << 24 | /*MSB*/
				m_cAKGHWCDummy6Axis.m_cBuff[6] << 16 |
				m_cAKGHWCDummy6Axis.m_cBuff[7] << 8 |
				m_cAKGHWCDummy6Axis.m_cBuff[8];/*LSB*/
		}
		else
			AfxMessageBox(_T("Checksum Validation Error..(gbr)"));
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period(G)."));
	}
	return iBr;
}

//UINT32 CTrumpLaserInterfaceDll::getBaudRate()
//{
//	// Prepare command
//	unsigned char command = 0x11; // Command byte for getting RS-232 baud rate
//
//	// Create and send the packet
//	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, {});
//	m_cAKGHWCDummy6Axis.DataToSend(packet);
//
//	// Wait for a response with a timeout (e.g., 5 seconds)
//	WaitForData(5000);
//
//	// Check if data was received
//	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
//	{
//		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);
//
//		if (length >= 4) // We expect at least 4 bytes for the baud rate
//		{
//			// Extract the baud rate from the received data
//			UINT32 baudRate = (static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[0]) << 24) |
//				(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[1]) << 16) |
//				(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[2]) << 8) |
//				(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[3]));
//
//			// Validate baud rate
//			static const UINT32 validBaudRates[] = { 9600, 19200, 38400, 57600, 115200 };
//			if (std::find(std::begin(validBaudRates), std::end(validBaudRates), baudRate) != std::end(validBaudRates))
//			{
//				return baudRate;
//			}
//			else
//			{
//				AfxMessageBox(_T("Received an invalid baud rate."));
//				return 0; // Return 0 or any other value to indicate error
//			}
//		}
//		else
//		{
//			AfxMessageBox(_T("Received data length is incorrect."));
//			return 0; // Return 0 or any other value to indicate error
//		}
//	}
//	else
//	{
//		AfxMessageBox(_T("No response received within the timeout period."));
//		return 0; // Return 0 or any other value to indicate error
//	}
//}


bool CTrumpLaserInterfaceDll::setBaudRate(UINT32 baudRate)
{
	// Valid baud rates and their corresponding values
	static const UINT32 validBaudRates[] = { 9600, 19200, 38400, 57600, 115200 };
	bool isValid = std::find(std::begin(validBaudRates), std::end(validBaudRates), baudRate) != std::end(validBaudRates);

	if (!isValid)
	{
		AfxMessageBox(_T("Invalid baud rate."));
		return false;
	}

	// Prepare command and arguments
	unsigned char command = 0x10; // Command byte for setting RS-232 baud rate
	std::vector<unsigned char> arguments(4); // Array to hold the baud rate arguments

	// Convert baudRate to four bytes (MSB, ..., LSB)
	arguments[0] = static_cast<unsigned char>((baudRate >> 24) & 0xFF); // MSB
	arguments[1] = static_cast<unsigned char>((baudRate >> 16) & 0xFF);
	arguments[2] = static_cast<unsigned char>((baudRate >> 8) & 0xFF);
	arguments[3] = static_cast<unsigned char>(baudRate & 0xFF);        // LSB

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			HandleBaudRateResponse(response[0]);
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

void CTrumpLaserInterfaceDll::HandleBaudRateResponse(BYTE response)
{
	switch (response)
	{
	case 0x00:
		//AfxMessageBox(_T("Baud rate set successfully."));
		break;
	case 0x01:
		AfxMessageBox(_T("Invalid baud rate value."));
		break;
	case 0x02:
		AfxMessageBox(_T("Internal error."));
		break;
	default:
		AfxMessageBox(_T("Unknown response received."));
		break;
	}
}

UINT CTrumpLaserInterfaceDll::getLaserInterfaceControlMode()
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	UINT iBr = 0;

	// Prepare command and arguments
	unsigned char command = 0x15; // Command byte for setting RS-232 baud rate
	std::vector<unsigned char> arguments; // Array to hold the baud rate arguments
	arguments.clear();

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			iBr = m_cAKGHWCDummy6Axis.m_cBuff[5];

		}
		else
			AfxMessageBox(_T("Checksum Validation Error..(gLCM)"));
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period(gLCM)."));
	}
	return iBr;
}
bool CTrumpLaserInterfaceDll::setLaserInterfaceControlMode(UINT16 mode)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Validate the mode argument (should be between 0-7)
	if (mode > 7)
	{
		AfxMessageBox(_T("Invalid mode value. It must be between 0 and 7."));
		return false;
	}

	// Construct the command packet
	BYTE command = 0x14;
	BYTE arguments[1] = { mode };

	// Send the command and arguments to the Laser device
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, std::vector<unsigned char>(arguments, arguments + sizeof(arguments)));
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			HandleLaserInterfaceControlModeResponse(response[0]);
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

void CTrumpLaserInterfaceDll::HandleLaserInterfaceControlModeResponse(BYTE response)
{
	switch (response)
	{
	case 0x00:
		//AfxMessageBox(_T("Mode changed successfully."));
		break;
	case 0x01:
		AfxMessageBox(_T("Mode not changed."));
		break;
	case 0x02:
		AfxMessageBox(_T("Internal error."));
		break;
	default:
		AfxMessageBox(_T("Unknown response received."));
		break;
	}

}

UINT CTrumpLaserInterfaceDll::getLaserControlSignals()
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	UINT iBr = 0;

	// Prepare command and arguments
	unsigned char command = 0x1B; // Command byte for setting RS-232 baud rate
	std::vector<unsigned char> arguments; // Array to hold the baud rate arguments
	arguments.clear();

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			iBr = m_cAKGHWCDummy6Axis.m_cBuff[5];

		}
		else
			AfxMessageBox(_T("Checksum Validation Error..(gLCS)"));
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period(gLCS)."));
	}
	return iBr;
}
bool CTrumpLaserInterfaceDll::setLaserControlSignals(UINT16 controlSignals)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Prepare the arguments from the 16-bit control signal
	unsigned char msb = static_cast<unsigned char>(controlSignals >> 8);   // Most Significant Byte (MSB)
	unsigned char lsb = static_cast<unsigned char>(controlSignals & 0xFF); // Least Significant Byte (LSB)

	// Store the arguments in a vector
	std::vector<unsigned char> arguments = { msb, lsb };

	// Command byte for setting Laser control signals
	unsigned char command = 0x1A;

	// Create packet (assuming createPacket prepares the data in the correct format)
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);

	// Send packet to the Laser
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			HandleLaserControlSignalsResponse(response[0]);
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

void CTrumpLaserInterfaceDll::HandleLaserControlSignalsResponse(BYTE response)
{
	switch (response)
	{
	case 0x00:
		//AfxMessageBox(_T("Requested bit settings accepted."));
		break;
	case 0x01:
		AfxMessageBox(_T("Requested bit settings not accepted."));
		break;
	default:
		AfxMessageBox(_T("Unknown response received."));
		break;
	}
}

UINT CTrumpLaserInterfaceDll::getAnalogOrActiveSimmerCurrent(BOOL bIsSetSimmerCurrent)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	UINT iBr = 0;

	// Prepare command and arguments
	unsigned char command = 0x1D; // Command byte for setting RS-232 baud rate
	std::vector<unsigned char> arguments(2); // Array to hold the baud rate arguments
	arguments[0] = 0;
	arguments[1] = bIsSetSimmerCurrent;

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			//0 Level read correctly
			//1 Set point requested does not exist
			if (m_cAKGHWCDummy6Axis.m_cBuff[6] == 0)
			{
				iBr = m_cAKGHWCDummy6Axis.m_cBuff[7] << 8 |
					m_cAKGHWCDummy6Axis.m_cBuff[8];
			}
			else
				AfxMessageBox(_T("Set point requested does not exist"));

		}
		else
			AfxMessageBox(_T("Checksum Validation Error..(gLCS)"));
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period(gLCS)."));
	}
	return iBr;
}
bool CTrumpLaserInterfaceDll::setAnalogSimmerCurrent(UINT16 currentValue)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Ensure the currentValue is within valid range (0 to 100 for simmer, 0 to 1000 for active)
	if (currentValue > 100)
	{
		AfxMessageBox(_T("Invalid current value. It must be between 0 and 100."));
		return false;
	}

	// Convert setPointType to MSB and LSB
	unsigned char msb1 = 0;
	unsigned char lsb1 = 1;

	// Convert currentValue to MSB and LSB
	unsigned char msb2 = static_cast<unsigned char>(currentValue >> 8);
	unsigned char lsb2 = static_cast<unsigned char>(currentValue & 0xFF);

	// Store the arguments in a vector
	std::vector<unsigned char> arguments = { msb1, lsb1, msb2, lsb2 };

	// Command byte for setting the analog current set point
	unsigned char command = 0x1C;

	// Create packet (assuming createPacket prepares the data in the correct format)
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);

	// Send packet to the Laser
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			HandleAnalogCurrentSetPointResponse(response[0]);
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}
bool CTrumpLaserInterfaceDll::setAnalogActiveCurrent(UINT16 currentValue)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Ensure the currentValue is within valid range (0 to 100 for simmer, 0 to 1000 for active)
	if (currentValue > 1000)
	{
		AfxMessageBox(_T("Invalid current value. It must be between 0 and 1000."));
		return false;
	}

	// Convert setPointType to MSB and LSB
	unsigned char msb1 = 0;
	unsigned char lsb1 = 0;

	// Convert currentValue to MSB and LSB
	unsigned char msb2 = static_cast<unsigned char>(currentValue >> 8);
	unsigned char lsb2 = static_cast<unsigned char>(currentValue & 0xFF);

	// Store the arguments in a vector
	std::vector<unsigned char> arguments = { msb1, lsb1, msb2, lsb2 };

	// Command byte for setting the analog current set point
	unsigned char command = 0x1C;

	// Create packet (assuming createPacket prepares the data in the correct format)
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);

	// Send packet to the Laser
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			HandleAnalogCurrentSetPointResponse(response[0]);
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

void CTrumpLaserInterfaceDll::HandleAnalogCurrentSetPointResponse(BYTE response)
{
	switch (response)
	{
	case 0x00:
		//AfxMessageBox(_T("Set point set correctly."));
		break;
	case 0x01:
		AfxMessageBox(_T("Set point requested does not exist."));
		break;
	case 0x02:
		AfxMessageBox(_T("Set point too large."));
		break;
	case 0x03:
		AfxMessageBox(_T("Set point too small."));
		break;
	case 0x04:
		AfxMessageBox(_T("Laser is in an inappropriate interface control mode."));
		break;
	default:
		AfxMessageBox(_T("Unknown response received."));
		break;
	}
}

UINT CTrumpLaserInterfaceDll::getPulseWaveform(UINT& selectedWaveform)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Prepare command
	unsigned char command = 0x21; // Command byte for getting pulse waveform

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, {});
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length >= 6) // We expect 6 bytes for the response
		{

			if (getCheckSumValidation())
			{
				// Extract the selected waveform (2 bytes) and PRF0 (4 bytes) from the received data
				selectedWaveform = static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[6]);

				UINT32 PRF = (static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[7]) << 24) |
					(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[8]) << 16) |
					(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[9]) << 8) |
					(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[10]));

				// Validate PRF
				if (PRF <= 1000000)
				{
					return PRF;
				}
				else
				{
					AfxMessageBox(_T("Received an invalid PRF value."));
					return 0; // Return 0 or any other value to indicate error
				}
			}
			else
			{
				AfxMessageBox(_T("Checksum Validation Error..(gLCS)"));
				return 0;
			}
		}
		else
		{
			AfxMessageBox(_T("Received data length is incorrect."));
			return 0; // Return 0 or any other value to indicate error
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return 0; // Return 0 or any other value to indicate error
	}
}

bool CTrumpLaserInterfaceDll::setPulseWaveform(UINT16 waveformNumber)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Ensure the waveformNumber is within the valid range (0 to 63)
	if (waveformNumber > 63)
	{
		AfxMessageBox(_T("Invalid waveform number. It must be between 0 and 63."));
		return false;
	}

	// Convert waveformNumber to MSB and LSB (although the value is small, it's still processed as Uint16)
	unsigned char msb = static_cast<unsigned char>(waveformNumber >> 8);
	unsigned char lsb = static_cast<unsigned char>(waveformNumber & 0xFF);

	// Store the arguments in a vector
	std::vector<unsigned char> arguments = { msb, lsb };

	// Command byte for setting the pulse waveform
	unsigned char command = 0x20;

	// Create packet (assuming createPacket prepares the data in the correct format)
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);

	// Send packet to the Laser
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			HandlePulseWaveformResponse(response[0]);
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

void CTrumpLaserInterfaceDll::HandlePulseWaveformResponse(BYTE response)
{
	switch (response)
	{
	case 0x00:
		//AfxMessageBox(_T("Pulse waveform selected successfully."));
		break;
	case 0x01:
		AfxMessageBox(_T("Waveform number does not exist."));
		break;
	case 0x02:
		AfxMessageBox(_T("Laser is in an inappropriate interface control mode."));
		break;
	default:
		AfxMessageBox(_T("Unknown response received."));
		break;
	}
}

UINT CTrumpLaserInterfaceDll::getPulseRate()
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	UINT pRet = 0;

	// Prepare command and arguments
	unsigned char command = 0x23; // Command byte for setting RS-232 baud rate
	std::vector<unsigned char> arguments; // Array to hold the baud rate arguments
	arguments.clear();

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			pRet = m_cAKGHWCDummy6Axis.m_cBuff[5] << 24 | /*MSB*/
				m_cAKGHWCDummy6Axis.m_cBuff[6] << 16 |
				m_cAKGHWCDummy6Axis.m_cBuff[7] << 8 |
				m_cAKGHWCDummy6Axis.m_cBuff[8];/*LSB*/
		}
		else
			AfxMessageBox(_T("Checksum Validation Error..(gPR)"));
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period(gPR)."));
	}
	return pRet;
}

bool CTrumpLaserInterfaceDll::setPulseRate(UINT32 pulseRate)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Ensure the pulseRate is within the valid range according to the laser settings
	// Here, we assume that the valid ranges are known and applicable:
	// 1000 – 1000000 for Pulsed mode
	// 0 - 99 for CW mode
	// 100 - 100000 for CW-M Mode

	if ((pulseRate < 1000 || pulseRate > 1000000) &&
		(pulseRate < 0 || pulseRate > 99) &&
		(pulseRate < 100 || pulseRate > 100000))
	{
		AfxMessageBox(_T("Invalid pulse rate value. Please ensure it is within the valid range."));
		return false;
	}

	// Convert pulseRate to 4 bytes (MSB to LSB)
	unsigned char byte1 = static_cast<unsigned char>((pulseRate >> 24) & 0xFF);
	unsigned char byte2 = static_cast<unsigned char>((pulseRate >> 16) & 0xFF);
	unsigned char byte3 = static_cast<unsigned char>((pulseRate >> 8) & 0xFF);
	unsigned char byte4 = static_cast<unsigned char>(pulseRate & 0xFF);

	// Store the arguments in a vector
	std::vector<unsigned char> arguments = { byte1, byte2, byte3, byte4 };

	// Command byte for setting the pulse rate
	unsigned char command = 0x22;

	// Create packet (assuming createPacket prepares the data in the correct format)
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);

	// Send packet to the Laser
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			HandlePulseRateResponse(response[0]);
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

void CTrumpLaserInterfaceDll::HandlePulseRateResponse(BYTE response)
{
	switch (response)
	{
	case 0x00:
		//AfxMessageBox(_T("Pulse rate set correctly."));
		break;
	case 0x01:
		AfxMessageBox(_T("Pulse rate too slow for active mode."));
		break;
	case 0x02:
		AfxMessageBox(_T("Pulse rate too fast for active mode."));
		break;
	case 0x03:
		AfxMessageBox(_T("Laser is in an inappropriate interface control mode."));
		break;
	default:
		AfxMessageBox(_T("Unknown response received."));
		break;
	}
}

UINT CTrumpLaserInterfaceDll::getPulseBurstLength()
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	UINT pRet = 0;

	// Prepare command and arguments
	unsigned char command = 0x25; // Command byte for setting RS-232 baud rate
	std::vector<unsigned char> arguments; // Array to hold the baud rate arguments
	arguments.clear();

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			pRet = m_cAKGHWCDummy6Axis.m_cBuff[5] << 24 | /*MSB*/
				m_cAKGHWCDummy6Axis.m_cBuff[6] << 16 |
				m_cAKGHWCDummy6Axis.m_cBuff[7] << 8 |
				m_cAKGHWCDummy6Axis.m_cBuff[8];/*LSB*/
		}
		else
			AfxMessageBox(_T("Checksum Validation Error..(gPBL)"));
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period(gPBL)."));
	}
	return pRet;
}

bool CTrumpLaserInterfaceDll::setPulseBurstLength(UINT32 burstLength)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Ensure the burstLength is within the valid range (0 to 100000)
	if (burstLength > 100000)
	{
		AfxMessageBox(_T("Invalid pulse burst length. It must be between 0 and 100000."));
		return false;
	}

	// Convert burstLength to 4 bytes (MSB to LSB)
	unsigned char byte1 = static_cast<unsigned char>((burstLength >> 24) & 0xFF);
	unsigned char byte2 = static_cast<unsigned char>((burstLength >> 16) & 0xFF);
	unsigned char byte3 = static_cast<unsigned char>((burstLength >> 8) & 0xFF);
	unsigned char byte4 = static_cast<unsigned char>(burstLength & 0xFF);

	// Store the arguments in a vector
	std::vector<unsigned char> arguments = { byte1, byte2, byte3, byte4 };

	// Command byte for setting the pulse burst length
	unsigned char command = 0x24;

	// Create packet (assuming createPacket prepares the data in the correct format)
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);

	// Send packet to the Laser
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			HandlePulseBurstLengthResponse(response[0]);
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

void CTrumpLaserInterfaceDll::HandlePulseBurstLengthResponse(BYTE response)
{
	switch (response)
	{
	case 0x00:
		//AfxMessageBox(_T("Pulse burst length set correctly."));
		break;
	case 0x01:
		AfxMessageBox(_T("Burst count too big."));
		break;
	default:
		AfxMessageBox(_T("Unknown response received."));
		break;
	}
}

UINT CTrumpLaserInterfaceDll::getPumpDutyFactor()
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	UINT pRet = 0;

	// Prepare command and arguments
	unsigned char command = 0x27; // Command byte for setting RS-232 baud rate
	std::vector<unsigned char> arguments; // Array to hold the baud rate arguments
	arguments.clear();

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			pRet = m_cAKGHWCDummy6Axis.m_cBuff[5] << 8 |
				m_cAKGHWCDummy6Axis.m_cBuff[6];/*LSB*/
		}
		else
			AfxMessageBox(_T("Checksum Validation Error..(gPDF)"));
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period(gPDF)."));
	}
	return pRet;
}

bool CTrumpLaserInterfaceDll::setPumpDutyFactor(UINT16 dutyFactor)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Ensure the dutyFactor is within the valid range (0 to 1000)
	if (dutyFactor > 1000)
	{
		AfxMessageBox(_T("Invalid pump duty factor. It must be between 0 and 1000."));
		return false;
	}

	// Convert dutyFactor to 2 bytes (MSB to LSB)
	unsigned char byte1 = static_cast<unsigned char>((dutyFactor >> 8) & 0xFF); // MSB
	unsigned char byte2 = static_cast<unsigned char>(dutyFactor & 0xFF);       // LSB

	// Store the arguments in a vector
	std::vector<unsigned char> arguments = { byte1, byte2 };

	// Command byte for setting the pump duty factor
	unsigned char command = 0x26;

	// Create packet (assuming createPacket prepares the data in the correct format)
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);

	// Send packet to the Laser
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			HandlePumpDutyFactorResponse(response[0]);
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

void CTrumpLaserInterfaceDll::HandlePumpDutyFactorResponse(BYTE response)
{
	switch (response)
	{
	case 0x00:
		//AfxMessageBox(_T("Duty factor set correctly."));
		break;
	case 0x01:
		AfxMessageBox(_T("Duty factor too big."));
		break;
	case 0x02:
		AfxMessageBox(_T("In inappropriate interface control mode."));
		break;
	default:
		AfxMessageBox(_T("Unknown response received."));
		break;
	}
}

bool CTrumpLaserInterfaceDll::setPulseGeneratorParameters(UINT16 waveform, UINT32 pulseRate, UINT32 burstLength, UINT16 dutyFactor)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Validate arguments
	if (waveform > 63)
	{
		AfxMessageBox(_T("Pulse waveform number too big."));
		return false;
	}
	if (pulseRate > 1000000)
	{
		AfxMessageBox(_T("Pulse specified rate too big."));
		return false;
	}
	if (burstLength > 1000000)
	{
		AfxMessageBox(_T("Pulse burst count too big."));
		return false;
	}
	if (dutyFactor > 1000)
	{
		AfxMessageBox(_T("Duty factor too big."));
		return false;
	}

	// Prepare command and arguments
	unsigned char command = 0x2C; // Command byte for setting pulse generator parameters
	std::vector<unsigned char> arguments(12); // Array to hold the arguments

	// Convert and set arguments in the correct byte order
	arguments[0] = static_cast<unsigned char>((waveform >> 8) & 0xFF); // MSB of waveform
	arguments[1] = static_cast<unsigned char>(waveform & 0xFF);        // LSB of waveform

	arguments[2] = static_cast<unsigned char>((pulseRate >> 24) & 0xFF); // MSB of pulseRate
	arguments[3] = static_cast<unsigned char>((pulseRate >> 16) & 0xFF);
	arguments[4] = static_cast<unsigned char>((pulseRate >> 8) & 0xFF);
	arguments[5] = static_cast<unsigned char>(pulseRate & 0xFF);        // LSB of pulseRate

	arguments[6] = static_cast<unsigned char>((burstLength >> 24) & 0xFF); // MSB of burstLength
	arguments[7] = static_cast<unsigned char>((burstLength >> 16) & 0xFF);
	arguments[8] = static_cast<unsigned char>((burstLength >> 8) & 0xFF);
	arguments[9] = static_cast<unsigned char>(burstLength & 0xFF);        // LSB of burstLength

	arguments[10] = static_cast<unsigned char>((dutyFactor >> 8) & 0xFF); // MSB of dutyFactor
	arguments[11] = static_cast<unsigned char>(dutyFactor & 0xFF);        // LSB of dutyFactor

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			switch (response[0])
			{
			case 0x00:
				AfxMessageBox(_T("Pulse parameters set correctly."));
				break;
			case 0x01:
				AfxMessageBox(_T("Pulse waveform number too big."));
				break;
			case 0x02:
				AfxMessageBox(_T("Pulse specified rate too big."));
				break;
			case 0x03:
				AfxMessageBox(_T("Pulse burst count too big."));
				break;
			case 0x04:
				AfxMessageBox(_T("Duty factor too big."));
				break;
			default:
				AfxMessageBox(_T("Unknown response received."));
				break;
			}
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

bool CTrumpLaserInterfaceDll::restartPulseGenerator(UINT16 waveform)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Validate argument
	if (waveform > 63 && waveform != 32768)
	{
		AfxMessageBox(_T("Pulse waveform number not supported."));
		return false;
	}

	// Prepare command and argument
	unsigned char command = 0x2F; // Command byte for restarting pulse generator
	std::vector<unsigned char> arguments(2); // Array to hold the argument

	// Convert waveform to two bytes (MSB, LSB)
	arguments[0] = static_cast<unsigned char>((waveform >> 8) & 0xFF); // MSB
	arguments[1] = static_cast<unsigned char>(waveform & 0xFF);        // LSB

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			switch (response[0])
			{
			case 0x00:
				//AfxMessageBox(_T("Pulse generator restarted correctly."));
				break;
			case 0x01:
				AfxMessageBox(_T("Pulse waveform number not supported."));
				break;
			case 0x02:
				AfxMessageBox(_T("Laser is in an inappropriate interface control mode."));
				break;
			case 0x03:
				AfxMessageBox(_T("Laser not enabled."));
				break;
			default:
				AfxMessageBox(_T("Unknown response received."));
				break;
			}
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

bool CTrumpLaserInterfaceDll::setLaserDiagnosisState()
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Prepare command
	unsigned char command = 0x60; // Command byte for setting laser into diagnosis state

	// Create and send the packet with no arguments
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, {});
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		BYTE response[1];
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length > 0)
		{
			// Copy received data into the response buffer
			response[0] = m_cAKGHWCDummy6Axis.m_cBuff[5];

			// Handle the response
			switch (response[0])
			{
			case 0x00:
				AfxMessageBox(_T("Default state set correctly."));
				break;
			case 0x01:
				AfxMessageBox(_T("Default state not set."));
				break;
			case 0x02:
				AfxMessageBox(_T("Internal error."));
				break;
			default:
				AfxMessageBox(_T("Unknown response received."));
				break;
			}
		}
		else
		{
			AfxMessageBox(_T("Failed to receive a valid response from the device."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

bool CTrumpLaserInterfaceDll::WaitForData(int timeoutMilliseconds)
{
	auto startTime = std::chrono::high_resolution_clock::now(); // Record the start time
	do
	{
		DoEvent(10);  // Process events for a short duration (e.g., 10 milliseconds)
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		auto currentTime = std::chrono::high_resolution_clock::now(); // Get the current time
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

		// Check if the timeout has been reached
		if (elapsedTime >= timeoutMilliseconds)
		{
			AfxMessageBox(_T("Timeout: No data received within the specified duration."));
			return false;
		}

	} while (m_cAKGHWCDummy6Axis.m_bDataReceived == 0);
}

void CTrumpLaserInterfaceDll::DoEvent(int iDelay)
{
	MSG msg;
	ULONGLONG dwStTime = GetTickCount64();
	ULONGLONG dwEndTime = dwStTime + iDelay;

	while (GetTickCount64() < dwEndTime)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

CString CI2CS(int iVal)
{
	CString csvAL = _T("");
	csvAL.Format(_T("%d"), iVal);
	return csvAL;
}

void CTrumpLaserInterfaceDll::setReceivedDataFromTheAPS(COMMAND iCommandType, UINT iVal)
{
	// Map COMMAND values to their corresponding control IDs
	std::map<COMMAND, int> commandToControlID = {

		// For Active Parameter Set
		{COMMAND::L_CM, IDC_CONTROL_MODE_VALUE},
		{COMMAND::L_CWP, IDC_CW_PULSE_VALUE},
		{COMMAND::L_WAVEFORM, IDC_WAVEFORM_VALUE},
		{COMMAND::L_PRF, IDC_PRF_VALUE},
		{COMMAND::L_PRF0, IDC_PRF0_VALUE},
		{COMMAND::L_ACTIVE, IDC_ACTIVE_VALUE},
		{COMMAND::L_SIMMER, IDC_SIMMER_VALUE},
		{COMMAND::L_DF, IDC_DUTY_FACTOR_VALUE},
		{COMMAND::L_BL, IDC_BURST_LENGTH_VALUE},
	};

	auto it = commandToControlID.find(iCommandType);
	if (it != commandToControlID.end())
	{
		CString csShow = CI2CS(iVal);
		GetDlgItem(it->second)->SetWindowText(csShow);
	}
}

void CTrumpLaserInterfaceDll::setReceivedDataFromTheLaserStatus(COMMAND iCommandType, double dVal)
{
	// Map COMMAND values to their corresponding control IDs
	std::map<COMMAND, int> commandToControlID = {
		// For show Status (Temp, Currents, Voltages)
		{COMMAND::L_LTV, IDC_STATIC_LASER_TEMP_VALUE},
		{COMMAND::L_BTV, IDC_STATIC_BDO_TEMP_VALUE},
		{COMMAND::L_PACV, IDC_STATIC_PRE_AMP_CURR_VALUE},
		{COMMAND::L_MACV, IDC_STATIC_MAIN_AMP_CURR_VALUE},
		{COMMAND::L_LPVV, IDC_STATIC_LOGIC_PSU_VOLT_VALUE},
		{COMMAND::L_APVV, IDC_STATIC_AMP_PSU_VOLT_VALUE},
	};

	auto it = commandToControlID.find(iCommandType);
	if (it != commandToControlID.end())
	{
		CString csShow;
		csShow.Format(_T("%.2f"), dVal);  // Format with 2 decimal points
		GetDlgItem(it->second)->SetWindowText(csShow);
	}
}

BOOL CTrumpLaserInterfaceDll::getCheckSumValidation()
{
	std::vector<unsigned char> vChkckSum;
	size_t iRDLength = static_cast<size_t>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength); // Changed to size_t
	for (size_t i = 0; i < iRDLength - 1; i++)
	{
		vChkckSum.push_back(m_cAKGHWCDummy6Axis.m_cBuff[i]);
	}
	unsigned char cChksum = m_cAKGHWCDummy6Axis.calculateChecksum(vChkckSum);
	if (cChksum == m_cAKGHWCDummy6Axis.m_cBuff[iRDLength - 1])
		return TRUE;
	else
		return FALSE;
}

UINT32 CTrumpLaserInterfaceDll::getLaserSerialNumber()
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Prepare command
	unsigned char command = 0x62; // Command byte for getting the laser serial number

	// Create and send the packet with no arguments
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, {});
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length >= 4) // We expect at least 4 bytes for the serial number
		{
			// Extract the serial number from the received data
			UINT32 serialNumber = (static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[0]) << 24) |
				(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[1]) << 16) |
				(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[2]) << 8) |
				(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[3]));

			// Return the serial number
			return serialNumber;
		}
		else
		{
			AfxMessageBox(_T("Received data length is incorrect."));
			return 0; // Return 0 or any other value to indicate error
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return 0; // Return 0 or any other value to indicate error
	}
}

CString CTrumpLaserInterfaceDll::getLaserPartNumber()
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Prepare command
	unsigned char command = 0x63; // Command byte for getting the laser part number

	// Create and send the packet with no arguments
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, {});
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length >= 23) // Ensure there is at least 23 bytes for the part number
		{
			// Extract the part number from the received data
			CString partNumber;

			for (int i = 0; i < 32; ++i)
			{
				if (i < length)
				{
					char c = static_cast<char>(m_cAKGHWCDummy6Axis.m_cBuff[i]);
					if (c == 0x00)
						break; // Stop if null terminator is encountered
					partNumber += c;
				}
			}

			// Return the extracted part number
			return partNumber;
		}
		else
		{
			AfxMessageBox(_T("Received data length is incorrect."));
			return _T(""); // Return an empty CString to indicate error
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return _T(""); // Return an empty CString to indicate error
	}
}

FirmwareDetails CTrumpLaserInterfaceDll::getLaserFirmwareDetails()
{
	// Prepare command
	unsigned char command = 0x64; // Command byte for getting laser firmware details

	// Create and send the packet with no arguments
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, {});
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Create a FirmwareDetails struct to hold the result
	FirmwareDetails details = {};

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length >= 22) // Ensure there is at least 22 bytes for the firmware details
		{
			// Extract the firmware details from the received data
			details.fpgaHardwareRevMajor = (static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[0]) << 8) | m_cAKGHWCDummy6Axis.m_cBuff[1];
			details.fpgaHardwareRevMinor = (static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[2]) << 8) | m_cAKGHWCDummy6Axis.m_cBuff[3];
			details.fpgaHardwareRelease = (static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[4]) << 8) | m_cAKGHWCDummy6Axis.m_cBuff[5];
			details.fpgaFirmwareRevMajor = (static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[6]) << 8) | m_cAKGHWCDummy6Axis.m_cBuff[7];
			details.fpgaFirmwareRevMinor = (static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[8]) << 8) | m_cAKGHWCDummy6Axis.m_cBuff[9];
			details.fpgaFirmwareRelease = (static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[10]) << 8) | m_cAKGHWCDummy6Axis.m_cBuff[11];
			details.stellarisFirmwareVersion = (static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[12]) << 24) |
				(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[13]) << 16) |
				(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[14]) << 8) |
				m_cAKGHWCDummy6Axis.m_cBuff[15];
			details.driverFirmware = (static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[16]) << 8) | m_cAKGHWCDummy6Axis.m_cBuff[17];

			// Optionally, handle the reserved and additional bytes
			// Reserved bytes are from index 18 to 21
			// Additional characters at the end can be handled as needed

			// Return the extracted firmware details
			return details;
		}
		else
		{
			AfxMessageBox(_T("Received data length is incorrect."));
			return details; // Return default-initialized struct indicating error
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return details; // Return default-initialized struct indicating error
	}
}

LaserDescription CTrumpLaserInterfaceDll::getLaserDescription()
{
	// Prepare command
	unsigned char command = 0x65; // Command byte for getting laser description

	// Create and send the packet with no arguments
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, {});
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	WaitForData(5000);

	// Create a LaserDescription struct to hold the result
	LaserDescription description = {};

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		int length = static_cast<int>(m_cAKGHWCDummy6Axis.m_iReceivedDataLength);

		if (length >= 10) // Ensure there are at least 10 bytes for the description
		{
			// Extract the laser description from the received data
			description.ratedPowerLevel = (static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[0]) << 8) | m_cAKGHWCDummy6Axis.m_cBuff[1];
			description.maxPulseRate = (static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[2]) << 8) | m_cAKGHWCDummy6Axis.m_cBuff[3];
			description.ratedEnergy = (static_cast<UINT16>(m_cAKGHWCDummy6Axis.m_cBuff[4]) << 8) | m_cAKGHWCDummy6Axis.m_cBuff[5];
			description.features = (static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[6]) << 24) |
				(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[7]) << 16) |
				(static_cast<UINT32>(m_cAKGHWCDummy6Axis.m_cBuff[8]) << 8) |
				m_cAKGHWCDummy6Axis.m_cBuff[9];

			// Return the extracted laser description
			return description;
		}
		else
		{
			AfxMessageBox(_T("Received data length is incorrect."));
			return description; // Return default-initialized struct indicating error
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return description; // Return default-initialized struct indicating error
	}
}

bool CTrumpLaserInterfaceDll::getLaserTemperatures(UINT16& laserTemperature, UINT16& beamDeliveryTemperature)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	laserTemperature = 0;
	beamDeliveryTemperature = 0;

	// Prepare command
	unsigned char command = 0x51; // Command byte for querying laser temperatures
	std::vector<unsigned char> arguments; // No arguments required for this command

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			// Extract laser and beam delivery temperatures
			laserTemperature = (m_cAKGHWCDummy6Axis.m_cBuff[5] << 8) | m_cAKGHWCDummy6Axis.m_cBuff[6];
			beamDeliveryTemperature = (m_cAKGHWCDummy6Axis.m_cBuff[7] << 8) | m_cAKGHWCDummy6Axis.m_cBuff[8];
		}
		else
		{
			AfxMessageBox(_T("Checksum Validation Error."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

bool CTrumpLaserInterfaceDll::getLaserCurrents(UINT16& preAmplifierCurrent, UINT16& powerAmplifierCurrent)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	preAmplifierCurrent = 0;
	powerAmplifierCurrent = 0;

	// Prepare command
	unsigned char command = 0x52; // Command byte for querying laser currents
	std::vector<unsigned char> arguments; // No arguments required for this command

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			// Extract pre-amplifier and power amplifier diode currents
			preAmplifierCurrent = (m_cAKGHWCDummy6Axis.m_cBuff[5] << 8) | m_cAKGHWCDummy6Axis.m_cBuff[6];
			powerAmplifierCurrent = (m_cAKGHWCDummy6Axis.m_cBuff[7] << 8) | m_cAKGHWCDummy6Axis.m_cBuff[8];
		}
		else
		{
			AfxMessageBox(_T("Checksum Validation Error."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}
}

bool CTrumpLaserInterfaceDll::getPowerSupplyVoltages(UINT16& logicVoltage, UINT16& diodeVoltage)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	// Initialize the voltages to zero
	logicVoltage = 0;
	diodeVoltage = 0;

	// Command byte for querying power supply voltages
	unsigned char command = 0x53;
	std::vector<unsigned char> arguments; // No arguments to send

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			// Extract the received voltages from the buffer
			logicVoltage = (m_cAKGHWCDummy6Axis.m_cBuff[5] << 8) | m_cAKGHWCDummy6Axis.m_cBuff[6];
			diodeVoltage = (m_cAKGHWCDummy6Axis.m_cBuff[7] << 8) | m_cAKGHWCDummy6Axis.m_cBuff[8];
		}
		else
		{
			AfxMessageBox(_T("Checksum Validation Error..(gvs)"));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period(GVS)."));
		return false;
	}
}

bool CTrumpLaserInterfaceDll::getLaserCurrents(UINT16& preAmplifierCurrent, UINT16& powerAmplifierCurrent1, UINT16& powerAmplifierCurrent2, UINT16& powerAmplifierCurrent3)
{
	if (!m_bConnectResponce)
	{
		return false;
	}

	preAmplifierCurrent = 0;
	powerAmplifierCurrent1 = 0;
	powerAmplifierCurrent2 = 0;
	powerAmplifierCurrent3 = 0;

	// Prepare command
	unsigned char command = 0x57; // Command byte for querying extended laser currents
	std::vector<unsigned char> arguments; // No arguments required for this command

	// Create and send the packet
	std::vector<unsigned char> packet = m_cAKGHWCDummy6Axis.createPacket(command, arguments);
	m_cAKGHWCDummy6Axis.DataToSend(packet);

	// Wait for a response with a timeout (e.g., 5 seconds)
	if (!WaitForData(5000))
		return false;

	// Check if data was received
	if (m_cAKGHWCDummy6Axis.m_bDataReceived)
	{
		if (getCheckSumValidation())
		{
			// Extract currents
			preAmplifierCurrent = (m_cAKGHWCDummy6Axis.m_cBuff[1] << 8) | m_cAKGHWCDummy6Axis.m_cBuff[2];
			powerAmplifierCurrent1 = (m_cAKGHWCDummy6Axis.m_cBuff[3] << 8) | m_cAKGHWCDummy6Axis.m_cBuff[4];
			powerAmplifierCurrent2 = (m_cAKGHWCDummy6Axis.m_cBuff[5] << 8) | m_cAKGHWCDummy6Axis.m_cBuff[6];
			powerAmplifierCurrent3 = (m_cAKGHWCDummy6Axis.m_cBuff[7] << 8) | m_cAKGHWCDummy6Axis.m_cBuff[8];
		}
		else
		{
			AfxMessageBox(_T("Checksum Validation Error."));
			return false;
		}
	}
	else
	{
		AfxMessageBox(_T("No response received within the timeout period."));
		return false;
	}

	return true;
}

BOOL CTrumpLaserInterfaceDll::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST)
	{
		m_ToolTip.RelayEvent(pMsg);
	}

	// Determine which control is focused and trigger corresponding logic
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd* pFocus = GetFocus();

		if (pFocus == GetDlgItem(IDC_EDIT_PRF))
		{
			OnEnKillfocusEditPrf();
			return TRUE;
		}
		else if (pFocus == GetDlgItem(IDC_EDIT_ACTIVE))
		{
			OnEnKillfocusEditActive();
			return TRUE;
		}
		else if (pFocus == GetDlgItem(IDC_EDIT_SIMMER))
		{
			OnEnKillfocusEditSimmer();
			return TRUE;
		}
		else if (pFocus == GetDlgItem(IDC_EDIT_BURST_LENGTH))
		{
			OnEnKillfocusEditBurstLength();
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CTrumpLaserInterfaceDll::OnDeltaposSpinPrf(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int pos = pNMUpDown->iPos;

	// Ensure pos is within range
	pos = max(0, min(pos, 1000000));

	// Update spin control position
	m_ctrlSpinPRF.SetPos(pos);

	// Update control box with the spin control value
	CString strValue;
	strValue.Format(_T("%d"), pos);
	GetDlgItem(IDC_EDIT_PRF)->SetWindowText(strValue);

	*pResult = 0;
}

void CTrumpLaserInterfaceDll::OnDeltaposSpinActive(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int pos = pNMUpDown->iPos;

	// Ensure pos is within range
	pos = max(0, min(pos, 1000));

	// Update spin control position
	m_ctrlSpinActive.SetPos(pos);

	// Update control box with the spin control value
	CString strValue;
	strValue.Format(_T("%d"), pos);
	GetDlgItem(IDC_EDIT_ACTIVE)->SetWindowText(strValue);

	*pResult = 0;
}

void CTrumpLaserInterfaceDll::OnDeltaposSpinSimmer(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int pos = pNMUpDown->iPos;

	// Ensure pos is within range
	pos = max(0, min(pos, 100));

	// Update spin control position
	m_ctrlSpinSimmer.SetPos(pos);

	// Update control box with the spin control value
	CString strValue;
	strValue.Format(_T("%d"), pos);
	GetDlgItem(IDC_EDIT_SIMMER)->SetWindowText(strValue);

	*pResult = 0;
}


void CTrumpLaserInterfaceDll::OnDeltaposSpinDutyFactor(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int pos = pNMUpDown->iPos;

	// Ensure pos is within range
	pos = max(0, min(pos, 100));

	// Update spin control position
	m_ctrlSpinDutyFactor.SetPos(pos);

	// Update control box with the spin control value
	CString strValue;
	strValue.Format(_T("%d"), pos);
	GetDlgItem(IDC_EDIT_DUTY_FACTOR)->SetWindowText(strValue);

	*pResult = 0;
}


void CTrumpLaserInterfaceDll::OnDeltaposSpinBurstLength(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int pos = pNMUpDown->iPos;

	// Ensure pos is within range
	pos = max(0, min(pos, 1000000));

	// Update spin control position
	m_ctrlSpinBurstLength.SetPos(pos);

	// Update control box with the spin control value
	CString strValue;
	strValue.Format(_T("%d"), pos);
	GetDlgItem(IDC_EDIT_BURST_LENGTH)->SetWindowText(strValue);

	*pResult = 0;
}

void CTrumpLaserInterfaceDll::OnCbnSelchangeComboControlMode()
{
	UINT iControlMode = m_ctrlControlMode.GetCurSel();
	if (!setLaserInterfaceControlMode(iControlMode))
		return;

	UINT iBR = getLaserInterfaceControlMode();
	setReceivedDataFromTheAPS(COMMAND::L_CM, iBR);
}

void CTrumpLaserInterfaceDll::OnCbnSelchangeComboCwPulse()
{
	if (!m_bConnectResponce)
	{
		return;
	}

	GetDlgItem(IDC_CW_PULSE_VALUE)->SetWindowText(_T("PULSE"));
}

void CTrumpLaserInterfaceDll::OnCbnSelchangeComboWaveform()
{
	UINT iWaveform = m_ctrlWaveform.GetCurSel();
	if (!setPulseWaveform(iWaveform))
		return;

	UINT iBR = getPulseWaveform(iWaveform);
	setReceivedDataFromTheAPS(COMMAND::L_WAVEFORM, iWaveform);
	setReceivedDataFromTheAPS(COMMAND::L_PRF0, iBR);
}

void CTrumpLaserInterfaceDll::OnEnKillfocusEditPrf()
{
	UpdateData();

	if (!setPulseRate(_ttoi(m_csSetPRF)))
		return;

	UINT iBR = getPulseRate();
	setReceivedDataFromTheAPS(COMMAND::L_PRF, iBR);
}

void CTrumpLaserInterfaceDll::OnEnKillfocusEditActive()
{
	UpdateData();

	if (!setAnalogActiveCurrent(_ttoi(m_csSetActive)))
		return;

	UINT iBR = getAnalogOrActiveSimmerCurrent(0);
	setReceivedDataFromTheAPS(COMMAND::L_ACTIVE, iBR);
}

void CTrumpLaserInterfaceDll::OnEnKillfocusEditSimmer()
{
	UpdateData();

	if (!setAnalogSimmerCurrent(_ttoi(m_csSetSimmer)))
		return;

	UINT iBR = getAnalogOrActiveSimmerCurrent(1);
	setReceivedDataFromTheAPS(COMMAND::L_SIMMER, iBR);
}

void CTrumpLaserInterfaceDll::OnEnKillfocusEditDutyFactor()
{
	UpdateData();

	int dutyFactor = _ttoi(m_csSetDutyFactor) * 10; // Convert percentage to 0-1000 range

	if (!setPumpDutyFactor(dutyFactor))
		return;

	UINT iBR = getPumpDutyFactor();
	setReceivedDataFromTheAPS(COMMAND::L_DF, iBR);
}

void CTrumpLaserInterfaceDll::OnEnKillfocusEditBurstLength()
{
	UpdateData();

	if (!setPulseBurstLength(_ttoi(m_csSetBurstLength)))
		return;

	UINT iBR = getPulseBurstLength();
	setReceivedDataFromTheAPS(COMMAND::L_BL, iBR);
}

void CTrumpLaserInterfaceDll::OnBnClickedButtonStandby()
{
	if (!m_bConnectResponce)
	{
		return;
	}

	m_bEnableOn = false;

	GetDlgItem(IDC_COMBO_CONTROL_MODE)->ShowWindow(SW_SHOW);

	if (!setLaserControlSignals(0))
		return;

	CString buttonText;
	GetDlgItem(IDC_BUTTON_RAL_ON)->GetWindowText(buttonText);

	if (buttonText == _T("RAL OFF"))
	{
		GetDlgItem(IDC_STATIC_TRUPULSENANO_LASER_LABEL)->SetWindowText(_T("STANDBY"));
		setLEDLaserOn(0);
		setLEDLaserEnabled(0);
	}
	else
	{
		GetDlgItem(IDC_STATIC_TRUPULSENANO_LASER_LABEL)->SetWindowText(_T("PILOT IRQ"));
		setLEDLaserEnabled(0);
		setLEDMonitor(1);
	}

	setLEDTaskActive(0);

	// Disable "Trigger" button
	GetDlgItem(IDC_BUTTON_TRIGGER)->EnableWindow(FALSE);
}

void CTrumpLaserInterfaceDll::OnBnClickedButtonEnable()
{
	if (!m_bConnectResponce)
	{
		return;
	}

	m_bEnableOn = true;

	GetDlgItem(IDC_COMBO_CONTROL_MODE)->ShowWindow(SW_HIDE);

	if (!setLaserControlSignals(1))
		return;

	CString buttonText;
	GetDlgItem(IDC_BUTTON_RAL_ON)->GetWindowText(buttonText);

	if (buttonText == _T("RAL OFF"))
	{
		GetDlgItem(IDC_STATIC_TRUPULSENANO_LASER_LABEL)->SetWindowText(_T("SIMMER"));
		setLEDLaserOn(1);
		setLEDLaserEnabled(1);
	}
	else
	{
		GetDlgItem(IDC_STATIC_TRUPULSENANO_LASER_LABEL)->SetWindowText(_T("PILOT IRQ"));
		setLEDLaserEnabled(1);
		setLEDMonitor(1);
	}

	setLEDTaskActive(0);

	// Enable "Trigger" button
	GetDlgItem(IDC_BUTTON_TRIGGER)->EnableWindow(TRUE);
}

void CTrumpLaserInterfaceDll::OnBnClickedButtonTrigger()
{
	if (!m_bConnectResponce)
	{
		return;
	}

	UINT iWaveform = m_ctrlWaveform.GetCurSel();
	if (!restartPulseGenerator(iWaveform))
		return;

	CString buttonText;
	GetDlgItem(IDC_BUTTON_RAL_ON)->GetWindowText(buttonText);

	UINT iLCS = getLaserControlSignals();

	if (buttonText == _T("RAL OFF") && iLCS == 1)
	{
		setLEDTaskActive(1);
	}
	else
	{
		setLEDTaskActive(0);
	}
}

void CTrumpLaserInterfaceDll::OnBnClickedButtonRalOn()
{
	if (!m_bConnectResponce)
	{
		return;
	}

	if (m_bRalOn)
	{
		if (m_bEnableOn)
		{
			if (!setLaserControlSignals(1))
				return;
		}
		else
		{
			if (!setLaserControlSignals(0))
				return;
		}

		// If currently "RAL ON", change to "RAL OFF"
		GetDlgItem(IDC_BUTTON_RAL_ON)->SetWindowText(_T("RAL OFF"));

		UINT iLCS = getLaserControlSignals();
		if (iLCS == 0)
		{
			setLEDLaserOn(0);
			setLEDLaserEnabled(0);
			GetDlgItem(IDC_STATIC_TRUPULSENANO_LASER_LABEL)->SetWindowText(_T("STANDBY"));
		}
		else if (iLCS == 1)
		{
			setLEDLaserOn(1);
			setLEDLaserEnabled(1);
			GetDlgItem(IDC_STATIC_TRUPULSENANO_LASER_LABEL)->SetWindowText(_T("SIMMER"));
		}

		setLEDMonitor(0);
	}
	else
	{
		if (!setLaserControlSignals(2))
			return;

		// If currently "RAL OFF", change to "RAL ON"
		GetDlgItem(IDC_BUTTON_RAL_ON)->SetWindowText(_T("RAL ON"));

		GetDlgItem(IDC_STATIC_TRUPULSENANO_LASER_LABEL)->SetWindowText(_T("PILOT IRQ"));

		setLEDLaserOn(0);
		setLEDMonitor(1);

	}

	setLEDTaskActive(0);

	// Toggle the RAL ON/OFF state
	m_bRalOn = !m_bRalOn;
}


void CTrumpLaserInterfaceDll::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		KillTimer(m_nTimerID);
		m_nTimerID = 0;

		if (m_cAKGHWCDummy6Axis.m_bTimerPause == 0)
			UpdateLaserData();

		// Start a timer to periodically update the data
		m_nTimerID = SetTimer(1, 500, nullptr);  // Timer ID = 1, Interval = 500 ms (0.5 second)
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CTrumpLaserInterfaceDll::OnClose()
{
	readWriteLaserActiveParameterSet(WRITE_SETTING);

	m_bConnectResponce = false;

	if (m_nTimerID != 0)
	{
		KillTimer(m_nTimerID);
		m_nTimerID = 0;
	}

	// Disconnect the TCP/IP client
	disconnectFromTCPIPClient();

	CDialogEx::OnClose();
}

void CTrumpLaserInterfaceDll::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	m_bConnectResponce = false;

	CDialogEx::OnCancel();
}

void CTrumpLaserInterfaceDll::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}

void CTrumpLaserInterfaceDll::setLEDLaserOn(bool val)
{
	setLED(m_ctrlLaserOn, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDLaserEnabled(bool val)
{
	setLED(m_ctrlLaserEnabled, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDLaserDisabled(bool val)
{
	setLED(m_ctrlLaserDisabled, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDLaserEmissionGate(bool val)
{
	setLED(m_ctrlLaserEmissionGate, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDLaserEmission(bool val)
{
	setLED(m_ctrlLaserEmission, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDMonitor(bool val)
{
	setLED(m_ctrlMonitor, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDCW(bool val)
{
	setLED(m_ctrlCW, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDAlarm(bool val)
{
	setLED(m_ctrlAlarm, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDSystemFault(bool val)
{
	setLED(m_ctrlSystemFault, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDTaskActive(bool val)
{
	setLED(m_ctrlTaskActive, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDLaserBodyTemp(bool val)
{
	setLED(m_ctrlLaserBodyTemp, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDBeamDeliveryTemp(bool val)
{
	setLED(m_ctrlBeamDeliveryTemp, val, m_bmpYellow, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDPowerSupplyFault(bool val)
{
	setLED(m_ctrlPowerSupplyFault, val, m_bmpRed, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDFanFault(bool val)
{
	setLED(m_ctrlFanFault, val, m_bmpRed, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLEDEmergencyStopFault(bool val)
{
	setLED(m_ctrlEmergencyStopFault, val, m_bmpRed, m_bmpGrey);
}

void CTrumpLaserInterfaceDll::setLED(CStatic& ctrlLED, bool val, HBITMAP hBitmapOn, HBITMAP hBitmapOff)
{
	HBITMAP hBitmap = val ? hBitmapOn : hBitmapOff;
	ctrlLED.SetBitmap(hBitmap);
}

HBRUSH CTrumpLaserInterfaceDll::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// Check if the control is the static text
	if (nCtlColor == CTLCOLOR_STATIC && pWnd->GetDlgCtrlID() == IDC_STATIC_TRUPULSENANO_LASER_LABEL)
	{
		CString strText;
		pWnd->GetWindowText(strText);

		// Change color and font based on the text value
		if (strText == _T("STANDBY"))
		{
			pDC->SetTextColor(RGB(0, 255, 0)); // Green for STANDBY
		}
		else if (strText == _T("SIMMER") || strText == _T("PILOT IRQ"))
		{
			pDC->SetTextColor(RGB(255, 0, 0)); // Red for SIMMER and PILOT IRQ
		}

		// Use larger font
		pDC->SelectObject(&m_fontLarge);

		// Set background mode to transparent to avoid overlapping text
		pDC->SetBkMode(TRANSPARENT);

		// Use the dialog's background brush instead of NULL_BRUSH
		return (HBRUSH)GetStockObject(WHITE_BRUSH); // Set a background brush for proper repainting
	}

	return hBrush;
}

void CTrumpLaserInterfaceDll::readWriteLaserActiveParameterSet(BOOL bIsReading)
{
	CString sSection = _T("LaserActiveParameterSet");
	m_IniReadWritePrm.setINIFileName(ACTIVEPARAMETERSET_FILE_PATH);

	if (bIsReading)
	{
		m_csLaserIPAddress = m_IniReadWritePrm.ReadString(_T("IPAddress"), sSection, _T("192.168.101.22"));
		m_iPort = m_IniReadWritePrm.ReadInt(_T("Port"), sSection, 58174);
		if (m_bConnectResponce)
		{
			m_csSetControlMode = m_IniReadWritePrm.ReadString(_T("ControlMode"), sSection, _T("0"));
			m_csSetCWPulse = m_IniReadWritePrm.ReadString(_T("CWPulse"), sSection, _T("Pulse"));
			m_csSetWaveform = m_IniReadWritePrm.ReadString(_T("Waveform"), sSection, _T("33"));
			m_csSetPRF = m_IniReadWritePrm.ReadString(_T("PRF"), sSection, _T("60000"));
			//m_csSetPRF0 = m_IniReadWritePrm.ReadString(_T("PRF0"), sSection, 0);
			m_csSetActive = m_IniReadWritePrm.ReadString(_T("Active"), sSection, _T("600"));
			m_csSetSimmer = m_IniReadWritePrm.ReadString(_T("Simmer"), sSection, _T("50"));
			m_csSetBurstLength = m_IniReadWritePrm.ReadString(_T("BurstLength"), sSection, _T("70000"));
			m_bEnableOn = m_IniReadWritePrm.ReadInt(_T("EnableOn"), sSection, 0);
		}
	}
	else
	{
		UpdateData(TRUE);  // Get current data from controls

		// Writing settings to the INI file
		m_IniReadWritePrm.WriteString(_T("IPAddress"), sSection, m_csLaserIPAddress);
		m_IniReadWritePrm.WriteInt(_T("Port"), sSection, m_iPort);
		if (m_bConnectResponce)
		{
			m_IniReadWritePrm.WriteString(_T("ControlMode"), sSection, m_csSetControlMode);
			m_IniReadWritePrm.WriteString(_T("CWPulse"), sSection, m_csSetCWPulse);
			m_IniReadWritePrm.WriteString(_T("Waveform"), sSection, m_csSetWaveform);
			m_IniReadWritePrm.WriteString(_T("PRF"), sSection, m_csSetPRF);
			//m_IniReadWritePrm.WriteString(_T("PRF0"), sSection, m_csSetPRF0);
			m_IniReadWritePrm.WriteString(_T("Active"), sSection, m_csSetActive);
			m_IniReadWritePrm.WriteString(_T("Simmer"), sSection, m_csSetSimmer);
			m_IniReadWritePrm.WriteString(_T("BurstLength"), sSection, m_csSetBurstLength);
			m_IniReadWritePrm.WriteInt(_T("EnableOn"), sSection, m_bEnableOn);
		}
	}
}

void CTrumpLaserInterfaceDll::setGetActiveParameterSet()
{
	setGetLaserInterfaceControlMode(_ttoi(m_csSetControlMode));
	GetDlgItem(IDC_CW_PULSE_VALUE)->SetWindowText(_T("PULSE"));
	setGetPulseWaveform(_ttoi(m_csSetWaveform));
	setGetPulseRate(_ttoi(m_csSetPRF));
	setGetAnalogActiveCurrent(_ttoi(m_csSetActive));
	setGetAnalogSimmerCurrent(_ttoi(m_csSetSimmer));
	setGetPulseBurstLength(_ttoi(m_csSetBurstLength));
}

bool CTrumpLaserInterfaceDll::setGetLaserInterfaceControlMode(UINT16 mode)
{
	if (!setLaserInterfaceControlMode(mode))
		return false;
	m_ctrlControlMode.SetCurSel(_ttoi(m_csSetControlMode));

	UINT iBR = getLaserInterfaceControlMode();
	setReceivedDataFromTheAPS(COMMAND::L_CM, iBR);
}

bool CTrumpLaserInterfaceDll::setGetPulseWaveform(UINT16 waveformNumber)
{
	if (!setPulseWaveform(waveformNumber))
		return false;
	m_ctrlWaveform.SetCurSel(_ttoi(m_csSetWaveform));

	UINT selectedWaveform;
	UINT iBR = getPulseWaveform(selectedWaveform);
	setReceivedDataFromTheAPS(COMMAND::L_WAVEFORM, selectedWaveform);
	setReceivedDataFromTheAPS(COMMAND::L_PRF0, iBR);
}

bool CTrumpLaserInterfaceDll::setGetPulseRate(UINT32 pulseRate)
{
	if (!setPulseRate(pulseRate))
		return false;
	GetDlgItem(IDC_EDIT_PRF)->SetWindowText(m_csSetPRF);

	UINT iBR = getPulseRate();
	setReceivedDataFromTheAPS(COMMAND::L_PRF, iBR);
}

bool CTrumpLaserInterfaceDll::setGetAnalogActiveCurrent(UINT16 currentValue)
{
	if (!setAnalogActiveCurrent(currentValue))
		return false;
	GetDlgItem(IDC_EDIT_ACTIVE)->SetWindowText(m_csSetActive);

	UINT iBR = getAnalogOrActiveSimmerCurrent(0);
	setReceivedDataFromTheAPS(COMMAND::L_ACTIVE, iBR);
}

bool CTrumpLaserInterfaceDll::setGetAnalogSimmerCurrent(UINT16 currentValue)
{
	if (!setAnalogSimmerCurrent(currentValue))
		return false;
	GetDlgItem(IDC_EDIT_SIMMER)->SetWindowText(m_csSetSimmer);

	UINT iBR = getAnalogOrActiveSimmerCurrent(1);
	setReceivedDataFromTheAPS(COMMAND::L_SIMMER, iBR);
}

bool CTrumpLaserInterfaceDll::setGetPumpDutyFactor(UINT16 dutyFactor)
{
	if (!setPumpDutyFactor(dutyFactor * 10))
		return false;
	GetDlgItem(IDC_EDIT_DUTY_FACTOR)->SetWindowText(m_csSetDutyFactor);

	UINT iBR = getPumpDutyFactor();
	setReceivedDataFromTheAPS(COMMAND::L_DF, iBR);
}

bool CTrumpLaserInterfaceDll::setGetPulseBurstLength(UINT32 burstLength)
{
	if (!setPulseBurstLength(burstLength))
		return false;
	GetDlgItem(IDC_EDIT_BURST_LENGTH)->SetWindowText(m_csSetBurstLength);

	UINT iBR = getPulseBurstLength();
	setReceivedDataFromTheAPS(COMMAND::L_BL, iBR);
}

void CTrumpLaserInterfaceDll::setStandby()
{
	OnBnClickedButtonStandby();
}

void CTrumpLaserInterfaceDll::setEnable()
{
	OnBnClickedButtonEnable();
}

void CTrumpLaserInterfaceDll::setTrigger()
{
	OnBnClickedButtonTrigger();
}

void CTrumpLaserInterfaceDll::setRalOn()
{
	OnBnClickedButtonRalOn();
}