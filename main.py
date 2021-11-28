# EZSens -- Monitor Distanceに基づいて腰だめからADS振り向きを計算します

from get import Gets
from calc import Calculation

while True:
    print('計算を終了したかったら "!q" を、やり直したかったら "!r" を入力')
    get = Gets()
    game, aratio, mdratio, curfov, curdist = get.Input()
    calculation = Calculation()
    calc = calculation.calc(game, aratio, mdratio, curfov, curdist)
    del calculation
    # TODO: gameの種類を増やす。
