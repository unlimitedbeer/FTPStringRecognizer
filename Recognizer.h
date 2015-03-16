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
	void ShowPreambula1Error(char c);
	bool isPreambulaCorrect(char c);
	bool isUsernameCorrect(char c);
	bool isServerCorrect(char c);
	bool isDomainCorrect(char c);
	bool isZoneCorrect(char c);

	// ��� ������� ���������, ��� ������ �������� ���� ���������
	bool isPreambulaFinished(char c);
	bool isUsernameFinished(char c);
	bool isServerFinished(char c);
	bool isDomainFinished(char c);
	bool isZoneFinished(char c);

	// ������ ����������� �� ��������� "�����"? ���� ��, �� ��� ���� ��� ����
	// �� ��� ������ �������� ��������������
	bool isStringFinished(char c);

	// ��� ������� ����������, ����� ������ �������� ���� ��������� 
	// � ��������� ������� � ����������
	void preambulaPassed(char c);
	void usernamePassed(char c);
	void serverPassed(char c);
	void domainPassed(char c);
	void zonePassed(char c);

	// ��� ������� ����������, ����� ���������� ������ ����������
	// ������� ���������������� ����
	void preambulaReading(char c);
	void usernameReading(char c);
	void serverReading(char c);
	void domainReading(char c);
	void zoneReading(char c);

	void showError(char c);
	void ReadChar(char c);

	bool isLetterOrNumber(char c);

	void readFile(std::string filename);
	void countUser(); // ����������� ���������� ������������� ����� ����������� � ����������
	void Recognizer::ShowStatistic();  // ����� ����������
};

#endif