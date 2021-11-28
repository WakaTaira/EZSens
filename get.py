from basics import Pycolor, is_valid_num, Commands


# 入力用クラス
class Gets(Commands, Pycolor):
    # Noneで初期化
    def __init__(self):
        self.game = self.aratio = self.mdratio = self.curfov = self.curdist = None

    # ゲームタイトルの取得
    def Game(self):
        gamelist = ["Apex", "R6S", "Valorant", "Splitgate", "CSGO"]
        print("ゲームタイトルをリストから選んで入力 " + self.YELLOW + str(gamelist) + self.CYAN + "\n=> " + self.END, end="",)
        game = input()
        command = self.read_if_command(game)
        if command == 0 or command == 1:
            return -1
        for title in gamelist:
            if title.lower() == game.lower():
                if game.lower() == "valorant":
                    self.curfov = 103.0
                    self.aratio = 16 / 9
                elif game.lower() == "csgo":
                    self.curfov = 90
                return title
        else:
            print(self.RED + '"' + game + '"' + self.RED + self.ACCENT + " is not in the list" + self.END)
            return -1

    # アスペクト比の取得
    def AspectRatio(self):
        aratio = input("アスペクト比を入力 " + self.YELLOW + "(horizontal:vertical)" + self.CYAN + "\n=> " + self.END)
        command = self.read_if_command(aratio)
        if command == 0:
            self.game = None
            return -1
        elif command == 1:
            return -1
        if aratio != "":
            if (aratio[0].isdigit() and aratio[-1].isdigit() and aratio.count(":") == 1 and is_valid_num(aratio.split(":"))):
                aratio = float(aratio[: aratio.find(":")]) / float(
                    aratio[aratio.find(":") + 1:]
                )
                return aratio
        print(self.RED + self.ACCENT + "\n無効な入力です" + self.END)
        return -1

    # Monitor Distance[%]の取得
    def MDRatio(self):
        mdratio = input(
            "0から1の割合で水平Monitor Distanceを入力" + self.CYAN + "\n=> " + self.END)
        command = self.read_if_command(mdratio)
        if command == 0:
            self.game = self.aratio = None
            return -1
        elif command == 1:
            return -1
        if is_valid_num(mdratio) and float(mdratio) <= 1:
            if mdratio == 0:
                mdratio = 0.000000000000000000000000000000000001
            return float(mdratio)
        else:
            print(self.RED + self.ACCENT + "\n無効な入力です" + self.END)
            return -1

    # FOVの取得
    def CurrentFov(self, game):
        curfov = input(
            "ゲーム内設定のFOVを入力" + self.YELLOW + " (Apexだけはcl_fovscaleで)" + self.CYAN + "\n=> " + self.END)
        command = self.read_if_command(curfov)
        if command == 0:
            self.game = self.aratio = self.mdratio = None
            return -1
        elif command == 1:
            return -1
        if is_valid_num(curfov):
            if game == "Apex" and float(curfov) < 2:
                return float(curfov)
            elif game == "R6S" and float(curfov) <= 90:
                return float(curfov)
            elif game == "Splitgate" and float(curfov) < 180.0:
                return float(curfov)
        print(self.RED + self.ACCENT + "\n無効な入力です" + self.END)
        return -1

    # 360°振り向きの取得
    def CurrentDistance(self):
        curdist = input(
            "360°振り向きを入力" + self.CYAN + "\n=> " + self.END
        )
        command = self.read_if_command(curdist)
        if command == 0:
            self.game = self.aratio = self.mdratio = self.curfov = None
            return -1
        elif command == 1:
            return -1
        if is_valid_num(curdist):
            return float(curdist)
        print(self.RED + self.ACCENT + "\n無効な入力です" + self.END)
        return -1

    # 上記のメソッドを使ったInput関数
    def Input(self):
        while 1:
            """
            Noneならメソッドを実行、-1ならNoneに戻しcontinue
            restartが呼び出されればそれ以前に入力した値はすべてNoneに戻る、continue後に最初からやり直し
            正しくない値、コマンドの入力があった場合、その時入力していた値のみNoneに戻され、そこからやり直し
            """
            if self.game is None:
                self.game = self.Game()
            if self.game == -1:
                self.game = None
                continue
            if self.aratio is None:
                self.aratio = self.AspectRatio()
            if self.aratio == -1:
                self.aratio = None
                continue
            if self.mdratio is None:
                self.mdratio = self.MDRatio()
            if self.mdratio == -1:
                self.mdratio = None
                continue
            if self.curfov is None:
                self.curfov = self.CurrentFov(self.game)
            if self.curfov == -1:
                self.curfov = None
                continue
            if self.curdist is None:
                self.curdist = self.CurrentDistance()
            if self.curdist == -1:
                self.curdist = None
                continue
            return self.game, self.aratio, self.mdratio, self.curfov, self.curdist
