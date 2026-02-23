#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void print_help() {
    std::cout << "Команды:\n";
    std::cout << "  ls            - показать содержимое текущей папки\n";
    std::cout << "  cd <папка>    - перейти в папку\n";
    std::cout << "  pwd           - показать текущий путь\n";
    std::cout << "  help          - показать эту справку\n";
    std::cout << "  exit          - выйти из программы\n";
}

void list_directory(const fs::path& path) {
    std::cout << "Содержимое " << path.string() << ":\n";
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            std::string type = entry.is_directory() ? "[DIR] " : "[FILE]";
            std::cout << "  " << type << " " << entry.path().filename().string() << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    fs::path current_path = fs::current_path();
    std::string command;

    std::cout << "Файловый менеджер (C++ версия). Введите 'help' для списка команд.\n";

    while (true) {
        std::cout << "\n[" << current_path.string() << "]$ ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        } else if (command == "help") {
            print_help();
        } else if (command == "pwd") {
            std::cout << current_path.string() << std::endl;
        } else if (command == "ls") {
            list_directory(current_path);
        } else if (command.rfind("cd ", 0) == 0) {
            std::string new_dir = command.substr(3);
            fs::path new_path = (new_dir == "..") ? current_path.parent_path() : current_path / new_dir;

            try {
                if (fs::exists(new_path) && fs::is_directory(new_path)) {
                    current_path = fs::canonical(new_path);
                } else {
                    std::cerr << "Ошибка: папка не существует" << std::endl;
                }
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
            }
        } else if (!command.empty()) {
            std::cerr << "Неизвестная команда" << std::endl;
        }
    }

    std::cout << "Работа завершена." << std::endl;
    return 0;
}