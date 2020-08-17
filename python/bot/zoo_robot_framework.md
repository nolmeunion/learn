# robot framework 

노키아에서 만든 자동화 도구이다. 테스트와 로봇 공정 시뮬레이션과 제어에 주로 사용한다. 

로봇 프레임워크의 기능, 구조, 소스를 살펴보면서 게임용 봇 툴에 적용할 수 있는 개념들이 있는 지 
찾고 가능하면 도입하여 구현하도록 한다. 

매우 일반적이면서 빠른 게임 부하 테스트와 컨텐츠 학습과 테스트 프레임워크를 만들려고 하므로 
도움이 많이 될 수 있다. 적어도 파이썬 실력을 늘리는데 도움이 많이 될 것이다. 

## 사용 

사용으로 시작하여 접근한다. 

http://robotframework.org/robotframework/latest/RobotFrameworkUserGuide.html

- library 
  - tools to develop actions
  - reuse python modules

- action suite
  - actions

- action scenario 
  - context
    - data map
      - server address, user account number, and so on
  - actions
    - with the list of (signal, transition) 
    - action data

- runner 
  - listens on controller's commands
  - get scenario and execute them with bots
  - report result to the controller

- controller 
  - drive execution of test scenarios 
    - scheduling
    - setup parameters of test scenarios
    - collect test results 
  - flask gui 
  - coordination and interaction with bots distributed on runners

- agent 
  - waits on controller command and starts a runner 
  - runs as a service or a daemon
  - flask gui 
    - control and monitoring ui 

python, flask, web application, 3d rendering

위의 구조가 지금까지 정리한 부하 테스트 프레임워크이다. 기본 플레이 구현과 부하 테스트에 
주로 잘 맞는 구조이다. 컨텐츠 학습과 테스트는 별도로 고민해야 한다. 빠르고 쉽게 
게임 부하 테스트를 진행할 수 있도록 만들어 시간을 확보하고 공부를 지속하여 더 많은 
범위를 테스트하여 게임의 성공을 보장하는 수준으로 나아간다. 

git repo에서 개발을 하고 controller를 통해 runner들이 받도록 하여 배포한다. 
배포된 여러 파일들은 test suite를 구성하고 이를 시나리오화 하여 
콘트롤러 gui나 파이썬으로 만들고 파라미터를 설정하여 여러 runner에서 
실행할 수 있게 한다. 



### 개념들 

- test library 
  - 키워드를 제공

- 리소스 파일 
  - 사용자 키워드와 변수를 가짐

- 변수 파일 
  - 변수를 효율적으로 정의 

```re
*** Settings ***
Documentation     Example using the space separated format.
Library           OperatingSystem

*** Variables ***
${MESSAGE}        Hello, world!

*** Test Cases ***
My Test
    [Documentation]    Example test.
    Log    ${MESSAGE}
    My Keyword    ${CURDIR}

Another Test
    Should Be Equal    ${MESSAGE}    Hello, world!

*** Keywords ***
My Keyword
    [Arguments]    ${path}
    Directory Should Exist    ${path}
```

라이브러리를 사용하여 키워드를 만들고, 키워드와 변수로 테스트를 만든다. 이것이 로봇프레임워크의 핵심이다. 
