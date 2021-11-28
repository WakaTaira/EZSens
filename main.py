# EZSens -- Monitor Distanceに基づいて腰だめからADS振り向きを計算します

# get.py, calc.pyからクラスの取得
from get import Gets
from calc import Calculation

# main関数
while True:
    print('計算を終了したかったら "!q" を、やり直したかったら "!r" を入力')
    get = Gets()
    game, aratio, mdratio, curfov, curdist = get.Input()
    calculation = Calculation()
    calc = calculation.calc(game, aratio, mdratio, curfov, curdist)
    del calculation
    # TODO: gameの種類を増やす。
