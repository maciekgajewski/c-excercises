#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include <numeric>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

std::string humanReadableByteCount(size_t bytes) {
  const int unit = 1024;

  if (bytes < unit)
  {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << bytes << 'B';
    return ss.str();
  }

  int exp = static_cast<int>(std::log(bytes) / std::log(unit));
  auto pre = "KMGTPE"[exp-1];

  std::stringstream ss;
  ss << std::fixed << std::setprecision(1) << (bytes / std::pow(unit, exp))
      << pre << 'B';
  return ss.str();
}

size_t getDirectorySize(const boost::filesystem::path& path)
{
  using namespace boost::filesystem;

  assert(is_directory(path));
  boost::filesystem::recursive_directory_iterator dir_iterator(path);
  return std::accumulate(begin(dir_iterator), end(dir_iterator), 0,
        [](int size, const auto& it) {
          return size + (is_regular_file(it.path()) ? file_size(it.path()) : 0);
        });
}

void print(const boost::filesystem::path& path, int level, bool showDetails)
{
  using namespace boost::filesystem;

  // details
  if (showDetails) {
    std::cout << humanReadableByteCount(is_regular_file(path) ? file_size(path) : getDirectorySize(path)) << "\t";
  }

  // identation
  std::cout << std::string(level * 3, ' ');

  // file name
  std::cout << path.filename().string();
  if (is_directory(path))
    std::cout << "/";

  std::cout << std::endl;
}

void printDirectoryContents(const boost::filesystem::recursive_directory_iterator& dir_iterator, bool showDetails)
{
  for (auto it = begin(dir_iterator); it != end(dir_iterator); ++it) {
    print(it->path(), it.level(), showDetails);
  }
}

void printDirectoryContents(const boost::filesystem::directory_iterator& dir_iterator, bool showDetails)
{
  for (auto& entry : dir_iterator) {
    print(entry.path(), 0, showDetails);
  }
}

auto printDirectoryContents(const std::string& directory, bool recursive, bool showDetails)
{
  auto path = boost::filesystem::path(directory);

  recursive
      ? printDirectoryContents(boost::filesystem::recursive_directory_iterator(path), showDetails)
      : printDirectoryContents(boost::filesystem::directory_iterator(path), showDetails);
}

auto parseArguments(int argc, char** argv)
{
  namespace po = boost::program_options;

  po::options_description argsDescription("Options");
  argsDescription.add_options()
    ("help,h", "show this help message")
    ("long,l", "display additional information")
    ("tree,t", "recursively shows the content of the directory")
    ("directory", "directory to list content")
  ;

  po::positional_options_description positionalArgsDescription;
  positionalArgsDescription.add("directory", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv)
        .options(argsDescription).positional(positionalArgsDescription).run(), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << argsDescription << std::endl;
    exit(0);
  }

  return vm;
}

int main(int argc, char** argv)
{
  auto arguments = parseArguments(argc, argv);

  bool showDetails = arguments.count("long");
  bool showTree = arguments.count("tree");
  
  std::string directory;
  if (arguments.count("directory") == 1) {
    directory = arguments["directory"].as<std::string>();
  }
  else if (arguments.count("directory") == 0) {
    directory = ".";
  }
  else {
    std::cout << "More than one directory specified\n";
    return 1;
  }

  printDirectoryContents(directory, showTree, showDetails);
}
