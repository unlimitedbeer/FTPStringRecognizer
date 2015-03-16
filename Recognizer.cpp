
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

bool Recognizer::isPreambulaCorrect()
{
	if (fieldLength >= MAX_LENGTH_PREAMBULA)
		return false;

	return (
		(getCurrentChar() == PREAMBULA[charIndex]) || 
		(getCurrentChar() == PREAMBULA[charIndex] - HIGH_AND_LOW_LETTERS_DIFFERENCE)
	);
}

bool Recognizer::isUsernameCorrect()
{
	if (fieldLength > MAX_LENGTH_USERNAME)
		return false;

	return (isLetterOrNumber(getCurrentChar()));
}

bool Recognizer::isServerCorrect()
{
	if (fieldLength > MAX_LENGTH_SERVER)
		return false;

	return (isLetterOrNumber(getCurrentChar()));
}

bool Recognizer::isDomainCorrect()
{	
	if (fieldLength > MAX_LENGTH_DOMAIN)
		return false;

	return (isLetterOrNumber(getCurrentChar()));
}

bool Recognizer::isZoneCorrect()
{
	if (fieldLength > MAX_LENGTH_ZONE)
		return false;

	return (isLetterOrNumber(getCurrentChar()));
}

void Recognizer::DoRecognize()
{

	for (int i = 0; i < strings.size(); i++) {
		fieldLength = 0;
		stringIndex = i;
		charIndex = 0;
		currentRecord.username.clear();
		currentRecord.server.clear();
		currentRecord.domain.clear();
		currentRecord.zone.clear();

		fsm->setState(MainMap::Preambula);
		std::cout << "Current string: " << strings[stringIndex] << std::endl;
		std::cout << "Initial state: " << fsm->getState().getName() << "Start reading.\n";

		while (
			(fsm->getState().getId() != MainMap::Error.getId()) &&
			(fsm->getState().getId() != MainMap::End.getId())
			) {
			fsm->readChar();
			std::cout << "Reading next char... ";
			std::cout << "Current state: " << fsm->getState().getName() << "\n";
			charIndex++;
		}

		currentRecord.isStringOK = (fsm->getState().getId() == MainMap::End.getId());

		std::cout << "Parsed string:\n";
		std::cout << "Username: " << currentRecord.username.c_str() << "\n";
		std::cout << "Server: " << currentRecord.server.c_str() << "\n";
		std::cout << "Domain: " << currentRecord.domain.c_str() << "\n";
		std::cout << "Zone: " << currentRecord.zone.c_str() << "\n";

		if (currentRecord.isStringOK) {
			std::cout << "String is OK\n";
			countUser();
		}
		else
			std::cout << "String contain error\n";

		std::cout << "\n";
	}

	ShowStatistic();
}

char Recognizer::getCurrentChar()
{
	return strings[stringIndex][charIndex];
}

void Recognizer::preambulaPassed()
{
	fieldLength = 0;
	std::cout << "Preambula passed: " << getCurrentChar() << "\n";
}

void Recognizer::usernamePassed()
{
	fieldLength = 0;
	std::cout << "Username passed: " << getCurrentChar() << "\n";
}

void Recognizer::serverPassed()
{
	fieldLength = 0;
	std::cout << "Server passed: " << getCurrentChar() << "\n";
}

void Recognizer::domainPassed()
{
	fieldLength = 0;
	std::cout << "domain passed: " << getCurrentChar() << "\n";
}

void Recognizer::zonePassed()
{
	fieldLength = 0;
	std::cout << "Zone passed: " << getCurrentChar() << "\n";
}

void Recognizer::ShowError()
{
	fieldLength = 0;
	std::cout << "Error occured.\n";
}

bool Recognizer::isPreambulaFinished()
{
	int preambulaIndex = MAX_LENGTH_PREAMBULA - 1;
	if ((fieldLength == preambulaIndex) &&
		(getCurrentChar() == PREAMBULA[preambulaIndex])) {
		return true;
	}
	else
		return false;
}

bool Recognizer::isUsernameFinished()
{
	return (getCurrentChar() == '@');
}

bool Recognizer::isServerFinished()
{
	return (getCurrentChar() == '.');
}

bool Recognizer::isDomainFinished()
{
	return (getCurrentChar() == '.');
}

bool Recognizer::isZoneFinished()
{
	return (getCurrentChar() == 0);
}

bool Recognizer::isStringFinished()
{
	if (getCurrentChar() == 0) {
		currentRecord.zone = currentRecord.domain;
		currentRecord.domain.clear();
		return true;
	}
	else
		return false;
}

void Recognizer::preambulaReading()
{
	char c = getCurrentChar();
	std::cout << "Preambula reading: " << c << "\n";
	fieldLength++;
}

void Recognizer::usernameReading()
{
	char c = getCurrentChar();
	currentRecord.username.push_back(c);
	std::cout << "Username reading: " << c << "\n";
	fieldLength++;
}

void Recognizer::serverReading()
{
	char c = getCurrentChar();
	currentRecord.server.push_back(c);
	std::cout << "Server reading: " << c << "\n";
	fieldLength++;
}

void Recognizer::domainReading()
{
	char c = getCurrentChar();
	currentRecord.domain.push_back(c);
	std::cout << "domain reading: " << c << "\n";
	fieldLength++;
}

void Recognizer::zoneReading()
{
	char c = getCurrentChar();
	currentRecord.zone.push_back(c);
	std::cout << "Zone reading: " << c << "\n";
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