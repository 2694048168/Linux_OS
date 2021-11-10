/**
 * @File    : file_utility.cpp
 * @Brief   : Understanding file utilities.
 * ------------------------
 * @Command : g++ -std=c++2a file_utility.cpp -lstdc++fs
 * ------------------------
 * @Author  : Wei Li
 * @Date    : 2021-11-06
*/

/** File utility
 * All of the C++ APIs described in this chapter thus far were added prior to C++17. 
 * Although C++ provided the ability to read and write a file, 
 * it didn't provide all of the other file operations that are needed to manage a filesystem, 
 * including file paths, directory management, and so on.
 * 
 * Focus on the std::filesystem additions in C++17 that address most of these shortcomings.
 * 
 * Paths:
 * A path is nothing more than a string that represents a node in a filesystem.
 * The purpose of a path is to represent the name and location of a file, 
 * which can then be used to perform an action on the file such as opening the file for reading and writing, 
 * changing the file's permissions, or even removing the file from the filesystem.
 * 
 * It should be noted that a path can represent many different types of nodes in a filesystem,
 * including files, directories, links, devices, and so on. 
 * 1. Block devices : The path refers to a POSIX-style block device such as /dev/sda
 * 2. Character devices : The path refers to a POSIX-style character device such as /dev/random
 * 3. Directories : The path refers to a regular diretory
 * 4. Fifo : The path refers to a pipe or other form of IPC
 * 5. Socket : The path refers to a POSIX socket
 * 6. Symlink : The path refers to a POSIX symlink
 * 7. Files : The path refers to a regular file
 */

#include <fstream>
#include <filesystem>
#include <iostream>

