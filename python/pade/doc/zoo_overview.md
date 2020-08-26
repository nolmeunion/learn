# pade overview

pade는 python multiagent system 라이브러리이다. 
pade는 여러 에이전트 간의 FIPA 통신을 할 수 있고, 여러 프로세스에서 실행할 수 있다. 

pade는 트위스티드 라이브러리를 사용한다. 

공부하는 목표는 다음과 같다. 
- asyncio 기반의 agent 프레임워크 개발 
- agent를 봇으로 하고 실행을 협업을 통해 제어 
- 테스트는 행동이고 이를 연결하고 협업하여 테스트를 진행 
- 테스트 선택에 강화 학습으로 행동 선택 


## 소스 다운로드와 설치 

소스를 파악하면서 asyncio 포팅을 어떻게 할 지 정리해 간다. 

설치 에러: 

``` python
ERROR: Command errored out with exit status 1:
   command: 'c:\app\python37\python.exe' 'c:\app\python37\lib\site-packages\pip' install --ignore-installed --no-user --prefix 'C:\Users\KEEDON~1\AppData\Local\Temp\pip-build-env-cjycmma1\overlay' --no-warn-script-location --no-binary :none: --only-binary :none: --no-index --find-links . -- 'setuptools>=40.8.0' wheel
       cwd: None
  Complete output (4 lines):
  Looking in links: .
  Processing c:\users\keedongpark\nolme\download\setuptools-49.6.0-py3-none-any.whl
  ERROR: Could not find a version that satisfies the requirement wheel (from versions: none)
  ERROR: No matching distribution found for wheel
  ----------------------------------------
ERROR: Command errored out with exit status 1: 'c:\app\python37\python.exe' 'c:\app\python37\lib\site-packages\pip' install --ignore-installed --no-user --prefix 'C:\Users\KEEDON~1\AppData\Local\Temp\pip-build-env-cjycmma1\overlay' --no-warn-script-location --no-binary :none: --only-binary :none: --no-index --find-links . -- 'setuptools>=40.8.0' wheel Check the logs for full command output.
```

wheel 버전이 안 맞아 나온 에러이다. wheel download 후 설치 되었다. 

## features

* Object Orientation:
    - Abstraction for build agents and its behaviours using object orientation concepts.
* Run time execution
    - It’s a module to initialize the agents execution enviroment written 100% in Python language.
* FIPA-ACL messages
    - It’s a module to build and handle messages in FIPA-ACL standard.
* Filtering Messages
    - Filter functionalities to multiagent messages.
* FIPA protocols
    - It’s a module for implement FIPA standard protocols, like ContractNet, Request and Subscribe.
* Cyclic and Timed Behaviours
    - Module for cyclic and timed behaviours.
* Data Base
    - Module for Data Base interaction.
* Serialized objects exchange
    - It’s possible to send serialized objects in the FIPA-ACL messages content.


## FIPA-ACL 

Agent Communication Language. 

