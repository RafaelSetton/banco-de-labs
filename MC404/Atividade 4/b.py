import scipy.io as sio
from espectro import espectro
import IPython.display as ipd


Fs, y = sio.wavfile.read("creed_overcome.wav")
y=(y[:,0]+y[:,1])/2

y = y[::6]

espectro(y, "Espectro Decimado.png")

ipd.Audio(y,rate=Fs/6)