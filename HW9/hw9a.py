# HW9 Part 1: Low-pass filter with moving average

# reading csv file
import csv
import matplotlib.pyplot as plt # for plotting
import numpy as np # for sine function

t = [] # column 0
data = [] # column 1

with open('sigD.csv') as f:
    # open the csv file
    reader = csv.reader(f)
    for row in reader:
        # read the rows 1 one by one
        t.append(float(row[0])) # leftmost column
        data.append(float(row[1])) # second column

# creating MAF
lpf = np.zeros(len(t))
X = 5
for i in range(X, len(t)):
    for j in range(X):
        sum = 0
        sum += data[i-j]
    maf = sum/X
    lpf[i] = maf

# plt.plot(t, data, 'b-*', t, lpf, 'r-*')
# plt.xlabel('Time [s]')
# plt.ylabel('Signal')
# plt.title('Signal vs Time')
# plt.show()

# lp filter with fft
dt = t[1] - t[0]
Fs = 1/dt # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector

y1 = data # the data to make the fft from
y2 = lpf

n = len(y1) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range

Y1 = np.fft.fft(y1)/n # fft computing and normalization
Y1 = Y1[range(int(n/2))]
Y2 = np.fft.fft(y2)/n # fft computing and normalization
Y2 = Y2[range(int(n/2))]

fig, (ax1, ax2) = plt.subplots(2,1)
ax1.plot(t, y1, 'b', t, y2, 'r')
ax1.set_title('Signal vs Time and FFT (X = ' + str(X) + ')')
ax1.set_xlabel('Time [s]')
ax1.set_ylabel('Amplitude')
ax2.loglog(frq, abs(Y1), 'b', frq, abs(Y2), 'r')
ax2.set_xlabel('Freq (Hz)')
ax2.set_ylabel('|Y(freq)|')
plt.show()