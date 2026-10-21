/*Write a program to implement Huffman Encoding using a greedy strategy.*/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Node of Huffman Tree
struct Node {
    char ch;
    int freq;

    Node* left;
    Node* right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = nullptr;
        right = nullptr;
    }
};

// Comparator for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Generate Huffman codes
void generateCodes(Node* root,
                   string code,
                   unordered_map<char, string>& huffmanCode) {

    if (root == nullptr)
        return;

    // Leaf node
    if (root->left == nullptr &&
        root->right == nullptr) {

        huffmanCode[root->ch] = code;
        return;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Print Huffman tree codes
void printCodes(const unordered_map<char, string>& huffmanCode) {

    cout << "\nHuffman Codes:\n";

    for (auto pair : huffmanCode) {
        cout << pair.first << " : "
             << pair.second << endl;
    }
}

// Encode input string
string encode(const string& text,
              const unordered_map<char, string>& huffmanCode) {

    string encoded = "";

    for (char ch : text) {
        encoded += huffmanCode.at(ch);
    }

    return encoded;
}

int main() {

    string text;

    cout << "Enter the string: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "String cannot be empty." << endl;
        return 0;
    }

    // ---------------------------------------
    // Step 1: Calculate frequency
    // ---------------------------------------

    unordered_map<char, int> frequency;

    for (char ch : text) {
        frequency[ch]++;
    }

    cout << "\nCharacter Frequencies:\n";

    for (auto pair : frequency) {
        cout << pair.first << " : "
             << pair.second << endl;
    }

    // ---------------------------------------
    // Step 2: Create priority queue
    // ---------------------------------------

    priority_queue<Node*,
                   vector<Node*>,
                   Compare> pq;

    for (auto pair : frequency) {

        pq.push(
            new Node(pair.first, pair.second)
        );
    }

    // ---------------------------------------
    // Step 3: Build Huffman Tree
    // ---------------------------------------

    while (pq.size() > 1) {

        // Select two nodes with minimum frequency
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        // Combine them
        Node* parent = new Node(
            '\0',
            left->freq + right->freq
        );

        parent->left = left;
        parent->right = right;

        // Insert combined node
        pq.push(parent);
    }

    // Root of Huffman Tree
    Node* root = pq.top();

    // ---------------------------------------
    // Step 4: Generate Huffman Codes
    // ---------------------------------------

    unordered_map<char, string> huffmanCode;

    generateCodes(
        root,
        "",
        huffmanCode
    );

    printCodes(huffmanCode);

    // ---------------------------------------
    // Step 5: Encode the string
    // ---------------------------------------

    string encodedText =
        encode(text, huffmanCode);

    cout << "\nOriginal String: "
         << text << endl;

    cout << "Encoded String: "
         << encodedText << endl;

    cout << "\nOriginal Size: "
         << text.length() * 8
         << " bits" << endl;

    cout << "Encoded Size: "
         << encodedText.length()
         << " bits" << endl;

    return 0;
}