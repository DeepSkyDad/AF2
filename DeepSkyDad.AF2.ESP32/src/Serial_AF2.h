#include "StringProxy_AF2.h"

#pragma once
class Serial_AF2
{
	private:
        StringProxy_AF2* _stringProxy;
		char _serialCommandRaw[70];
        int _serialCommandRawIdx;
        int _serialCommandRawLength;
        char _command[5];
        char _commandParam[65];
        int _commandParamLength;
        void _printResponse(int response);
        void _printResponse(long response);
        void _printResponse(char response[]);
        void _printResponse(float response);
        void _printSuccess();
        void _printResponseErrorCode(int code);
	public:
		void init(StringProxy_AF2 &stringProxy);
        void serialEvent();
        bool commandEndsWith(char character);
};