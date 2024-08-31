%matplotlib inline
import math
import matplotlib
#matplotlib.use("Agg")
import matplotlib.cm as cm  # colormap
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches
import matplotlib.animation as animation
#%matplotlib nbagg

plt.rcParams['font.family'] = 'Arial' 
plt.rcParams["text.usetex"] =True
plt.rcParams["font.size"] = 30

from matplotlib.collections import PatchCollection
from matplotlib.patches import Circle
import numpy as np

resolution = 500 # the number of vertices

fig = plt.figure(figsize=(13,14))
ax = fig.add_subplot(111)
ax.spines['top'].set_linewidth(3)
ax.spines['bottom'].set_linewidth(3)
ax.spines['left'].set_linewidth(3)
ax.spines['right'].set_linewidth(3)
plt.tick_params(which='major',width = 1, length = 10)
plt.tick_params(which='minor',width = 1, length = 5)
plt.xticks(color='k', size=30)
plt.yticks(color='k', size=30)
plt.xlabel(r"$x$",color='k', size=45)
plt.ylabel(r"$y$",color='k', size=45)
ax.set_aspect('equal')

ims = []
a = [0] * 1500
#########################
chi=0.25
T=1
rho=0.84
Np=4000
#########################
L = (Np*3.14159/4*(1.+2.*chi)/ rho)**0.5;

ax.text(0, L+5, r"$T=1.0\times 10^{-4},\ \ a_{\ell}/a_s=1.5$", size =40, color = "k")
plt.xlim(0, L)
plt.ylim(0, L)   
print(L)

for j in range(1,95):       
    a[j]=1000*j
    x, y,theta,r = np.loadtxt("./Documents/Data_research/education/Anisotropic/harmonic/{}/T{}N4000c{}/bina2d_{}.dat".format(rho,T,chi,j), comments='#', unpack=True)
    patches = []
    for i in range(4000):
        circle = mpatches.Ellipse((x[i],y[i]), (1+2*chi)*r[i], r[i],theta[i]/6.28*360)
        patches.append(circle)    
    #colors = theta % 3.141592
    colors = r% 3.141592
    p = PatchCollection(patches, cmap=matplotlib.cm.hsv, alpha=0.9,ec='k',linewidth = 0.3)
    p.set_array(colors)
    p.set_clim(0,3.141)
    ax.add_collection(p)
#  im = plt.plot() 
    title = ax.text(0.7*L, L+5, "$t={}$".format(a[j]),size =40, color = "k") #title コマ送り
    ims.append([p,title])                # グラフを配列 ims に追加
   # plt.cla()
    #plt.xlim(0, L)
    #plt.ylim(0, L)   
   
ani = animation.ArtistAnimation(fig, ims, interval=100)

ani.save("rho{}T{}N4000c{}N4k_nocolor.gif".format(rho,T,chi), writer="imagemagick")
ani.save("rho{}T{}N4000c{}N4k_nocolor.mp4".format(rho,T,chi), writer="ffmpeg")
plt.show()
