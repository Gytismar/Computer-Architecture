import matplotlib.pyplot as plt

auktis_per_metus = 0.4

#p_aukstis = int(input("Pradinis medžio aukštis: "))
#santykis = int(input("Santykis tarp aukščio ir spindulio: "))
#metai = int(input("Po kiek metu: "))

p_aukstis = 24
santykis = 3
metai = 5

p_spindulys = p_aukstis/santykis

pradinis_medis = [[0,0],[p_spindulys*2,0],[p_spindulys,p_aukstis]]
pradinis_medis.append(pradinis_medis[0])
pxs,pxy = zip(*pradinis_medis)

s_i_l = 1 #stiebas iki lapu

g_aukstis = p_aukstis + metai*auktis_per_metus;
g_spindulys = g_aukstis/santykis

g_aukstis = g_aukstis*1.05
g_spindulys = g_spindulys*1.05

g_medis = [[p_spindulys-g_spindulys,0],[p_spindulys+g_spindulys,0],[p_spindulys,g_aukstis]]
g_medis.append(g_medis[0])
gxs, gxy = zip(*g_medis)


############################################
img = plt.imread("egle.png")
fig, ax = plt.subplots()
ax.imshow(img, extent=[0+1, p_spindulys+p_spindulys-1, 0-s_i_l, p_aukstis*0.98])
#############################################


plt.plot(pxs,pxy,ls='dotted')
plt.plot(gxs,gxy)

plt.axis('equal') 
plt.savefig('saved_figure.png')
plt.show()