#include <iostream>
#include "cmath"
#include "vector"
#include "string"
#include <chrono>
#include "boost/multiprecision/cpp_int.hpp"

using namespace std;
using namespace std::chrono;
using namespace boost::multiprecision;

void kerberos(pair <string, string>* users) {
    hash <string> hashStr;
    cpp_int keyUser1(hashStr(users[0].second)), keyUser2 (hashStr(users[1].second));
    cout << "\nПользователь " << users[0].first << " зерегистрирован в системе Kerberos. Общий секретный ключ: " << keyUser1;
    cout << "\nПользователь " << users[1].first << " зарегистрирован в системе Kerberos. Общий секретный ключ: " << keyUser2;

    cout << "\n\nПользователь " << users[0].first << " отправляет Kerberos сообщение (" << users[0].first << ", " << users[1].first << ")";

    uint64_t sec = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    cpp_int timestamp(sec), ttl = 300, mainKey = rand() * rand() * rand();
    cout << "\n\nKerberos создаёт сообщение (" << timestamp << ", " << ttl << ", " << mainKey << ", " << users[0].first << ") для пользователя " << users[1].first;
    cout << "\nKerberos создаёт сообщение (" << timestamp << ", " << ttl << ", " << mainKey << ", " << users[1].first << ") для пользователя " << users[1].first;
    
}

int main() {
    setlocale(LC_ALL, "ru");
    cout << "\tПротокол Kerberos";

    pair <string, string>* users = new pair <string, string>[2];
    string login, password;
    cout << "\nВведите логин и пароль пользователя 1: ";
    cin >> login >> password;
    users[0] = make_pair(login, password);
    cout << "Введите логин и пароль пользователя 2: ";
    cin >> login >> password;
    users[1] = make_pair(login, password);

    kerberos(users);
    cout << endl;
    return 0;
}