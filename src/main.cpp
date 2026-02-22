#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::cout << "Файловый менеджер запущен!" << std::endl;
    std::cout << "Текущая папка: " << fs::current_path() << std::endl;
    return 0;
}