#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функція для шифрування через ротор
string encode_alphabet(const string& message, const string& from, const string& to) {
    string value = "";
    for (char ch : message) {
        size_t pos = from.find(ch);
        value += to[pos];  // Додавання відповідного символу з другого алфавіту
    }
    return value;
}

// Функція для шифрування повідомлення
string encode(const string& message, const vector<string>& rotors, int pseudoRandomNumber) {
    string encodedMessage = message;
    for (const string& rotor : rotors) {
        encodedMessage = encode_alphabet(encodedMessage, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", rotor);
    }
    return encodedMessage;
}

// Функція для дешифрування повідомлення
string decode(const string& message, const vector<string>& rotors, int pseudoRandomNumber) {
    string decodedMessage = message;
    for (auto it = rotors.rbegin(); it != rotors.rend(); ++it) {  // Проходження роторами у зворотному порядку
        decodedMessage = encode_alphabet(decodedMessage, *it, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }
    return decodedMessage;
}

int main() {
    // Зчитування операції (ENCODE або DECODE)
    string operation;
    cin >> operation;

    // Зчитування початкового зсуву
    int pseudoRandomNumber;
    cin >> pseudoRandomNumber;

    // Масив для зберігання роторів
    vector<string> rotors(3);
    for (int i = 0; i < 3; ++i) {
        cin >> rotors[i];  // Зчитування ротора
    }

    // Зчитування повідомлення для шифрування або дешифрування
    string message;
    cin >> message;

    // Обробка шифрування
    if (operation == "ENCODE") {
        string value = "";
        // Цикл для кожного символу повідомлення
        for (size_t i = 0; i < message.length(); i++) {
            // Зсув символу з використанням початкового зсуву та індексу символу
            int pos = (message[i] - 'A' + pseudoRandomNumber + i) % 26;
            value += 'A' + pos;  // Додавання нового символу до результату
        }
        message = value;
        // Виконання шифрування через ротори
        message = encode(message, rotors, pseudoRandomNumber);
    } else {
        // Виконання дешифрування через ротори
        message = decode(message, rotors, pseudoRandomNumber);
        string value = "";
        // Цикл для кожного символу повідомлення
        for (size_t i = 0; i < message.length(); i++) {
            // Обчислення позиції символу з урахуванням зсуву
            int pos = (message[i] - 'A') - pseudoRandomNumber - i;
            // Корекція позиції, щоб уникнути негативних значень
            while (pos < 0) {
                pos += 26;
            }
            value += 'A' + pos;  // Додавання нового символу до результату
        }
        message = value;
    }

    // Виведення закодованого або декодованого повідомлення
    cout << message << endl;

    return 0;
}
