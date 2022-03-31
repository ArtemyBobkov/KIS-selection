#include <suffix_automaton.hpp>

#include <string>
#include <vector>

using namespace suffix_automaton;

void SuffixAutomaton::Rehang(int64_t new_class, int64_t vertex, int64_t clone) {
    data_[clone].length = data_[vertex].length + 1;
    data_[clone].to = data_[new_class].to;
    data_[clone].link = data_[new_class].link;
    data_[clone].first_position = data_[new_class].first_position;
}

void SuffixAutomaton::UpdateSize() {
    if (size_ >= kDefaultBuffer) {
        data_.emplace_back();
    }
    ++size_;
}

int64_t SuffixAutomaton::ReturnToLastState(int64_t vertex, int64_t current, char symbol) {
    while (vertex != kInvalid && data_[vertex].to.count(symbol) == 0) {
        data_[vertex].to[symbol] = current;
        vertex = data_[vertex].link;
    }
    return vertex;
}

void SuffixAutomaton::UpdateVertex(int64_t current, int64_t new_class) {
    data_[current].link = new_class;
    last_ = current;
}

int64_t SuffixAutomaton::SetNewClass(int64_t vertex, char symbol) {
    if (data_[vertex].to.count(symbol) == 0) {
        return -1;
    } else {
        return data_[vertex].to[symbol];
    }
}

void SuffixAutomaton::AddCloneVertex(int64_t current, char symbol, int64_t vertex, int64_t new_class) {
    UpdateSize();
    int64_t clone = size_ - 1;
    Rehang(new_class, std::max(vertex, 0l), clone);
    while (vertex != -1 && data_[vertex].to[symbol] == new_class) {
        data_[vertex].to[symbol] = clone;
        vertex = data_[vertex].link;
    }
    last_ = current;
    data_[last_].link = clone;
    data_[new_class].link = clone;
}

void SuffixAutomaton::AddSymbol(char new_symbol) {
    UpdateSize();
    int64_t current = size_ - 1;
    data_[current].length = data_[last_].length + 1;
    data_[current].first_position = data_[current].length - 1;
    int64_t vertex = last_;
    vertex = ReturnToLastState(vertex, current, new_symbol);
    if (vertex == -1) {
        UpdateVertex(current, 0);
        return;
    }
    int64_t new_class = SetNewClass(vertex, new_symbol);
    if (data_[new_class].length == data_[vertex].length + 1) {
        UpdateVertex(current, new_class);
    } else {
        AddCloneVertex(current, new_symbol, vertex, new_class);
    }
}

SuffixAutomaton::SuffixAutomaton(const std::string &data_string) {
    int64_t s_size = 0;
    for (auto symbol: data_string) {
        ++s_size;
        AddSymbol(std::tolower(symbol));
    }
    for (int64_t vertex = 1; vertex < size_; ++vertex) {
        data_[data_[vertex].link].occurrences.insert(vertex);
    }
}

void SuffixAutomaton::AddString(const std::string &new_string) {
    for (auto symbol: new_string) {
        AddSymbol(std::tolower(symbol));
    }
    for (int64_t vertex = 1; vertex < size_; ++vertex) {
        data_[data_[vertex].link].occurrences.insert(vertex);
    }
}

int64_t SuffixAutomaton::CheckOccurrence(const std::string &pattern) {
    int64_t current = 0;
    for (auto symbol: pattern) {
        if (data_[current].to.count(symbol) == 0) {
            return -1;
        }
        current = data_[current].to[symbol];
    }
    return current;
}

void SuffixAutomaton::FindOccurencesImpl(std::set<int64_t>& big_set, int64_t vertex, int64_t length) {
    if (vertex != -1) {
        big_set.insert(data_[vertex].first_position - length + 1);
        for (auto index: data_[vertex].occurrences) {
            FindOccurencesImpl(big_set, index, length);
        }
    }
}

std::set<int64_t> SuffixAutomaton::FindAllOccurrences(const std::string &pattern) {
    int64_t current = CheckOccurrence(pattern);
    std::set<int64_t> answer;
    FindOccurencesImpl(answer, current, static_cast<int64_t>(pattern.size()));
    return answer;
}
