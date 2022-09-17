#pragma once
#include <Windows.h>
typedef void (CALLBACK *callBackOnEventMessage)(int eventType, const char *msg, void *pParameter);
typedef void (CALLBACK *callBackOnBinaryMessage)(int eventType, const char *msg, void *pParameter);
