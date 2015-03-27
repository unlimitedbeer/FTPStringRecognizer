// FTPStringRecognizer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int start_time = clock();
	Recognizer rec(NULL);
	rec.DoRecognize();
	std::cout << "Process time: " << clock() - start_time;
	getchar();
	return 0;
}

