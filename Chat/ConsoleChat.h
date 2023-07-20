#pragma once
#include <map>
#include <memory>
#include "Message.h"
#include "NetWorkStream.h"

class LoginException :public exception // Класс исключения наследник от класса exception
{
public:
	LoginException(const std::string& msg) :_msg(msg) {}
	virtual const char* what() const noexcept override // Виртуальный метод what() выводит предупреждение, если логин не уникален
	{
		return "error: user login already exists ";
	}
private:
	std::string _msg;
};

class ConsoleChat
{
	NetWorkStream ns;
public:
	ConsoleChat(int connection):ns(connection){}
	void start();
	bool сhatStarted() const;
	void startMenu();
	void signUp();
	void logIn();
	shared_ptr<User> getOnlineUser() const;
	void chatMenu();
	void sendMessage();
	string hashPassword(const string& password); // Функция для хеширования пароля
	bool verifyPassword(const string& password, const string& hashedPassword); // Функция для проверки соответствия хэша пароля
	
private:

	static map<string, User> _user;
	static map<int, Message> _message;

	shared_ptr<User> _onlineUser = nullptr;	
	bool _сhatStarted = false;
	shared_ptr<User> getUserByLogin(const string login) const;
	void openChat();// const;
	
};