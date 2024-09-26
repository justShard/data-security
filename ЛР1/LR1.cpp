#include <iostream>
#include <vector>
#include <string>

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
    return 'A' + rotor.find(input);
}

std::string encrypt(const std::string& plaintext, const std::vector<std::string>& rotors, int shift) {
    std::string ciphertext = plaintext;
    
    // Проходимо через кожен символ в рядку
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char currentChar = ciphertext[i];
        
        // Перевіряємо, що це велика літера
        if (currentChar >= 'A' && currentChar <= 'Z') {
            // Спочатку зсуваємо (шифр Цезаря)
            currentChar = rotate(currentChar, shift);
            
            // Проходимо через всі три ротори
            for (const auto& rotor : rotors) {
                currentChar = substitute(currentChar, rotor);
            }
            
            ciphertext[i] = currentChar;
        }
    }
    
    return ciphertext;
}

std::string decrypt(const std::string& ciphertext, const std::vector<std::string>& rotors, int shift) {
    std::string plaintext = ciphertext;
    
    // Проходимо через кожен символ в рядку
    for (size_t i = 0; i < plaintext.length(); ++i) {
        char currentChar = plaintext[i];
        
        // Перевіряємо, що це велика літера
        if (currentChar >= 'A' && currentChar <= 'Z') {
            // Проходимо через ротори у зворотньому порядку
            for (int j = rotors.size() - 1; j >= 0; --j) {
                currentChar = reverseSubstitute(currentChar, rotors[j]);
            }
            
            // Відновлюємо зсув (шифр Цезаря)
            currentChar = rotate(currentChar, 26 - shift);
            
            plaintext[i] = currentChar;
        }
    }
    
    return plaintext;
}

int main() {
    // Три ротори
    std::vector<std::string> rotors = {
        "EKMFLGDQVZNTOWYHXUSPAIBRCJ", // Ротор 1
        "AJDKSIRUXBLHWTMCQGZNPYFVOE", // Ротор 2
        "BDFHJLCPRTXVZNYEIWGAKMUSQO"  // Ротор 3
    };
    
    // Вхідне повідомлення
    std::string plaintext = "HELLOENIGMA";
    int shift = 3; // Зсув для шифру Цезаря
    
    // Шифрування
    std::string encrypted = encrypt(plaintext, rotors, shift);
    std::cout << "Зашифроване повідомлення: " << encrypted << std::endl;
    
    // Дешифрування
    std::string decrypted = decrypt(encrypted, rotors, shift);
    std::cout << "Розшифроване повідомлення: " << decrypted << std::endl;
    
    return 0;
}
