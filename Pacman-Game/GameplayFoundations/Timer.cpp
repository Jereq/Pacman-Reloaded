#include "Timer.h"
#include <windows.h>

Timer::Timer()
: mSecondsPerCount(0.0), mDeltaTime(-1.0), mBaseTime(0), 
  mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

float Timer::getTime()const
{
	if( mStopped )
	{
		return (float)((mStopTime - mBaseTime)*mSecondsPerCount);
	}	
	else
	{
		return (float)(((mCurrTime-mPausedTime)-mBaseTime)*mSecondsPerCount);
	}
}

float Timer::getDeltaTime()const
{
	return (float)mDeltaTime;
}

void Timer::reset()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped  = false;
}

void Timer::start()
{
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if( mStopped )
	{
		mPausedTime += (startTime - mStopTime);	

		mPrevTime = startTime;
		mStopTime = 0;
		mStopped  = false;
	}
}

void Timer::stop()
{
	if( !mStopped )
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		mStopTime = currTime;
		mStopped  = true;
	}
}

void Timer::tick()
{
	if( mStopped )
	{
		mDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	mDeltaTime = (mCurrTime - mPrevTime)*mSecondsPerCount;

	mPrevTime = mCurrTime;

	if(mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}