int main(int argc, char **argv)
{
    // To determine what type a path is, C++17
    std::cout << std::boolalpha;
    std::cout << std::filesystem::is_block_file("/dev/sda1") << '\n';
    std::cout << std::filesystem::is_character_file("/dev/random") << '\n';
    std::cout << std::filesystem::is_directory("/dev") << '\n';
    std::cout << std::filesystem::is_empty("/dev") << '\n';
    std::cout << std::filesystem::is_fifo("file_utility.cpp") << '\n';
    std::cout << std::filesystem::is_other("file_utility.cpp") << '\n';
    std::cout << std::filesystem::is_regular_file("file_utility.cpp") << '\n';
    std::cout << std::filesystem::is_socket("file_utility.cpp") << '\n';
    std::cout << std::filesystem::is_symlink("file_utility.cpp") << '\n';

    // To determine if a path exists, C++17 provides the exists() function
    std::cout << std::filesystem::exists("/dev") << '\n';
    std::cout << std::filesystem::exists("/dev/random") << '\n';
    std::cout << std::filesystem::exists("file_utility.cpp") << '\n';

    //  To determine this directory, C++17 provides the current_path() function
    std::cout << std::filesystem::current_path() << '\n';
    // To turn an absolute path into a relative path, use the relative() function
    auto current_path = std::filesystem::current_path();
    std::cout << std::filesystem::relative(current_path) << '\n';
    // Similarly, to turn a relative path into an absolute path, C++17 provides the canonical()
    std::cout << std::filesystem::canonical(".") << '\n';
    std::cout << std::filesystem::canonical("../chapter08") << '\n';
    // absolute() function
    std::cout << std::filesystem::absolute("../chapter08") << '\n';

    // Since there are different ways to represent
    // the same path (that is, relative, canonical, and absolute),
    // C++17 provides the equivalent() function
    auto path1 = std::filesystem::path{"."};
    auto path2 = std::filesystem::path{"../chapter08"};
    auto path3 = std::filesystem::path{"../chapter08/../chapter08"};
    auto path4 = std::filesystem::current_path();
    auto path5 = std::filesystem::current_path() / "../chapter08/";
    std::cout << "---------------------------------------" << '\n';
    std::cout << std::filesystem::equivalent(path1, path2) << '\n';
    std::cout << std::filesystem::equivalent(path1, path3) << '\n';
    std::cout << std::filesystem::equivalent(path1, path4) << '\n';
    std::cout << std::filesystem::equivalent(path1, path5) << '\n';

    // If you wish to determine if two paths are lexically equal (containing the same exact characters), use == operator() instead
    std::cout << (path1 == path2) << '\n';
    std::cout << (path1 == path3) << '\n';
    std::cout << (path1 == path4) << '\n';
    std::cout << (path1 == path5) << '\n';

    // different concatenation function for paths
    auto path_cat = std::filesystem::current_path();
    auto path_cat1 = std::filesystem::current_path();
    path_cat /= "file_utility.cpp";
    path_cat1 += "/file_utility.cpp";
    std::cout << path_cat << '\n';
    std::cout << path_cat1 << '\n';

    //  removes the filename from a path
    std::cout << "----------------------" << '\n';
    auto path_remove = std::filesystem::current_path();
    path_remove /= "file_utility.cpp";
    std::cout << path_remove << '\n';
    path_remove.remove_filename();
    std::cout << path_remove << '\n';

    std::cout << "----------------------" << '\n';
    // It is also possible to replace the filename with something else
    auto path_replace = std::filesystem::current_path();
    path_remove /= "file_utility.cpp";
    std::cout << path_replace << '\n';
    path_replace.replace_filename("test.cpp");
    std::cout << path_replace << '\n';

    // it is also possible to replace the extension
    std::cout << "----------------------" << '\n';
    auto path_replace_extension = std::filesystem::current_path();
    path_replace_extension /= "file_utility.cpp";
    std::cout << path_replace_extension << '\n';
    path_replace_extension.replace_extension("txt");
    std::cout << path_replace_extension << '\n';

    // it's possible to clear a path using the clear() function
    std::cout << "----------------------" << '\n';
    auto path_clear = std::filesystem::current_path();
    path_clear /= "file_utility.cpp";
    std::cout << path_clear << '\n';
    path_clear.clear();
    std::cout << path_clear << '\n';

    // As stated, a path consists of different parts
    // including a root name, directory, stem, and extension.
    // To dissect a path into these different components, C++17 provides some helper functions
    std::cout << "----------------------" << '\n';
    auto path_parts = std::filesystem::current_path();
    path_parts /= "file_utility.cpp";
    std::cout << path_parts.root_name() << '\n';
    std::cout << path_parts.root_directory() << '\n';
    std::cout << path_parts.root_path() << '\n';
    std::cout << path_parts.relative_path() << '\n';
    std::cout << path_parts.parent_path() << '\n';
    std::cout << path_parts.filename() << '\n';
    std::cout << path_parts.stem() << '\n';
    std::cout << path_parts.extension() << '\n';

    // To figure out which parts a path contains
    std::cout << "----------------------" << '\n';
    auto path_parts_contains = std::filesystem::current_path();
    path_parts_contains /= "file_utility.cpp";
    std::cout << path_parts_contains.empty() << '\n';
    std::cout << path_parts_contains.has_root_path() << '\n';
    std::cout << path_parts_contains.has_root_name() << '\n';
    std::cout << path_parts_contains.has_root_directory() << '\n';
    std::cout << path_parts_contains.has_relative_path() << '\n';
    std::cout << path_parts_contains.has_parent_path() << '\n';
    std::cout << path_parts_contains.has_filename() << '\n';
    std::cout << path_parts_contains.has_stem() << '\n';
    std::cout << path_parts_contains.has_extension() << '\n';
    std::cout << path_parts_contains.is_absolute() << '\n';
    std::cout << path_parts_contains.is_relative() << '\n';

    // C++17 provides different mechanisms for managing paths on a filesystem,
    // depending on the type of path you're using.
    std::cout << "----------------------" << '\n';
    auto path_mechanism = std::filesystem::current_path();
    path_mechanism /= "test";
    std::cout << std::filesystem::create_directory(path_mechanism) << '\n';
    std::cout << std::filesystem::remove(path_mechanism) << '\n';

    //  rename a path using the rename() function
    std::cout << "----------------------" << '\n';
    auto path_rename_1 = std::filesystem::current_path();
    auto path_rename_2 = std::filesystem::current_path();
    path_rename_1 /= "test1";
    path_rename_2 /= "test2";
    std::cout << std::filesystem::create_directory(path_rename_1) << '\n';
    std::filesystem::rename(path_rename_1, path_rename_2);
    std::cout << std::filesystem::remove(path_rename_1) << '\n';
    std::cout << std::filesystem::remove(path_rename_2) << '\n';

    std::cout << "----------------------" << '\n';
    // To remove a directory that is not empty, use the remove_all() function
    auto path_all = std::filesystem::current_path();
    path_all /= "test";
    std::cout << std::filesystem::create_directory(path_all) << '\n';

    std::fstream(path_all / "test1.txt", std::ios::app);
    std::fstream(path_all / "test2.txt", std::ios::app);
    std::fstream(path_all / "test3.txt", std::ios::app);
    std::cout << std::filesystem::remove_all(path_all) << '\n';

    /**
    auto path = std::experimental::filesystem::current_path();
    path /= "test";
    std::cout << std::boolalpha;
    std::cout << std::experimental::filesystem::create_directory(path) << '\n';

    std::fstream(path / "test1.txt", std::ios::app);
    std::fstream(path / "test2.txt", std::ios::app);
    std::fstream(path / "test3.txt", std::ios::app);

    for(const auto &p: std::experimental::filesystem::directory_iterator(path)) {
        std::cout << p << '\n';
    }

    std::cout << std::experimental::filesystem::remove_all(path) << '\n';
    */

    // C++17 provides a convenient function for determining 
    // the path to the temporary directory, 
    // which can be used to create temporary directories
    std::cout << std::filesystem::temp_directory_path() << '\n';
    //  POSIX systems, the temporary directory is usually '/tmp'

    return 0;
}
