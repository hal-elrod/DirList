#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
        + system_clock::now());
    return system_clock::to_time_t(sctp);
}

int main(int argc, char **argv[])
{
    if (argc < 3)
    {
        std::cout << "dirlist path outfile" << std::endl;
        return(0);
    }

    std::cout << "from " << (char *) argv[1] << " to " << (char *) argv[2] << std::endl;
    std::ofstream myfile;
    myfile.open((char*)argv[2]);

    std::string path = (char *) argv[1];
    for (const auto& entry : fs::directory_iterator(path))
    {
        std::time_t tt = to_time_t(entry.last_write_time());
        std::tm* gmt = std::gmtime(&tt);
        myfile << entry.path() << "," << entry.file_size() << "," <<
            std::put_time(gmt, "%m/%d/%Y") << std::endl;
    }
}
