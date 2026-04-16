#ifndef __CPPFILE_HPP__
#define __CPPFILE_HPP__

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

namespace cppfile {

    inline const static size_t CHUNK_MAX_SIZE = 1024;

    bool write_to(const fs::path& path, const std::vector<char> &binary_data) {

        std::ofstream file(path, std::ofstream::binary);
        
        if (!file) return false;

        size_t file_size = fs::file_size(path);

        file.write(binary_data.data(), binary_data.size());
        file.close();

        return true;
    }

    /* String overload of write_to */
    bool write_to(const fs::path& path, const std::string &data) {

        std::vector<char> binary_data(data.begin(), data.end());
        return write_to(path, binary_data);
    }

    /* Reads data as binary */
    bool read_from(const fs::path& path, std::vector<char> &binary_data) {
        
        std::ifstream file(path, std::ifstream::binary | std::ifstream::ate);
        
        if (!file) return false;

        size_t file_size = fs::file_size(path);
        binary_data.resize(file_size);

        file.seekg(0, std::ifstream::beg);
        file.read(binary_data.data(), file_size);

        file.close();

        return true;
    }

    /* String overload of read_from */
    bool read_from(const fs::path& path, std::string &data) {
        std::vector<char> binary_data;
        if (!read_from(path, binary_data)) {
            return false;
        }
        data.assign(binary_data.begin(), binary_data.end());
        return true;
    }

    bool move_to(const fs::path& from, const fs::path& to) {
        fs::path origin = from;
        fs::path destiny = to;
        try {
            fs::rename(from, to);
            return true;
        } catch (const std::exception &e) {
            std::cerr << "error at move_to(): " << e.what();
            return false;
        }
    }

    bool create_dir(const fs::path& path) {
        try {
            fs::create_directory(path);
            return true;
        } catch (const std::exception &e) {
            std::cerr << "error at create_dir(): " << e.what();
            return false;
        }
    }

    bool exists(const fs::path& path) {
        return fs::exists(path);
    }


    bool create_dirs(const fs::path& path) {
        try {
            fs::create_directories(path);
            return true;
        } catch (const std::exception &e) {
            std::cerr << "error at create_dir(): " << e.what();
            return false;
        }
    }
    
    std::vector<fs::path> get_path_tree_from(const fs::path &path) {
        std::vector<fs::path> result;
        
        for (auto entry : fs::recursive_directory_iterator(path)) {
            if (entry.is_directory()) {
                continue;
            }
            else if (entry.is_regular_file()) {
                auto striped_entry = entry.path().lexically_relative(path.parent_path());
                result.push_back(striped_entry);
            }
            else {
                std::runtime_error("Unsuported entry type encountered at get_path_tree_from()");
            }
        }

        return result;
    }
}


#endif