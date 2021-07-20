# Docker 정리 자료
[초보를 위한 도커 안내서](https://subicura.com/2017/01/19/docker-guide-for-beginners-1.html)과 도커/쿠버네티스를 활용한 컨테이너 개발 실전 입문(야마다 아키노리)를 정리하여 만들었습니다.

Table of contents
=================
<!--ts-->
   * [Docker](#Docker)
   * [Container](#Container)
   * [Advantage](#Advantage)
   * [Disadvantage](#Disadvantage)
   * [Installation](#Installation)
   * [Run](#Run)
   * [Command](#Command)
   * [Docker Compose](#Docker-Compose)
   * [Making Image](#Making-Image)
   * [Docker Hub](#Docker-Hub)
   * [Deployment](#Deployment)
   * [Docker API](#Docker-API)
   * [Advanced](#Advanced)
<!--te-->

Docker
=======
* `도커`: 컨테이너 기반의 가상화 오픈소스 플랫폼
* 기능
  * 다양한 프로그램, 실행환경을 컨테이너로 추상화하고 동일한 인터페이스를 제공하여 프로그램의 배포 및 관리를 단순하게 해준다.
  * 개발환경 구축뿐만 아니라 개발 후 운영 환경에 대한 배포나 애플리케이션 플랫폼으로 사용이 가능하다.
  * 서버 관리는 서버 환경 설정 및 개발 환경 설정이 달라지며 설치하는 애플리케이션에 따라 충돌 등의 문제로 관리가 어려워졌기 때문에 `도커`를 사용하여 서버관리 및 개발 방식을 편하게 함

Container
=======
* `컨테이너`: 컨테이너는 격리된 공간에서 `프로세스`가 동작하는 기술
* 가상머신: 도커와 같이 한 서버에 여러 개를 설치할 수 있고 서버의 상태 자체를 이미지로 그대로 활용할 수 있게 하는 기술
* 가상머신(OS 가상화)과 도커(컨테이너)의 차이: 기존의 가상머신들은 0S 자체를 가상화하여 호스트 OS 위에 하이퍼바이저를 통해 게스트 OS 전체를 가상화하여 사용하였으나 컨테이너는 전체 OS를 가상화하는 방식이 아니라 도커 엔진이 호스트의 자원을 직접 격리하여 이용하기 때문에 가볍고 빠르다.
* `이미지`: 컨테이너 실행에 필요한 파일과 설정값등을 포함하고 있는 것으로 상태값을 가지지 않고 변하지 않는다. Dockerfile을 이용하여 만든 이미지는 컨테이너의 템플릿이고 컨테이너는 이미지를 실행한 상태이다. `ex) Ubuntu, MySQL, Go, Redis, Nginx....`
* `컨테이너 오케스트레이션 도구`: `Docker Compose`와 `Docker Swarm` 그리고 `Kubernetes`가 존재한다. 단일 서버의 여러 컨테이너 관리만이 목적이라면 Docker Compose를 사용하고 여러 서버에 걸쳐 있는 여러 컨테이너를 관리가 목적이라면 `Docker Swarm`와 `Kubernetes`를 사용한다.
* 컨테이너 오케스트레이션 도구의 특징
  - 스케줄링: 컨테이너를 `적당한 서버`에 배포해 주는 작업
  - 클러스터링: 여러 개의 서버를 하나의 서버처럼 사용
  - 서비스 디스커버리: 클러스터 환경에서 컨테이너는 어느 서버에 생성될지 알 수 없는데, 서비스를 찾아주는 기능

Advantage
=======
* `레이어 저장 방식`: 유니온 파일 시스템을 이용하여 여러 개의 레이어를 하나의 파일시스템으로 사용하여 이미지 파일이 추가되거나 수정되면 새로운 레이어가 생성되고 기존의 레이어를 제외한 내용만 새로 디운로드 받기 때문에 효율적으로 이미지 관리를 할 수 있다.
* `Dockerfile`: 자체 DSL(Domain Specific Language)언어를 이용하여 `코드 기반으로` 이미지 생성 과정을 적는 Dockerfile을 통해서 이미지를 만들어서 프로그램 설치 및 설정 과정을 간단하게 하고 쉽게 관리할 수 있어 복제 및 배포에서 높은 재현성을 갖고 있다.
* `Docker Hub`: 큰 용량의 이미지를 서버에 저장하고 관리하는 것은 쉽지 않은데 도커는 Docker Hub를 통해 공개 이미지를 무료로 관리해주는 서비스를 제공한다.
* `Command와 API`: 도커의 대부분의 명령어는 직관적이고 사용하기 쉬우며 `Docker REST API`도 지원하여 확장성이 좋다.
* `배포 효율성`: 명령어를 통해 쉽게 프로그램을 배포 확장할 수 있고 `애플리케이션과 인프라 실행 환경`을 묶어 통째로 배포하는 방식으로 의존성 문제를 근본적으로 해결한다.
* `성능`: 이미지 용량이 크게 줄어들고 하드웨어를 가상화하는 계층(Hyper-V)이 없이 호스트의 자원을 직접 이용하기 때문에 가상머신에 비해 가볍고 빠르면서 스케일 아웃 또한 쉽다.

Disadvantage
============
* 리눅스 기반 플랫폼: 도커 자체는 리눅스 기반이기 때문에 리눅스가 호스트에 있을 때 최적으로 동작한다. 기존에는 윈도우와 맥을 호스트 OS로 사용할 수 없었으나 최근에는 도입이 되긴 했다.


Installation
=======
* 리눅스에서 도커 설치하기
  * Docker Script를 이용한 설치 
  ```sh
  $ curl -fsSL https://get.docker.com/ | sudo sh
  ```
  * Docker 설치 확인
  ```sh
  $ docker version
  ```
  * Docker에 sudo 권한 부여
  ```sh
  $ sudo setfacl -m user:$USER:rw /var/run/docker.sock
  ```
* 도커 실행 시의 특징: 도커는 하나의 실행파일이지만 실제로 클라이언트와 서버역할을 각각 할 수 있다. 도커 커맨드를 입력하면 도커 클라이언트가 도커 서버로 명령을 전송하고 결과를 받아 터미널에 출력하는 구조이다.

Run
=======
* 컨테이너 실행하기 
  ```sh
  $ docker run [OPTIONS] IMAGE[:TAG] [COMMAND] [ARG...]
  ```
* 컨테이너 실행 옵션  

| 옵션 |설명 |
|:--------|:--------|
| `-d` | detached mode 흔히 말하는 백그라운드 모드 |
| `-p` | 호스트 포트와 컨테이너 포트를 연결 `(포워딩)` |
| `-v` | 호스트와 컨테이너의 디렉토리를 연결 `(마운트)` - 데이터 볼륨, {호스트 디렉토리}:{컨테이너 내 디렉토리} |
| `-e` | 컨테이너 내에서 사용할 환경변수 설정 |
| `-name` | 컨테이너 이름 설정 |
| `-rm` | 프로세스 종료시 컨테이너 자동 제거 |
| `-it` | -i와 -t를 동시에 사용한 것으로 터미널 입력을 위한 옵션 |
| `-link` | 컨테이너 연결 [컨테이너명:별칭] |
| `--network` | 속할 네트워크 지정 |

* 우분투 컨테이너 실행하기
  * 컨테이너 실행하기
  ```sh
  $ docker run ubuntu:20.04
  ```
  * 실행 프로세스(Bash)가 전달된 컨테이너 실행
  ```sh
  $ docker run --rm -it ubuntu:20.04 /bin/sh
  ```
* Redis 컨테이너 실행하기
  * 컨테이너 실행하기
  ```sh
  $ docker run -d -p 1234:6379 redis
  ```
* MySQL 컨테이너 실행하기
  * 컨테이너 실행하기
  ```sh
  $ docker run -d -p 3306:3306 -e MYSQL_ALLOW_EMPTY_PASSWORD=true --name mysql mysql:5.7
  ```

Command
=======
* 컨테이너 목록 확인하기
  ```sh
  $ docker ps [OPTIONS]
  ```
  * -a 옵션은 중지, 종료된 모든 컨테이너 리스트를 보여줌
* 컨테이너 실행하기
  ```sh
  $ docker run [OPTIONS] IMAGE[:TAG] [COMMAND] [ARG...]
  ```
* 컨테이너 중지하기
  ```sh
  $ docker stop [OPTIONS] CONTAINER [CONTAINER...]
  ```
* 컨테이너 재시작하기
  ```sh
  $ docker restart [OPTIONS] CONTAINER [CONTAINER...]
  ```
* 컨테이너 제거하기
  ```sh
  $ docker rm [OPTIONS] CONTAINER [CONTAINER...]
  ```
* 컨테이너 로그 확인
  ```sh
  $ docker logs [OPTIONS] CONTAINER
  ```
  * -f 옵션을 하면 계속 대기하면서 추가적으로 보여줌
* 구동 중인 컨테이너에 명령어 실행하기
  ```sh
  $ docker exec [OPTIONS] CONTAINER COMMAND [ARG...]
  ```
* 구동 중인 컨테이너에 지속적 명령을 위해 접속하기
  ```sh
  $ docker exec -it CONTAINER /bin/bash
  ```
* 이미지 빌드하기
  ```sh
  $ docker build IMAGE[:TAG] Dockerfile_PATH
  ```
* 이미지 태깅하기
  ```sh
  $ docker tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG]
  ```
* 이미지 업로드하기
  ```sh
  $ docker push Docker_REGISTRY_URL/IMAGE[:TAG]
  ```
* 다운로드된 이미지 목록 확인하기
  ```sh
  $ docker images [OPTIONS] [REPOSITORY[:TAG]
  ```
* 이미지 다운로드하기
  ```sh
  $ docker pull [OPTIONS] REPOSITORY_NAME[:TAG]
  ```
* 이미지 삭제하기
   ```sh
   $ docker rmi [OPTIONS] IMAGE [IMAGE...]
   ```
* 이미지 내역 확인하기
  ```sh
  $ docker image history IMAGE
  ```
* 컨테이너끼리 통신할 수 있는 가상 네트워크 만들기
  ```
  $ docker network create [OPTIONS] NETWORK
  ```
* 가상 네트워크에 컨테이너 추가하기
  ```
  $ docker network connect [OPTIONS] NETWORK CONTAINER
  ```


Docker Compose
=======
* `Docker Compose`: 하나의 호스트 안에 있는 여러 컨테이너의 복잡한 설정을 쉽게 관리하기 위해 YAML방식의 설정파일을 이용하는 툴
* Docker Compose 설치하기
  * 설치하기
  ```sh
  $ curl -L "https://github.com/docker/compose/releases/download/1.9.0/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
  ```
  * 권한설정
  ```sh
  $ chmod +x /usr/local/bin/docker-compose
  ```
  * 설치확인
  ```sh
  $ docker-compose version
  ``` 
* docker-compose.yml 파일을 통해 Wordpress 컨테이너 만들기
  * docker-compose.yml 파일 정의
  ```yml
  version: '2' # 파일 명세 버전
  services: 
    db: # 컨테이너 정의
      image: mysql:5.7 # 컨테이너에 사용할 이미지 이름과 태그
      volumes:
            - db_data:/var/lib/mysql
      restart: always
      environment:
            MYSQL_ROOT_PASSWORD: wordpress
            MYSQL_DATABASE: wordpress
            MYSQL_USER: wordpress
            MYSQL_PASSWORD: wordpress
    django:
      build: # 이미지를 자체 빌드하기 위해 image 속성 대신 사용(도커 파일 필요)
      context: .
      dockerfile: ./compose/django/Dockerfile-dev
    wordpress: 
      depends_on:
            - db
      image: wordpress:latest
      volumes:
            - wp_data:/var/www/html
      ports: # 포트 연결 ({호스트 포트}:{컨테이너 포트})
            - "8000:80"
      restart: always
      environment: # 컨테이너에서 사용할 환경변수({환경변수 이름}:{값})
            WORDPRESS_DB_HOST: db:3306
            WORDPRESS_DB_PASSWORD: wordpress
  volumes: # 마운트 하려는 디렉토리 ({호스트 디렉터리}:{컨테이너 디렉터리})
    db_data: 
    wp_data:
  ```
  * 실행하기
  ```sh
  $ docker-compose up
  ```
  * 정지하기
  ```sh
  $ docker-compose down
  ```
* docker-compose yml 형식
  * `version`: docker compose 문법 버전
  * `services`: 컨테이너 이름
  * `images`: 도커의 이미지
  * `ports`: 포트포워딩 설정
  * `build`: image 속성 대신 사용하는 요소로 Dockerfile의 경로를 지정
  * `volumes`: 호스트와 컨테이너 사이에 파일을 공유할 수 있는 매커니즘


Making Image
=======
* 도커 이미지 만들기: 도커는 가상머신의 스냅샷과 같은 방식으로 애플리케이션을 설치하고 그 상태로 이미지를 저장한다.
* Dockerfile 기본 명령어
  * FROM: 베이스 이미지(운영체제)를 정의
  ```yml
  FROM <image>:<tag>
  ```
  ```yml
  FROM ubuntu:16.04
  ```
  * MAINTAINER: Dockerfile을 관리하는 사람의 정보를 저장 
  ```yml
  MAINTAINER <name>
  ```
  ```yml
  MAINTAINER subicura@subicura.com
  ```
  * COPY: 컨테이너에서 실행할 실행 파일이나 디렉토리를 이미지로 복사
  ```yml
  COPY <src>... <dest>
  ```
  ```yml
  COPY . /usr/src/app
  ```  
  * ADD: COPY와 유사하나 `src`에 파일 대신 URL을 입력할 수 있음 
  ```yml
  ADD <src>... <dest>
  ```
  ```yml
  ADD . /usr/src/app
  ``` 
  * RUN: 이미지를 빌드할 때 실행되는 컨테이너 안에서 실행할 명령 정의
  ```yml
  RUN ["executable", "param1", "param2"] (추천)
  RUN <command>
  ```
  ```yml
  RUN bundle install
  ``` 
  * CMD: 도커 컨테이너가 구동을 시작했을 때 실행할 명령어를 정의
  ```yml
  CMD ["executable", "param1", "param2"] (추천)
  CMD <command> <param1> <param2>
  ```
  ```yml
  CMD bundle exec ruby app.rb
  ``` 
  * WORKDIR: RUN, CMD, ADD, COPY등이 이루어질 기본 디렉토리를 설정
  ```yml
  WORKDIR <path>
  ```
  ```yml
  WORKDIR /path/to/workdir
  ```
  * EXPOSE: 도커 컨테이너가 실행되었을 때 요청을 기다리고 있는(Listen) 포트를 지정
  ```yml
  EXPOSE <port> [<port>...]
  ```
  ```yml
  EXPOSE 4567
  ``` 
  * VOLUME: 컨테이너 외부에 파일시스템을 마운트 할 때 사용
  ```yml
  VOLUME <path>
  ```
  ```yml
  VOLUME ["/data"]
  ``` 
  * ENV: 컨테이너에서 사용할 환경변수를 지정
  ENV <key> <value>
  ENV <key>=<value> ...
  ```yml
  ENV DB_URL mysql
  ``` 
  * ENTRYPOINT: 컨테이너 기본 실행 명령어
  * USER: RUN, CMD, ENTRYPOINT를 실행하는 사용자
  * WORKDIR: 작업 디렉토리 설정
  * ARGS: 빌드타임 환경변수 설정
  * LABEL: key - value 데이터
  * ONBUILD: 다른 빌드의 베이스로 사용될때 사용하는 명령어
* 깃을 설치한 우분투 이미지 만들기
  * 우분투 컨테이너 실행
  ```sh
  $ docker run -it --name git ubuntu:latest bash
  ```
  * 컨테이너 내에서 깃 설치
  ```sh
  $ apt-get update
  $ apt-get install -y git
  $ git --version
  ```
  * 이미지 빌드하기(커밋)
  ```sh
  $ docker commit git ubuntu:git
  ```
* 깃을 설치한 우분투 이미지 만들기 방법2
  * 도커 파일 만들기
  ```yml
  FROM ubuntu:latest
  RUN apt-get update
  RUN apt-get install -y git
  ```
  * 
  ```sh
  $ docker build -t ubuntu:git-dockerfile .
  ```
* Sinatra 애플리케이션 `Dockerizing`
  * Ruby 패키지 파일 생성
  ```sh
  $ vi Gemfile
  ```
  ```yml
  source 'https://rubygems.org'
  gem 'sinatra'
  ```
  * Ruby 소스 파일 생성
  ```sh
  $ vi arr.rb
  ```
  ```ruby
  require 'sinatra'
  require 'socket'
  get '/' do
    Socket.gethostname
  end
  ```
  * Dockerfile(빌드 파일) 생성
  ```yml
  # 1. ubuntu 설치 (패키지 업데이트 + 만든사람 표시)
  FROM       ubuntu:16.04
  MAINTAINER subicura@subicura.com
  RUN        apt-get -y update

  # 2. ruby 설치
  RUN apt-get -y install ruby
  RUN gem install bundler

  # 3. 소스 복사
  COPY . /usr/src/app

  # 4. Gem 패키지 설치 (실행 디렉토리 설정)
  WORKDIR /usr/src/app
  RUN     bundle install

  # 5. Sinatra 서버 실행 (Listen 포트 정의)
  EXPOSE 4567
  CMD    bundle exec ruby app.rb -o 0.0.0.0
  ```
  또는
  ```yml
  FROM ruby:2.3
  MAINTAINER subicura@subicura.com
  COPY Gemfile* /usr/src/app/
  WORKDIR /usr/src/app
  RUN bundle install --no-rdoc --no-ri
  COPY . /usr/src/app
  EXPOSE 4567
  CMD bundle exec ruby app.rb -o 0.0.0.0
  ```
  * 이미지 빌드하기
  ```sh
  $ docker build -t app .
  ```
  * 이미지 확인하기
  ```sh
  $ docker images
  ```

Docker Hub
=======
* `도커 레지스트리`: 도커는 빌드한 이미지를 서버에 배포하기 위해 직접 파일을 복사하는 방법 대신 도커 레지스트리 `Docker Registry`라는 이미지 저장소를 사용하여 push와 pull하는 구조이다. `Docker Registry`를 사용하기 싫다면 `Docker Hub`를 사용할 수 있다.
* `Docker Hub`: 도커에서 제공하는 기본 이미지 저장소로 대용량의 이미지를 무료로 저장 및 다운로드 할 수 있다. 단, 기본적으로 모든 이미지는 공개되어 누구나 접근 가능하므로 비공개로 사용하려면 유료 서비스를 이용해야한다.
* Docker Hub 사용하기
  * 도커 허브 페이지에서 회원 가입을 하고 허브 계정을 사용하기
  ```sh
  $ docker login
  ```
  * 도커 이미지 태깅하기
  ```
  $ docker tag SOURCE_IMAGE[:TAG] TARGET_IMAGE[:TAG]
  ```
  cf) 도커 이미지 구조: `[사용자 ID]/[이미지명]:[tag]`
  * 도커 허브에 이미지를 전송
  ```sh
  $ docker push IMAGE[:TAG]
  ```

Deployment
=======
* 도커 배포하기
  * 서버 환경에서 등록된 이미지를 다운받고 컨테이너를 실행
* 도커 컨테이너 업데이트하기
  * 최신 이미지를 기반으로 새 컨테이너를 만들고 이전 컨테이너를 삭제


Docker API
=======
* 컨테이너 리스트 얻기: `GET /containers/json`
* 컨테이너 생성: `POST /containers/create` + Request Body
* 컨테이너 시작: `POST /containers/{id}/start`
* 컨테이너 정지: `POST /containers/{id}/stop`
* 컨테이너 재시작: `POST /containers/{id}/restart`
* 컨테이너 종료: `POST /containers/{id}/kill`

Advanced
=======
* 애플리케이션과 시스템 내 단일 컨테이너의 적정 비중
  * 컨테이너 1개 == 프로세스 1개가 아닌 컨테이너 1개는 `한가지 역할이나 문제 영역에 집중하는 것`이 옳은 설계이므로 컨테이너가 맡을 역할을 적절히 나누고 시스템에 설계해야한다.
* 컨테이너의 이식성
  * 이식성: 도커의 장점으로 어떤 호스트 운영체제와 플랫폼에서든 그대로 동작하는 것이 장점이다.
  * 도커의 이식성이 사라지는 경우
    1. 호스트 운영체제와 커널 리소스를 공유하기 때문에, `x86_64` 아키텍처 리눅스 기반 호스트에서만 실행이 보장된다.
    2. `동적 링크`의 경우 라이브러리가 다르다면 동작하지 않으므로 되도록 네이티브 라이브러리를 정적 링크하여 이미지를 빌드해야한다.
* 환경 변수 사용
  * 실행 시 인자 사용: CMD같은 명령을 통해서 실행할 때 사용할 명령을 정의할 수 있으나 명령이 많아지면 관리하기가 어려워질 수 있다.
  * 애플리케이션 설정 파일 사용: maven이나 gradle같은 애플리케이션 설정 파일을 통해서 제어하면 도커 이미지를 각각의 설정 파일 별로 만들어 둬야한다. 
  * 애플리케이션 동작을 환경 변수로 제어: 매번 이미지를 다시 빌드하지 않아도 되지만, 게층 구조를 가지기는 어렵다.
  * 애플리케이션 설정 파일에 환경 변수로 제어: 설정 파일에서 환경 변수를 포함할 수 있다면 환경 변수를 포함한 파일을 이미지로 되므로 가장 좋은 방법이다.
* 영속적인 데이터를 다루는 방법
  * `데이터 볼륨`: 컨테이너 안의 디렉토리를 디스크에 퍼시스턴스 데이터로 남기기 위한 매커니즘으로 `호스트`와 `컨테이너` 사이의 지정한 디렉터리 공유 및 재사용 기능을 제공하여 컨테이너를 파기해도 디스크에 남아 영속적으로 데이터를 저장할 수 있다.
  * `데이터 볼륨 컨테이너`: 컨테이너 간의 디렉토리를 공유하는 매커니즘으로 디스크에 저장된 컨테이너가 갖는 퍼시스턴스 데이터를 볼륨으로 만들어 다른 컨테이너에 공유하는 데이터를 저장하는 것만이 목적인 컨테이너를 이용하여 `var/lib/docker/volumes/` 아래에 볼륨을 위치시켜 영속적으로 데이터를 저장할 수 있다. 
