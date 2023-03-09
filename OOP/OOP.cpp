#include <iostream>
#include <string>
#include <fstream>
#include <ranges>
#include <string_view>
#include <sstream>
#include <vector>
#include <memory>
#include <tuple>
#include <Windows.h>

#include "Dictionary.h"

namespace rv = std::ranges::views;
namespace ranges = std::ranges;

class GameSaver;

class GameObject {
public:
    virtual void render() = 0;
    virtual std::optional<std::string> serialize() {
        // do nothing by default
        return std::nullopt;
    }

    virtual ~GameObject() = default;
};

class Player : public GameObject {
public:
    void render() override {
        std::cout << hp_ << "hp\no\n|\n";
    }

    std::optional<std::string> serialize() override {
        return (std::stringstream() << "Player\n" << hp_ << '\n').str();
    }

    // deserialization constructor
    template <typename IterType>
    Player(IterType begin) {
        hp_ = *begin;
    }

    Player()
        : hp_{100}
    {}
private:
    uint16_t hp_;
};

class Door : public GameObject {
public:
    void render() override {
        if(GetKeyState('D') & 0x8000)
        {
            if (is_opened)
                close();
            else
                open();
        }
        std::cout << (is_opened ? "\n" : "---\n");
    }
    Door()
        : is_opened(false)
    {}
    void open() {
        is_opened = true;
    }
    void close() {
        is_opened = false;
    }
private:
    bool is_opened;
};

class GameSaver {
public:
    static const std::string DELIMITER;

    static std::vector<std::string> load_object_values(std::istream in) {
        std::vector<std::string> values(2);
        while (!in.eof()) {
            std::string value;
            in.getline(value, 100, '\n');

            if (value == DELIMITER)
                break;

            values.push_back(std::move(value));
        }

        return values;
    }

    GameSaver(std::string file_path)
        : file_path_(file_path)
    {
        if (object != nullptr)
            *this = GameSaver(std::move(*object));
        else
            object = this;
    }

    template <typename ContainerType>
    void save(ContainerType container) {
        std::ofstream output(file_path_);
        for (GameObject* item : container) {
            if ((std::optional<std::string> serialized_item = item->serialize()) != std::nullopt) {
                output << serialized_item << GameSaver::DELIMITER;
            }
        }
    }

    void load(std::vector<GameObject*> game_objects) {
        std::ifstream input(file_path_);
        while (!input.eof()) {
            auto object_values = load_object_values(input);

            GameObject* object;

            const std::string& type_value = object_values[0];
            const auto fields_iterator = object_values.begin()+1;

            if (type_value == "Player") {
                    object = new Player(fields_iterator);
            }

            game_objects.push_back(object);
        }
    }
private:
    static GameSaver* object;
    std::string file_path_;
};
const std::string DELIMITER = ":::<>:::";
GameSaver* GameSaver::object = nullptr;

int main()
{
    using std::unique_ptr;
    using std::make_unique;
    GameObject* d = new Door();

    std::vector<GameObject*> objects {
        new Door(),
        new Player()
    };

    for (;;) {
        for (auto object : objects) {
            object->render();
        }

        Sleep(1000);
        system("cls");
    }
}




int ex() {
    std::fstream file("../../dict.txt", std::ios::out);

    if (file.bad())
        return 1;

    Dictionary dictionary({{"forest", "place with trees"}});

    for (const auto& [word, definition] : dictionary) {
        file << word << ":::" << definition << '\n';
    }

    file.close();
    file = std::fstream("../../dict.txt", std::ios::in);

//    for (const auto& line : ranges::istream_view<std::string>(file)
//                            | rv::split("\n")
//            ) {
//        std::cout << ;
//    }
}