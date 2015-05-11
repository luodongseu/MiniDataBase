#pragma once

#ifndef __MyTimer_H__
#define __MyTimer_H__
#include <windows.h>
#include <iomanip>
#include <iostream>

class miniTimer
{
private:
    int _freq;
    LARGE_INTEGER _begin;
    LARGE_INTEGER _end;

public:
    double costTime;            // ���ѵ�ʱ��(��ȷ��΢��)

public:
    miniTimer()
    {
        LARGE_INTEGER tmp;
        QueryPerformanceFrequency(&tmp);
        _freq = tmp.QuadPart;
        costTime = 0;
    }

    void Start()            // ��ʼ��ʱ
    {
        QueryPerformanceCounter(&_begin);
    }

    void Stop()                // ������ʱ
    {
        QueryPerformanceCounter(&_end);
        costTime = (double)((_end.QuadPart - _begin.QuadPart) * 1000.00 / _freq);
		std::cout<<"--------���κ�ʱ��"<<std::fixed<<std::setprecision(2)<<costTime<<" ms--------"<<std::endl;
    }

    void Reset()            // ��ʱ��0
    {
        costTime = 0;
    }
};
#endif