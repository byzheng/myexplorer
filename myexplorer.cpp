
#include <iostream>
#include <shlwapi.h>

std::string replace_all(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

//    defining main with arguments
int main(int argc, char** argv)
{
    // Check argument 
    if (argc != 2) {
        std::cout << "Require single argument for path." << "\n";
        return -1;
    }

    std::string prefix = "me:///";
    std::string path = argv[1];
    // check starts with "me:///"
    if (path.rfind(prefix, 0) != 0) {
        std::cout << "Path has to start with \"me:///\"" << "\n";
        return -1;
    }

    path.erase(0, prefix.length());

    // NFS folder start with "//"
    if (path.rfind("fs1", 0) == 0) {
        path = "\\\\" + replace_all(path, "/", "\\");
        path = replace_all(path, "%7B", "{");
        path = replace_all(path, "%7D", "}");
    }

    std::cout << path << "\n";
    const char* file_path = path.c_str();
    // Open folder if it is existed
    if (PathIsDirectoryA(file_path)) {
        ShellExecuteA(NULL, "open", file_path, NULL, NULL, SW_SHOWDEFAULT);
    }
    const char* ext = PathFindExtensionA(file_path);
    // Open specific file extension
    if (strcmp(ext, ".docx") == 0 ||
        strcmp(ext, ".Rproj") == 0 ||
        strcmp(ext, ".lnk") == 0 ||
        strcmp(ext, ".rdp") == 0) {
        if (PathFileExistsA(file_path)) {
            ShellExecuteA(NULL, "open", file_path, NULL, NULL, SW_SHOWDEFAULT);
        }
    }
    return 0;
}