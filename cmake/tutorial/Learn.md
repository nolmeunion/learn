# Learn 

## cmake 최신 버전 설치 

* openssl-devl 설치 
* download 
* bootstrap ; gmake ; gmake install 

설치가 꽤 오래 걸린다.

* gmake -j4와 같이 병렬로 진행

## vscode 

* code .으로 서버 설치 
* <C><S>P cmake에서 명령들 확인 
  - Configure 
  - Build 
  - Debug 

디버깅이 제공되지 않는다. 

## Step 1

cmake_minimum_required(VERSION version)

project(name)

add_executable(name srcs)


