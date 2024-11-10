#ifndef WCTOOL_HPP_
#define WCTOOL_HPP_

#include <string_view>
#include <filesystem>
#include <fstream>
#include <exception>

class wctool final
{
private:
    size_t _lineCount{0U};
    size_t _byteCount{0U};
    size_t _charCount{0U};
    size_t _wordCount{0U};

    bool _lastCharIsSpace{true};
    std::locale _locale;


    template<typename T>
    void processWordCount(const T& str)
    {
        for(auto ch: str)
        {
            if(isspace(ch, _locale))
            {
                _lastCharIsSpace = true;
            }
            else
            {
                if(_lastCharIsSpace)
                {
                    ++_wordCount;
                }
                _lastCharIsSpace = false;
            }
        }
    }

    template<typename T>
    void processWordCountInLine(const T& str)
    {
        /* We assume that the new line character is not inserted into str.
        * So we set _lastCharIsSpace manually.
        */
        processWordCount<T>(str);
        _lastCharIsSpace = true;
    }
public:
    wctool(std::string_view locstr = std::string_view("en_US.utf8")):_locale(std::locale(locstr.data()))
    {
            std::setlocale(LC_ALL, locstr.data());
    }

    wctool& operator<< (const std::wstring_view& str)
    {
        if(str.length() != 0)
        {
            if(_lineCount == 0)
                ++_lineCount;
            
            for(auto ch : str)
            {
                if(ch == '\n')
                    ++_lineCount;
            }
        }

        processWordCount(str);
        wchar_t dest[16*1024];
        auto src = str.data();
	
        _charCount += str.length();
        _byteCount += str.size();
        return *this;
    }

    wctool& operator<< (const std::string_view& str)
    {
        

        if(str.length() != 0)
        {
            if(_lineCount == 0)
                ++_lineCount;
            
            for(auto ch : str)
            {
                if(ch == '\n')
                    ++_lineCount;
            }
        }

        processWordCount(str);
        wchar_t dest[16*1024];
        auto src = str.data();

        
        _charCount += mbstowcs(nullptr,
                       str.data(),
                       str.size());
                       
	
        //_charCount += str.length();
        _byteCount += str.size();
        return *this;
    }

    wctool& operator<< (const std::filesystem::path& path)
    {
        std::wstring str;

    
        if(std::filesystem::exists(path))
        {
            if(std::filesystem::is_directory(path))
            {
                throw std::filesystem::filesystem_error( path.string()+ " is a directory", std::error_code());
            }


            std::wifstream inputStream(path.string(), std::ios_base::in);
            

            if(! inputStream.is_open())
            {
                throw std::filesystem::filesystem_error("Cannot open " + path.string(), std::error_code());
            }

            inputStream.imbue(_locale);
            _byteCount = std::filesystem::file_size(path);
            while(std::getline(inputStream, str))
            {
                _lineCount++;
                _charCount += str.length();
                processWordCountInLine(str);
                if(!inputStream.eof())
                    _charCount++;
            }
        }
        else
        {
            throw std::filesystem::filesystem_error("File does not exist " + path.string(), std::error_code());
        }
        
        return *this;
    }
    [[nodiscard]] constexpr size_t getLineCount() const
    {
        return _lineCount;
    }
    [[nodiscard]] constexpr size_t getCharCount() const
    {
        return _charCount;
    }
    [[nodiscard]] constexpr size_t getByteCount() const
    {
        return _byteCount;
    }
    [[nodiscard]] constexpr size_t getWordCount() const
    {
        return _wordCount;
    }
};



#endif /* WCTOOL_HPP_ */
