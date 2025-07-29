#include <iostream>
#include <conio.h>    // _kbhit, _getch
#include <windows.h>  // Sleep
#include <cstdlib>    // atoi
#include <cstring>    // strcmp

void printHelp() {
    std::cout <<
        "PauseReverse v1.0\n"
        "使い方:\n"
        "  PauseReverse.exe [-t 秒] [-h | /h | -? | /? | --help]\n\n"
        "オプション:\n"
        "  -t 秒, /t 秒        指定した秒数だけ待機（デフォルトは3秒）\n"
        "  -h, /h, -?, /?, --help\n"
        "                     このヘルプを表示\n\n"
        "処理内容:\n"
        "  指定時間の間、キーが押されなければ続行します。\n"
        "  その間にキーが押されると中断します。\n";
}

int main(int argc, char* argv[]) {
    int waitSeconds = 3; // デフォルト
    bool showHelp = false;

    // 引数解析
    for (int i = 1; i < argc; ++i) {
        if (
            strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "/h") == 0 ||
            strcmp(argv[i], "-?") == 0 || strcmp(argv[i], "/?") == 0 ||
            strcmp(argv[i], "--help") == 0
            ) {
            showHelp = true;
        }
        else if ((strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "/t") == 0) && i + 1 < argc) {
            waitSeconds = std::atoi(argv[i + 1]);
            if (waitSeconds < 0) waitSeconds = 0;
            i++; // 秒数を読み飛ばす
        }
        else {
            // 不明なオプション → 無視して続行も可
        }
    }

    if (showHelp) {
        printHelp();
        return 0;
    }

    std::cout << "続行するには何もキーを押さないでください . . .（" << waitSeconds << "秒）\n";

    int elapsed = 0;
    while (elapsed < waitSeconds * 1000) {
        if (_kbhit()) {
            _getch(); // キー取得（バッファを空にする）
            std::cout << "\nキーが押されたため中断しました。\n";
            return 0;
        }
        Sleep(100); // 100ms ごとに確認
        elapsed += 100;
    }

    std::cout << "\n" << waitSeconds << "秒経過したので続行します。\n";
    return 0;
}
