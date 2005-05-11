// OpenSGDemoDoc.h : interface of the COpenSGDemoDoc class
//


#pragma once

class COpenSGDemoDoc : public CDocument
{
protected: // create from serialization only
	COpenSGDemoDoc();
	DECLARE_DYNCREATE(COpenSGDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~COpenSGDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


