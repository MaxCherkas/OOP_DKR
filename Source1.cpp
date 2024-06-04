#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>

// Клас Logger для ведення логів важливих подій
class Logger {
private:
    std::ofstream logFile;

public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios_base::app);
        if (logFile.is_open()) {
            log("Логування розпочато");
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            log("Логування завершено");
            logFile.close();
        }
    }

    void log(const std::string& message) {
        //std::time_t now = std::time(0);
        auto currentTime = std::chrono::system_clock::now();
        auto currentTimeEpoch = std::chrono::duration_cast<std::chrono::microseconds>(currentTime.time_since_epoch()).count();
        if (logFile.is_open()) {

            //char* dt = std::ctime(&now);
            std::cout << currentTimeEpoch << std::endl;
            logFile << "[" << currentTimeEpoch << "] " << message << std::endl;
        }
    }
};

// Клас Vector для роботи з векторами
class Vector {
private:
    double x, y, z;

public:
    // Конструктори
    Vector() : x(0), y(0), z(0) {}
    Vector(double x, double y, double z) : x(x), y(y), z(z) {}

    // Сеттери та геттери
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setZ(double z) { this->z = z; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Обчислення модуля вектора
    double magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    // Скалярний добуток
    double scalarProduct(const Vector& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Додавання векторів
    Vector add(const Vector& other) const {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    // Віднімання векторів
    Vector subtract(const Vector& other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    // Множення на константу
    Vector multiply(double scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }

    // Перевірка на колінеарність
    bool isCollinear(const Vector& other) const {
        double crossProductX = y * other.z - z * other.y;
        double crossProductY = z * other.x - x * other.z;
        double crossProductZ = x * other.y - y * other.x;
        return (crossProductX == 0 && crossProductY == 0 && crossProductZ == 0);
    }

    // Перевірка на ортогональність
    bool isOrthogonal(const Vector& other) const {
        return scalarProduct(other) == 0;
    }

    // Перевантаження оператора << для виводу на консоль
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        os << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

    // Перетворення до рядка
    std::string toString() const {
        std::ostringstream oss;
        oss << "Vector(" << x << ", " << y << ", " << z << ")";
        return oss.str();
    }

    // Запис вектора до файлу з базовим "шифруванням"
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << x + 1 << " " << y + 1 << " " << z + 1 << std::endl; // Просте шифрування шляхом додавання 1
            file.close();
        }
    }
};

// Головна функція
int main() {
    Logger logger("program_log.txt");

    Vector v1(1.0, 2.0, 3.0);
    Vector v2(4.0, 5.0, 6.0);

    logger.log("Створено вектори v1 та v2");

    // Виконання операцій
    Vector v3 = v1.add(v2);
    logger.log("Додавання v1 та v2: " + v3.toString());

    Vector v4 = v1.subtract(v2);
    logger.log("Віднімання v2 від v1: " + v4.toString());

    double scalarProd = v1.scalarProduct(v2);
    logger.log("Скалярний добуток v1 та v2: " + std::to_string(scalarProd));
    bool collinear = v1.isCollinear(v2);
    logger.log("v1 та v2 є колінеарними: " + std::string(collinear ? "так" : "ні"));

    bool orthogonal = v1.isOrthogonal(v2);
    logger.log("v1 та v2 є ортогональними: " + std::string(orthogonal ? "так" : "ні"));

    v1.saveToFile("vectors.txt");
    logger.log("Збережено вектор v1 до файлу");
    v2.saveToFile("vectors.txt");
    logger.log("Збережено вектор v2 до файлу");

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
    std::cout << v4 << std::endl;

    return 0;
}