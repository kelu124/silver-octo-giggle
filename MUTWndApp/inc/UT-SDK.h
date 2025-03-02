
#pragma once
#include <windows.h>

extern"C" bool   __declspec(dllexport) ConfigDevice(LPCTSTR lpFileName);
extern"C" bool   __declspec(dllexport) initParam();
extern"C" bool   __declspec(dllexport) initSystem();
extern"C" bool   __declspec(dllexport) setSolution(int index);
extern"C" bool   __declspec(dllexport) setFreq(int index);
extern"C" double __declspec(dllexport) getFreq();
extern"C" int    __declspec(dllexport) getFreqIndex();
extern"C" bool   __declspec(dllexport) setDepth(int index);
extern"C" int    __declspec(dllexport) getDepth();
extern"C" int    __declspec(dllexport) getDepthIndex();
extern"C" bool   __declspec(dllexport) setGain(int iGain);
extern"C" int    __declspec(dllexport) getGain();
extern"C" PWORD  __declspec(dllexport) getImageData( int &iRows, int &iColumns , DWORD &dwFrameNum);
extern"C" bool   __declspec(dllexport) setRun(bool bRun);
extern"C" bool   __declspec(dllexport) isRun();
extern"C" void   __declspec(dllexport) Process(unsigned char *pDataDst, int nDstWidth, int nDstHeight, unsigned short *pSrcData, int nSrcWidth, int nSrcHeight);
extern"C" double __declspec(dllexport) getPixelPerMM();
extern"C" bool   __declspec(dllexport) getHardwareExist();
extern"C" double __declspec(dllexport) getTranSpaceInMM();
extern"C" double __declspec(dllexport) getVertSpaceInMM();
extern"C" bool   __declspec(dllexport) setFrameCorr(int index, bool bok);
extern"C" int    __declspec(dllexport) getFrameCorr();
extern"C" bool   __declspec(dllexport) setBright(int iBright, bool bok);
extern"C" int    __declspec(dllexport) getBright();
extern"C" bool   __declspec(dllexport) setSharp(int iSharp, bool bok);
extern"C" int    __declspec(dllexport) getSharp();
extern"C" bool   __declspec(dllexport) setGamma(int iGamma, bool bok);
extern"C" int    __declspec(dllexport) getGamma();
extern"C" bool   __declspec(dllexport) setEdgeFilter(int iFilter, bool bok);
extern"C" int    __declspec(dllexport) getEdgeFilter();
extern"C" bool   __declspec(dllexport) setLineCorr(int iLineCorr, bool bok);
extern"C" int    __declspec(dllexport) getLineCorr();
extern"C" bool   __declspec(dllexport) setColFilter(bool bFilter, bool bok);
extern"C" bool   __declspec(dllexport) getColFilter();
extern"C" bool   __declspec(dllexport) setRowFilter(bool bFilter, bool bok);
extern"C" bool   __declspec(dllexport) getRowFilter();
extern"C" bool   __declspec(dllexport) setSmoothFilter(bool bFilter, bool bok);
extern"C" bool   __declspec(dllexport) getSmoothFilter();