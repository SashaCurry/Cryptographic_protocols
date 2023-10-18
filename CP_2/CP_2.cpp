#include <iostream>
#include "cmath"
#include "vector"
#include "string"
#include <chrono>
#include "boost/multiprecision/cpp_int.hpp"

using namespace std;
using namespace std::chrono;
using namespace boost::multiprecision;

map <char, string> book { {'0', "11"}, {'1', "12"}, {'2', "13"}, {'3', "14"}, {'4', "15"}, {'5', "16"}, {'6', "17"}, {'7', "18"}, {'8', "19"}, {'9', "21"},
                            {' ', "22"}, {'!', "23"}, {'"', "24"}, {'#', "25"}, {'$', "26"}, {'%', "27"}, {'^', "28"}, {'&', "29"}, {'\'', "31"}, {'(', "32"},
                            {')', "33"}, {'*', "34"}, {'+', "35"}, {',', "36"}, {'-', "37"}, {'.', "38"}, {'/', "39"}, {':', "41"}, {';', "42"}, {'<', "43"},
                            {'=', "44"}, {'>', "45"}, {'?', "46"}, {'@', "47"}, {'[', "48"}, {'\\', "49"}, {']', "51"}, {'_', "52"}, {'`', "53"}, {'{', "54"},
                            {'}', "55"}, {'|', "56"}, {'~', "57"}, {'\n', "58"}, {'а', "59"}, {'б', "61"}, {'в', "62"}, {'г', "63"}, {'д', "64"}, {'е', "65"},
                            {'ё', "66"}, {'ж', "67"}, {'з', "68"}, {'и', "69"}, {'й', "71"}, {'к', "72"}, {'л', "73"}, {'м', "74"}, {'н', "75"}, {'о', "76"},
                            {'п', "77"}, {'р', "78"}, {'с', "79"}, {'т', "81"}, {'у', "82"}, {'ф', "83"}, {'х', "84"}, {'ц', "85"}, {'ч', "86"}, {'ш', "87"},
                            {'щ', "88"}, {'ъ', "89"}, {'ы', "91"}, {'ь', "92"}, {'э', "93"}, {'ю', "94"}, {'я', "95"} };

map <string, char> bookRvs{ {"11", '0'}, {"12", '1'}, {"13", '2'}, {"14", '3'}, {"15", '4'}, {"16", '5'}, {"17", '6'}, {"18", '7'}, {"19", '8'}, {"21", '9'},
                            {"22", ' '}, {"23", '!'}, {"24", '"'}, {"25", '#'}, {"26", '$'}, {"27", '%'}, {"28", '^'}, {"29", '&'}, {"31", '\''}, {"32", '('},
                            {"33", ')'}, {"34", '*'}, {"35", '+'}, {"36", ','}, {"37", '-'}, {"38", '.'}, {"39", '/'}, {"41", ':'}, {"42", ';'}, {"43", '<'},
                            {"44", '='}, {"45", '>'}, {"46", '?'}, {"47", '@'}, {"48", '['}, {"49", '\\'}, {"51", ']'}, {"52", '_'}, {"53", '`'}, {"54", '{'},
                            {"55", '}'}, {"56", '|'}, {"57", '~'}, {"58", '\n'}, {"59", 'а'}, {"61", 'б'}, {"62", 'в'}, {"63", 'г'}, {"64", 'д'}, {"65", 'е'},
                            {"66", 'ё'}, {"67", 'ж'}, {"68", 'з'}, {"69", 'и'}, {"71", 'й'}, {"72", 'к'}, {"73", 'л'}, {"74", 'м'}, {"75", 'н'}, {"76", 'о'},
                            {"77", 'п'}, {"78", 'р'}, {"79", 'с'}, {"81", 'т'}, {"82", 'у'}, {"83", 'ф'}, {"84", 'х'}, {"85", 'ц'}, {"86", 'ч'}, {"87", 'ш'},
                            {"88", 'щ'}, {"89", 'ъ'}, {"91", 'ы'}, {"92", 'ь'}, {"93", 'э'}, {"94", 'ю'}, {"95", 'я'} };

set <char> workSymbs{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '!', '\"', '#', '$', '%', '^', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
                        ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '_', '`', '{', '}', '|', '~', '\n', 'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з',
                        'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я' };

