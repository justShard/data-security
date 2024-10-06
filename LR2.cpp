#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <limits>

const double englishFrequency[26] = {
    8.08, 1.67, 3.18, 3.99, 12.56, 2.17, 1.80, 5.27, 7.24, 0.14,
    0.63, 4.04, 2.60, 7.38, 7.47, 1.91, 0.09, 6.42, 6.59, 9.15,
    2.79, 1.00, 1.89, 0.21, 1.65, 0.07
};

// Функція для обчислення частот символів у тексті
void calculateFrequency(const std::string& text, double freq[26]) {
    int totalLetters = 0;
    std::fill(freq, freq + 26, 0.0);

    for (char c : text) {
        if (std::isalpha(c)) {
            c = std::tolower(c);
            freq[c - 'a']++;
            totalLetters++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (totalLetters > 0) {
            freq[i] = (freq[i] / totalLetters) * 100.0; // % частота
        }
    }
}

// Функція для обчислення оцінки частотного відхилення
double calculateScore(double freq[26]) {
    double score = 0.0;
    for (int i = 0; i < 26; i++) {
        score += std::pow(freq[i] - englishFrequency[i], 2);
    }
    return score;
}

// Функція для декодування з використанням зсуву
void decodeWithShift(const std::string& encodedText, std::string& decodedText, int shift) {
    decodedText = encodedText; // Створюємо копію закодованого тексту

    for (size_t i = 0; i < encodedText.length(); ++i) {
        char c = encodedText[i];
        if (std::isalpha(c)) {
            char base = std::islower(c) ? 'a' : 'A';
            decodedText[i] = (c - base - shift + 26) % 26 + base; // Застосування зсуву
        }
    }
}

int main() {
    std::string encodedMessage;
    std::getline(std::cin, encodedMessage); // Зчитування закодованого повідомлення

    std::string bestDecodedMessage;
    double bestScore = std::numeric_limits<double>::max();
    double freq[26];

    // Перебір всіх можливих зсувів від 0 до 25
    for (int shift = 0; shift < 26; ++shift) {
        std::string decodedMessage;
        decodeWithShift(encodedMessage, decodedMessage, shift);

        // Обчислюємо частоти символів
        calculateFrequency(decodedMessage, freq);

        // Обчислюємо оцінку частотного відхилення
        double score = calculateScore(freq);

        // Зберігаємо результат з найменшою оцінкою
        if (score < bestScore) {
            bestScore = score;
            bestDecodedMessage = decodedMessage;
        }
    }

    // Виведення найкращого розшифрованого повідомлення
    std::cout << bestDecodedMessage << std::endl;

    return 0;
}
