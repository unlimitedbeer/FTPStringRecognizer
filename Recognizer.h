#ifndef RECOGNIZER
#define RECOGNIZER

#include "stdafx.h"

#define STRING_LENGTH 255 
#define PREAMBULA "ftp://"
#define HIGH_AND_LOW_LETTERS_DIFFERENCE 32 // ������� ����� ����� ������� � ��������� �����
#define MAX_LENGTH_PREAMBULA (strlen(PREAMBULA)) // ������������ ����� ���������
#define MAX_LENGTH_USERNAME 20	// ������������ ����� ����� ������������
#define MAX_LENGTH_SERVER 20	// ������������ ����� ����� �������
#define MAX_LENGTH_DOMAIN 20		// ������������ ����� ����� ������
#define MAX_LENGTH_ZONE 5		// ������������ ����� ����� ����

// ����, ���������� �� ������
struct FTPRecord {
	std::string username;
	std::string server;
	std::string domain;
	std::string zone;
	bool isStringOK; // ������ ������ ���������? ���� ������������ ��������� ������ ��������� ��������
};

class Recognizer {
	recognizerContext *fsm; // �����, ����������� �������� �������
	int charIndex;		// ������ �������� ������� � ������
	int stringIndex;	// ������ ������� ������
	int fieldLength;	// ����� �������� ������������ ����

	FTPRecord currentRecord; // ���� ������� ������
	std::vector<std::string> strings; // ������, ���������� �� �����

	// ������������ � ��������� ��������� ��������
	// ����������� ���� "��� ������������ - ���������� �������������"
	std::map<std::string, int> usersStatistic; 

public:
	Recognizer(char *filename);
	~Recognizer();

	void DoRecognize();

	// ��� ������� ��������� ������� ������ �� ������������ 
	// � ������������ � ��������� ������� �������� ����
	void ShowPreambula1Error();
	bool isPreambulaCorrect();
	bool isUsernameCorrect();
	bool isServerCorrect();
	bool isDomainCorrect();
	bool isZoneCorrect();

	// ��� ������� ���������, ��� ������ �������� ���� ���������
	bool isPreambulaFinished();
	bool isUsernameFinished();
	bool isServerFinished();
	bool isDomainFinished();
	bool isZoneFinished();

	// ������ ����������� �� ��������� "�����"? ���� ��, �� ��� ���� ��� ����
	// �� ��� ������ �������� ��������������
	bool isStringFinished(); 

	// ��� ������� ����������, ����� ������ �������� ���� ��������� 
	// � ��������� ������� � ����������
	void preambulaPassed();
	void usernamePassed();
	void serverPassed();
	void domainPassed();
	void zonePassed();

	// ��� ������� ����������, ����� ���������� ������ ����������
	// ������� ���������������� ����
	void preambulaReading();
	void usernameReading();
	void serverReading();
	void domainReading();
	void zoneReading();

	char getCurrentChar();
	void ShowError();
	void ReadChar();

	bool isLetterOrNumber(char c);

	void readFile(std::string filename);
	void countUser(); // ����������� ���������� ������������� ����� ����������� � ����������
	void Recognizer::ShowStatistic();  // ����� ����������
};

#endif