# play with pybullet 

## 설치 

pip install PyBullet 

whl (wheel) 파일을 사용한다. 

pip install wheel 

위 명령으로 wheel을 설치한다. 

wheel이 없어 setup.py를 사용한다고 나온다. 이전 방법도 지원한다. 
C API와 불릿 빌드 과정을 포함하므로 꽤 오래 걸린다. 


## 최초 사용 

https://docs.google.com/document/d/10sXEhzFRSnvFcl3XxNGhnD4N2SedqwdAvK3dsihxVUA/edit#

Quick Start Guide가 친철하게 설명한다. 간략하지만 괜찮아 보인다. 

매우 인상적이다. 프로그래밍이나 게임이 이런 것이다. 마법을 만들기, 그래서 삶을 
보다 낫게 만들 수 있는 수단을 제공하기. 사람의 선택이 항상 그런 방향으로 
나아가지는 않지만. 


## URDF 

http://wiki.ros.org/urdf/XML/model

The Unified Robot Description Format (URDF) is an XML specification to describe a robot. 
We attempt to keep this specification as general as possible, but obviously the specification cannot 
describe all robots. The main limitation at this point is that only tree structures can be represented, 
ruling out all parallel robots. Also, the specification assumes the robot consists of rigid links 
connected by joints; flexible elements are not supported. The specification covers:

- Kinematic and dynamic description of the robot
- Visual representation of the robot
- Collision model of the robot

```xml
   <robot name="pr2">
       <link> ... </link>
       <link> ... </link>
       <link> ... </link>
     
       <joint>  ....  </joint>
       <joint>  ....  </joint>
       <joint>  ....  </joint>
   </robot>
```

```xml 
   <link name="my_link">
        <inertial>
          <origin xyz="0 0 0.5" rpy="0 0 0"/>
          <mass value="1"/>
          <inertia ixx="100"  ixy="0"  ixz="0" iyy="100" iyz="0" izz="100" />
        </inertial>
     
        <visual>
          <origin xyz="0 0 0" rpy="0 0 0" />
          <geometry>
            <box size="1 1 1" />
          </geometry>
          <material name="Cyan">
            <color rgba="0 1.0 1.0 1.0"/>
          </material>
        </visual>
   
        <collision>
          <origin xyz="0 0 0" rpy="0 0 0"/>
          <geometry>
            <cylinder radius="1" length="0.5"/>
          </geometry>
        </collision>
   </link>
```

위 정도로 이해한다. 필요할 때 더 보면 된다. 

## tiny renderer 

초간단 소프트웨어 렌더러. 품질과 성능이 봇 툴에 적당한 정도이다. 

그 정도가 좋다. 필요하면 기능을 개선해 나간다. 


## 오브젝트 관리와 제어

- createCollisionShapeArray
- createVisualShapeArray
- createMultiBody
- removeCollisionShape
- createVisualShape
- createTexturedMeshVisualShape

- getBasePositionAndOrientation
- resetBasePositionAndOrientation

- getBaseVelocity
- resetBaseVelocity

- applyExternalForce
- applyExternalTorque

## 충돌 

- getOverlappingObjects
- getAABB
- getContactPoints
- getClosestPoints

- rayTest
- rayTestBatch

- getCollisionShapeData
- setCollisionFilterGroupMask

## examples

https://github.com/bulletphysics/bullet3/tree/master/examples/pybullet/examples

아주 많은 예제가 있다. 이렇게 테스트와 예제가 많은 라이브러리가 좋은 라이브러리이다. 

step들을 여기서 따온다. 








