/* huge parts copied from the AMIRE project... */

#include <afx.h>
#include <string.h>

#include <vector>

#include <dshow.h>
#include <atlbase.h>
#include <qedit.h>

#include <dshow.h>
#include <iostream>
#include <tchar.h>
#include <atlstr.h>
#include <Dvdmedia.h>

#include "InitGUID.h"

#include "DirectShowFrameGrabber.h"
#include "SelectCameraDialog.h"



DirectShowFrameGrabber::DirectShowFrameGrabber(){
	init();
}

void displayProperties( IBaseFilter *pFilter ){
	ISpecifyPropertyPages *pProp;
	
	HRESULT hr = pFilter->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pProp);
	
	if (SUCCEEDED(hr)) 
	{
		// Get the filter's name and IUnknown pointer.
		FILTER_INFO FilterInfo;
		hr = pFilter->QueryFilterInfo(&FilterInfo); 
		IUnknown *pFilterUnk;
		pFilter->QueryInterface(IID_IUnknown, (void **)&pFilterUnk);

		// Show the page. 
		CAUUID caGUID;
		pProp->GetPages(&caGUID);
		pProp->Release();
		OleCreatePropertyFrame(
        0,                   // Parent window
        0, 0,                   // Reserved
        FilterInfo.achName,     // Caption for the dialog box
        1,                      // Number of objects (just the filter)
        &pFilterUnk,            // Array of object pointers. 
        caGUID.cElems,          // Number of property pages
        caGUID.pElems,          // Array of property page CLSIDs
        0,                      // Locale identifier
        0, NULL                 // Reserved
    );

    // Clean up.
    pFilterUnk->Release();
    FilterInfo.pGraph->Release(); 
    CoTaskMemFree(caGUID.pElems);
}

}
    
static void CleanupDirectX() {
	CoUninitialize();
}

static int selectCamera(const std::vector<std::string> &cameras) {
	if (cameras.size() < 1) {
        return -1;
      } else if (cameras.size() == 1) {
        return 0;
      } else {
        SelectCameraDialog dialog(cameras);
        if (dialog.DoModal() == IDOK) {
          return dialog.getSelection();
        }
        return -2;
      }
}

void DirectShowFrameGrabber::InitializeDirectX() {
	static initialized = false;
    if (!initialized) {
      initialized = true;
      CoInitialize(NULL);
	  atexit(CleanupDirectX);
	}
 }

int DirectShowFrameGrabber::SelectDirectXFilter(std::vector<std::wstring> &monikerNames) {
      std::vector<std::string> cameras;
      int size = int(monikerNames.size());
      for (int i = 0; i < size; ++i) {
        std::string camera;
        std::wstring &monikerName = monikerNames[i];
        int length = int(monikerName.size());
        camera.resize(length);
        for (int j = 0; j < length; ++j) {
          camera[j] = char(monikerName[j]);
        }
        cameras.push_back(camera);
      }
      int result = selectCamera(cameras);
      if (result == -2) {
        exit(0);
      } else if (result == -1) {
        printf("no camera detected!\n");
      }
      return result;
}

HRESULT DirectShowFrameGrabber::GetDirectXFilterNames(std::vector<std::wstring> &monikerNames, REFCLSID clsId) {
      ULONG fetched;
      HRESULT hr = S_OK;
      CComPtr<IMoniker> moniker = NULL;
      CComPtr<ICreateDevEnum> captureDevices = NULL;
      CComPtr<IEnumMoniker> monikers = NULL;
      monikerNames.clear();
      captureDevices.CoCreateInstance(CLSID_SystemDeviceEnum);
      captureDevices->CreateClassEnumerator(clsId, &monikers, 0);
      if (monikers != NULL) {
        while ((hr = monikers->Next(1, &moniker, &fetched)) == S_OK) {
          CComPtr<IPropertyBag> propertyBag = NULL;
          moniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&propertyBag);
          VARIANT friendlyName;
          VariantInit(&friendlyName);
          hr = propertyBag->Read(L"FriendlyName", &friendlyName, 0); 
          if (SUCCEEDED(hr)) {
            monikerNames.push_back(friendlyName.bstrVal);
          }
          VariantClear(&friendlyName);
          moniker = NULL;
        }
      }
      return hr;
}

