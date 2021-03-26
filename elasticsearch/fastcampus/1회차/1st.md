# ES 교육 1회차 & 강의 교안 1

<hr>

### ES
* ES - 준 실시간 풀 텍스트 검색엔진이자 분석엔진 오픈소스
* `Lucene(루씬)`
    * 자바 기반의 고성능 정보 검색 라이브러리
    * API를 통해 전문(full-text) 색인과 검색 기능 사용 가능
* 검색엔진으로서의 ES
    * ES 단독으로 사용
    * Lucene 라이브러리를 기반으로 만든 검색 엔진
    * RESTFul API와 JSON 형태의 문서를 지원
    * 루씬이 가진 기능을 제공 하면서도 분산처리를 비롯한 대용량 데이터를 처리하기 위한 다양한 기능을 가짐
* 분석엔진으로서의 ES
    * Beats, Logstash, Kibana를 통해 분석 엔진으로 확장 이용 가능
    * `Beats`: 데이터 수집기용 플랫폼으로 애플리케이션에 설치하여 ES나 Logstash로 데이터를 전송(스트리밍)하는 도구
    * `Logstash`: 필터링한 데이터(로그)를 ES에 문서로 저장하는 도구 
    * `Kibana`: 수집된 데이터를 통계/집계하는 웹 기반 시각화 도구

### ES 용어 및 개념 정리
* `필드`
    * 문서를 구성하기 위한 속성
    * 동적인 데이터 타입을 지원하여 필드 안에 여러 속성이 들어갈 수 있음
* `문서`
    * JSON 형태의 Key-Value 쌍으로 실제 의미 있는 데이터를 가진 ES 저장의 기본 단위
    * Value에 Obejct나 List가 포함될 수 있음
    * 문서를 ES에 저장할 때 설정하거나 랜덤 설정한 고유한 ID를 가짐
    * 문서 ID는 문서 데이터를 찾아가는 고유한 메타 정보
* `타입`
    * 인덱스의 논리적 구조(파티션)를 의미
    * ES 6.x 이상부터 인덱스의 타입은 _doc으로 고정되어 타입을 분류 목적으로 사용하지 않고 인덱스를 분류 목적으로 사용하고 1 Index - 1 Type - 1 Mapping이므로 테이블의 논리적 정의인 스키마와 스키마에 의해 행과 열로 구성된 테이블이 하나씩만 존재하는 데이터베이스라고 생각하면 됨
* `인덱스`
    * 문서가 저장되는 가장 큰 단위
    * 하나의 인덱스에 여러 문서가 저장되는 구조
    * 빠른 검색을 위해 데이터를 정렬 및 분류하여 저장하는 것을 `인덱싱(색인)`이라고 함
    * 최초 데이터를 클러스터에 저장할 때 인덱스가 자동으로 생성되고 매핑 스키마도 동적으로 생성
    * `인덱싱`을 할 경우 클러스터 내의 데이터 노드에 Primary Shard가 제일 먼저 쓰여지고 이후 Replica Shard가 복제
    * 인덱싱 이후 Refresh가 되어 세그먼트에 데이터가 쓰여야 검색이 가능
* `노드`
    * 클러스터를 구성하는 물리적인 인스턴스 내의 ES 프로세스
    * node_name과 node_uuid를 가짐
    * `마스터 노드`: 클러스터를 관리하는 노드
    * `데이터 노드`: 실질적인 데이터를 저장하고 검색과 통계 관련 작업 수행하는 노드
    * `인제스트 노드`: 색인에 앞서 전처리를 하기 위한 노드
    * `클라이언트 노드(코디네이팅 노드)`: 사용자의 쿼리를 받기 위한 노드로 데이터 노드가 리턴해준 데이터를 사용자에게 리턴하는 노드
* `클러스터`
    * 여러 개의 노드를 하나의 논리적인 개념으로 묶어 클러스터라고 부름
    * 클러스터를 대상으로 데이터 저장을 요청하거나 검색 요청을 함
    * 클러스터 내에서 요청을 어떤 노드로 보낼지 정하고 분산 처리함
    * cluster_name과 cluster_uuid를 가짐
