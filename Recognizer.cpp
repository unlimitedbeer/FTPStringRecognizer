
#include "stdafx.h"

Recognizer::Recognizer(char *filename)
{
	fsm = new recognizerContext(*this);
	strings.clear();
	readFile("input.txt");
}

Recognizer::~Recognizer()
{
	delete fsm;
}

bool Recognizer::isPreambulaCorrect(char c)
{
	if (fieldLength >= MAX_LENGTH_PREAMBULA)
		return false;

	return (
		(c == PREAMBULA[fieldLength]) || 
		(c == PREAMBULA[fieldLength] - HIGH_AND_LOW_LETTERS_DIFFERENCE)
	);
}

bool Recognizer::isUsernameCorrect(char c)
{
	if (fieldLength > MAX_LENGTH_USERNAME)
		return false;

	return (isLetterOrNumber(c));
}

bool Recognizer::isServerCorrect(char c)
{
	if (fieldLength > MAX_LENGTH_SERVER)
		return false;

	return (isLetterOrNumber(c));
}

bool Recognizer::isDomainCorrect(char c)
{	
	if (fieldLength > MAX_LENGTH_DOMAIN)
		return false;

	return (isLetterOrNumber(c));
}

bool Recognizer::isZoneCorrect(char c)
{
	if (fieldLength > MAX_LENGTH_ZONE)
		return false;

	return (isLetterOrNumber(c));
}

void Recognizer::DoRecognize()
{
	int charIndex;		// индекс текущего символа в строке

	// цикл по всем строкам
	for (int stringIndex = 0; stringIndex < strings.size(); stringIndex++) {
		fieldLength = 0;
		charIndex = 0;
		currentRecord.username.clear();
		currentRecord.server.clear();
		currentRecord.domain.clear();
		currentRecord.zone.clear();

		fsm->setState(MainMap::Preambula);
		//std::cout << "Current string: " << strings[stringIndex] << std::endl;
		//std::cout << "Initial state: " << fsm->getState().getName() << "Start reading.\n";

		// разбираем посимвольно строку, пока не получим состояние
		// "ошибка" или "конец"
		while (
			(fsm->getState().getId() != MainMap::Error.getId()) &&
			(fsm->getState().getId() != MainMap::End.getId())
			) {
			fsm->readChar(strings[stringIndex][charIndex]);
			//std::cout << "Reading next char... ";
			//std::cout << "Current state: " << fsm->getState().getName() << "\n";
			charIndex++;
		}

		currentRecord.isStringOK = (fsm->getState().getId() == MainMap::End.getId());

		/*
		std::cout << "Parsed string:\n";
		std::cout << "Username: " << currentRecord.username.c_str() << "\n";
		std::cout << "Server: " << currentRecord.server.c_str() << "\n";
		std::cout << "Domain: " << currentRecord.domain.c_str() << "\n";
		std::cout << "Zone: " << currentRecord.zone.c_str() << "\n";
		*/
		if (currentRecord.isStringOK) {
			std::cout << "String is OK\n";
			countUser();
		}
		else
			std::cout << "String contain error\n";

		//std::cout << "\n";
	}

	ShowStatistic();
}

void Recognizer::preambulaPassed(char c)
{
	fieldLength = 0;
	//std::cout << "Preambula passed: " << c << "\n";
}

void Recognizer::usernamePassed(char c)
{
	fieldLength = 0;
	//std::cout << "Username passed: " << c << "\n";
}

void Recognizer::serverPassed(char c)
{
	fieldLength = 0;
	//std::cout << "Server passed: " << c << "\n";
}

void Recognizer::domainPassed(char c)
{
	fieldLength = 0;
	//std::cout << "domain passed: " << c << "\n";
}

void Recognizer::zonePassed(char c)
{
	fieldLength = 0;
	//std::cout << "Zone passed: " << c << "\n";
}

void Recognizer::showError(char c)
{
	fieldLength = 0;
	//std::cout << "Error occured.\n";
}

bool Recognizer::isPreambulaFinished(char c)
{
	int preambulaIndex = MAX_LENGTH_PREAMBULA - 1;
	if ((fieldLength == preambulaIndex) &&
		(c == PREAMBULA[preambulaIndex])) {
		return true;
	}
	else
		return false;
}

bool Recognizer::isUsernameFinished(char c)
{
	return (c == '@');
}

bool Recognizer::isServerFinished(char c)
{
	return (c == '.');
}

bool Recognizer::isDomainFinished(char c)
{
	return (c == '.');
}

bool Recognizer::isZoneFinished(char c)
{
	return (c == 0);
}

bool Recognizer::isStringFinished(char c)
{
	if (c == 0) {
		currentRecord.zone = currentRecord.domain;
		currentRecord.domain.clear();
		return true;
	}
	else
		return false;
}

void Recognizer::preambulaReading(char c)
{
	//std::cout << "Preambula reading: " << c << "\n";
	fieldLength++;
}

void Recognizer::usernameReading(char c)
{
	currentRecord.username.push_back(c);
	//std::cout << "Username reading: " << c << "\n";
	fieldLength++;
}

void Recognizer::serverReading(char c)
{
	currentRecord.server.push_back(c);
	//std::cout << "Server reading: " << c << "\n";
	fieldLength++;
}

void Recognizer::domainReading(char c)
{
	currentRecord.domain.push_back(c);
	//std::cout << "domain reading: " << c << "\n";
	fieldLength++;
}

void Recognizer::zoneReading(char c)
{
	currentRecord.zone.push_back(c);
	//std::cout << "Zone reading: " << c << "\n";
	fieldLength++;
}

bool Recognizer::isLetterOrNumber(char c)
{
	return (
		((c >= 'a') &&
		 (c <= 'z')) ||
		((c >= 'A') &&
		 (c <= 'Z')) ||
		((c >= '0') &&
		 (c <= '9'))
	);
}

void Recognizer::readFile(std::string filename)
{
	std::ifstream inputFile(filename);
	if (inputFile.is_open())
	{
		while (!inputFile.eof())
		{
			std::string line;
			std::getline(inputFile, line, '\n');
			strings.push_back(line);
		}

		inputFile.close();
	}
	else
		std::cout << "Can't open file 'input.txt'.\n";
}

void Recognizer::countUser()
{
	std::map<std::string, int>::iterator user;
	user = usersStatistic.find(currentRecord.username);

	if (user != usersStatistic.end()) {
		usersStatistic[currentRecord.username] =
			usersStatistic[currentRecord.username] + 1;
	}
	else {
		usersStatistic.insert(
			std::pair<std::string, int>(currentRecord.username, 1)
		);
	}
}

void Recognizer::ShowStatistic()
{
	std::map<std::string, int>::iterator user;
	std::cout << "\n";

	for (user = usersStatistic.begin(); user != usersStatistic.end(); ++user) {		
		std::cout << "User: " << user->first.c_str() << " " <<
			"Count: " << user->second << "\n";
	}
	
}