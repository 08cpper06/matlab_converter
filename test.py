import sys
import os
import glob
import subprocess
from importlib import import_module

sys.dont_write_bytecode = True

test_case = [
#                '001_step',
                '002_tokenizer'
            ]


def run_test(test_dir):
    mod = import_module(test_dir + '.' + test_dir)
    return mod.run()

if __name__ == '__main__':
    test_dir = './test/'

    sys.path.insert(0, './test/')
    for item in test_case:
        if not os.path.isdir(test_dir + item):
            print(item + ' is not directory')
            exit(1)
        else:
            print('--- ' + item + ' ---')
            if not run_test(item):
                print('TEST SSUCCEED!!')
            else:
                print('TEST FAILED!!')

    sys.path.remove('./test/')
