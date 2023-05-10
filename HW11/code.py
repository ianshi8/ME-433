from ulab import numpy as np
import time

a = np.zeros(1024)

# defining frequencies
f1 = 50
f2 = 100
f3 = 200
amp = 0.1

for i in range(len(a)):
    a[i] = amp*np.sin(2*np.pi*f1*i/len(a)) + amp*np.sin(2*np.pi*f2*i/len(a)) + amp*np.sin(2*np.pi*f3*i/len(a))

# perform fft
Y = np.fft.fft(a)
#frq = np.fft.fftfreq(len(a), d = 1/len(a))

print(Y)
#print(frq)

# while 1: # printing with plotting function
#     for i in range(len(Y)):
#         print("("+str(Y[i])+",)")
#         time.sleep(.05)