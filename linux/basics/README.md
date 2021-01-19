# 리눅스 토막 지식 정리 자료
생활코딩 Linux 정리

## 리눅스 기초
- `$ pwd`: 현재 위치를 보여줌
- `$ mkdir {생성할 디렉토리 이름}`: 비어 있는 디렉토리를 새로 생성
- `$ touch {새로 생성할 파일 이름}`: 비어 있는 파일을 생성
- `$ ls -al`: 디렉토리에 존재하는 모들 파일 리스트를 보여줌
  - 맨 앞에 d가 붙어 있는 것은 디렉토리이고 -이면 파일
- `$ cd {이동할 디렉토리의 경로}`: 디렉토리를 변경
- `$ rm -rf {파일/디렉토리 이름}`: 파일을 재귀적이며 강제로 삭제
- `$ man {명령어}`: 명령어 사용을 위한 상세 명세
- `$ cp {파일 A의 이름} {파일 B의 이름}`: 파일 A를 복사해서 파일 B를 만듦
- `$ mv {파일/디렉토리 A 이름} {파일/디렉토리 B 이름}`: A를 B 경로로 이동하거나 이름을 변경
- `$ sudo {명령어}`: Super User의 권한으로 명령어 실행
- `$ su {유저 이름}`: 해당 User로 실행자 변경, 유저 이름이 없는 경우 Super User
- `$ wget {다운로드 받을 파일이 있는 url}`: 타겟 url에서 파일 다운로드

**apt, brew, rpm, yum 패키지 매니저를 설치하고 이를 통해서 각 운영체제마다 패키지 설치 및 관리를 할 수도 있음**

## IO Redirection
- `$ {명령} 1> {파일 이름}`: 명령의 Standard Output의 결과를 파일로 Redirection, 1은 생략 가능
- `$ {명령} 2> {파일 이름}`: 명령의 Standard Error의 결과를 파일로 Redirection
- `$ {명령} >> {파일 이름}`: 명령의 Standard Output의 결과를 파일로 Redirection을 기존 파일에 이어 쓰기

## 쉘과 쉘 스크립트
- 쉘: 사용자와 운영체제간에 대화를 가능하게 해주는 명령기와 해석기 역할을 하는 프로그램으로, 사용자(명령) -> 쉘(해석) -> 커널(명령 수행 후 결과 전송) -> 쉘(해석) -> 사용자(결과 확인) 과정에서 역할을 함
- `$ echo $0`: 내가 사용하고 있는 쉘이 무엇인지 보여줌
- 쉘 스크립트: 명령어들이 나열되어 있는 파일

## 디렉토리 구조
- /: root
  - `/bin`: User Binaries
  - `/sbin`: System Binaries
  - `/etc`: Configuration Files
  - /dev: Device Files
  - `/proc`: Process Infomation
  - /var: Variable Files
  - /tmp: Temporary Files
  - `/usr`: User Programs
    - /usr/bin
    - /usr/sbin
    - /usr/lib
    - /usr/local
  - `/home`: Home Directory
  - /boot: Boot Loader Files
  - /lib: System Libaries
  - `/opt`: Optional add-on Apps
  - /mnt: Mount Directory
  - /media: Rmovable Device
  - /srv: Service Data

## 파일 찾는 법
- `$ locate {파일 이름}`: 시스템의 mlocate라는 데이터베이스를 뒤져서 파일의 위치 검색
- `$ find {디렉토리} -name {파일 이름}`: 디렉토리를 뒤져서 파일의 위치 검색
- `$ whereis {명령어 이름}`: whereis는 명령어의 실행 파일 위치, 소스 위치, man 페이지 파일의 위치를 찾아줌

## 프로세스와 실행

## 사용자

## 그룹

## 인터넷, 네트워크, 서버

## 도메인

