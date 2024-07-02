import matplotlib.pyplot as plt
import numpy as np

def plot_polygon(polygon, label):
    polygon.append(polygon[0])  # Kapatmak için ilk noktayı tekrar ekleyin
    xs, ys = zip(*polygon)
    plt.plot(xs, ys, label=label)

#Çizmek istediğiniz şekillerin koordinatlarını liste olarak aşağı yazınız
# [[(3, 10), (3, 1), (10, 5), (10, 6)], [(1, 6), (4, 6), (2, 7)]]
dortgen_noktalari = [(3, 10), (3, 1), (10, 5), (10, 6)]
ucgen_noktalari = [(1, 6), (4, 6), (2, 7)]
# Dörtgeni ve üçgeni çiz
plot_polygon(dortgen_noktalari, 'Dörtgen')
plot_polygon(ucgen_noktalari, 'Üçgen')

# Eksenleri ayarla
plt.axhline(0, color='black',linewidth=0.5)
plt.axvline(0, color='black',linewidth=0.5)

# Grafik penceresini göster
plt.legend()
plt.grid(color = 'gray', linestyle = '--', linewidth = 0.5)
plt.show()
