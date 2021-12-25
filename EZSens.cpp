#include "名前何がいいかな.cpp"
int main() {
    // ループ中にクラスの実体の生成、削除をして、ループ毎に初期化を行う
    while (true) {
        Gets *get                                        = new Gets();
        auto [gameidx, aratio, mdratio, hipfov, curdist] = get->getInput();

        Calculation *calc = new Calculation (gameidx, aratio, mdratio, hipfov, curdist);
        calc->doCalc();
        delete calc;
    }
}