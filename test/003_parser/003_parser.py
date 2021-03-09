import subprocess
import os
import sys

sys.path.insert(0, '..')
import run_unit
sys.path.remove('..')


def run():
    ret = 0
    ret += 1 if run_unit.run('./test/003_parser/001') else 0
    ret += 1 if run_unit.run('./test/003_parser/002') else 0
    ret += 1 if run_unit.run('./test/003_parser/003') else 0

    return ret
