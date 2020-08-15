# learn flask

웹 서버를 내장한 서비스는 외부에서 자유롭게 접근할 수 있으면서 web app을 제공할 수 있다. 
웹 애플리케이션으로 에이전트들을 서비스로 실행하고 명령의 배포, 결과의 수집 등을 자유롭게 할 수 있다. 

파이썬으로 하면 느릴 수 있지만 장비를 늘리면 되므로 크게 문제 될 게 없다. 

https://github.com/locustio/locust

위 로커스트를 보면 웹으로 접속하여 테스트를 실행하고 그래프를 볼 수 있다. 
개별로 실행할 수도 있고, 스크립트로 전체 에이전트에 접속하여 명령을 보낼 수도 있다. 

테스트 업데이트는 gitea가 매우 효과적인 것으로 증명되었다. 
개발에도 gitea를 사용하고, 테스트 실행에도 사용할 수 있다. 

파이썬으로 제작이 어려운 게임이 있다면 cython의 도움을 받아 해결이 안 되는 부분만 작성한다. 

관리해야 할 에이전트 장비의 대수가 증가할 가능성이 높기 때문에 에이전트의 배포와 
테스트 결과 수집과 분석을 최대한 자동화 해야 한다. 


* flask 
  * embedded web server 
  * css / html / javascript
* service 
  * windows, linux
* git 
  * gitea 
  * git client
* net (asyncio) 
* cython
* test framework 
  * hfsm 
  * AI * pandas3d
* analysis 
  * pandas, numpy, matplotlib 

## tutorial

https://flask.palletsprojects.com/en/1.1.x/tutorial/


https://opentutorials.org/module/3669/22003

웹은 우리가 강하다. 

- jinja
- css
- python code

잘 만든 걸 활용해서 작업한다. 디자인도 그렇다. 

- flask_sqlalchemy 

좋은 글이다. 전체 흐름을 이해했다. 

몇 가지 의문이 남는다. 

- 테스트 시작 버튼을 누르면 테스트를 시작하고 진행화면을 표시한다. 
- 페이지가 변경되면서 표시하는 방법이 웹의 기본 방법이다. 
- Web application으로 한 화면에서 처리하는 방법이 있을까? 그게 나을까? 


