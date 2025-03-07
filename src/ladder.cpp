#include "../src/ladder.h"

#define my_assert(e) {std::cout << #e << ((e) ? " passed": " failed") << std::endl;}

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
    /*
    function generate_word_ladder(begin_word, end_word, word_list):

    ladder_queue = queue of vector of strings

    ladder_queue.push([begin_word])

    visited = set of strings

    visited.insert(begin_word)

    while ladder_queue is not empty:

        ladder = ladder_queue.pop_front()

        last_word = last element of ladder

        for word in word_list:

            if is_adjacent(last_word, word):

                if word not in visited:

                    visited.insert(word)

                    new_ladder = copy of ladder

                    new_ladder.push_back(word)

                    if word equals end_word:

                        return new_ladder

                    ladder_queue.push(new_ladder)

    return no ladder found

end function
    */
    std::queue<std::vector<std::string>> q;
    std::map<std::string, std::string> previous;
    q.push({begin_word});
    while (!q.empty()) {
        std::vector<std::string> current = q.front();
        q.pop();
        std::string last_word = current.back();
        if (last_word == end_word) {
            std::vector<std::string> result;
            for (std::string word = end_word; word != begin_word; word = previous[word]) {
                result.push_back(word);
            }
            result.push_back(begin_word);
            reverse(result.begin(), result.end());
            return result;
        }
        for (const auto& word : word_list) {
            if (is_adjacent(last_word, word) && previous.find(word) == previous.end()) {
                previous[word] = last_word;
                std::vector<std::string> next = current;
                next.push_back(word);
                q.push(next);
            }
        }
    }
    return {};  
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
    for (const auto& word : ladder) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}