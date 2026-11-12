#include "TreeHtml.h"
#include <fstream>

using namespace std;

void treeHtml::add_node(queue<node*>& nodes, node*& temp, node* child, bool is_left) {
    if (child) {
        nodes.push(child);
        out << temp->index << "[\"" << temp->value << "\"]---" << child->index << "[\"" << child->value << "\"]\n";
    }
    else {
        unsigned idx = is_left ? temp->index * 2 : temp->index * 2 + 1;
        out << temp->index << "[\"" << temp->value << "\"]~~~" << idx << ":::hidden\n";
    }
}

treeHtml::treeHtml(string file, string title)
    : file(file.empty() ? "tree.html" : file), title(title) {}

void treeHtml::push(const tree& instance, const string& description) {
    out << "<div class=\"tree\">\n";
    if (!description.empty()) out << "<span>" << description << "</span>\n";
    if (!instance.head()) return;

    out << "<div class=\"mermaid\" align=\"center\">graph TD;\n";
    queue<node*> nodes;
    nodes.push(instance.head());
    while (!nodes.empty()) {
        node* temp = nodes.front();
        nodes.pop();
        add_node(nodes, temp, temp->left.get(), true);
        add_node(nodes, temp, temp->right.get(), false);
    }
    out << "classDef hidden display: none;</div>\n</div>\n";
}

bool treeHtml::save() const {
    ofstream f(file);
    if (!f.is_open()) return false;

    f << "<!DOCTYPE html>\n"
    "<html lang=\"ru\">\n"
    "<head>\n"
    "<meta charset=\"UTF-8\">\n"
    "<title>" << title << "</title>\n"
    "<script type=\"module\">\n"
    "import mermaid from "
    "\"https://cdn.jsdelivr.net/npm/mermaid@10/dist/mermaid.esm.min.mjs\";\n"
    "mermaid.initialize({startOnLoad:true, flowchart:{useMaxWidth:false, curve:'linear', nodeSpacing:30, rankSpacing:30}});\n"
    "</script>\n"
    "<style>\n"
    "body { display: flex; flex-wrap: wrap; gap: 20px; background: #212121; color: white; }\n"
    ".tree { display: flex; flex-direction: column; background: #333; padding: 10px; border-radius: 10px; width: min-content; height: min-content; }\n"
    ".mermaid svg path {  stroke: white !important; }\n"
    ".mermaid .node rect { fill: #212121 !important; stroke: white !important; }\n"
    ".mermaid .nodeLabel { color: white !important; }\n"
    "span { text-align: center; margin-bottom: 5px; }\n"
    "</style>\n"
    "</head>\n<body>\n";
    f << out.str();
    f << "\n</body>\n</html>\n";

    return true;
}