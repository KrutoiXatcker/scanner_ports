#include "scanner_ports.h"

// Запускает сканирование портов.
void Scanner::start() {
    threads.reserve(endPort - startPort + 1); // Резервируем место для потоков.
    
    // Создаем и запускаем потоки для каждого порта в диапазоне.
    for (int port = startPort; port <= endPort; ++port) {
        threads.emplace_back([this, port]() { // Захватываем указатель и порт.
            if (createConnection(ip, port)) {  // Проверяем соединение.
                std::cout << "Port " << port << " is open.\n";
            }
        });
    }
    
    // Ожидаем завершения потоков или устанавливаем рабочее время.
    if (waitForCompletion) {
        for (auto& thread : threads) { // Ожидаем завершения всех потоков.
            thread.join(); 
        }
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(Working_hour)); // Устанавливаем рабочее время
    }

}

// Проверяет соединение с заданным IP и портом.
bool Scanner::createConnection(const std::string& ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0); // Создаем сокет.
    if (sock == -1) {
        return false; // Возвращаем false при ошибке создания сокета.
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) { // Преобразуем IP.
        close(sock);
        return false; // Возвращаем false при ошибке преобразования IP.
    }

    bool result = (connect(sock, (sockaddr*)&addr, sizeof(addr)) == 0); // Устанавливаем соединение.
    close(sock); // Закрываем сокет.
    return result; // Возвращаем результат.
}

// Устанавливает начальный порт сканирования.
void Scanner::setStartPort(int firstPort) {
     if(firstPort<0)
         throw std::invalid_argument("Некорректный диапазон начального порта: начальный порт должен быть больше нулья.");
    else if(firstPort>65535)
        throw std::invalid_argument("Некорректный диапазон начального порта: начальный порт должен быть меньше 65535.");
    else if(firstPort>endPort)
         throw std::invalid_argument("Некорректный диапазон портов: начальный порт должен быть меньше конечного.");
    else
    startPort = firstPort; // Устанавливаем начальный порт.
}

// Устанавливает конечный порт сканирования.
void Scanner::setEndPort(int lastPort) {
    if(lastPort<0)
        throw std::invalid_argument("Некорректный диапазон начального порта: начальный порт должен быть больше нулья.");
    else if(lastPort>65535)
        throw std::invalid_argument("Некорректный диапазон начального порта: начальный порт должен быть меньше 65535.");
    else if(lastPort<startPort)
         throw std::invalid_argument("Некорректный диапазон портов: начальный порт должен быть меньше конечного.");
    else
    endPort = lastPort; // Устанавливаем конечный порт.
}

// Устанавливает диапазон сканирования.
void Scanner::setScannDiapozon(int firstPort,int lastPort){
    setStartPort(firstPort);
    setEndPort(lastPort);
}

// Устанавливает рабочее время сканирования (waitForCompletion == false).
void Scanner::setWorking_hour(int time_ms){
    if(time_ms>0){
        Working_hour = time_ms;
        waitForCompletion = false;
    }
    else throw std::invalid_argument("Некорректное работчее время: Отрицательное работчее время.");
}
// Устанавливает флаг ожидания завершения потоков (waitForCompletion == true).
void Scanner::rsetWorking_hour(){
    waitForCompletion = true;
}
