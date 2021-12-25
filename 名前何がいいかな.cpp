#include "名前何がいいかな.hpp"

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <numbers>

using namespace std;

// GAMELIST 計算可能なゲームタイトル
static const vector<string> GAMELIST = { "Apex", "R6S", "Valorant", "Splitgate", "CSGO", "Overwatch" };
// π
static const double pi = numbers::pi;


// Basic_Functionsクラスのインスタンス
bool Basic_Functions::isValidNum (string s) {
    int    count = 0;
    string s1    = s; // erase等の処理を加えるためバックアップ

    if (s1[0] == '.') { return false; }
    if (s1[0] == '0' && isdigit (s1[1])) { return false; } // 最初の0の次に数字がある場合false
    for (const auto &c : s1) {
        if (c == '.') {
            if (++count == 2) { return false; } // 小数点が二つ以上あったらfalse
        }
    }
    // 小数点を削除したs1をforeachで回してそれぞれ数値かどうか判定
    if (count > 0) { s1.erase (s1.find ('.')); }
    for (char const &c : s1) {
        if (std::isdigit (c) == 0) return false;
    }
    return stod (s) >= 0 ? true : false; // 0以上かどうかの判定
}

/* double Basic_Functions::roundIt (double x, int sig) {
    double result;
    int    dig = 1;

    if (x >= 1) {
        // 1以上の場合の処理
        while (x > 10) {
            x /= 10; // 数値が10を切るまで10で割り続ける
            dig++;   // 割った回数
        }
        / * 10を切って一桁になった数値に10^(有効桁数-1)をかけてから整数に丸める -> 指定した有効桁数を持つ整数値となる
           10^(割った回数 - 有効桁数)をかけ、もとの位に戻す -> 有効数字がとれる * /
        result = round (x * pow (10, sig - 1)) * pow (10, dig - sig);
    } else {
        // 1未満の場合の処理
        while (x <= 1) {
            x *= 10; //数値が1以上になるまで10をかけ続ける
            dig++;   // かけた回数
        }
        / * 1以上になって一桁になった数値に10^(有効桁数-1)をかけてから整数に丸める -> 指定した有効桁数を持つ整数値となる
           10^(かけた回数 +1)で割り、もとの位に戻す -> 有効数字がとれる * /
        result = round (x * pow (10, sig - 1)) / pow (10, dig + 1);
    }
    return (result);
} */

vector<string> Basic_Functions::split (string str, char del) {
    int first = 0;
    int last  = str.find_first_of (del);

    vector<string> result;
    while (first < str.size()) {
        std::string subStr (str, first, last - first);
        result.push_back (subStr);
        first = last + 1;
        last  = str.find_first_of (del, first);
        if (last == std::string::npos) { last = str.size(); }
    }
    return result;
}

int Basic_Functions::readIfCommand (string input) {
    /* 戻り値が
      0: 通常の入力を続ける
     -1: コマンド入力失敗、もう一度同じ入力
     -2: メインループの最初に戻る */
    if (input[0] == '!') {
        if (input.length() == 2) {
            switch (input[1]) {
            case 'q': system ("PAUSE"); exit (EXIT_SUCCESS); // 終了コマンドは返り値を持たずexit()で処理
            case 'r': cout << "\n計算をやりなおします . . . " << endl; return -2;
            default: cout << input << RED << " というコマンドはありません" << END << endl; return -1;
            }
        } else {
            cout << RED << "コマンドは一文字です" << END << endl;
            return -1;
        }
    }
    return 0;
}


// Getsクラスのインスタンス
Gets::Gets() {
    __gameidx = __aratio = __mdratio = __hipfov = __curdist = -1;
} // 0を扱うことがあるので-1をデフォルトの値として初期化する

