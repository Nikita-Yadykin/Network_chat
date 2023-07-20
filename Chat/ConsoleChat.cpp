#include"ConsoleChat.h"
#include<iostream>
#include "sha1.h" // Подключаем заголовочный файл для хеширования SHA-1
#include <cstring>
#ifdef _WIN64
#include <windows.h>
#endif
using namespace std;

map<string, User> ConsoleChat::_user;
map<int, Message> ConsoleChat::_message;

bool ConsoleChat::сhatStarted() const
{
	return _сhatStarted;
}

void ConsoleChat::start()
{
	_сhatStarted = true;
}

void ConsoleChat::startMenu() // Стартовое меню, отображается при запуске
{
    #ifdef _WIN64
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
     #endif
	ns << "\tWelcome to chat!\n\n"
		<< "Choose an action to continue: \n\n"
		<< "1-Register\n"
		<< "2-Enter chat\n"
		<< "3-Leave the chat\n";
	string str;
	char action = '0';

	ns >> str;

	if (!str.empty())
		action = '0';

	action = str[0];

	switch (action)
	{
	case '1':
    #ifdef _WIN64
		SetConsoleTextAttribute(hConsole, 10);
        #endif
		signUp(); // Зарегистрироваться
		break;
	case '2':

		logIn(); // Войти
		break;
	case '3':
		_сhatStarted = false; // Выход из чата
		ns << "CDATA:CMD:EXIT\n";
        #ifdef _WIN64
		SetConsoleTextAttribute(hConsole, 15);
        #endif
		break;
	default:
    #ifdef _WIN64
		SetConsoleTextAttribute(hConsole, 12);
         #endif
		ns << "Please check that the characters you are entering are correct.\n";
        #ifdef _WIN64
		SetConsoleTextAttribute(hConsole, 11);
        #endif
		break;
	}

};

shared_ptr<User> ConsoleChat::getUserByLogin(const string login) const
{
	auto it = ConsoleChat::_user.find(login);
	if (it != _user.end()) // Если введенный логин совпал с логином одного из пользователей
		return make_shared<User>(it->second); // Возвращаем указатель на этого пользователя
	return nullptr;

}

shared_ptr<User>  ConsoleChat::getOnlineUser() const
{
	return _onlineUser;
}

void ConsoleChat::logIn() // Вход в чат
{
	string login;
	string password;

	ns << "Please enter a login: ";
	ns >> login;
	ns << "Enter password: ";
	ns >> password;

	_onlineUser = getUserByLogin(login); // Указатель на онлайн пользователя получает указатель на пользователя с указанным логином

	if (_onlineUser == nullptr || !verifyPassword(password, _onlineUser->getPassword())) // Если нет онлайн пользователя или указанный пароль не соответствует хэшу пароля онлайн пользователя
	{
		_onlineUser = nullptr; // Сообщаем, что онлайн пользователь отсутствует
        #ifdef _WIN64
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);
        #endif
		ns << "Invalid login or password, please try again\n";
        #ifdef _WIN64
		SetConsoleTextAttribute(hConsole, 11);
         #endif
	}
}

void ConsoleChat::signUp() // Регистрация
{
    #ifdef _WIN64
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
     #endif
	string login, password, name;

	ns << "Please enter your login: ";
	ns >> login;
	ns << "Choose security password: ";
	ns >> password;
	ns << "Enter your name: ";
	ns >> name;

	try
	{
		if (getUserByLogin(login) || login == "all") // Если пользователь с таким логином существует или логин = all
		{
			throw LoginException("error: "); // Уникальность логина
		};
	}
	catch (const LoginException& ex) // Ловим выброшенное исключение
	{
        #ifdef _WIN64
		SetConsoleTextAttribute(hConsole, 12);
        #endif
		ns /*cerr*/ << "\n\n (" << ex.what() << ") \n\n"; // Вызываем метод what()
        #ifdef _WIN64
		SetConsoleTextAttribute(hConsole, 15);
         #endif
		return;
	}

	string hashedPassword = hashPassword(password); // Хешируем пароль

	User user = User(login, hashedPassword, name); // Создаем нового пользователя
	_user.insert(make_pair(login, user)); // Добавляем нового пользователя
	_onlineUser = make_shared<User>(user); // Новый пользователь становится онлайн пользователем
	ns << "\nCongratulations! You have successfully registered!\n";
}

