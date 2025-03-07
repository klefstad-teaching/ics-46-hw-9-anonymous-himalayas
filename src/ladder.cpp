#include "../src/ladder.h"


void error(std::string word1, std::string word2, std::string msg) {
    std::cout << word1 << " " << word2 << " " << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string &str2, int d) {
    int count = 0;
    for (size_t i = 0; i < str1.size(); i++) {
        if (str1[i] != str2[i]) {
            count++;
        }
    }
    return count <= d; 
}

bool is_adjacent(const std::string& word1, const std::string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<std::string> generate_word_ladder(const std::string& begin_word, const std::string& end_word, const std::set<std::string>& word_list) {

}

void load_words(std::set<std::string>& word_list, const std::string& file_name) {
    std::ifstream in(file_name);
    if (!in) {
        error("Unable to open file", file_name, "for reading");
    }
    std::string word;
    while (in >> word) {
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const std::vector<std::string>& ladder) {
    std::cout << "Word Ladder: ";
    for (const auto& word : ladder) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

void verify_word_ladder() {
    std::set<std::string> word_list;
    load_words(word_list, "words.txt");
    std::vector<std::string> ladder = generate_word_ladder("hit", "cog", word_list);
    print_word_ladder(ladder);
}
