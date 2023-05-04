
#include <iostream>
#include <shlwapi.h>

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