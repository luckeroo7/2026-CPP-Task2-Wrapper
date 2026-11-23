#include "textdoc.h"
#include <cctype>
#include <sstream>

using namespace std;

textdoc::textdoc(string text) : text_(text) {}

string textdoc::replaceWord(const string& target, const string& replacement) const {
    if (target.empty()) return text_;
    string res = text_;
    size_t pos = 0;
    while ((pos = res.find(target, pos)) != string::npos) {
        res.replace(pos, target.length(), replacement);
        pos += replacement.length();
    }
    return res;
}

string textdoc::findPhrase(const string& phrase) const {
    if (phrase.empty()) return "Empty phrase.";
    size_t pos = text_.find(phrase);
    if (pos != string::npos) {
        return "Found at: " + to_string(pos);
    }
    return "Not found";
}

string textdoc::capitalizeWords() const {
    string res = text_;
    bool flag = true;
    for (size_t i = 0; i < res.length(); i++) {
        if (isspace(static_cast<unsigned char>(res[i]))) {
            flag = true;
        }
        else if (flag && isalpha(static_cast<unsigned char>(res[i]))) {
            res[i] = static_cast<char>(toupper(static_cast<unsigned char>(res[i])));
            flag = false;
        }
        else {
            flag = false;
        }
    }
    return res;
}

string textdoc::capitalizeSentences() const {
    string res = text_;
    bool flag = true;
    for (size_t i = 0; i < res.length(); i++) {
        if (flag && isalpha(static_cast<unsigned char>(res[i]))) {
            res[i] = static_cast<char>(toupper(static_cast<unsigned char>(res[i])));
            flag = false;
        }
        else if (res[i] == '.' || res[i] == '!' || res[i] == '?' || res[i] == '\n') {
            flag = true;
        }
    }
    return res;
}

string textdoc::numberSentences() const {
    stringstream ss(text_);
    string sentence;
    string res;
    int count = 1;

    while (getline(ss, sentence, '.')) {
        size_t start = sentence.find_first_not_of(" \t\r\n");
        if (start != string::npos) {
            res += to_string(count++) + ". " + sentence.substr(start) + "\n";
        }
    }
    return res;
}

string textdoc::getText() const {
    return text_;
}