/**
 * @author Yuncheng Li (raingomm[AT]gmail.com)
 * @version 2013/04/22
 */

#include "main.h"

using namespace std;

struct crypt_data data;
const char *salt = "00";

void crack(const char *hash);

int main(int argc, const char *argv[])
{
    string encFile("passwd.dat");
    if (argc > 1)
        encFile = string(argv[1]);

    ifstream infile(encFile.c_str());

    string encStr;
    infile >> encStr;
    infile.close();

    const char *hash = encStr.c_str();
    cout << hash << endl;

    cout << "Attempting to crack it " << endl;

    crack(hash);
    return 0;
}

bool do_check(const char *hash, const char *cur)
{
    char *enc = crypt_r(cur, salt, &data);
    if (strcmp(hash, enc) == 0)
        return true;
    return false;
}

bool do_crack(const char *hash, char *cur, int cur_depth)
{
    if (cur_depth == MAX_LEN)
        return do_check(hash, cur);

    char i = 0;
    for (i = '0'; i < '9'; i++) {
        cur[cur_depth] = i;
        if (do_crack(hash, cur, cur_depth + 1) == true)
            return true;
     }
    return false;
}

void crack(const char *hash)
{
    char cur[MAX_LEN + 1];
    memset(cur, 0, MAX_LEN + 1);

    data.initialized = 0;
    char *enc = crypt_r("TMP", salt, &data);

    if(do_crack(hash, cur, 0) == true)
        cout << "Got it: " << cur << endl;
    else
        cout << "Failed" << endl;
}
