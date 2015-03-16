#ifndef RECOGNIZER
#define RECOGNIZER

#include "stdafx.h"

#define STRING_LENGTH 255 
#define PREAMBULA "ftp://"
#define HIGH_AND_LOW_LETTERS_DIFFERENCE 32 // разница между кодом большой и маленькой буквы
#define MAX_LENGTH_PREAMBULA (strlen(PREAMBULA)) // максимальная длина преамбулы
#define MAX_LENGTH_USERNAME 20	// максимальная длина имени пользователя
#define MAX_LENGTH_SERVER 20	// максимальная длина имени сервера
#define MAX_LENGTH_DOMAIN 20		// максимальная длина имени домена
#define MAX_LENGTH_ZONE 5		// максимальная длина имени зоны

// поля, полученные из строки
struct FTPRecord {
	std::string username;
	std::string server;
	std::string domain;
	std::string zone;
	bool isStringOK; // строка задана корректно? сюда записывается результат работы конечного автомата
};

class Recognizer {
	recognizerContext *fsm; // класс, реализующий конечный автомат
	int charIndex;		// индекс текущего символа в строке
	int stringIndex;	// индекс текущей строки
	int fieldLength;	// длина текущего прочитанного поля

	FTPRecord currentRecord; // поля текущей строки
	std::vector<std::string> strings; // строки, полученные из файла

	// пользователи с корректно заданными строками
	// отображение вида "имя пользователя - количество использований"
	std::map<std::string, int> usersStatistic; 

public:
	Recognizer(char *filename);
	~Recognizer();

	void DoRecognize();

	// эти функции проверяют текущий символ на корректность 
	// в соответствии с правилами задания текущего поля
	void ShowPreambula1Error();
	bool isPreambulaCorrect();
	bool isUsernameCorrect();
	bool isServerCorrect();
	bool isDomainCorrect();
	bool isZoneCorrect();

	// эти функции проверяют, что чтение текущего поля завершено
	bool isPreambulaFinished();
	bool isUsernameFinished();
	bool isServerFinished();
	bool isDomainFinished();
	bool isZoneFinished();

	// строка закончилась на состоянии "домен"? если да, то это было имя зоны
	// тк имя домена является необязательным
	bool isStringFinished(); 

	// эти функции вызываются, когда чтение текущего поля завершено 
	// и произошел переход к следующему
	void preambulaPassed();
	void usernamePassed();
	void serverPassed();
	void domainPassed();
	void zonePassed();

	// эти функции вызываются, когда происходит чтение очередного
	// символа соответствующего поля
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
	void countUser(); // увеличиваем количество использований имени пользования в статистике
	void Recognizer::ShowStatistic();  // вывод статистики
};

#endif