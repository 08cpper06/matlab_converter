import subprocess
import os
import sys


sys.path.insert(0, '..')
import run_unit
sys.path.remove('..')


def run():
    option = ['-mode', 'debug_001']
    ret = 0
    ret += 1 if run_unit.run('./test/001_step/001', option) else 0

    return ret
