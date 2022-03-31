#include <string_finder.hpp>

#include <iostream>

using namespace string_finder;

int main() {
    std::string path_to_file;
    StringFinder worker;
    worker.Greetings();
    while (!worker.HasValidFile()) {
        std::cin >> path_to_file;
        worker = StringFinder(path_to_file);
        if (worker.HasValidFile()) {
            break;
        }
        std::cout << "Возможно, вы желаете выйти? y/n" << std::endl;
        char answer;
        std::cin >> answer;
        if (answer == 'y') {
            worker.Goodbye();
            return 0;
        }
    }
    worker.Process();
    return 0;
}

/* int main() {
    wchar_t inquiry = '\0';
    std::wstring s, buffer;
    SuffixAutomaton automaton(s);
    while (std::wcin >> inquiry) {
        std::wcin >> s;
        for (auto sym: s) {
            buffer += std::tolower(sym);
        }
        if (inquiry == '+') {
            automaton.AddString(buffer);
        }
        if (inquiry == '?') {
            for (auto item : automaton.FindAllOccurrences(buffer)) {
                std::cout << item << ' ';
            }
            std::cout << std::endl;
        }
        buffer.clear();
    }
    return 0;
} */
