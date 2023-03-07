#ifndef OOP_DICTIONARY_H
#define OOP_DICTIONARY_H

#include <string>
#include <map>

class Dictionary
{
    using string = std::string;
    using dict_type = std::map<string, string>;
    using iterator = dict_type::iterator;
    using const_iterator = dict_type::const_iterator;
public:
    Dictionary(std::initializer_list<dict_type::value_type> base)
            : words_(std::move(base))
    {}

    const const_iterator get(const string& word) const
    {
        return words_.find(word);
    }

    std::pair<iterator, bool> add(
            string word,
            string definition
    ) {
        return words_.insert({
                                     std::move(word),
                                     std::move(definition)
                             });
    }

    void remove(const string& word)
    {
        words_.erase(word);
    }

    const const_iterator begin() const
    {
        return words_.begin();
    }

    const const_iterator end() const
    {
        return words_.end();
    }

private:
    dict_type words_;
};

#endif //OOP_DICTIONARY_H