* `샤드`
    * `물리적` 공간에 존재하는 여러 개의 `논리적인 파티션`으로 `루씬의 인덱스` 역할을 함
    * 단일 `루씬의 인덱스`가 포함할 수 있는 문서의 최대 한도는 2,147,483,519건
    * 인덱스의 데이터를 샤드 단위로 나누고 복제 및 분산 저장하여 검색의 병렬성을 높이고 안정성을 추구
    * 인덱스를 여러 개의 샤드로 나눠 수평 분할하여 병렬성을 높이고 단일 디스크 볼륨의 한계를 극복하는 것을 `샤딩`이라고 함
    * 샤드 ID를 통해서 샤드를 구분
    * 샤드 할당 알고리즘 = `shard = hash(routing) % number_of_primary_shards`
    * `원본 샤드(Primary Shard)`: 색인되어 저장되는 `문서의 원본 샤드`로 색인 생성 시점에 정의되고 이후 개수를 변경할 수 없고 변경하려면 다시 인덱싱 해야함(6.x 버전에서는 기본 Primary Shard가 5개이고 7.x 버전에서는 1개)
    * `복제본 샤드(Replica Shard)`: 색인되어 들어온 문서의 원본 샤드에 대한 `복제본 샤드`로 복제본의 개수를 변경 가능(1개의 Replica Shard가 기본으로 설정)
    * Fail이 나는 경우 복제본 샤드를 원본 샤드로 승격
    * 인덱싱의 필수 요건은 원본 샤드가 먼저 쓰여져야한다는 것으로 원본 샤드가 전부 다 쓰여진 이후 복제본 샤드가 쓰여짐
* `세그먼트`
    * 샤드보다 더 작은 단위로 문서가 저장되는 최소의 단위로 `물리적인` 단위
    * 문서는 먼저 메모리(페이지 캐시/버퍼 캐시)에 저장되고 이후 Refresh 과정에서 디스크에 파일로 저장(6.x 버전에서는 1초마다 refresh 7.x 버전에서는 30초 동안 검색 요청이 없으면 refresh disable)
    * 저장된 문서는 `immutable 속성`을 가져 update 할 수 없고 update 시엔 copy 이후 update
    * 세그먼트에 쓰이는 Refresh 이후부터 검색이 가능
    * 백그라운드에서 세그먼트들의 병합을 진행

### ES와 관계형 데이터베이스 비교
| 엘라스틱서치 | 관계형 데이터베이스 |
|:--------|:--------|
| 인덱스 | 데이터베이스 |
| 매핑 | 스키마 |
| 타입 | 테이블 |
| 문서 | 행(레코드) |
| 필드 | 열(필드) |
| 샤드 | 파티션 |
| Query DSL | SQL |

### ES 설치하기
* Java 설치 - ES는 Java 기반의 검색 라이브러리인 루씬을 이용한 엔진이므로 자바 설치가 필요
```bash 
yum install -y java-1.8.0-openjdk-devel.x86_64
```

* YUM을 통해 ES 설치
    * repo 등록(6.x버전으로 등록)
    ```bash
    $ vi /etc/yum.repos.d/elasticsearch.repo
    ```
    ```yml
    [elasticsearch-6.x]
    name=Elasticsearch repository for 6.x packages
    baseurl=https://artifacts.elastic.co/packages/6.x/yum
    gpgcheck=1
    gpgkey=https://artifacts.elastic.co/GPG-KEY-elasticsearch
    enabled=1
    autorefresh=1
    type=rpm-md
    ```
    * ES 설치(6.7버전으로 설치)
    ```bash
    $ yum install -y elasticsearch-6.7.0
    ```

* RPM을 다운로드하여 ES 설치
    * wget 설치
    ```bash
    $ sudo yum -y install wget
    ```
    * rpm 다운로드(7.3버전으로 설치)
    ```bash
    $ wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-7.3.0-x86_64.rpm
    ```
    * ES 설치(7.3버전으로 설치)
    ```bash
    $ sudo rpm -ivh elasticsearch-7.3.0-x86_64.rpm
    ```

* 설정 파일
    * `/etc/sysconfig/`에 ES 환경변수 파일 존재 - `elasticsearch`
    * `/etc/elasticsearch`에 ES 환경변수 파일들이 존재 - `elasticsearch.yml` / `jvm.options` / `log4j2.properties` ...
    * `/var/log/elasticsearch/`에 로그 파일들이 존재 - `elasticsearch.log` / {클러스터이름.log} ...

### ES 실행하기 및 실행 확인하기
* 실행
    * init 
    ```bash
    $ sudo service elasticsearch start
    ```

    * systemd
    ```bash
    $ sudo systemctl start elasticsearch.service
    ```

* 재시작
    * init 
    ```bash
    $ sudo service elasticsearch restart
    ```

    * systemd
    ```bash
    $ sudo systemctl restart elasticsearch.service
    ```

* 종료
    * init 
    ```bash
    $ sudo service elasticsearch stop
    ```

    * systemd
    ```bash
    $ sudo systemctl stop elasticsearch.service
    ```

* 실행 확인하기
    * 프로세스 실행 확인
    ```bash
    $ ps -ef | grep elasticsearch
    ```
    * 어플리케이션 반응 확인(ES는 9200번을 기본 포트로 사용)
    ```bash
    $ curl localhost:9200
    ```

