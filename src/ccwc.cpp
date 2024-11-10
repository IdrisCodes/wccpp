#include <iostream>
#include <string>
#include <filesystem>
#include <cwchar>
#include <bitset>

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

#include <wctool/wctool.hpp>


namespace po = boost::program_options;




#include <cassert>
#include <iterator>
#include <string>


constexpr size_t BUFFER_SIZE{16*1024};

constexpr unsigned CountLinesIndex{0U};
constexpr unsigned CountWordsIndex{1U};
constexpr unsigned CountCharsIndex{2U};
constexpr unsigned CountBytesIndex{3U};


static void formResponseString(const wctool& wc,
                                std::bitset<4> options,
                                std::string_view filename,
                                std::string& result);

static void readFromStandardInput(std::bitset<4> options, bool printDash=false);

static void processProgramInput(int argc, char **argv,
                                std::bitset<4>& options,
                                std::vector<std::filesystem::path>& files);


static std::string globalLocaleString;

int main(int argc, char *argv[])
{
    int retvalue{0};
    std::vector<std::filesystem::path> filelist;
    std::bitset<4> options(0);

    char* locale_str = setlocale(LC_CTYPE, nullptr);
    if(locale_str)
    {
        globalLocaleString = locale_str;
    }
    else
    {
        globalLocaleString = "en_US.utf8";
    }
    
    processProgramInput(argc, argv, options, filelist);

    if(filelist.size()== 0)
    {
        readFromStandardInput(options);
        return 0;
    }

    /* Process files in list */
    for(auto& file : filelist)
    {

        if(file.string() == "-")
        {
            readFromStandardInput(options, true);
            continue;
        }

        std::string result;
        wctool wc(globalLocaleString);

        try
        {
            wc << file;
        }
        catch(...)
        {
            std::cerr << "Could not open " << file << '\n';
            retvalue = ENOENT;
            continue;
        }

        formResponseString(wc, options, file.string(), result);
        std::cout << result;
    }

    return retvalue;
}


static void readFromStandardInput(std::bitset<4> options, bool printDash)
{
    std::string result;


    /* Read from standard input */
    wctool wc(globalLocaleString);
    char buff[BUFFER_SIZE];
    while(!std::cin.eof())
    {
        std::cin.read(buff, sizeof(buff));
        auto readCount{std::cin.gcount()};
        std::string_view s(buff, readCount);
        wc << std::string_view(buff, readCount);
    }

    if(printDash)
        formResponseString(wc, options, "-", result);
    else
        formResponseString(wc, options, "", result);

    std::cout << result;
}

static void formResponseString(const wctool& wc, std::bitset<4> options, std::string_view filename, std::string& result)
{
    result += '\t';
    if(options[CountLinesIndex])
        result += std::to_string(wc.getLineCount())+ '\t';

    if(options[CountWordsIndex])
        result += std::to_string(wc.getWordCount())+ '\t';

    if(options[CountCharsIndex])
        result += std::to_string(wc.getCharCount())+ '\t';

    if(options[CountBytesIndex])
        result += std::to_string(wc.getByteCount())+ '\t';

    if(filename.length())
        result += filename;

    boost::trim_right(result);
    result += '\n';
}

static void processProgramInput(int argc, char **argv, std::bitset<4>& options, 
                                std::vector<std::filesystem::path>& files)
{

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help,h", "Display help message")
    ("bytes,c", "Count bytes in files")
    ("words,w", "Count words in files")
    ("lines,l", "Count lines in files")
    ("chars,m", "Count characters in files")
    ("inputfile", po::value<std::vector<std::string>>(), "input file");


    po::variables_map vm;
    po::positional_options_description pd;
    pd.add("inputfile", -1);

    try
    {
        auto parsed = po::command_line_parser(argc, argv)
                    .options(desc)
                    .positional(pd)
                    .run();

        po::store(parsed, vm);
    }
    catch(const boost::program_options::unknown_option& e)
    {
        std::cerr << e.what() << '\n';
    }

    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        exit(0);
    }

    options[CountBytesIndex] = vm.count("bytes") > 0;
    options[CountCharsIndex] = vm.count("chars") > 0;
    options[CountLinesIndex] = vm.count("lines") > 0;
    options[CountWordsIndex] = vm.count("words") > 0;

    /* No parameters specified, display l w c */
    if(options.none())
    {
        options[CountLinesIndex] = true;
        options[CountWordsIndex] = true;
        options[CountBytesIndex] = true;
    }


    /* Extract files to process */
    if (vm.count("inputfile"))
    {
        files.reserve(vm.count("inputfile"));
        auto files_str = vm["inputfile"].as<std::vector<std::string>>();

        for (auto path : files_str)
        {
            files.emplace_back(path);
        }
    }

}