HRESULT DirectShowFrameGrabber::GetDirectXFilter(CComPtr<IBaseFilter> &filter, REFCLSID clsId, const std::wstring &deviceName) {
      ULONG fetched;
      bool exit = false;
      HRESULT hr = S_OK;
      CComPtr<ICreateDevEnum> devices = NULL;
      CComPtr<IEnumMoniker> monikers = NULL;
      CComPtr<IMoniker> moniker = NULL;
      devices.CoCreateInstance(CLSID_SystemDeviceEnum);
      devices->CreateClassEnumerator(clsId, &monikers, 0);
      while ((!exit) && ((hr = monikers->Next(1, &moniker, &fetched)) == S_OK)) {
        CComPtr<IPropertyBag> propertyBag = NULL;
        moniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&propertyBag);
        VARIANT friendlyName;
        VariantInit(&friendlyName);
        hr = propertyBag->Read(L"FriendlyName", &friendlyName, 0); 
        if (SUCCEEDED(hr) && (deviceName.compare(friendlyName.bstrVal) == 0)) {
          hr = moniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&filter);
          exit = true;
        }
        VariantClear(&friendlyName);
        moniker = NULL;
      }
      return hr;
}

 HRESULT DirectShowFrameGrabber::ChooseDirectXFilter(CComPtr<IBaseFilter> &filter, REFCLSID clsId) {
      std::vector<std::wstring> deviceNames;
      GetDirectXFilterNames(deviceNames, clsId);
      int selected = SelectDirectXFilter(deviceNames);
      HRESULT hr = S_OK;
      if (selected >= 0) {
        hr = GetDirectXFilter(filter, clsId, deviceNames[selected]);
      } else {
        filter = NULL;
      }
      return hr;
}


