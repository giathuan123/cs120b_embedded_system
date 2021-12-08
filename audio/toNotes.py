from aubio import source, pitch

with source('sample.wav') as src:
    src_pitch = pitch('yin', samplerate=src.samplerate)
    cnt = 0
    print('#include "define.h"') 
    print('double gameSong[] = {')
    duration = src.duration;
    while True:
        sample, read = src()
        cnt+=1
        freq = int(round(src_pitch(sample)[0]))
        if(freq == 0):
            print('0,')
        elif(freq < 110):
            print('A_NOTE,')
        elif(freq < 200):
            print('B_NOTE,')
        elif(freq < 300):
            print('C_NOTE,')
        elif(freq < 500):
            print('D_NOTE,') 
        elif(freq < 1320):
            print('E_NOTE,') 
        else:
            print('F_NOTE,') 
        if(cnt == 3000 or read < src.hop_size):
            break
    print('};') 
    # print(duration, cnt*11.6) 