int Gets::getGameTitle() {
    cout << "ゲームタイトルをリストから選んで入力 " << YELLOW << "[";
    for (const auto &c : GAMELIST) {
        cout << c;
        if (c != GAMELIST.back()) { cout << ", "; }
    }
    cout << "]" << CYAN << endl << "=> " << END;

    string input;
    cin >> input;

    int command = readIfCommand (input);
    if (command == -2 || command == -1) { return -1; } // 他はcaseで取るけどこれは一つ目なのでrestartも入力ミスも同じ

    for (int gameidx = 0; gameidx < GAMELIST.size(); gameidx++) {
        // strcasecmpで大文字小文字を無視してinputとGAMELISTを比較
        if (strcasecmp (input.c_str(), GAMELIST[gameidx].c_str()) == 0) {
            // hipfov, aratio等が固定のゲームは先に代入
            if (strcasecmp (input.c_str(), GAMELIST[2].c_str()) == 0) { // Valorant
                __hipfov = 103;
                __aratio = 16 / 9;
            } else if (strcasecmp (input.c_str(), GAMELIST[4].c_str()) == 0) { // CSGO
                __hipfov = 90;
            } else if (strcasecmp (input.c_str(), GAMELIST[5].c_str()) == 0) { // Overwatch
                __aratio = 16 / 9;
            }
            return (int)gameidx; // 要素番号を返す
        }
    }
    cout << RED << "\"" << input << "\"" << ACCENT << " はリストにありません" << END << endl;
    return -1;
}

double Gets::getAspectRatio() {
    cout << "アスペクト比を入力 " << YELLOW << "(horizontal:vertical)" << CYAN << endl << "=> " << END;

    string input;
    cin >> input;

    int command = readIfCommand (input);
    switch (command) {
    case -2: return -2; break;
    case -1: return -1; break;
    }

    int count = 0;

    for (const auto &caratio : input) {
        if (caratio == ':') {
            // ":"が二個以上ならデフォルトを返す
            if (++count == 2) {
                cout << RED << ACCENT << "\":\"は一つだけ入力してください" << END << endl;
                return -1;
            }
        }
    }

    // ":"がない場合も同様
    if (count == 0) {
        cout << RED << ACCENT << "h:v の形にしてください" << END << endl;
        return -1;
    }

    vector<string> vinput = split (input, ':'); // split関数でhとvを分ける
    // 0以上の有効な数値ならh/vしたdoubleを返す
    if (isValidNum (vinput[0]) && isValidNum (vinput[1])) {
        double hori = stod (vinput[0]);
        double vert = stod (vinput[1]);
        if (hori > 0 && vert > 0) {
            double aratio = hori / vert;
            return aratio;
        }
    }
    cout << RED << ACCENT << "正しい数値を入力してください" << END << endl;
    return -1;
}

double Gets::getMonitorDistance() {
    cout << "0から1の割合で水平Monitor Distanceを入力" << CYAN << "\n=> " << END;

    string input;
    cin >> input;

    int command = readIfCommand (input);
    switch (command) {
    case -2: return -2; break;
    case -1: return -1; break;
    }

    if (isValidNum (input) && stod (input) <= 1) {
        double mdratio = stod (input);
        if (mdratio == 0) { mdratio = 0.0000000000000000000000000000001; } // 0を無限小っぽい数に
        return mdratio;
    } else {
        cout << RED << ACCENT << "0から1の数値を入力してください" << END << endl;
    }
    return -1;
}

double Gets::getHipfireFOV() {
    cout << "ゲーム内設定のFOVを入力 " << YELLOW << "(Apexだけはcl_fovscaleで)" << CYAN << "\n=> " << END;

    string input;
    cin >> input;

    int command = readIfCommand (input);
    switch (command) {
    case -2: return -2; break;
    case -1: return -1; break;
    }

    // gameidx毎に範囲を定めて判定
    if (isValidNum (input)) {
        double hipfov = stod (input);
        if (__gameidx == 0 && hipfov < 2 && hipfov > 0) { // Apex
            return 70 * hipfov;
        } else if (__gameidx == 1 && hipfov <= 90 && hipfov >= 60) { // R6S
            return hipfov;
        } else if (__gameidx == 3 && hipfov < 180 && hipfov > 0) { // Splitgate
            return hipfov;
        } else if (__gameidx == 5 && hipfov <= 103 && hipfov >= 80) { // Overwatch
            return hipfov;
        }
    }
    cout << RED << ACCENT << "正しい数値を入力してください" << END << endl;
    return -1;
}

double Gets::getCurrentDistance() {
    cout << "360°振り向き[cm]を入力" << CYAN << "\n=> " << END;

    string input;
    cin >> input;

    int command = readIfCommand (input);
    switch (command) {
    case -2: return -2; break;
    case -1: return -1; break;
    }

    if (isValidNum (input) && stod (input) > 0) { return stod (input); }
    cout << RED << ACCENT << "正しい数値を入力してください" << END << endl;
    return -1;
}

