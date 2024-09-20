// IniFile.h: interface for the CIniReader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__99976B4B_DBA1_4D1E_AA14_CBEB63042FD1__INCLUDED_)
#define AFX_INIFILE_H__99976B4B_DBA1_4D1E_AA14_CBEB63042FD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniReader
{
public:

    // Constructors and Destructor
    CIniReader();
    CIniReader(const CString& fileName);
    ~CIniReader();

    // Reading and writing string values
    CString ReadString(const CString& key, const CString& section, const CString& defaultValue);
    BOOL WriteString(const CString& key, const CString& section, const CString& value);

    // Reading and writing integer values
    int ReadInt(const CString& key, const CString& section, int defaultValue);
    BOOL WriteInt(const CString& key, const CString& section, int value);

    // Reading and writing float values
    float ReadFloat(const CString& key, const CString& section, float defaultValue);
    BOOL WriteFloat(const CString& key, const CString& section, float value);

    // Set the INI file name
    void setINIFileName(const CString& iniFileName);

    // Methods to return lists of section names and section data
    CStringList* getSectionNames();
    CStringList* getSectionData(const CString& section);

    // Check if the section exists in the file
    BOOL sectionExists(const CString& section);

    // Add or update key-value pair
    long setKey(const CString& value, const CString& key, const CString& section);

    // Retrieve key value for the specified key of a section
    CString getKeyValue(const CString& key, const CString& section);

    // Member variables to store section and section data
    CStringList* m_sectionList;
    CStringList* m_sectionDataList;

    // INI file name
    CString m_strFileName;

    // For return values from API calls
    long m_lRetValue;
};

#endif // !defined(AFX_INIFILE_H__99976B4B_DBA1_4D1E_AA14_CBEB63042FD1__INCLUDED_)
