import subprocess
import os
import sys

sys.path.insert(0, '..')
import run_unit
sys.path.remove('..')


def run():
    option = []
    ret = 0
    ret += 1 if run_unit.run('./test/003_parser/001', option) else 0
    ret += 1 if run_unit.run('./test/003_parser/002', option) else 0
    ret += 1 if run_unit.run('./test/003_parser/003', option) else 0

    return ret
