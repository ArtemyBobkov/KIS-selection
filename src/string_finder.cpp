#include <string_finder.hpp>

#include <fstream>
#include <iostream>

using namespace string_finder;

StringFinder::StringFinder(const std::string &file_path, size_t offset) {
    std::fstream new_stream;
    new_stream.open("../data/" + file_path, std::ios_base::in);
    if (!new_stream.is_open()) {
        is_valid_ = false;
        std::cout << "Пожалуйста, введите корректное имя файла. Данного файла не существует!" << std::endl;
        return;
    }
    std::string content( (std::istreambuf_iterator<char>(new_stream)),
                         (std::istreambuf_iterator<char>()));
    automaton_ = suffix_automaton::SuffixAutomaton(content);
    text_ = content;
    offset_ = offset;
    is_valid_ = true;
}

void StringFinder::Reload(const std::string &new_file_path) {
    *this = StringFinder(new_file_path);
}

bool StringFinder::HasValidFile() {
    return is_valid_;
}

void StringFinder::PrintOccurrences(const std::string &pattern) {
    std::set<int64_t> occurrences = automaton_.FindAllOccurrences(pattern);

    for (auto occurrence: occurrences) {
        std::cout << "Номер вхождения: " << occurrence << std::endl;
        std::cout << "...";
        int64_t left_border = std::max(occurrence - static_cast<int64_t>(offset_), 0l);
        int64_t right_border = std::min(occurrence + static_cast<int64_t>(pattern.size() + offset_),
                                        static_cast<int64_t>(text_.size()));
        for (int64_t index = left_border; index < right_border; ++index) {
            std::cout << text_[index];
        }
        std::cout << "..." << std::endl;
    }
    if (occurrences.empty()) {
        std::cout << "К сожалению, ничего по запросу \'" << pattern <<  "\' не нашлось." << std::endl;
    }
}

void StringFinder::UpdateOffset(size_t new_offset) {
    offset_ = new_offset;
}

void StringFinder::Greetings() {
    std::cout << "Добро пожаловать! Надеемся, вам понравится наша работа! :)" << std::endl;
    std::cout << "Введите, пожалуйста, имя своего рабочего файла." << std::endl;
}

void StringFinder::Options() {
    std::cout << "Выберите одно из предложенных действий:" << std::endl;
    std::cout << "0: Выход из программы;" << std::endl;
    std::cout << "1: Найти строку по подстроке;" << std::endl;
    std::cout << "2: Обновить файл для чтения;" << std::endl;
    std::cout << "3: Изменить число символов, показываемых в контексте найденных строк." << std::endl;
    std::cout << "4: Посмотреть несколько тестовых примеров;" << std::endl;
    std::cout << "5: Заново вывести номера доступных команд." << std::endl << std::endl;
    std::cout << "Затем нажмите Enter, чтобы продолжить." << std::endl;
}

void StringFinder::Goodbye() {
    std::cout << "Приятно было работать с Вами! Спасибо, что пользуетесь нашими услугами! (^・ω・^ )" << std::endl;
}

void StringFinder::RunTests() {
    std::cout << "Загрузим большой текст про Шерлока Холмса. Не бойтесь, препроцессинг может занимать какое-то время." << std::endl;
    Reload("Holmes.txt");
    std::cout << "Вхождения строчки \'lovely\' в большой текст романов про Шерлока Холмса" << std::endl;
    PrintOccurrences("lovely");
    std::cout << "Заменим файл на сонеты Шекспира:" << std::endl;
    Reload("Shakespeare.txt");
    PrintOccurrences("lovely");
    std::cout << "Изменим количество печатаемых совместно символов до двух:" << std::endl;
    UpdateOffset(2);
    PrintOccurrences("lovely");
    std::cout << "Попробуем найти слово, которого точно нет:" << std::endl;
    PrintOccurrences("punksnotdead");
    std::cout << "Ура! Всё работает!" << std::endl;
}

void StringFinder::Serve(int32_t &state) {
    std::string buffer_string;
    std::string buffer_filename;
    size_t buffer_offset;
    std::cin >> state;
    std::getline(std::cin, buffer_string);
    switch (state) {
        case kRead:
            std::getline(std::cin, buffer_string);
            PrintOccurrences(buffer_string);
            break;
        case kReload:
            std::cin >> buffer_filename;
            Reload(buffer_filename);
            break;
        case kResetOffset:
            std::cin >> buffer_offset;
            UpdateOffset(buffer_offset);
            break;
        case kTest:
            RunTests();
            break;
        case kExit:
            break;
        default:
            Options();
    }
}

void StringFinder::Process() {
    int32_t state = StringFinderStates::kRead;
    Options();
    while (state != StringFinderStates::kExit) {
        Serve(state);
    }
    Goodbye();
}
