#define BLACK     "\e[30m"
#define RED       "\e[31m"
#define GREEN     "\e[32m"
#define YELLOW    "\e[33m"
#define BLUE      "\e[34m"
#define PURPLE    "\e[35m"
#define CYAN      "\e[36m"
#define WHITE     "\e[37m"
#define RETURN    "\e[07m"    // 反転
#define ACCENT    "\e[01m"    // 強調
#define FLASH     "\e[05m"    // 点滅
#define RED_FLASH "\e[05;41m" // 赤背景 + 点滅
#define END       "\e[0m"
#include <string>
#include <tuple>
#include <vector>

// ちょくちょく使う関数まとめたやつ
class Basic_Functions {
  protected:
    bool isValidNum (std::string s); // stringがdoubleに変換可能且つ0以上かどうか判定する
    // double roundIt (double x, int sig); // 指定した桁数で変数の有効数字を丸める setprecision関数あったから使わない
    std::vector<std::string> split (std::string str, char del); // 文字列の分割 https://www.sejuku.net/blog/49378
    int readIfCommand (std::string input); // "!"で始まる入力をコマンドとして処理する
};


// 計算に必要なデータの取得用クラス
class Gets : public Basic_Functions {
  private:
    int    __gameidx; // GAMELISTのインデックス
    double __aratio, __mdratio, __hipfov,
      __curdist; // アス比, モニターディスタンス, 腰だめ視野角, 腰だめ振り向き

  public:
    Gets();
    int    getGameTitle();       // ゲームタイトルの取得(GAMELISTのインデックスの取得)
    double getAspectRatio();     // アス比の取得
    double getMonitorDistance(); // モニターディスタンスの取得
    double getHipfireFOV();      // 腰だめ視野角の取得
    double getCurrentDistance(); // 腰だめ振り向きの取得
    // 以上のメソッドをまとめて実行
    std::tuple<int, double, double, double, double> getInput();
};


// Getsクラスで得たデータをもとに計算をするクラス
class Calculation {
  private:
    std::vector<std::pair<std::string, double>> __fovWithOptics,
      __distanceWithOptics; // スコープ倍率毎のFOVと振り向き

    int    __gameidx; // GAMELISTのインデックス
    double __aratio, __mdratio, __hipfov, __curdist, __alpha0,
      __alpha1; // アス比, モニターディスタンス, 腰だめ視野角, 腰だめ振り向き, 振り向き計算の分子, 分母

    // FOV修正系
    void VtoH();
    void Hdeg4to3Fix(); // In-Game FOVが4:3のゲームのHFOV修正
    // ゲーム毎の計算
    void calcApex();
    void calcCSGO();
    void calcR6S();
    void calcOverwatch();
    void calcSplitgate();
    void calcValorant();

  public:
    Calculation (int gameidx, double aratio, double mdratio, double hipfov, double curdist);
    // ゲーム毎の計算をするメソッドを選択して実行する
    void doCalc();
    // 解放の際に計算結果を出力
    ~Calculation();
};