tuple<int, double, double, double, double> Gets::getInput() {
    /* -1を空の値として、空なら取得、入力が無効でまた-1が返ってきたらcontinue
       continueしてもそれまでの値は取得済みなのでその入力から再開
       restartで-2が返ってきた場合は、取得しようとしていた値以前の値を空にしてcontinue */
    while (true) {
        if (__gameidx == -1) {
            __gameidx = getGameTitle();
            if (__gameidx == -1) { continue; } // 最初はrestartでも-1しか返さない
        }
        if (__aratio == -1) {
            __aratio = getAspectRatio();
            if (__aratio == -2) {
                __gameidx = __aratio = -1;
                continue;
            } else if (__aratio == -1) {
                continue;
            }
        }
        if (__mdratio == -1) {
            __mdratio = getMonitorDistance();
            if (__mdratio == -2) {
                __gameidx = __aratio = __mdratio = -1;
                continue;
            } else if (__mdratio == -1) {
                continue;
            }
        }
        if (__hipfov == -1) {
            __hipfov = getHipfireFOV();
            if (__hipfov == -2) {
                __gameidx = __aratio = __mdratio = __hipfov = -1;
                continue;
            } else if (__hipfov == -1) {
                continue;
            }
        }
        if (__curdist == -1) {
            __curdist = getCurrentDistance();
            if (__curdist == -2) {
                __gameidx = __aratio = __mdratio = __hipfov = __curdist = -1;
                continue;
            } else if (__curdist == -1) {
                continue;
            }
        }
        return { __gameidx, __aratio, __mdratio, __hipfov, __curdist };
    }
}


// Calculationクラスのインスタンス
Calculation::Calculation (int gameidx, double aratio, double mdratio, double hipfov, double curdist) {
    __gameidx = gameidx;
    __aratio  = aratio;
    __mdratio = mdratio;
    __hipfov  = hipfov;
    __curdist = curdist;
}

void Calculation::VtoH() {
    for (auto &fwoElement : __fovWithOptics) {
        fwoElement.second = 2 * atan (tan (fwoElement.second * __hipfov / 2 * pi / 180) * __aratio) / pi * 180;
    }
    __hipfov = 2 * atan (tan (__hipfov / 2 * pi / 180) * __aratio) / pi * 180;
    cout << __hipfov << endl;
}

void Calculation::Hdeg4to3Fix() {
    for (auto &fwoElement : __fovWithOptics) {
        fwoElement.second = 2 * atan (tan (fwoElement.second * __hipfov / 2 * pi / 180) * __aratio * 3 / 4) / pi * 180;
    }
    __hipfov = 2 * atan (tan (__hipfov / 2 * pi / 180) * __aratio * 3 / 4) / pi * 180;
    cout << __hipfov << endl;
}

void Calculation::calcApex() {
    Hdeg4to3Fix();
    for (int i = 0; i < __fovWithOptics.size(); i++) {
        __alpha0 = atan (__mdratio * tan (__hipfov / 2 * pi / 180));
        __alpha1 = atan (__mdratio * tan (__fovWithOptics[i].second / 2 * pi / 180));

        __distanceWithOptics[i].second = __curdist * __alpha0 / __alpha1;
    }
}

void Calculation::calcR6S() {
    VtoH();
    for (int i = 0; i < __fovWithOptics.size(); i++) {
        __alpha0 = atan (__mdratio * tan (__hipfov / 2 * pi / 180));
        __alpha1 = atan (__mdratio * tan (__fovWithOptics[i].second / 2 * pi / 180));

        __distanceWithOptics[i].second = __curdist * __alpha0 / __alpha1;
    }
}

void Calculation::calcValorant() {
    for (int i = 0; i < __fovWithOptics.size(); i++) {
        __alpha0 = atan (__mdratio * tan (__hipfov / 2 * pi / 180));
        __alpha1 = atan (__mdratio * tan (__hipfov / __fovWithOptics[i].second / 2 * pi / 180));

        __distanceWithOptics[i].second = __curdist * __alpha0 / __alpha1;
    }
}

