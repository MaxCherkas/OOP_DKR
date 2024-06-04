#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <chrono>

// ���� Logger ��� ������� ���� �������� ����
class Logger {
private:
    std::ofstream logFile;

public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios_base::app);
        if (logFile.is_open()) {
            log("��������� ���������");
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            log("��������� ���������");
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

// ���� Vector ��� ������ � ���������
class Vector {
private:
    double x, y, z;

public:
    // ������������
    Vector() : x(0), y(0), z(0) {}
    Vector(double x, double y, double z) : x(x), y(y), z(z) {}

    // ������� �� �������
    void setX(double x) { this->x = x; }
    void setY(double y) { this->y = y; }
    void setZ(double z) { this->z = z; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // ���������� ������ �������
    double magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    // ��������� �������
    double scalarProduct(const Vector& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // ��������� �������
    Vector add(const Vector& other) const {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    // ³������� �������
    Vector subtract(const Vector& other) const {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    // �������� �� ���������
    Vector multiply(double scalar) const {
        return Vector(x * scalar, y * scalar, z * scalar);
    }

    // �������� �� �����������
    bool isCollinear(const Vector& other) const {
        double crossProductX = y * other.z - z * other.y;
        double crossProductY = z * other.x - x * other.z;
        double crossProductZ = x * other.y - y * other.x;
        return (crossProductX == 0 && crossProductY == 0 && crossProductZ == 0);
    }

    // �������� �� ��������������
    bool isOrthogonal(const Vector& other) const {
        return scalarProduct(other) == 0;
    }

    // �������������� ��������� << ��� ������ �� �������
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        os << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

    // ������������ �� �����
    std::string toString() const {
        std::ostringstream oss;
        oss << "Vector(" << x << ", " << y << ", " << z << ")";
        return oss.str();
    }

    // ����� ������� �� ����� � ������� "�����������"
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << x + 1 << " " << y + 1 << " " << z + 1 << std::endl; // ������ ���������� ������ ��������� 1
            file.close();
        }
    }
};

// ������� �������
int main() {
    Logger logger("program_log.txt");

    Vector v1(1.0, 2.0, 3.0);
    Vector v2(4.0, 5.0, 6.0);

    logger.log("�������� ������� v1 �� v2");

    // ��������� ��������
    Vector v3 = v1.add(v2);
    logger.log("��������� v1 �� v2: " + v3.toString());

    Vector v4 = v1.subtract(v2);
    logger.log("³������� v2 �� v1: " + v4.toString());

    double scalarProd = v1.scalarProduct(v2);
    logger.log("��������� ������� v1 �� v2: " + std::to_string(scalarProd));
    bool collinear = v1.isCollinear(v2);
    logger.log("v1 �� v2 � �����������: " + std::string(collinear ? "���" : "�"));

    bool orthogonal = v1.isOrthogonal(v2);
    logger.log("v1 �� v2 � ��������������: " + std::string(orthogonal ? "���" : "�"));

    v1.saveToFile("vectors.txt");
    logger.log("��������� ������ v1 �� �����");
    v2.saveToFile("vectors.txt");
    logger.log("��������� ������ v2 �� �����");

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
    std::cout << v4 << std::endl;

    return 0;
}