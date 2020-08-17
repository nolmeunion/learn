import pybullet as p
import time
import math
import pybullet_data

useGui = True

if (useGui):
  #p.connect(p.GUI)
  p.connect(p.GUI, options="--opengl2")
else:
  p.connect(p.DIRECT)
p.setAdditionalSearchPath(pybullet_data.getDataPath())

p.configureDebugVisualizer(p.COV_ENABLE_GUI, 0)
#p.configureDebugVisualizer(p.COV_ENABLE_RENDERING,0)

#p.loadURDF("samurai.urdf")

f = 0

while f < 2*3.141592:
    f += 0.5
    x = 3*math.cos(f)
    y = 3*math.sin(f)
    p.loadURDF("r2d2.urdf", [3 + x, 3 + y, 1])

rayFrom = []
rayTo = []
rayIds = []

numRays = 1024

rayLen = 13

rayHitColor = [1, 0, 0]
rayMissColor = [0, 1, 0]

replaceLines = True

p.setGravity(0,0,-10)

for i in range(numRays):
  rayFrom.append([0, 0, 1])
  rayTo.append([
      rayLen * math.sin(2. * math.pi * float(i) / numRays),
      rayLen * math.cos(2. * math.pi * float(i) / numRays), 1
  ])
  if (replaceLines):
    rayIds.append(p.addUserDebugLine(rayFrom[i], rayTo[i], rayMissColor))
  else:
    rayIds.append(-1)

if (not useGui):
  timingLog = p.startStateLogging(p.STATE_LOGGING_PROFILE_TIMINGS, "rayCastBench.json")

numSteps = 10
if (useGui):
  numSteps = 327680

for i in range(numSteps):
  p.stepSimulation()
  for j in range(8):
    results = p.rayTestBatch(rayFrom, rayTo, j + 1)

  #for i in range (10):
  #	p.removeAllUserDebugItems()

  if (useGui):
    if (not replaceLines):
      p.removeAllUserDebugItems()

    for i in range(numRays):
      hitObjectUid = results[i][0]

      if (hitObjectUid < 0):
        hitPosition = [0, 0, 0]
        p.addUserDebugLine(rayFrom[i], rayTo[i], rayMissColor, replaceItemUniqueId=rayIds[i])
      else:
        hitPosition = results[i][3]
        p.addUserDebugLine(rayFrom[i], hitPosition, rayHitColor, replaceItemUniqueId=rayIds[i])

  #time.sleep(1./240.)

if (not useGui):
  p.stopStateLogging(timingLog)