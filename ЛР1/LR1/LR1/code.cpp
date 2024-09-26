#include <iostream>
#include <string>
#include <cctype>

// Функція для обертання ротора (зсув)
char rotate(char input, int shift) {
    return 'A' + (input - 'A' + shift) % 26;
}

// Функція для заміни за допомогою ротора
char substitute(char input, const std::string& rotor) {
    return rotor[input - 'A'];
}

// Функція для зворотньої заміни (для дешифрування)
char reverseSubstitute(char input, const std::string& rotor) {
    for (int i = 0; i < 26; i++) {
        if (rotor[i] == input) {
            return 'A' + i;
        }
    }
    return input; // Якщо не знайдено, повертаємо вхідний символ
}

// Функція шифрування
void encrypt(const std::string& plaintext, std::string& result, const std::string rotors[3], int shift) {
    result = plaintext;

    // Проходимо через кожен символ і застосовуємо зсув (шифр Цезаря)
    for (int i = 0; i < result.length(); ++i) {
        char currentChar = std::toupper(result[i]);

        // Перевіряємо, що це велика літера
        if (currentChar >= 'A' && currentChar <= 'Z') {
            currentChar = rotate(currentChar, shift);
            result[i] = currentChar;
        }
    }

    // Вивести результат після зсуву
    std::cout << "After Caesar cipher shift: " << result << std::endl;

    // Проходимо через кожен ротор
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < result.length(); ++i) {
            char currentChar = std::toupper(result[i]);

            if (currentChar >= 'A' && currentChar <= 'Z') {
                currentChar = substitute(currentChar, rotors[j]);
                result[i] = currentChar;
            }
        }

        // Вивести результат після кожного ротора
        std::cout << "After rotor " << j + 1 << ": " << result << std::endl;
    }
}

// Функція дешифрування
void decrypt(const std::string& ciphertext, std::string& result, const std::string rotors[3], int shift) {
    result = ciphertext;

    // Проходимо через кожен ротор у зворотньому порядку
    for (int j = 2; j >= 0; --j) {
        for (int i = 0; i < result.length(); ++i) {
            char currentChar = std::toupper(result[i]);

            if (currentChar >= 'A' && currentChar <= 'Z') {
                currentChar = reverseSubstitute(currentChar, rotors[j]);
                result[i] = currentChar;
            }
        }

        // Вивести результат після кожного ротора
        std::cout << "After rotor " << j + 1 << ": " << result << std::endl;
    }

    // Відновлюємо зсув (шифр Цезаря)
    for (int i = 0; i < result.length(); ++i) {
        char currentChar = std::toupper(result[i]);

        if (currentChar >= 'A' && currentChar <= 'Z') {
            currentChar = rotate(currentChar, 26 - shift); // Зворотній зсув
            result[i] = currentChar;
        }
    }

    // Вивести результат після зсуву
    std::cout << "After reverse Caesar cipher shift: " << result << std::endl;
}

int main() {
    // Три ротори
    const std::string rotors[3] = {
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ", // Ротор 1
        "AJDKSIRUXBLHWTMCQGZNPYFVOE", // Ротор 2
        "BDFHJLCPRTXVZNYEIWGAKMUSQO"  // Ротор 3
    };

    // Введення зсуву для шифру Цезаря
    int shift = 3;

    bool repeat = true; // Прапорець для повторення циклу

    while (repeat) {
        // Введення слова для кодування або декодування
        std::string input;
        std::cout << "Enter the word (capital letters only): ";
        std::cin >> input;

        // Вибір дії: шифрування або дешифрування
        int choice;
        std::cout << "Choose an action:\n1 - Encrypt\n2 - Decrypt\nYour choice: ";
        std::cin >> choice;

        std::string result;

        if (choice == 1) {
            // Шифрування
            encrypt(input, result, rotors, shift);
            std::cout << "Encrypted message: " << result << std::endl;
        }
        else if (choice == 2) {
            // Дешифрування
            decrypt(input, result, rotors, shift);
            std::cout << "Decrypted message: " << result << std::endl;
        }
        else {
            std::cout << "Invalid choice." << std::endl;
        }

        // Запитати, чи потрібно повторити
        char again;
        std::cout << "Do you want to repeat? (y/n): ";
        std::cin >> again;

        if (again == 'n' || again == 'N') {
            repeat = false; // Завершити цикл
        }
    }

    return 0;
}
