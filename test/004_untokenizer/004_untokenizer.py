import subprocess
import os
import sys

sys.path.insert(0, '..')
import run_unit
sys.path.remove('..')


def run():
    option = ['-mode', 'debug_004']
    ret = 0
    ret += 1 if run_unit.run('./test/004_untokenizer/001', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/002', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/003', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/004', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/005', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/006', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/007', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/008', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/009', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/010', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/011', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/012', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/013', option) else 0
    ret += 1 if run_unit.run('./test/004_untokenizer/014', option) else 0

    return ret
