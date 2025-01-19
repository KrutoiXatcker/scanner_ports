#ifndef _SCANIP_H_
#define _SCANIP_H_

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

// Класс Scanner отвечает за сканирование IP-адресов на открытые порты.
class Scanner {
public:
    // Устанавливает начальный порт для сканирования.
    void setStartPort(int firstPort);
    
    // Устанавливает конечный порт для сканирования.
    void setEndPort(int lastPort);
    
    // Устанавливает диапазон портов для сканирования.
    void setScannDiapozon(int firstPort, int lastPort);
    
    // Устанавливает IP-адрес для сканирования.
    void setIp(const std::string& ipAddress) { ip = ipAddress; }
    
    // Устанавливает время работы в миллисекундах.
    void setWorking_hour(int time_ms);
    
    // Сбрасывает время работы.
    void rsetWorking_hour();
    
    // Запускает процесс сканирования.
    void start();

private:
    std::string ip;         // IP-адрес для сканирования
    int startPort = 0;      // Начальный порт, инициализирован нулем
    int endPort = 10000;    // Конечный порт, по умолчанию 10000
    std::vector<std::thread> threads; // Вектор для хранения потоков

    // Метод для создания соединения с указанным IP и портом.
    // Возвращает true, если соединение успешно, и false в противном случае.
    bool createConnection(const std::string& ip, int port);

    // Флаг, указывающий, нужно ли ждать завершения всех потоков.
    bool waitForCompletion = true;
    
    // Время, выделенное на работу, в миллисекундах.
    int Working_hour;   
};

#endif // _SCANIP_H_