### ES 클러스터링
* `/etc/elasticsearch/elasticsearch.yml`에 ES 노드 별로 클러스터링 환경 설정이 가능
    * 마스터 노드
    ```yml
    # Cluster name
    cluster.name: alan-cluster

    # Node name
    node.name: alan-es-master-1

    # Paths
    path.data: /var/lib/elasticsearch
    path.logs: /var/log/elasticsearch

    # Network - bind_host는 해당 노드가 받아들일 인터페이스 / publish_host는 본인 IP
    network.bind_host: 0.0.0.0
    network.publish_host: 10.202.19.29

    # Set a custom port for HTTP 
    http.port: 9200

    # Discovery - Dicovery를 위한 마스터 노드의 IP와 최소 필수 마스터 노드의 개수
    discovery.zen.ping.unicast.hosts: ["10.202.19.29","10.202.19.12","10.202.19.24"]
    discovery.zen.minimum_master_nodes: 2

    # Node - 노드 역할 설정
    node.master: true
    node.data: false

    # For Head - Head 플러그인을 위한 설정
    http.cors.enabled: true
    http.cors.allow-origin: "*"

    # For TCP among nodes - 노드들 간의 TCP 연결을 위한 포트
    transport.tcp.port: 9300
    ```

    * 데이터 노드
    ```yml
    # Cluster
    cluster.name: alan-cluster

    # Node
    node.name: alan-es-data-1

    # Paths
    path.data: /var/lib/elasticsearch
    path.logs: /var/log/elasticsearch

    # Network
    network.bind_host: 0.0.0.0
    network.publish_host: 10.202.19.29

    # Set a custom port for HTTP
    http.port: 9200

    # Discovery
    discovery.zen.ping.unicast.hosts: ["10.202.19.29","10.202.19.12","10.202.19.24"]
    discovery.zen.minimum_master_nodes: 2

    # Node
    node.master: true
    node.data: false

    # For Head
    http.cors.enabled: true
    http.cors.allow-origin: "*"

    # For TCP among nodes
    transport.tcp.port: 9300
    ```

### Kibana 설치 및 Dev Tools 활용하기
* YUM을 통해 설치하기
    * repo 등록(6.x 버전으로 등록)
    ```bash
    $ vi /etc/yum.repos.d/kibana.repo
    ```
    ```yml
    [kibana-6.x]
    name=Kibana repository for 6.x packages 
    baseurl=https://artifacts.elastic.co/packages/6.x/yum 
    gpgcheck=1 
    gpgkey=https://artifacts.elastic.co/GPG-KEY-elasticsearch 
    enabled=1
    autorefresh=1
    type=rpm-md
    ```
    * Kibana 설치
    ```bash
    $ sudo yum install kibana
    ```
* 설정 파일
    * `/etc/kibana/`에 Kibana 환경변수 파일 존재 - `kibana.yml`
    ```yml
    server.host: "0.0.0.0"
    elasticsearch.url: "http://localhost:9200" 
    kibana.index: ".kibana"
    ```
    * 7.x부터는 elasticsearch.url이 elasticsearch.hosts로 필드 명이 변경
* Kibana 실행하기
    * init 
    ```bash
    $ sudo service kibana start
    ```
    * systemd
    ```bash
    $ sudo systemctl start kibana.service
    ```
* 실행 확인하기
    * 프로세스 실행 확인
    ```bash
    $ ps -ef | grep node
    ```
* Kibana 웹을 통해서 ES에 쿼리를 날릴 수 있는 Dev Tools가 존재
* Elastic Stack(ElasticSearch, Logstash, Kibana)은 하나의 패키지로 버전을 같게 설치해야함

### 보충
* 페이지 캐시: 디스크 접근을 최소화 하여 파일 I/O 성능을 향상시키기 위해 사용되는 메모리 영역으로 한 번 읽은 파일의 내용을 이 페이지 캐시 영역에 저장하고 같은 파일의 접근이 일어나면 디스크에서 읽어오는 것이 아니라 페이지 캐시에서 읽음
* 버퍼 캐시: 디스크의 블록 단위로 데이터를 전송하는 블록 디바이스가 가지고 있는 블록 자체에 대한 캐시로 커널이 특정 블록에 접근하면 블록의 내용을 버퍼 캐시 영역에 저장하고 동일한 블록에 접근할 시에 버퍼 캐시에서 읽음(현재는 페이지 캐시가 버퍼 캐시 내에 포함되어 있음)
* init와 systemd 차이: RHEL7/CentOS7로 올라오면서 전체 시스템 초기화 및 관리 프로세스를 init 프로세스에서 systemd로 바꾸었음
* systemd와 systemctl: systemctl은 systemd의 자원 통합 관리 도구로 systemd를 제어
* systemctl 사용법 
    - 서비스 활성화/비활성화
    ```bash
    $ systemctl enable/disable [서비스명]
    ```
    - 서비스 시작/종료/재시작
    ```bash
    $ systemctl start/stop/restart [서비스명]
    ```
    - 서비스 갱신
    ```bash
    $ systemctl reload [서비스명]
    ```
