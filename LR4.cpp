#include <openssl/md5.h> // Підключаємо бібліотеку OpenSSL для використання функції MD5
using namespace std;

// Функція для доповнення рядка символами '0' до заданої довжини
std::string toLength(std::string s, int length) {
  int diff = length - s.size(); // Рахуємо, скільки символів треба додати
  std::stringstream ss;
  ss << std::string(diff, '0') << s; // Створюємо новий рядок з доданими '0'
  return ss.str(); // Повертаємо результат
}

// Функція для зламу MD5-хешу методом грубої сили
std::string crack(const std::string& hash) {
  // Перебираємо всі можливі значення від 00000 до 99999
  for (int i = 0; i < 99999; i++) {
    std::string tmp = toLength(std::to_string(i), 5); // Преобразуємо число до рядка з п'яти символів
    unsigned char md5buffer[MD5_DIGEST_LENGTH]; // Буфер для зберігання MD5-хешу
    MD5((unsigned char*)tmp.data(), tmp.size(), md5buffer); // Обчислюємо MD5-хеш для рядка tmp
    char md5view[MD5_DIGEST_LENGTH * sizeof(MD5_LONG) + 1]{}; // Масив для збереження хешу у вигляді рядка
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
      sprintf(md5view + 2 * i, "%02x", md5buffer[i]); // Форматуємо MD5-хеш як рядок у шістнадцятковому форматі
    }
    std::string result(md5view); // Перетворюємо масив у рядок
    if (hash.compare(result) == 0) { // Якщо хеш збігається з переданим hash
      return tmp; // Повертаємо розшифроване значення
    }
  }
  return ""; // Якщо не вдалося знайти збіг, повертаємо порожній рядок
}
