class AutoCompleteSystem {
public:
    // Word class to store the frequency and the word itself
    class Word {
    public:
        int freq; // frequency
        string w; // word
        Word(string w_, int freq_): w(w_), freq(freq_) {}
    };
    
    // Trie Node class
    class TrieNode {
    public:
        vector<Word*> s; // list of words that match the prefix till this node
        unordered_map<char, TrieNode*> children; // map of child nodes
        TrieNode() {}
    };
    
    unordered_map<string, Word*> words; // map to store words and their frequencies
    
    // function to add a word to the Trie and update the frequency
    void add(string sentence, int times) {
        if (!words.count(sentence)) { // if the word is not in the words map
            words[sentence] = new Word(sentence, times); // create a new Word object and add it to the map
            auto w = words[sentence];
            auto cur = root;
            for (const auto c : sentence) { // iterate through each character of the sentence
                if (cur->children[c] == nullptr) // if the character is not a child of the current node
                    cur->children[c] = new TrieNode(); // create a new TrieNode and add it as a child
                cur = cur->children[c]; // move to the child node
                cur->s.push_back(w); // add the word to the list of words that match the prefix
            }
        } else ++words[sentence]->freq; // if the word is already in the words map, update its frequency
    }
    
    TrieNode *root, *cur; // create root and current pointers for the Trie
    AutoCompleteSystem(vector<string>& sentences, vector<int>& times) {
        root = new TrieNode(); // create a new root node for the Trie
        for (int i = 0; i < sentences.size(); ++i) {
            add(sentences[i], times[i]); // add each sentence to the Trie with its corresponding frequency
        }
        cur = root; // set the current pointer to the root
    }
    
    string ss; // string to store the current input
    
    // function to handle input character by character and return autocomplete suggestions
    vector<string> input(char c) {
        vector<string> res; // vector to store the autocomplete suggestions
        if (c == '#') { // if the input character is '#'
            add(ss, 1); // add the current input as a new word with frequency 1
            ss.clear(); // clear the current input string
            cur = root; // reset the current pointer to the root node
            return res; // return empty suggestions
        }
        ss += c; // add the input character to the current input string
        if (cur == nullptr) return res; // if the current pointer is null, return empty suggestions
        cur = cur->children[c]; // move the current pointer to the child node corresponding to the input character
        if (cur == nullptr) return res; // if the current pointer is null, return empty suggestions
        
        // define a custom comparison function for the priority queue based on frequency and word lexicographical order
        const auto cmp = [](const Word *a, const Word *b) {
            if (a->freq != b->freq) return a->freq > b->freq;
            return a->w < b->w;
        };
        
        priority_queue<Word*, vector<Word*>, decltype(cmp)> pq(cmp); // create a priority queue to find the top 3 suggestions
        
        for (auto t : cur->s) { // iterate through each word that matches the prefix
            pq.push(t); // add the word to the priority queue
            if (pq.size() > 3) pq.pop(); // if the priority queue size exceeds 3, remove the lowest priority word
        }
        
        while (!pq.empty()) { // loop until the priority queue is empty
            res.push_back(pq.top()->w); // add the word with highest priority to the result vector
            pq.pop(); // remove the word with highest priority from the priority queue
        }
        
        reverse(res.begin(), res.end()); // reverse the result vector to get the suggestions in descending order of priority
        
        return res; // return the autocomplete suggestions
    }
};
