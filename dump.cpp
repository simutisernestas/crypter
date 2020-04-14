int old_main()
{
    //    CryptoPP::byte testKey = *generate_key();
    //    std::cout << sizeof(testKey) << '\n';
    //    list_dir_recursive((char *) "/home/ernestas/Arduino");

    CryptoPP::AutoSeededRandomPool rnd;

    // Generate a random key
    CryptoPP::SecByteBlock key(nullptr, CryptoPP::AES::DEFAULT_KEYLENGTH);
    rnd.GenerateBlock(key, key.size());

    // Generate a random IV
    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    rnd.GenerateBlock(iv, iv.size());
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption(key, key.size(), iv);

    std::ifstream infile("/home/ernestas/stuff/CLionProjects/letscode/data.txt", std::ios::binary | std::ios::ate);
    std::ofstream outfile("/home/ernestas/stuff/CLionProjects/letscode/result.txt", std::ios::binary | std::ios::ate);

    std::streamsize full_size = infile.tellg();
    infile.seekg(0, std::ios::beg);
    std::streamsize size = full_size;

    //            if (encfile.gcount() < _BUFFER_SIZE) { // workaround
//                fstream encfile(file, std::ios::in | std::ios::out | std::ios::ate);
//                encfile.seekp(encfile.tellg() - encfile.gcount());
//                encfile.write(recovered.c_str(), recovered.length());
//                break;
//            }


    //    std::vector<char> buffer(size);
//    infile.read(buffer.data(), size);

    outfile.seekp(0, std::ios::beg);

    if (!infile.is_open()) {
        /* TODO: handle this case. Check, if input_file exists before. */
        std::cerr << "Failed to open" << "infile.";
    }
    if (!outfile.is_open()) {
        /* TODO: handle this case. Todo: Try/catch or check, if you have write access to the output file. */
        std::cerr << "Failed to open " << "outfile.";
    }

    infile.seekg(0, std::ios::end);
    std::streamsize full_size = infile.tellg();
    infile.seekg(0, std::ios::beg);
//    std::streamsize size = smallestDivisor((int)full_size);
    std::streamsize size = full_size;
    std::cout << full_size << '\n';
//    std::cout << desired_size << '\n';

//    size_t desired_size = 1 << 20; // 1 MB
//    size_t desired_size = 64;
    int count;

    std::vector<char> buffer(size);
    while (infile.read(buffer.data(), size)) {
//        infile.read(buffer.data(), size);
        std::cout << buffer.data() << '\n';

//        count = infile.gcount();
//        size_t messageLen = count + 1; // Todo: why +1 ?
        CryptoPP::byte plainText[size];

        if (count == size or true) {
            strcpy((char *) plainText, buffer.data());
        } else {
            // Todo: workaround for now
//            std::vector<char> end_buffer;
//            for (int i = 0; i < count; ++i)
//                end_buffer.push_back(buffer[i]);
//            strcpy((char *) plainText, end_buffer.data());
        }

//        if (count == size) {
//            cout << buffer.data() << endl;
//            continue;
//        }
//        // Todo: workaround for now
//        for (int i = 0; i < count; ++i)
//            cout << buffer[i];

// LOAD FULL FILE
//    std::vector<char> stream(std::istreambuf_iterator<char>(infile), {});
//    std::string buffer(stream.data(), stream.size());

        // Todo: do not reuse same variable ? maybe fucks up memory
        cfbEncryption.ProcessData(plainText, plainText, size);
        outfile.write((char *) plainText, size);
    }

    //    while ( getline(infile, line) )
//    string line;
//    while(getline(infile,line)) { // Todo: consider
//        cout << line.length() << endl;
//    }

    outfile.close();
    infile.close();

    buffer.clear();
    usleep(10000);

    std::ifstream encfile("/home/ernestas/stuff/CLionProjects/letscode/result.txt", std::ios::binary);
    std::ofstream decfile("/home/ernestas/stuff/CLionProjects/letscode/decrypted.txt");

    encfile.seekg(0, std::ios::end);
    int file_size = encfile.tellg();
    encfile.seekg(0, std::ios::beg);
    std::cout << file_size << '\n';
//    exit(0);
//    decfile.seekp(0, std::ios::beg);

    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cfbDecryption(key, key.size(), iv);
    while (encfile.read(buffer.data(), size)) {
//        count = encfile.gcount();
//        size_t messageLen = count + 1; // Todo: why +1 ?
        CryptoPP::byte plainText[size+1];

//        std::cout << buffer.data() << '\n';
//        std::cout << count << '\n';
//        std::cout << size << '\n';

        if (count == size or true) {
            strcpy((char *) plainText, buffer.data());
        } else {
            // Todo: workaround for now
//            std::vector<char> end_buffer;
//            for (int i = 0; i < count; ++i)
//                end_buffer.push_back(buffer[i]);
//            std::cout << end_buffer.data() << '\n';
//            std::cout << count << '\n';
//            std::cout << size << '\n';
//            strcpy((char *) plainText, end_buffer.data());
        }
//        exit(0);

        cfbDecryption.ProcessData(plainText, plainText, size);
        decfile.write((char *) plainText, size);
//        std::cout << sizeof(plainText);
//        decfile << plainText;
    }

    encfile.close();
    decfile.close();

    exit(0);

    //////////////////////////////////////////////////////////////////////////
    // Encrypt
//    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption(key, key.size(), iv);
//    cfbEncryption.ProcessData(plainText, plainText, messageLen);
//    std::cout << plainText << '\n';

    //////////////////////////////////////////////////////////////////////////
    // Decrypt
//    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cfbDecryption(key, key.size(), iv);
//    cfbDecryption.ProcessData(plainText, plainText, messageLen);
//    std::cout << plainText << '\n';

    return 0;
}

int smallestDivisor(int n);
// Function to find the smallest divisor
int smallestDivisor(int n)
{
    // if divisible by 2
    if (n % 2 == 0)
        return 2;

    // iterate from 3 to sqrt(n)
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return i;
    }

    return n;
}
//    long long div = smallestDivisor((int)full_size);
//    while (div < desired_size) {
//        div *= div;
//        std::cout << div << '\n';
//    }
//    std::cout << div << '\n';
//    std::cout << desired_size << '\n';
//    exit(0);
//    size = full_size;

void list_dir_recursive(const char *name)
{
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(name)) == NULL)
        return files.push_back(name);
//        return encrypt(name);

    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0)
            continue;
        if (strcmp(entry->d_name, "..") == 0)
            continue;

//        std::cout << entry->d_name << '\n';

        char result[strlen(name) + sizeof(char) + strlen(entry->d_name)];
        strcpy(result, name);
        strcat(result, "/");
        strcat(result, entry->d_name);

        list_dir_recursive(result);
    }

    closedir(dir);
}

bool is_directory(char *name)
{
    DIR *dir;
    if ((dir = opendir(name)) != NULL) {
        closedir(dir);
        return true;
    }

    return false;
}