#include "pch.h"
#include "INI.h"
#include <afxcoll.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniReader::CIniReader()
{
    m_sectionList = new CStringList();
    m_sectionDataList = new CStringList();
}

CIniReader::CIniReader(const CString& fileName)
{
    m_strFileName = fileName;
    m_sectionList = new CStringList();
    m_sectionDataList = new CStringList();
}

CIniReader::~CIniReader()
{
    delete m_sectionList;
    delete m_sectionDataList;
}

// Retrieve a value given the section and key
CString CIniReader::getKeyValue(const CString& key, const CString& section)
{
    TCHAR result[255] = { 0 };

    // Get the info from the .ini file
    m_lRetValue = GetPrivateProfileString(section, key, _T(""), result, sizeof(result) / sizeof(TCHAR), m_strFileName);

    return CString(result);
}

// Add or set a key-value pair to a section
long CIniReader::setKey(const CString& value, const CString& key, const CString& section)
{
    return WritePrivateProfileString(section, key, value, m_strFileName);
}

// Check if a given section exists
BOOL CIniReader::sectionExists(const CString& section)
{
    TCHAR result[100] = { 0 };

    // Get the section info from the .ini file
    m_lRetValue = GetPrivateProfileString(section, NULL, _T(""), result, sizeof(result) / sizeof(TCHAR), m_strFileName);

    // Return if any info was retrieved from the section
    return (m_lRetValue > 0);
}

// Retrieve all the section names in the ini file
CStringList* CIniReader::getSectionNames()
{
    TCHAR result[2000] = { 0 };
    m_sectionList->RemoveAll();

    m_lRetValue = GetPrivateProfileSectionNames(result, sizeof(result) / sizeof(TCHAR), m_strFileName);

    CString sectionName;
    for (int i = 0; i < m_lRetValue; ++i)
    {
        if (result[i] != _T('\0')) {
            sectionName += result[i];
        }
        else {
            if (!sectionName.IsEmpty()) {
                m_sectionList->AddTail(sectionName);
            }
            sectionName.Empty();
        }
    }

    return m_sectionList;
}

// Retrieve all key/value pairs of a given section
CStringList* CIniReader::getSectionData(const CString& section)
{
    TCHAR result[2000] = { 0 };  // Adjust size depending on needs
    m_sectionDataList->RemoveAll();

    m_lRetValue = GetPrivateProfileSection(section, result, sizeof(result) / sizeof(TCHAR), m_strFileName);

    CString sectionData;
    for (int i = 0; i < m_lRetValue; ++i)
    {
        if (result[i] != _T('\0')) {
            sectionData += result[i];
        }
        else {
            if (!sectionData.IsEmpty()) {
                m_sectionDataList->AddTail(sectionData);
            }
            sectionData.Empty();
        }
    }

    return m_sectionDataList;
}

// Set the ini file name
void CIniReader::setINIFileName(const CString& iniFileName)
{
    m_strFileName = iniFileName;
}

// Read a string value from the ini file
CString CIniReader::ReadString(const CString& key, const CString& section, const CString& defaultValue)
{
    CString value = getKeyValue(key, section);
    return value.IsEmpty() ? defaultValue : value;
}

// Write a string value to the ini file
BOOL CIniReader::WriteString(const CString& key, const CString& section, const CString& value)
{
    return setKey(value, key, section);
}

// Read a float value from the ini file
float CIniReader::ReadFloat(const CString& key, const CString& section, float defaultValue)
{
    CString value = getKeyValue(key, section);

    if (!value.IsEmpty()) {
        defaultValue = static_cast<float>(_tstof(value));
    }

    return defaultValue;
}

// Write a float value to the ini file
BOOL CIniReader::WriteFloat(const CString& key, const CString& section, float value)
{
    CString strValue;
    strValue.Format(_T("%f"), value);
    return setKey(strValue, key, section);
}

// Read an integer value from the ini file
int CIniReader::ReadInt(const CString& key, const CString& section, int defaultValue)
{
    CString value = getKeyValue(key, section);

    if (!value.IsEmpty()) {
        defaultValue = _ttoi(value);
    }

    return defaultValue;
}

// Write an integer value to the ini file
BOOL CIniReader::WriteInt(const CString& key, const CString& section, int value)
{
    CString strValue;
    strValue.Format(_T("%d"), value);
    return setKey(strValue, key, section);
}
