import math
import sympy
from basics import Pycolor


# 計算用クラス
class Calculation(Pycolor):
    # VFOV基準系のゲームでVFOVからHFOVへの変換
    def VtoH(self, aratio, curfov):
        for key, value in self.fov_with_optics.items():
            self.fov_with_optics[key] = (2 * sympy.atan(sympy.tan(value * curfov / 2 * math.pi / 180) * aratio) / math.pi * 180)
        curfov = (2 * sympy.atan(sympy.tan(curfov * 0.5 * math.pi / 180) * aratio) / math.pi * 180)
        return curfov

    # Hdeg 4:3基準系ゲームでの変換
    def Hdeg4to3_fix(self, aratio, curfov):
        for key, value in self.fov_with_optics.items():
            self.fov_with_optics[key] = (2 * sympy.atan(sympy.tan(value * curfov / 2 * math.pi / 180) * aratio * 3 / 4) / math.pi * 180)
        curfov = (2 * sympy.atan(sympy.tan(curfov / 2 * math.pi / 180) * aratio * 3 / 4) / math.pi * 180)
        return curfov

    # シージads振り向き計算
    def R6S(self, aratio, mdratio, curfov, curdist):
        curfov = self.VtoH(aratio, curfov)
        print(curfov)
        print(self.fov_with_optics)
        for key, value in self.fov_with_optics.items():
            alpha0 = sympy.atan(mdratio * sympy.tan(curfov * 0.5 * math.pi / 180))
            alpha1 = sympy.atan(mdratio * sympy.tan(value * 0.5 * math.pi / 180))
            self.distance_with_optics[key] = curdist * alpha0 / alpha1

    # えぺads振り向き計算
    def Apex(self, aratio, mdratio, curfov, curdist):
        curfov = self.Hdeg4to3_fix(aratio, curfov)
        for key, value in self.fov_with_optics.items():
            alpha0 = sympy.atan(mdratio * sympy.tan(curfov * 0.5 * math.pi / 180))
            alpha1 = sympy.atan(mdratio * sympy.tan(value * 0.5 * math.pi / 180))
            self.distance_with_optics[key] = curdist * alpha0 / alpha1

    # Valo ads振り向き計算
    def Valorant(self, mdratio, curfov, curdist):
        for key, value in self.fov_with_optics.items():
            alpha0 = sympy.atan(mdratio * sympy.tan(curfov * 0.5 * math.pi / 180))
            alpha1 = sympy.atan(mdratio * sympy.tan(value * 0.5 * math.pi / 180))
            self.distance_with_optics[key] = curdist * alpha0 / alpha1

    def Splitgate(self, aratio, mdratio, curfov, curdist):
        for key, value in self.fov_with_optics.items():
            self.fov_with_optics[key] = (2 * sympy.atan(sympy.tan(value / 2 * math.pi / 180) * aratio * 9 / 16) / math.pi * 180)
        curfov = (2 * sympy.atan(sympy.tan(curfov / 2 * math.pi / 180) * aratio * 9 / 16) / math.pi * 180)
        for key, value in self.fov_with_optics.items():
            alpha0 = sympy.atan(mdratio * sympy.tan(curfov * 0.5 * math.pi / 180))
            alpha1 = sympy.atan(mdratio * sympy.tan(value * 0.5 * math.pi / 180))
            self.distance_with_optics[key] = curdist * alpha0 / alpha1

    def CSGO(self, aratio, mdratio, curfov, curdist):
        if aratio != 4 / 3:
            curfov = self.Hdeg4to3_fix(aratio, curfov)
        for key, value in self.fov_with_optics.items():
            alpha0 = sympy.atan(mdratio * sympy.tan(curfov * 0.5 * math.pi / 180))
            alpha1 = sympy.atan(mdratio * sympy.tan(value * 0.5 * math.pi / 180))
            self.distance_with_optics[key] = curdist * alpha0 / alpha1

    def calc(self, game, aratio, mdratio, curfov, curdist):
        if game == "R6S":
            self.fov_with_optics = {
                "1x": 0.9,
                "1.5x": 0.59,
                "2x": 0.49,
                "2.5x": 0.42,
                "3x": 0.35,
                "4x": 0.3,
                "5x": 0.22,
                "12x": 0.092,
            }
            self.distance_with_optics = {
                "1x": 0.0,
                "1.5x": 0.0,
                "2x": 0.0,
                "2.5x": 0.0,
                "3x": 0.0,
                "4x": 0.0,
                "5x": 0.0,
                "12x": 0.0,
            }
            self.R6S(aratio, mdratio, curfov, curdist)
        elif game == "Apex":
            curfov = 70 * curfov
            self.fov_with_optics = {
                "1x, Pistol, SMG, SG": 6 / 7,
                "AR, LMG Sniper": 11 / 14,
                "2x": 1102591 / 2000000,
                "3x": 26275563 / 70000000,
                "4x": 992913 / 3500000,
                "6x": 1901823 / 10000000,
                "8x": 1 / 7,
                "10x": 1001339 / 8750000,
            }
            self.distance_with_optics = {
                "1x, Pistol, SMG, SG": 0.0,
                "AR, LMG Sniper": 0.0,
                "2x": 0.0,
                "3x": 0.0,
                "4x": 0.0,
                "6x": 0.0,
                "8x": 0.0,
                "10x": 0.0,
            }
            self.Apex(aratio, mdratio, curfov, curdist)
        elif game == "Valorant":
            self.fov_with_optics = {
                "1.15x - Ares, Odin, Spectre, Stinger": 89.565217,
                "1.25x - Bulldog, Phantom, Vandal": 82.4,
                "1.50x - Guardian, Headhunter": 68.666667,
                "2.50x - Operator, Tour de Force": 41.2,
                "3.50x - Marshal": 29.428571,
                "5x - Operator": 20.6,
            }
            self.distance_with_optics = {
                "1.15x - Ares, Odin, Spectre, Stinger": 0.0,
                "1.25x - Bulldog, Phantom, Vandal": 0.0,
                "1.50x - Guardian, Headhunter": 0.0,
                "2.50x - Operator, Tour de Force": 0.0,
                "3.50x - Marshal": 0.0,
                "5x - Operator": 0.0,
            }
            self.Valorant(mdratio, curfov, curdist)
        elif game == "Splitgate":
            self.fov_with_optics = {
                "Assault Rifle, Carbine, Rocket": 55,
                "Battle Rifle, Railgun": 40,
                "Sniper Rifle": 30
            }
            self.distance_with_optics = {
                "Assault Rifle, Carbine, Rocket": 0.0,
                "Battle Rifle, Railgun": 0.0,
                "Sniper Rifle": 0.0
            }
            self.Splitgate(aratio, mdratio, curfov, curdist)
        elif game == 'CSGO':
            self.fov_with_optics = {
                "Zoomed 1: AWP, SSG 08, G3SG1, SCAR-20": 40,
                "Zoomed 2: AWP": 10,
                "Zoomed 2: SSG 08, G3SG1, SCAR-20": 15,
                "Zoomed: AUG, SG 553": 45
            }
            self.distance_with_optics = {
                "Zoomed 1: AWP, SSG 08, G3SG1, SCAR-20": 40,
                "Zoomed 2: AWP": 10,
                "Zoomed 2: SSG 08, G3SG1, SCAR-20": 15,
                "Zoomed: AUG, SG 553": 45
            }
            self.CSGO(aratio, mdratio, curfov, curdist)

    def __del__(self):
        if self.distance_with_optics is not None:
            for optics, distance in self.distance_with_optics.items():
                print("\n" + str(distance) + "[cm/360°] を " + str(optics) + " で")
            print(
                self.RED + "\n振り向きからセンシへの計算は " + self.BLUE + "https://www.mouse-sensitivity.com" + self.RED + " を使えばヨシ！ その計算方法はあんまりわかってない\n" + self.END)
