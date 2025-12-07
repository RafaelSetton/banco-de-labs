import scipy.io as sio
from espectro import espectro
import IPython.display as ipd
from IPython.core.display import display_html

Fs, y = sio.wavfile.read("fixed.wav")
y=(y[:,0]+y[:,1])/2

espectro(y, "Espectro Original.png")

ipd.display(ipd.Audio(y,rate=Fs, autoplay=True))
input("Quit")