#include "scanner_ports.h"
#include <iostream>
#include <string>
#include <limits> 
#include <stdexcept>

// Функция для получения целого числа от пользователя с проверкой ввода
int getIntInput(const std::string& prompt) {
    int input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail()) {
            std::cout << "Некорректный ввод. Пожалуйста, введите целое число.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
    }
}
// Функция для получения строки от пользователя
std::string getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int main() {
    Scanner scanner;
    
    try {
          // Получение IP-адреса от пользователя
         std::string ip = getStringInput("Введите IP-адрес для сканирования: ");
         scanner.setIp(ip);
         
        // Получение диапазона портов от пользователя
         int firstPort = getIntInput("Введите начальный порт: ");
         int lastPort = getIntInput("Введите конечный порт: ");
         scanner.setScannDiapozon(firstPort, lastPort);


        // Получение режима работы от пользователя
        char mode;
        while (true) {
            std::cout << "Выберите режим работы:\n";
            std::cout << "1 - Сканировать с ожиданием завершения\n";
            std::cout << "2 - Сканировать с рабочим временем\n";
            std::cout << "Выберите 1 или 2: ";
            std::cin >> mode;
              if (std::cin.fail()) {
                  std::cout << "Некорректный ввод. Пожалуйста, введите целое число.\n";
                std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              }
             else if (mode == '1' || mode == '2'){
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                 break;
                } else {
                   std::cout << "Некорректный ввод режима.\n";
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               }

        }

        if (mode == '1') {
            scanner.rsetWorking_hour();
        } else {
           int workingTime = getIntInput("Введите рабочее время (в мс): ");
             scanner.setWorking_hour(workingTime);
        }

        // Запуск сканирования
        scanner.start();
        std::cout << "Сканирование завершено.\n";


    }
     catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
