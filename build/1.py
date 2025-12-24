names = set()

with open("/home/qiqi/geant4/Particle-Accelerator-Simulation/build/model.obj", "r") as f:
    for line in f:
        if line.startswith("o ") or line.startswith("g "):
            names.add(line.strip().split(maxsplit=1)[1])

for n in sorted(names):
    print(n)
