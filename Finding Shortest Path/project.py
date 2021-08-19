from matplotlib import pyplot as plt

print("Started")


class coordinates(object):
	def __init__(self, x, y):
		self.x, self.y = x, y


list = []
line = ""

f = open("output", "r")
i = 0

line = f.readline()
while line != "EOF\n":
	list.append(coordinates(float(line.split()[0]), float(line.split()[1])))
	line = f.readline()

print(str(len(list)) + " City")

for i in range(len(list) - 1):
	plt.scatter(list[i].x, list[i].y, s=1, color="#FF0000", marker=".")
	plt.plot([list[i].x, list[i + 1].x], [list[i].y, list[i + 1].y], 'k-')
plt.show()
