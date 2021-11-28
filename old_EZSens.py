# お好みの水平FOVで振り向きをMonitor Distanceに基づいて変換できます
# 数年前に適当に作ったやつですが別ゲーでFOVが変えられないときの感度合わせに使ってください

import math


def is_num(s):
    return s.replace(',', '').replace('.', '').replace('-', '').isnumeric()


para = 1
while(1):
    while(1):
        print()
        ratio = input('Monitor Distance入力 (0から1) => ')
        if is_num(ratio) == 0:
            print('\n入力できるのは数字')
            continue
        if float(ratio) > 1 or float(ratio) < 0:
            print('\n0から1で入力')
            continue
        else:
            ratio = float(ratio)
        if ratio == 0:
            ratio = 0.000000000000000000000000000000000001
        fov0 = input('変換前のFOV (0<fov<150) =>')
        if is_num(fov0) == 0:
            print('\n入力できるのは数字')
            continue
        if float(fov0) <= 0 or float(fov0) > 150 or is_num(fov0) == 0:
            print('\n0<fov<150で入力')
            continue
        fov0 = float(fov0)
        fov1 = input('変換後のFOV (0<fov<150) => ')
        if is_num(fov1) == 0:
            print('\n入力できるのは数字')
            continue
        if float(fov1) <= 0 or float(fov1) > 150 or is_num(fov1) == 0:
            print('\n0<fov<150で入力')
            continue
        fov1 = float(fov1)
        sens0 = input('360°振り向きを入力 => ')
        if is_num(sens0) == 0:
            print('\n入力できるのは数字')
            continue
        if float(sens0) <= 0 or is_num(sens0) == 0:
            print('\n0以上の正しい数値で入力')
            continue
        sens0 = float(sens0)
        alpha0 = math.atan(ratio * math.tan(fov0 * 0.5 * math.pi / 180))
        alpha1 = math.atan(ratio * math.tan(fov1 * 0.5 * math.pi / 180))
        sens1 = sens0 * alpha0 / alpha1
        print('\n    ' + str(sens1) + '[cm/360°] ' + str(fov1) + '[°]')
