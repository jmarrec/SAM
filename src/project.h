#ifndef __project_h
#define __project_h

#include <vector>


#include <lk_env.h>
#include "object.h"


class Case : public Object
{
public:
	Case();
	virtual ~Case();

	wxString GetName() { return m_name; }
	void SetName( const wxString &s ) { m_name = s; }
	
	virtual Object *Duplicate();
	virtual bool Copy( Object *obj );
	virtual wxString GetTypeName();
	virtual void Write( wxOutputStream & );
	virtual bool Read( wxInputStream & );

	lk::env_t &Variables() { return m_vars; }

private:
	wxString m_name;
	lk::env_t m_vars;
};

class ProjectFile
{
	typedef unordered_map<wxString, wxString, wxStringHash, wxStringEqual> pfStringHash;

public:
	ProjectFile();
	virtual ~ProjectFile();

	void Clear();

	// managing cases
	void AddCase( const wxString &name, Case *c );
	bool DeleteCase( const wxString &name );
	wxArrayString GetCases();
	Case *GetCase( const wxString &name );

	// simple project file properties
	wxString GetProperty( const wxString &name );
	void SetProperty( const wxString &name, const wxString &value );
	wxArrayString GetProperties();

	// general purpose data storage objects
	void AddObject( const wxString &name, Object * );
	void DeleteObject( const wxString &name );
	Object *GetObject( const wxString &name );
	wxArrayString GetObjects();

	void Write( wxOutputStream &out );
	bool Read( wxInputStream &in );

	wxString LastError() { return m_lastError; }

private:
	ObjectCollection m_cases;
	ObjectCollection m_objects;
	pfStringHash m_properties;
	wxString m_lastError;
};


#endif

