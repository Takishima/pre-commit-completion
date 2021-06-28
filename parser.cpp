#include <c4/fs/fs.hpp>
#include <ryml.hpp>
#include <ryml_std.hpp>

#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

auto load(std::string_view file)
{
    std::vector<char> src;
    c4::fs::file_get_contents(file.data(), &src);
    if (src.back() != '\0') {
        src.push_back('\0');
    }

    return src;
}

template <typename node_t>
void parse_repos(const node_t& repos)
{
    for (auto repo: repos) {
        if (repo.has_child("hooks")) {
            for (auto hook: repo["hooks"]) {
                if (hook.has_child("id")) {
                    std::cout << hook["id"].val() << '\n';
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Missing argument: path-to-yaml-file\n";
        return 1;
    }

    const auto src = load(argv[1]);  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

    const auto srcview = c4::to_csubstr(src.data());

    ryml::Tree tree = ryml::parse(srcview);

    for (auto node: tree.rootref()) {
        if (node.is_doc()) {
            if (node.is_map() && node.has_child("repos")) {
                parse_repos(node["repos"]);
            }
        }
        else if (node.has_key() && node.key() == "repos") {
            parse_repos(node);
        }
    }
    return 0;
}
