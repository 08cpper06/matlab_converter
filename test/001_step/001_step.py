import subprocess
import os
import sys

sys.path.insert(0, '..')
import run_unit
sys.path.remove('..')


def run():
    ret = 0
    ret += 1 if run_unit.run('./test/001_step/001') else 0




    return ret
