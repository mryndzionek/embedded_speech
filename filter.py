import numpy as np
from scipy import signal
import matplotlib.pyplot as plt


taps = signal.firwin(40, 4000, fs=32000)
w, h = signal.freqz(taps, fs=32000)
plt.plot(w, 20 * np.log10(abs(h)), "b")
plt.show()

lines = [taps[i: i+ 5] for i in range(0, len(taps), 5)]
for line in lines:
    print(", ".join(map(str, line)) + ",")

rnd = (np.random.random(256) - 0.5) * 2 * (1 << 10)
lines = [rnd[i: i+ 16] for i in range(0, len(rnd), 16)]
for line in lines:
    print("    " + ", ".join(map(lambda x: str(round(x)), line)) + ",")