string ConsoleChat::hashPassword(const string& password) // Функция для хеширования пароля
{
	uint* hashedPassword = sha1(password.c_str(), password.length());
	string hashStr;

	for (int i = 0; i < SHA1HASHLENGTHUINTS; ++i) {
		// Преобразуем каждое 32-битное слово хеша в строку шестнадцатеричного представления
		hashStr += to_string(hashedPassword[i]);
	}

	// Удаляем массив с хешем
	delete[] hashedPassword;

	return hashStr;
}

bool ConsoleChat::verifyPassword(const string& password, const string& hashedPassword) // Функция для проверки соответствия хэша пароля
{
	string hashedInput = hashPassword(password); // Хешируем введенный пароль
	return (hashedInput == hashedPassword); // Сравниваем хэши
}


void ConsoleChat::openChat() //const // Просмотр чата и списка пользователей
{
    #ifdef _WIN64
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
    #endif
	string sender, recipient;

	ns << "-------users chatting online-----\n";
	ns << "login  \t\t  name  \n";
	ns << "\n---------------------------------\n";
	for (const auto& user : _user) // Перебираем пользователей
		ns << user.first << "\t---\t" << user.second.getName() << "\n"; // Выводим логин и имя пользователя
	ns << "\n--------messages-----------------\n\n";
	ns << " -----------chat-------  \n";

	for (const auto& pair : _message) // Перебираем сообщения
	{
		const Message& message = pair.second;
		if (_onlineUser->getLogin() == message.getSender() || _onlineUser->getLogin() == message.getRecipient() || message.getRecipient() == "all") // Если логин онлайн пользователя равен логину отправителя или логину получателя или равен "all"
		{
			sender = (_onlineUser->getLogin() == message.getSender()) ? _onlineUser->getLogin() : getUserByLogin(message.getSender())->getName(); // Устанавливаем отправителя

			if (message.getRecipient() == "all") // Если сообщение предназначено для всех
			{
				recipient = "all";
			}
			else // Если сообщение для конкретного пользователя
			{
				recipient = (_onlineUser->getLogin() == message.getRecipient()) ? _onlineUser->getLogin() : getUserByLogin(message.getRecipient())->getName(); // Устанавливаем получателя
			}
			ns << "message from " << sender << ": to " << recipient << "\n";
			ns << " - " << message.getLetter() << " - \n";
		}
	}
	ns << "---------------------------\n";

}

void ConsoleChat::sendMessage() // Написать сообщение
{
    #ifdef _WIN64
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
	string recipient, text;
	ns << "to (login or all) - ";
	ns >> recipient; // Указать логин получателя или all
	ns << ">> ";
	//cin.ignore();
	//getline(cin, text);
	ns >> text; //?

	int messageId = _message.size() + 1; // Создаем уникальный идентификатор сообщения

	if (!(recipient == "all" || getUserByLogin(recipient))) {  // Если получатель не равен all или не найден логин пользователя

        #ifdef _WIN64
		SetConsoleTextAttribute(hConsole, 12);
         #endif
		ns << "error no such user  -- " << recipient << "\n";
        #ifdef _WIN64
		SetConsoleTextAttribute(hConsole, 11);
        #endif
		return;
	}
	if (recipient == "all") // Если сообщение для всех
		_message.insert(make_pair(messageId, Message(_onlineUser->getLogin(), "all", text))); // Создаем сообщение для всех
	//	_message.push_back(Message(_onlineUser->getLogin(), "all", text)); 
	else
		_message.insert(make_pair(messageId, Message(_onlineUser->getLogin(), getUserByLogin(recipient)->getLogin(), text))); // Создаем сообщение для конкретного пользователя
	//		_message.push_back(Message(_onlineUser->getLogin(), getUserByLogin(recipient)->getLogin(), text)); 
	ns << "message send -  " << recipient << ":\n ";
}

void ConsoleChat::chatMenu() // Меню чата
{
    #ifdef _WIN64
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
    #endif
	ns << "Welcome " << _onlineUser->getName() << "\n";
	while (_onlineUser) // Пока есть онлайн пользователь
	{
		ns << "Choose an action: \n"
			<< "1-Group chat \n"
			<< "2-Write a message \n"
			<< "3-Exit \n";
		string str;
		char action;

		ns >> str;

		if (!str.empty())
			action = '0';

		action = str[0];

		switch (action)
		{
		case '1':
			openChat(); // Открыть чат
			break;
		case '2':
			sendMessage(); // Написать сообщение
			break;
		case '3':
			_onlineUser = nullptr; // Выход
			break;
		default:
			ns << "Please try again\n";
			break;
		}
	}
}