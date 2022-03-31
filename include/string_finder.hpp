#pragma once

#include <suffix_automaton.hpp>

namespace string_finder {

    enum StringFinderStates {
        kExit,
        kRead,
        kReload,
        kResetOffset,
        kTest,
    };

    class StringFinder {
    private:

        suffix_automaton::SuffixAutomaton automaton_;
        bool is_valid_ = false;
        std::string text_;
        size_t offset_ = 15;

        void Reload(const std::string &new_file_path);
        void PrintOccurrences(const std::string &pattern);
        void UpdateOffset(size_t new_offset);
        void Options();
        void RunTests();
        void Serve(int32_t& state);

    public:

        StringFinder() = default;
        explicit StringFinder(const std::string &file_path, size_t offset = 15);

        bool HasValidFile();
        void Greetings();
        void Goodbye();
        void Process();
    };
}
