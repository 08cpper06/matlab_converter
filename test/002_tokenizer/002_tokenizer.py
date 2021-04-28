import subprocess
import os
import sys

sys.path.insert(0, '..')
import run_unit
sys.path.remove('..')


def run():
    option = ['-mode', 'debug_002']
    ret = 0
    ret += 1 if run_unit.run('./test/002_tokenizer/001', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/002', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/003', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/004', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/005', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/006', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/007', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/008', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/009', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/010', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/011', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/012', option) else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/013', option) else 0

    return ret
