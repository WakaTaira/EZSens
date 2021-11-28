# 標準入出力時に使用する色コード等
class Pycolor:
    BLACK = "\033[30m"
    RED = "\033[31m"
    GREEN = "\033[32m"
    YELLOW = "\033[33m"
    BLUE = "\033[34m"
    PURPLE = "\033[35m"
    CYAN = "\033[36m"
    WHITE = "\033[37m"
    RETURN = "\033[07m"  # 反転
    ACCENT = "\033[01m"  # 強調
    FLASH = "\033[05m"  # 点滅
    RED_FLASH = "\033[05;41m"  # 赤背景+点滅
    END = "\033[0m"
# 使用可能な入力値の最低条件の指定


def is_valid_num(s):
    if not isinstance(s, list):
        s = [s]
    for item in s:
        if not (item.replace(",", "").replace(".", "").isnumeric() and item.count(".") < 2 and float(item) > 0):
            return 0
    return 1


# TODO: できればGetsクラスのメソッドから読み込んだ時にもう少しコンパクトになるよう修正
# コマンド群
class Commands:
    def read_if_command(self, input):
        if input.startswith("!"):
            if input[1] == "q" and len(input) == 2:
                return self.quit()
            elif input[1] == "r" and len(input) == 2:
                return self.restart()
            else:
                return self.notCommand(input)
        else:
            return None

    # 終了コマンド
    def quit(self):
        exit("\n計算終わり.")

    # リスタートコマンド
    def restart(self):
        print("\n計算やり直し\n")
        return 0

    # コマンド一覧からはじかれたとき用
    def notCommand(self, input):
        print('\n"' + input + '" はコマンドじゃない\n')
        return 1
