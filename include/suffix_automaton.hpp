#pragma once

#include <cwctype>
#include <string>
#include <map>
#include <set>
#include <vector>

namespace suffix_automaton {

    const size_t kDefaultBuffer = 200'000;
    const int64_t kInvalid = -1;

    class SuffixAutomaton {

    private:

        struct Node {
            int64_t length = 0;
            int64_t link = -1;
            std::map<wint_t, int64_t> to;
            int64_t first_position;
            std::set<int64_t> occurrences;
        };

        std::vector<Node> data_ = std::vector<Node>(kDefaultBuffer);
        int64_t last_ = 0;
        int64_t size_ = 1;

        void Rehang(int64_t new_class, int64_t vertex, int64_t clone);

        void UpdateSize();

        void AddSymbol(char new_symbol);

        int64_t ReturnToLastState(int64_t vertex, int64_t current, char symbol);

        void UpdateVertex(int64_t current, int64_t new_value);

        int64_t SetNewClass(int64_t vertex, char symbol);

        void AddCloneVertex(int64_t current, char symbol, int64_t vertex, int64_t new_class);

        void FindOccurencesImpl(std::set<int64_t>& big_set, int64_t vertex, int64_t length);

    public:

        SuffixAutomaton() = default;

        explicit SuffixAutomaton(const std::string &data_string);

        void AddString(const std::string &new_string);

        int64_t CheckOccurrence(const std::string &pattern);

        std::set<int64_t> FindAllOccurrences(const std::string &pattern);
    };

}