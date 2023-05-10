# from ulab import numpy as np
import numpy as np
import matplotlib.pyplot as plt

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
frq = np.fft.fftfreq(len(a), d = 1/len(a))

# while 1: # printing with plotting function
#     for i in range(len(a)):
#         print("("+str(Y[i])+",)")
plt.plot(frq[:512], np.abs(Y)[:512])
plt.show()