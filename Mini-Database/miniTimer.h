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
    double costTime;            // 花费的时间(精确到微秒)

public:
    miniTimer()
    {
        LARGE_INTEGER tmp;
        QueryPerformanceFrequency(&tmp);
        _freq = tmp.QuadPart;
        costTime = 0;
    }

    void Start()            // 开始计时
    {
        QueryPerformanceCounter(&_begin);
    }

    void Stop()                // 结束计时
    {
        QueryPerformanceCounter(&_end);
        costTime = (double)((_end.QuadPart - _begin.QuadPart) * 1000.00 / _freq);
		std::cout<<"--------本次耗时："<<std::fixed<<std::setprecision(2)<<costTime<<" ms--------"<<std::endl;
    }

    void Reset()            // 计时清0
    {
        costTime = 0;
    }
};
#endif