#include "writeToFile.hpp"

writeToFile::writeToFile(std::string file_name)
{
    file_ = std::ofstream (file_name);
}

writeToFile::~writeToFile()
{
    file_.close();
}

void writeToFile::write(std::string input)
{
    file_ << input.c_str() << std::endl;
}