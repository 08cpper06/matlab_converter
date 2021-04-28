import subprocess
import os


def run(pth, option):
    in_file = pth + '.in'
    ok_file = pth + '.ok'
    print(pth + ' -> ', end='')

    exe_file = 'matlab_converter'
    if os.name == 'nt':
        exe_file = exe_file + '.exe'

    cmd_str = ['.' + os.sep + 'build' + os.sep + exe_file, in_file]
    if option:
        cmd_str.extend(option)

    proc = subprocess.Popen(cmd_str, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    log = proc.stdout.read()
    log = log.decode('utf-8')
    if os.name == 'nt':
        # CRLF -> LF
        log = log.replace('\r', '')

    err_log = proc.stderr.read()
    err_log = err_log.decode('utf-8')
    if os.name == 'nt':
        # CRLF -> LF
        err_log = err_log.replace('\r', '')

    ok_log = "".join([item for item in open(ok_file, 'r')])

#    print(ok_log.encode('utf-8'))
#    print(log.encode('utf-8'))

    proc.kill()

    if ok_log == log and not proc.returncode and not err_log:
        print('\033[33mOK\033[0m')
        return 0
    else:
        print('\033[31mNG')
        print('--- ok_file ---')
        print(ok_log.replace('\n', '↲\n'))
        print('--- actual ---')
        print(log.replace('\n', '↲\n'))
        print('--- error ---')
        print(err_log.replace('\n', '↲\n'))
        print('--------------\033[0m')
        return 1
