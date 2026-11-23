#include <iostream>
#include <any>
#include <memory>
#include <map>
#include <string>

#include "placeholder.h"
#include "textdoc.h"
#include "wrapper.h"
#include "engine.h"

using namespace std;

string getParam(const map<string, any>& args, const string& key) {
    auto it = args.find(key);
    if (it != args.end()) {
        const string* val = any_cast<string>(&it->second);
        if (val) {
            return *val;
        }
    }
    return "";
}

int main() {
    cout << "Hello Wrapper!\n";
    cout << "Hello Engine!\n";
    InitialArchitecturePlaceholder::projectInitialized();

    textdoc doc("hello world. this is a test document. it works fine.");
    Engine engine;

    auto replaceW = make_shared<Wrapper<textdoc>>(
        &doc,
        [](textdoc* d, const map<string, any>& args) {
            return d->replaceWord(getParam(args, "target"), getParam(args, "replacement"));
        },
        map<string, any>{{"target", string("world")}, { "replacement", string("C++") }}
    );
    engine.register_command("replace_word", replaceW);

    auto findW = make_shared<Wrapper<textdoc>>(
        &doc,
        [](textdoc* d, const map<string, any>& args) {
            return d->findPhrase(getParam(args, "phrase"));
        },
        map<string, any>{{"phrase", string("test")}}
    );
    engine.register_command("find_phrase", findW);

    auto capWordsW = make_shared<Wrapper<textdoc>>(
        &doc,
        [](textdoc* d, const map<string, any>&) { return d->capitalizeWords(); }
    );
    engine.register_command("capitalize_words", capWordsW);

    auto capSentW = make_shared<Wrapper<textdoc>>(
        &doc,
        [](textdoc* d, const map<string, any>&) { return d->capitalizeSentences(); }
    );
    engine.register_command("capitalize_sentences", capSentW);

    auto numW = make_shared<Wrapper<textdoc>>(
        &doc,
        [](textdoc* d, const map<string, any>&) { return d->numberSentences(); }
    );
    engine.register_command("number_sentences", numW);

    cout << "\nOriginal:\n" << doc.getText() << "\n\n";

    cout << "Replace default:\n" << engine.execute("replace_word") << "\n\n";

    map<string, any> customArgs;
    customArgs["target"] = string("test");
    customArgs["replacement"] = string("example");
    cout << "Replace custom:\n" << engine.execute("replace_word", customArgs) << "\n\n";

    cout << "Find phrase:\n" << engine.execute("find_phrase") << "\n\n";
    cout << "Capitalize words:\n" << engine.execute("capitalize_words") << "\n\n";
    cout << "Capitalize sentences:\n" << engine.execute("capitalize_sentences") << "\n\n";
    cout << "Number sentences:\n" << engine.execute("number_sentences") << "\n";

    return 0;
}