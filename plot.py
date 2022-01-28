import matplotlib.pyplot as plt
import csv

pmap = []

with open('war_final.csv') as csvfile:
    rdr = csv.reader(csvfile,delimiter=',')
    for row in rdr:
        prow = []
        for col in row:
            if col != ' ' and col != '':
                prow.append(float(col))
        pmap.append(prow)

print(pmap)

plt.imshow(pmap)
plt.show()