set <char> upSymbs{ 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П',
                    'Р', 'С', 'Т', 'У', 'Ф', 'Ч', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я' };


vector <cpp_int> deg2(cpp_int el, cpp_int n) {
	vector <cpp_int> res;
	while (n != 0) {
		if (n / el == 1) {
			res.push_back(el);
			n -= el;
			el = 1;
		}
		else
			el *= 2;
	}
	return res;
}


cpp_int multMod(cpp_int n, cpp_int mod, vector <pair <cpp_int, cpp_int>> lst) {
	if (lst.size() == 1) {
		cpp_int res = 1;
		for (int i = 0; i < lst[0].second; i++)
			res = res * lst[0].first % mod;
		return res;
	}
	else if (lst[0].second == 1) {
		cpp_int el = lst[0].first;
		lst.erase(lst.begin());
		return (el * multMod(n, mod, lst)) % mod;
	}
	else {
		for (int i = 0; i < lst.size(); i++)
			if (lst[i].second > 1) {
				lst[i].first = (lst[i].first * lst[i].first) % mod;
				lst[i].second /= 2;
			}
		return multMod(n, mod, lst);
	}
}


cpp_int powClosed(cpp_int x, cpp_int y, cpp_int mod) {
	if (y == 0)
		return 1;

	vector <cpp_int> lst = deg2(1, y);
	vector <pair <cpp_int, cpp_int>> xDegs;
	for (int i = 0; i < lst.size(); i++)
		xDegs.push_back(make_pair(x, lst[i]));

	cpp_int res = multMod(x, mod, xDegs);
	return res;
}


cpp_int usualEuclid(cpp_int a, cpp_int b) {
	if (a < b)
		swap(a, b);
	if (a < 0 || b < 0)
		throw string{ "Выполнение невозможно: a < 0 или b < 0" };
	else if (b == 0)
		return a;

	cpp_int r = a % b;
	return usualEuclid(b, r);
}


cpp_int decForm(string x) {
	cpp_int res = 0, deg = 1;
	if (x.back() == '1')
		res += 1;
	for (int i = 1; i < x.length(); i++) {
		deg = deg * 2;
		if (x[x.length() - i - 1] == '1')
			res += deg;
	}
	return res;
}


bool miller_rabin(cpp_int n, int k = 10) {
	if (n == 0 || n == 1)
		return false;

	cpp_int d = n - 1;
	cpp_int s = 0;
	while (d % 2 == 0) {
		s++;
		d = d / 2;
	}

	cpp_int nDec = n - 1;
	for (int i = 0; i < k; i++) {
		cpp_int a = rand() % nDec;
		if (a == 0 || a == 1)
			a = a + 2;

		cpp_int x = powClosed(a, d, n);
		if (x == 1 || x == nDec)
			continue;

		bool flag = false;
		for (int j = 0; j < s; j++) {
			x = (x * x) % n;
			if (x == nDec) {
				flag = true;
				break;
			}
		}
		if (!flag)
			return false;
	}

	return true;
}


vector <cpp_int>  generateKeys(cpp_int x) {
	cpp_int q = rand();
	while (!miller_rabin(q))
		q++;

	cpp_int s, p = 2, pDec;
	while (!miller_rabin(p)) {
		string sBin = "";
		int sBinSize = rand() % 50 + 1;
		for (int i = 0; i < sBinSize; i++)
			sBin = sBin + to_string(rand() % 2);
		s = decForm(sBin);

		p = (q * s) + 1;
		pDec = p - 1;
	}

	cpp_int a = 2, g;
	while (pDec > a) {
		g = powClosed(a, pDec / q, p);
		if (g == 1) {
			a++;
			continue;
		}
		break;
	}

	cpp_int y = powClosed(g, x % p, p);	
	return vector <cpp_int> {y, g, p}
}


//////////////////////////////////////////////////////////////////////РЕЖИМ ШИФРОВАНИЯ///////////////////////////////////////////////////////////////////////
vector <string> getKeys() {
    vector <string> keys;
    ifstream fin;
    while (true) {
        string fileKeys;
        cout << "\nФайл с ключами (по умолчанию keys.txt): ";
        getline(cin, fileKeys);
        if (fileKeys == "")
            fileKeys = "keys.txt";

        fin.open(fileKeys);
        if (fin.is_open())
            break;
        else
            cout << "Файл " << fileKeys << " не найден! \n";
    }

    string str;
    while (getline(fin, str))
        keys.push_back(str.substr(4));

    return keys;
}


string clearText() {
    ifstream fin;
    string fileText;
    while (true) {
        cout << "\nФайл с текстом (по умолчанию start.txt): ";
        getline(cin, fileText);
        if (fileText == "")
            fileText = "start.txt";

        fin.open(fileText);
        if (fin.is_open())
            break;
        else
            cout << "Файл " << fileText << " не найден! \n";
    }

    cout << "Была произведена очистка текста от неизвестных символов и приведение к нижнему регистру. Получившийся текст: \n";
    ofstream fout("clear_" + fileText);
    char el;
    string codeSymbs = "";
    while (fin.get(el)) {
        if (upSymbs.find(el) != upSymbs.end()) {
            cout << char(el + 32);
            fout << char(el + 32);
            codeSymbs += book[char(el + 32)];
        }
        else if (workSymbs.find(el) == workSymbs.end())
            continue;
        else {
            cout << el;
            fout << el;
            codeSymbs += book[el];
        }
    }

    fin.close();
    fout.close();
    return codeSymbs;
}


void encryption() {
    vector <string> keysPGXY = getKeys();
    string p = keysPGXY[0], g = keysPGXY[1], x = keysPGXY[2], y = keysPGXY[3];
    cout << "p = " << p << "\ng = " << g << "\nx = " << x << "\ny = " << y << endl;
    string codeSymbs = clearText();
    cout << "\n\nТекст, представленный в виде кодов его символов: " << codeSymbs;

    cout << "\n\nШифртекст (сохранён в файл encryptText.txt): ";
    ofstream fout("encryptText.txt");
    int offset = p.size();
    for (int i = 0; i < codeSymbs.length(); i += offset) {
        string M = codeSymbs.substr(i, offset);
        if (division(M, p).first != "0") {
            M.pop_back();
            i--;
        }

        string k = "2", pDec = subtraction(p, "1");
        int offset = pDec.length();
        while (nod(k, pDec) != "1") {
            string kBin = "";
            int kBinSize = rand() % offset;
            for (int i = 0; i < kBinSize; i++)
                kBin = kBin + to_string(rand() % 2);
            k = division(decForm(kBin + "1"), p).second;
        }

        string a = exponentiation(g, k, p), b = division(multiplication(exponentiation(y, k, p), M), p).second;
        cout << "(" << a << "," << b << ") ";
        fout << "(" << a << "," << b << ") ";
    }
    cout << endl;
    fout.close();
}


/////////////////////////////////////////////////////////////////////РЕЖИМ РАСШИФРОВАНИЯ//////////////////////////////////////////////////////////////////////
void decryption() {
    vector <string> keysPGXY = getKeys();
    string p = keysPGXY[0], g = keysPGXY[1], x = keysPGXY[2], y = keysPGXY[3];
    cout << "p = " << p << "\ng = " << g << "\nx = " << x << "\ny = " << y << endl;

    ifstream fin;
    string fileText;
    while (true) {
        cout << "\nФайл с шифртекстом (по умолчанию encryptText.txt): ";
        getline(cin, fileText);
        if (fileText == "")
            fileText = "encryptText.txt";

        fin.open(fileText);
        if (fin.is_open())
            break;
        else
            cout << "Файл " << fileText << " не найден! \n";
    }

    string codeSymbs = "";
    cout << "Шифртекст: \n";
    string str = "", a = "", b = "", pDec = subtraction(p, "1");
    char el;
    while (fin.get(el)) {
        cout << el;
        if (el == '(') {
            a = "";
            b = "";
        }
        else if (el == ',') {
            a = str;
            str = "";
        }
        else if (el == ')') {
            b = str;
            str = "";
            codeSymbs += division(multiplication(b, exponentiation(a, subtraction(pDec, x), p)), p).second; //b * a^(p-1-x) mod p
        }
        else if (isdigit(el))
            str += el;
    }

    cout << "\n\nТекст, представленный в виде кодов его символов: " << codeSymbs << endl;

    cout << "\nРасшифрованный текст (сохранён в файле decryptText.txt): \n";
    ofstream fout("decryptText.txt");
    for (int i = 0; i < codeSymbs.length(); i += 2) {
        string M = codeSymbs.substr(i, 2);
        if (bookRvs.find(M) == bookRvs.end())
            continue;
        cout << bookRvs[M];
        fout << bookRvs[M];
    }
    cout << endl;

    fin.close();
    fout.close();
}


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