void DirectShowFrameGrabber::init() {
	InitializeDirectX();
	HRESULT hr = S_OK;
	mediaEvent = NULL;
	mediaControl = NULL;
	sampleGrabber = NULL;
	buffer = NULL;
	bufferLength = 0;
	width = 640; // just default, will be overriden
	height = 480;  // just default, will be overriden

	CComPtr<IBaseFilter> captureFilter = NULL;

	// choose video capture device
	hr = ChooseDirectXFilter(captureFilter, CLSID_VideoInputDeviceCategory);

	ASSERT(SUCCEEDED(hr));
	//ASSERT(captureFilter != NULL, "no capturing device available!");
	CComPtr<IBaseFilter> sampleGrabberFilter = NULL;
	hr = sampleGrabberFilter.CoCreateInstance(CLSID_SampleGrabber);
	ASSERT(SUCCEEDED(hr));
	CComPtr<IBaseFilter> nullRendererFilter = NULL;
	hr = nullRendererFilter.CoCreateInstance(CLSID_NullRenderer);
	ASSERT(SUCCEEDED(hr));
	graphBuilder = NULL;
	hr = graphBuilder.CoCreateInstance(CLSID_FilterGraph);


	ASSERT(SUCCEEDED(hr));
	IMediaFilter *mediaFilter = 0;
	graphBuilder->QueryInterface(IID_IMediaFilter, (void**)&mediaFilter);
	mediaFilter->SetSyncSource(NULL);	  
	mediaFilter->Release();
	

	hr = graphBuilder->AddFilter(captureFilter, NULL);	  
	ASSERT(SUCCEEDED(hr));

	// open ui with video capture device properties
	displayProperties( captureFilter );

	hr = graphBuilder->AddFilter(nullRendererFilter, L"NullRenderer");
	ASSERT(SUCCEEDED(hr));
	hr = graphBuilder->AddFilter(sampleGrabberFilter, L"Grabber");
	ASSERT(SUCCEEDED(hr));


	hr = sampleGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&sampleGrabber);
	ASSERT(SUCCEEDED(hr));

	AM_MEDIA_TYPE mediaType;
	ZeroMemory(&mediaType, sizeof(AM_MEDIA_TYPE));
	mediaType.majortype = MEDIATYPE_Video;
	mediaType.subtype = MEDIASUBTYPE_RGB24;
	mediaType.formattype = FORMAT_VideoInfo; 
	hr = sampleGrabber->SetMediaType(&mediaType);
	ASSERT(SUCCEEDED(hr));

	CComPtr<IEnumPins> pins = NULL;
	CComPtr<IPin> cameraOutputPin = NULL;

	{
		hr = captureFilter->EnumPins(&pins);
		ASSERT(SUCCEEDED(hr));
		hr = pins->Reset();
		ASSERT(SUCCEEDED(hr));
		
		hr = pins->Next(1, &cameraOutputPin, NULL); 
		ASSERT(SUCCEEDED(hr));
		pins = NULL; 
	}


	hr = sampleGrabberFilter->EnumPins(&pins);
	ASSERT(SUCCEEDED(hr));
	hr = pins->Reset();
	ASSERT(SUCCEEDED(hr));
	CComPtr<IPin> grabberInputPin = NULL;
	hr = pins->Next(1, &grabberInputPin, NULL);
	ASSERT(SUCCEEDED(hr));
	CComPtr<IPin> grabberOutputPin = NULL;
	hr = pins->Next(1, &grabberOutputPin, NULL);
	ASSERT(SUCCEEDED(hr));
	pins = NULL;
	hr = nullRendererFilter->EnumPins(&pins);
	ASSERT(SUCCEEDED(hr));
	hr = pins->Reset();
	ASSERT(SUCCEEDED(hr));
	CComPtr<IPin> nullRendererInputPin = NULL;
	hr = pins->Next(1, &nullRendererInputPin, NULL);
	ASSERT(SUCCEEDED(hr));

	// show camera properties
		CComPtr<ISpecifyPropertyPages> propertyPages;
		hr = cameraOutputPin->QueryInterface(IID_ISpecifyPropertyPages, (void**)&propertyPages);
		if (SUCCEEDED(hr)) {
			PIN_INFO pinInfo;
			cameraOutputPin->QueryPinInfo(&pinInfo);
			CAUUID caGUID;
			propertyPages->GetPages(&caGUID);
			OleCreatePropertyFrame(NULL, 0, 0, L"Property Sheet", 1,
				(IUnknown **)&(cameraOutputPin.p), caGUID.cElems,
				caGUID.pElems, 0, 0, NULL);
			CoTaskMemFree(caGUID.pElems);
			pinInfo.pFilter->Release();
		}


	hr = graphBuilder->Connect(cameraOutputPin, grabberInputPin);
	ASSERT(SUCCEEDED(hr));
	hr = graphBuilder->Connect(grabberOutputPin, nullRendererInputPin);
	ASSERT(SUCCEEDED(hr));

	hr = graphBuilder->Render(grabberOutputPin);
	//      ASSERT(SUCCEEDED(hr)); // produces an error: "An invalid field name was used in a query string"

	hr = sampleGrabber->SetBufferSamples(TRUE);
	ASSERT(SUCCEEDED(hr));
	hr = sampleGrabber->SetOneShot(FALSE);
	ASSERT(SUCCEEDED(hr));
	hr = graphBuilder->QueryInterface(IID_IMediaControl, (void**)&mediaControl);
	ASSERT(SUCCEEDED(hr));
	hr = graphBuilder->QueryInterface(IID_IMediaEvent, (void**)&mediaEvent);
	ASSERT(SUCCEEDED(hr));
	AM_MEDIA_TYPE mt;
	hr = sampleGrabber->GetConnectedMediaType(&mt);
	ASSERT(SUCCEEDED(hr));
	ASSERT(mt.formattype == FORMAT_VideoInfo);
	VIDEOINFOHEADER *videoHeader;
	videoHeader = reinterpret_cast<VIDEOINFOHEADER*>(mt.pbFormat);
	width = videoHeader->bmiHeader.biWidth;
	height = videoHeader->bmiHeader.biHeight;
	bitmapFormat = 0;
	CComPtr<IAMVideoControl> videoControl;
	hr = captureFilter->QueryInterface(IID_IAMVideoControl, (void**)&videoControl);
	
	// run the graph!
	mediaControl->Run();
}

DirectShowFrameGrabber::~DirectShowFrameGrabber() {
	mediaControl->Stop();
}

void DirectShowFrameGrabber::grabFrame() {
  long oldBufferLength = bufferLength;
      HRESULT hr = S_OK;
      long eventCode = 0;
      mediaEvent->WaitForCompletion(0, &eventCode);
      hr = sampleGrabber->GetCurrentBuffer(&bufferLength, NULL);
      if (bufferLength) {
        if (buffer) {
          if (oldBufferLength != bufferLength) {
            delete[] buffer;
            buffer = new unsigned char[bufferLength];
          }
        } else {
          buffer = new unsigned char[bufferLength];
        }
        ASSERT(buffer);
        hr = sampleGrabber->GetCurrentBuffer(&bufferLength, reinterpret_cast<long*>(buffer));
      } else {
        bufferLength = oldBufferLength;
      }
}

unsigned char *DirectShowFrameGrabber::getFrame() const {
	return buffer;
}

long DirectShowFrameGrabber::getFrameBufferLength() const {
	return bufferLength;
}


int DirectShowFrameGrabber::getWidth() const {
	return width;
}

int DirectShowFrameGrabber::getHeight() const {
	return height;
}

bool DirectShowFrameGrabber::isTopDown(void) const
{
    return false;    
}