void Calculation::calcSplitgate() {
    if (__aratio != 16.0 / 9.0) {
        for (auto &fwoElement : __fovWithOptics) {
            fwoElement.second = 2 * atan (tan (fwoElement.second / 2 * pi / 180) * __aratio * 9 / 16) / pi * 180;
        }
    }
    __hipfov = 2 * atan (tan (__hipfov / 2 * pi / 180) * __aratio * 3 / 4) / pi * 180;
    for (int i = 0; i < __fovWithOptics.size(); i++) {
        __alpha0 = atan (__mdratio * tan (__hipfov / 2 * pi / 180));
        __alpha1 = atan (__mdratio * tan (__fovWithOptics[i].second / 2 * pi / 180));

        __distanceWithOptics[i].second = __curdist * __alpha0 / __alpha1;
    }
}

void Calculation::calcCSGO() {
    if (__aratio != 4.0 / 3.0) { Hdeg4to3Fix(); }
    for (int i = 0; i < __fovWithOptics.size(); i++) {
        __alpha0 = atan (__mdratio * tan (__hipfov / 2 * pi / 180));
        __alpha1 = atan (__mdratio * tan (__fovWithOptics[i].second / 2 * pi / 180));

        __distanceWithOptics[i].second = __curdist * __alpha0 / __alpha1;
    }
}

void Calculation::calcOverwatch() {
    for (int i = 0; i < __fovWithOptics.size(); i++) {
        __fovWithOptics[i].second =
          2 * atan (__mdratio * tan (__fovWithOptics[i].second / 2 * pi / 180) * __aratio) / pi * 180;
        __alpha0 = atan (__mdratio * tan (__hipfov / 2 * pi / 180));
        __alpha1 = atan (__mdratio * tan (__fovWithOptics[i].second / 2 * pi / 180));

        __distanceWithOptics[i].second = __curdist * __alpha0 / __alpha1;
    }
}

