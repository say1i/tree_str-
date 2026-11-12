#include <fstream>

#include "Tree/Tree.h"
#include "Html/TreeHtml.h"
#include <iostream>
#include <string>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;
int main(int argc, char* argv[]) {
    string file;
    string title;

    po::options_description desc("Options");
    desc.add_options()
        ("file", po::value<string>(&file)->default_value("../tree.html"), "HTML file")
        ("title", po::value<string>(&title)->default_value("Бинарное Дерево"), "HTML title");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    ifstream cfg("config.cfg");
    if (cfg) {
        po::store(po::parse_config_file(cfg, desc), vm);
    }
    po::notify(vm);
    tree t;
    treeHtml th("../tree.html");

    string x;
    int v = 0;

    while (true) {
        cout << "(1) Добавление\n"
             << "(2) Удаление\n"
             << "(3) Поиск\n"
             << "(4) Строки на уровне k\n"
             << "(5) Самое большое слово по алфавиту\n"
             << "(6) Самое большое слово по длине\n"
             << "(7) Самое большое слово по длине на k-ом уровне\n"
             << "(8) Экспорт\n"
             << "(0) Выход\n";

        cout << "> ";
        cin >> v;

        if (v == 0) break;

        switch (v) {
            case 1:
                cout << "Ввод строки\n> ";
                cin >> x;
                t.push(x);
                th.push(t, "Добавление: " + x);
                t.show();
                break;
            case 2:
                cout << "Ввод строки\n> ";
                cin >> x;
                if (t.eliminate(x)) {
                    th.push(t, "Удаление: " + x);
                    t.show();
                }
                else cout << "Нечего удалять!" << endl;
                break;
            case 3: {
                cout << "Ввод строки\n> ";
                cin >> x;
                int index = t.lookfor(x);
                cout << "Результат поиска: " << (index == -1 ? "Не найдено" : to_string(index)) << endl;
                break;
            }
            case 4: {
                int k;
                cout << "Ввод уровня\n> ";
                cin >> k;
                for (node* el : t.getKStage(k)) { cout << el->value << endl; }
                break;
            }
            case 5: cout << t.findMaxByLetters() << endl; break;
            case 6: cout << t.findMaxByLength() << endl; break;
            case 7: {
                int k;
                cout << "Ввод уровня\n> ";
                cin >> k;
                cout << t.findMaxByLengthOnKLevel(k) << endl;
                break;
            }
            case 8:
                th.save();
                cout << "Экспортировано!";
                break;
            default: {
                cout << "0-0 Ничего не знаю!" << endl;
                break;
            }
        }
        cout << endl;
    }

    th.save();

    return 0;
}