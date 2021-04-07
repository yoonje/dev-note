# 리눅스 기본 지식 정리 자료
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
- `$ {명령} 1> {파일 이름}`: 명령의 Standard Output(1)의 결과를 파일로 Redirection, 1은 생략 가능
- `$ {명령} 2> {파일 이름}`: 명령의 Standard Error(2)의 결과를 파일로 Redirection
- `$ {명령} >> {파일 이름}`: 명령의 Standard Output(1)의 결과를 파일로 Redirection을 기존 파일에 이어 쓰기

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
- `$ ps -ax`: 포어그라운드와 백그라운드에서 동작하고 있는 모든 프로세스를 출력
- `$ ps ax | grep {프로세스 이름}`: 프로세스 이름으로 ps의 결과에서 검색
- `$ kill -9 {PID 번호}`: 특정 PID 번호의 프로세스를 삭제
- `$ top`: 포그라운드와 백그라운드에서 동작하고 있는 모든 프로세스/스레드를 상태와 함께 실시간으로 출력
- `$ fg %{작업의 ID}`: 현재 백그라운드에 있는 프로그램을 포그라운드로 실행
- `$ bg %{작업의 ID}`: 현재 포그라운드에 있는 프로세스를 백그라운드로 보냄
- `$ jobs`: 백그라운드에 존재하는 프로그램을 출력
- Ctrl + z: 포그라운드에서 실행 중인 프로그램을 백그라운드 실행시키는 보내는 단축키
- `$ {명령어} &`: 명령어가 실행될 때 백그라운드로 실행
- 데몬: 항상 실행되는 프로그램
- 서비스: 데몬을 제어하는 명령
- 자동 실행
  - /etc/rc3.d: CLI 방식으로 구동가능한 프로그램을 자동 실행시키기 위해 등록하는 디렉토리로, 프로그램을 링킹해서 등록
  - /etc/rc5.d: GUI 방식으로 구동가능한 프로그램을 자동 실행시키기 위해 등록하는 디렉토리로, 프로그램을 링킹해서 등록
- 정기 실행
  - `$ crontab -e`: 정기적으로 실행할 명령을 작성할 페이지가 나옴
- `$ tail -f {파일 이름}`: 파일이 업데이트 될 때 이를 반영하여 뒷부분을 계속 출력 
- .bashrc / .zshrc: 쉘이 처음에 시작될 때 실행되는 코드

## 사용자
- `$ id`: 유저 아이디, 그룹 아이디 등등을 출력
- `$ who`: 시스템에 접속한 유저를 출력
- `$ su {유저 이름}`: 유저 이름으로 스위칭, 유저 이름을 주지 않으면 root로 스위칭
- `$ useradd -m {유저 이름}`: 유저 이름으로 유저를 하나 추가
- `$ passwd {유저 이름}`: 유저 이름을 갖은 유저의 비밀번호 추가
- `$ usermod -a -G sudo {유저 이름}`: 유저를 수도 그룹으로 추가하여 관지라 권한 부여

## 권한
- 리눅스의 권한 구조 `(_/___/___/___)`
  - 맨 앞은 디렉토리인지 파일인지
  - 유저의 권한: 유저가 Read(r), Write(w), Exceute(x)에 대해 어떻게 권한을 갖고 있는지
  - 그룹의 권한: 유저가 Read(r), Write(w), Exceute(x)에 대해 어떻게 권한을 갖고 있는지
  - Other의 권한: 유저가 Read(r), Write(w), Exceute(x)에 대해 어떻게 권한을 갖고 있는지
- `$ chmod {a,u,g,o}{+,-}{r,w,x} {파일 이름}`: 파일의 All, user, group, other에게 read, write, execute 권한을 +하거나 -
  - -R 옵션을 줄 경우 디렉토리 안에 반복하여 적용
- `$ chmod {숫자}{숫자}{숫자} {파일 이름}`: 파일의 user, group, other에게 read, write, execute 권한을 숫자 표햔에 따라 적용
  - 권한 표
    |8진수|권한|rwx 표기|
    |------|---|---|
    |7|읽기,쓰기,실행|rwx|
    |6|읽기,쓰기|rw-|
    |5|읽기,실행|r-x|
    |4|읽기|r--|
    |3|쓰기,실행|-wx|
    |2|쓰기|-w-|
    |1|실행|--x|
    |0|모든 권한 없음|---|

## 서버 관련 
- `$ df -h`: 디렉토리 별 디스크 용량 확인
- `$ cat /proc/cpuinfo`: CPU 확인
- `$ cat /proc/meminfo`: 메모리 용량 확인
- `$ grep . /etc/issue`: OS 버전 확인