void Calculation::doCalc() {
    // ゲームタイトル毎に__fovWithOptics, __distanceWithOpticsの中身を決定し、計算する
    switch (__gameidx) {
    case 0: // Apex
        __fovWithOptics.push_back ({ "1x, Pistol, SMG, SG", 6.0 / 7.0 });
        __fovWithOptics.push_back ({ "AR, LMG Sniper", 11.0 / 14.0 });
        __fovWithOptics.push_back ({ "2x", 1102591.0 / 2000000.0 });
        __fovWithOptics.push_back ({ "3x", 26275563.0 / 70000000.0 });
        __fovWithOptics.push_back ({ "4x", 992913.0 / 3500000.0 });
        __fovWithOptics.push_back ({ "6x", 1901823.0 / 10000000.0 });
        __fovWithOptics.push_back ({ "8x", 1.0 / 7.0 });
        __fovWithOptics.push_back ({ "10x", 1001339.0 / 8750000.0 });

        __distanceWithOptics.push_back ({ "1x, Pistol, SMG, SG", 0.0 });
        __distanceWithOptics.push_back ({ "AR, LMG Sniper", 0.0 });
        __distanceWithOptics.push_back ({ "2x", 0.0 });
        __distanceWithOptics.push_back ({ "3x", 0.0 });
        __distanceWithOptics.push_back ({ "4x", 0.0 });
        __distanceWithOptics.push_back ({ "6x", 0.0 });
        __distanceWithOptics.push_back ({ "8x", 0.0 });
        __distanceWithOptics.push_back ({ "10x", 0.0 });
        calcApex();
        break;
    case 1: // R6S
        __fovWithOptics.push_back ({ "1x", 0.9 });
        __fovWithOptics.push_back ({ "1.5x", 0.59 });
        __fovWithOptics.push_back ({ "2x", 0.49 });
        __fovWithOptics.push_back ({ "2.5x", 0.42 });
        __fovWithOptics.push_back ({ "3x", 0.35 });
        __fovWithOptics.push_back ({ "4x", 0.3 });
        __fovWithOptics.push_back ({ "5x", 0.22 });
        __fovWithOptics.push_back ({ "12x", 0.092 });

        __distanceWithOptics.push_back ({ "1x", 0.0 });
        __distanceWithOptics.push_back ({ "1.5x", 0.0 });
        __distanceWithOptics.push_back ({ "2x", 0.0 });
        __distanceWithOptics.push_back ({ "2.5x", 0.0 });
        __distanceWithOptics.push_back ({ "3x", 0.0 });
        __distanceWithOptics.push_back ({ "4x", 0.0 });
        __distanceWithOptics.push_back ({ "5x", 0.0 });
        __distanceWithOptics.push_back ({ "12x", 0.0 });
        calcR6S();
        break;
    case 2: // Valorant
        __fovWithOptics.push_back ({ "1.15x - Ares, Odin, Spectre, Stinger", 1.15 });
        __fovWithOptics.push_back ({ "1.25x - Bulldog, Phantom, Vandal", 1.25 });
        __fovWithOptics.push_back ({ "1.50x - Guardian, Headhunter", 1.5 });
        __fovWithOptics.push_back ({ "2.50x - Operator, Tour de Force", 2.5 });
        __fovWithOptics.push_back ({ "3.50x - Marshal", 3.5 });
        __fovWithOptics.push_back ({ "5x - Operator", 5.0 });

        __distanceWithOptics.push_back ({ "1.15x - Ares, Odin, Spectre, Stinger", 0.0 });
        __distanceWithOptics.push_back ({ "1.25x - Bulldog, Phantom, Vandal", 0.0 });
        __distanceWithOptics.push_back ({ "1.50x - Guardian, Headhunter", 0.0 });
        __distanceWithOptics.push_back ({ "2.50x - Operator, Tour de Force", 0.0 });
        __distanceWithOptics.push_back ({ "3.50x - Marshal", 0.0 });
        __distanceWithOptics.push_back ({ "5x - Operator", 0.0 });
        calcValorant();
        break;
    case 3: // Splitgate
        __fovWithOptics.push_back ({ "Assault Rifle, Carbine, Rocket", 55.0 });
        __fovWithOptics.push_back ({ "Battle Rifle, Railgun", 40.0 });
        __fovWithOptics.push_back ({ "Sniper Rifle", 30.0 });

        __distanceWithOptics.push_back ({ "Assault Rifle, Carbine, Rocket", 0.0 });
        __distanceWithOptics.push_back ({ "Battle Rifle, Railgun", 0.0 });
        __distanceWithOptics.push_back ({ "Sniper Rifle", 0.0 });
        calcSplitgate();
        break;
    case 4: // CSGO
        __fovWithOptics.push_back ({ "Zoomed 1: AWP, SSG 08, G3SG1, SCAR-20", 4.0 / 9.0 });
        __fovWithOptics.push_back ({ "Zoomed 2: AWP", 1.0 / 9.0 });
        __fovWithOptics.push_back ({ "Zoomed 2: SSG 08, G3SG1, SCAR-20", 15.0 / 90.0 });
        __fovWithOptics.push_back ({ "Zoomed: AUG, SG 553", 0.5 });

        __distanceWithOptics.push_back ({ "Zoomed 1: AWP, SSG 08, G3SG1", 0.0 });
        __distanceWithOptics.push_back ({ "Zoomed 2: AWP", 0.0 });
        __distanceWithOptics.push_back ({ "Zoomed 2: SSG 08, G3SG1, SCAR-20", 0.0 });
        __distanceWithOptics.push_back ({ "Zoomed: AUG, SG 553", 0.0 });
        calcCSGO();
        break;
    case 5: // Overwatch
        __fovWithOptics.push_back ({ "Ashe ADS", 40.0 });
        __fovWithOptics.push_back ({ "Widowmaker/Ana Scope", 30.0 });

        __distanceWithOptics.push_back ({ "Ashe ADS", 0.0 });
        __distanceWithOptics.push_back ({ "Widowmaker/Ana Scope", 0.0 });
        calcOverwatch();
        break;
    default: cout << "error!!" << endl; exit (EXIT_FAILURE);
    }
}

Calculation::~Calculation() {
    if (!__distanceWithOptics.empty()) {
        for (const auto &hoge : __distanceWithOptics) {
            cout << endl;
            cout << hoge.first << " は " << setprecision (10) << hoge.second << "[cm/360°]" << endl;
        }

        cout << RED << "\n振り向きからセンシへの計算は " << BLUE << "https://www.mouse-sensitivity.com" << RED
             << " を使えばヨシ！\n"
             << END << "振り向き→センシの計算方法はあんまりわかってない\n"
             << endl;
    }
}