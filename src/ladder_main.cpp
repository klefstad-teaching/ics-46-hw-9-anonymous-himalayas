#include "../src/ladder.h"


void test_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    vector<string> ladder = generate_word_ladder("hit", "cog", word_list);
    // verify_word_ladder();
    print_word_ladder(ladder);
}

int main()
{
    test_word_ladder();
    return 0;
}