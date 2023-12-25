import sympy

input = open("input.txt", "r").read()

lines = []
input = [line for line in input.splitlines()]
for l in input:
    pos, speed = l.split(" @ ")
    px, py, pz = [int(c) for c in pos.split(", ")]
    vx, vy, vz = [int(c) for c in speed.split(", ")]
    lines.append((px, py, pz, vx, vy, vz))

xr, yr, zr, vxr, vyr, vzr = sympy.symbols("xr, yr, zr, vxr, vyr, vzr")

equations = []

for i, (sx, sy, sz, vx, vy, vz) in enumerate(lines):
    equations.append((xr - sx) * (vy - vyr) - (yr - sy) * (vx - vxr))
    equations.append((yr - sy) * (vz - vzr) - (zr - sz) * (vy - vyr))
    if i >= 2:
        answers = [solution for solution in sympy.solve(equations) if all(x % 1 == 0 for x in solution.values())]
        if len(answers) == 1:
            (answer,) = answers
            print(answer[xr] + answer[yr] + answer[zr])
            break