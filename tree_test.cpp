#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Tree.h"


TEST_CASE("Пустое дерево") {
    tree t;

    CHECK(t.head() == nullptr);
    CHECK(t.lookfor("anything") == -1);
    CHECK_FALSE(t.eliminate("anything"));
    CHECK(t.findMaxByLetters() == "");
    CHECK(t.findMaxByLength() == "");
    CHECK(t.findMaxByLengthOnKLevel(1) == "");
    CHECK(t.getKStage(1).empty());
}