# Chat_using_STL
Чата с использованием контейнеров стандартной библиотеки шаблонов

В проекте выделили 3 класса: User (пользователи чата), Message (для обмена сообщениями) и ConsoleChat (реализация основных функций). При входе в программу пользователь выполняет регистрацию, входит в чат и имеет возможность написать сообщение как в общий чат, так и конкретному пользователю. После того как пользователь выйдет из системы, другой пользователь сможет выполнить те же действия.

Описание пользовательских типов и функций в проекте:

Класс User: принимает в конструктор логин, пароль и имя пользователя

getLogin()-Получить логин пользователя  
getPassword()-Получить пароль пользователя  
getName()-получить имя пользователя  

Класс Message: принимает в конструктор отправителя, получателя и текст сообщения

getSender()-Получить отправителя  
getRecipient()-Получить получателя  
getLetter()-Получить текст сообщения  

Класс ConsoleChat: Реализует основной функционал

start()-Переменная _сhatStarted принимает значение true  
сhatStarted()-Возвращает значение переменной _сhatStarted  
startMenu()-Стартовое меню программы, возможность зарегистрироваться, войти в чат, узнать имена всех пользователей и выйти из программы  
signUp()-Регистрация в чате, необходимо задать логин, пароль и имя  
logIn()-Вход в чат, необходимо указать логин и пароль  
getOnlineUser()-Возвращает текущего пользователя  
chatMenu()-Меню чата, позволяет просмотреть чат, написать сообщение и выйти из чата  
sendMessage()-Позволяет написать сообщение, в качестве адресата необходимо указать конкретного получателя/всех пользователей  
getUserByLogin(const string login)-Возвращает указатель на пользователя, если его логин совпадает с указанным  
openChat()-Отображает чат  
showAllUserNames()-Выводит имена всех пользователй  
hashPassword()-Функция для хеширования пароля  
verifyPassword()-Функция для проверки соответствия хэша пароля   

Класс sha1: Реализует криптографическую хэш-функцию

Класс исключения LoginException:public exception, наследуется от класса exception.
метод what() выводит строку с предупреждением, если указанный логин уже занят

Функция main() - Происходит создание класса ConsoleChat, пока чат запущен отображается стартовое меню, если есть онлайн пользователь, то отображается меню чата

Для OC Windows реализована цветовая поддержка консоли