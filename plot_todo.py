import glob
import sys
import os

sys.dont_write_bytecode = True

def extract_target(_file, idx, line):
    ss = ''
    if 'TODO' in line:
        print(_file + ':' + str(idx) + ':', end='')
        ss = 'TODO'
    if 'FIXME' in line:
        print(_file + ':' + str(idx) + ':', end='')
        ss = 'FIXME'

    if len(ss):
        print(ss + ':' + line[line.find(ss)+len(ss)+2:], end='')


if __name__ == '__main__':
    pth = '.' + os.sep + 'src' + os.sep + '*'
    _list = glob.glob(pth)

    for item in _list:
        # load file
        idx = 0
        with open(item, 'r') as f:
            data = f.readlines()
            for line in data:
                extract_target(os.path.basename(item), idx, line)
                idx = idx + 1
