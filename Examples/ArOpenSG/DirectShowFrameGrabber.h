
#ifndef _DIRECT_SHOW_FRAME_GRABBER_H
#define _DIRECT_SHOW_FRAME_GRABBER_H


#include <afx.h>
#include <dshow.h>
#include <atlbase.h>
#include <qedit.h>

#include <dshow.h>
#include <tchar.h>
#include <atlstr.h>
#include <Dvdmedia.h>

#include <afx.h>
#include <afxwin.h>
#include <afxmt.h>

class DirectShowFrameGrabber
{
	private:
		CComPtr<IMediaEvent> mediaEvent;
		CComPtr<IMediaControl> mediaControl;
		CComPtr<ISampleGrabber> sampleGrabber;
		unsigned char *buffer;

		long bufferLength;
		int bitmapFormat;
		int width;
		int height;
		bool horizontalFlipped;
		bool verticalFlipped;
		CComPtr<IGraphBuilder>	graphBuilder;
		
		void InitializeDirectX();

		int SelectDirectXFilter(std::vector<std::wstring> &monikerNames);
		HRESULT GetDirectXFilterNames(std::vector<std::wstring> &monikerNames, REFCLSID clsId);
		HRESULT GetDirectXFilter(CComPtr<IBaseFilter> &filter, REFCLSID clsId, const std::wstring &deviceName);
		HRESULT ChooseDirectXFilter(CComPtr<IBaseFilter> &filter, REFCLSID clsId);


	public:
		DirectShowFrameGrabber();

		~DirectShowFrameGrabber();
		void grabFrame();
		unsigned char *getFrame() const;
		long getFrameBufferLength() const;
		int getWidth() const;
		int getHeight() const;
        bool isTopDown(void) const;
		
		void init();
};
 
#endif
