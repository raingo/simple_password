/**
 * @author Yuncheng Li (raingomm[AT]gmail.com)
 * @version 2013/04/22
 */

#include "main.h"

using namespace std;

//http://stackoverflow.com/questions/1413445/read-a-password-from-stdcin
void SetStdinEcho(bool enable = true)
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode );

#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}

int main(int argc, const char *argv[])
{
    string passwd;
    while (true)
    {
        cout <<"Input your password: ";
        SetStdinEcho(true);
        cin >> passwd;
        SetStdinEcho(true);
        if (passwd.size() > MAX_LEN)
            cout << endl << "Sorry, you password is just too long ( > " << MAX_LEN << ")" << endl;
        else
            break;
    }

    struct crypt_data data;
    data.initialized = 0;
    const char *salt = "00";

    char *enc = crypt_r(passwd.c_str(), salt, &data);

    ofstream encFile("passwd.dat");
    encFile << enc;
    encFile.close();

    cout << endl << "Send the generated screte file passwd.dat to your chanlleger" << endl;
    return 0;
}
