# ES 교육 2회차 & 강의 교안 2

<hr>

### HTTP와 기본적인 의미
| 엘라스틱서치 HTTP 메소드 | CRUD |
|:------------|:------------|
| GET | READ |
| POST | CREATE |
| PUT | UPDATE |
| DELETE | DELETE |

`대표적인 API 요청 구조 = (HTTP 메서드) (인덱스)/(타입)/(문서id){json 데이터}`  

cf) HEAD 메소드는 자주 사용하지 않고 PUT 메소드는 업데이트 대상이 없을 시 POST 처럼 사용되기도 함

### 인덱스 생성 및 삭제, 조회
* 인덱스를 생성하는 방법
    * 인덱스의 `settings`를 정의
        1. 고정적인 인덱스 설정 - 원본 샤드 개수
        2. 동적으로 변경 가능한 인덱스 설정 - 복제본 샤드 개수 / refresh 주기 / 샤드 간의 라우팅 허용 여부  
            ```json 
            PUT {인덱스 이름} {"settings": {"index":{"number_of_shards":3, "number_of_replicas":1}}}
            ```
            ```json
            PUT {인덱스 이름} {"settings": {"index.number_of_shards":3, "index.number_of_replicas":1}
            ```
    * 인덱스의 스키마인 `mappings`를 정의  
    * 문서를 바로 인덱싱 - 기본 setting으로 설정되고 dynamic mapping이 발생

* 인덱스를 삭제하는 방법
    * DELETE 메소드를 사용  
    `DELETE {인덱스 이름}`

* 인덱스의 존재를 확인하는 방법
    * HEAD 메소드를 사용  
    `HEAD {인덱스 이름}` 

* 인덱스의 정보를 조회하는 방법
    * GET 메소드를 사용
    `GET {인덱스 이름}/_settings` 인덱스의 셋팅을 확인  
    `GET {인덱스 이름}/_mappings` 인덱스의 매핑을 확인  
    `GET {인덱스 이름}/_mapping` 인덱스의 매핑을 확인  
    `GET {인덱스 이름}/_stats` 인덱스의 상태를 확인  
    `GET {인덱스 이름}/_segments` 인덱스의 샤드 및 세그먼트 정보를 확인  
    `GET _cat/indices?v` 인덱스의 요약 정보를 확인  
    `GET _cat/indices/{인덱스 이름}?v` 인덱스의 요약 정보를 확인  

### 문서 색인 및 조회
* 문서를 색인하는 방법
    * PUT 메소드를 사용  
    문서 1번으로 인덱싱  
    ```json
    PUT {인덱스 이름}/_doc/1 {"user" : "kimchy","post_date" : "2009-11-15T14:12:12", "message" : "trying out Elasticsearch"}
    ```  
    ID가 없을 때만 문서 1번으로 인덱싱  
    ```json 
    PUT {인덱스 이름}/_doc/1/_create {"user" : "kimchy", "post_date" : "2009-11-15T14:12:12", "message" : "trying out Elasticsearch"}
    ```  
    ID가 없을 때만 문서 1번으로 인덱싱  
    ```json
    PUT {인덱스 이름}/_doc/?op_type=create {"user" : "kimchy", "post_date" : "2009-11-15T14:12:12", "message" : "trying out Elasticsearch"}
    ```  
    * POST 메소드를 사용  
    문서 ID를 랜덤하게 생성하여 인덱싱
    ```json
    POST {인덱스 이름}/_doc {"user" : "kimchy","post_date" : "2009-11-15T14:12:12", "message" : "trying out Elasticsearch"}
    ```  
    cf) PUT은 ID가 무조건 있어야 색인 가능하나 POST는 ID가 있어도 없어도 색인 가능

* 문서를 조회하는 방법
    * GET 메소드를 사용  
    `GET {인덱스 이름}/_doc/1` ID 1번 문서 조회  
    `GET {인덱스 이름}/_doc/1/_source` ID 1번 문서의 실제 데이터인 _source만 조회


### 문서 갱신 및 삭제
* 문서를 갱신하는 방법
    * POST/PUT 메소드를 사용  
    ID 1번 문서 업데이트(없을 시 생성)
    ```json
    PUT {인덱스 이름}/_doc/1 {"user" : "kimchy", "post_date" : "2009-11-15T14:12:12", "message" : "trying out Elasticsearch"}
    ```

* 문서를 삭제하는 방법
    * DELETE 메소드를 사용  
    `DELETE {인덱스 이름}/_doc/1` ID 1번 문서 삭제

### 인덱스 생성과 문서 조회 시의 매커니즘
* 인덱스 생성에서의 매커니즘
    인덱스는 프라이머리 샤드가 먼저 완전히 쓰이고 이후 리플리카 샤드가 복제되는 매커니즘을 가짐
* 문서 조회에서의 매커니즘
    조회 요청을 받은 노드가 직접 클라이언트에게 리턴해주는 것이 빠르지만 병렬성이 떨어지므로 조회 요청을 `Round Robin`으로 처리

### 클러스터 정보 확인
* 클러스터 상태 정보를 확인하는 방법
    * GET 메소드를 사용  
    `GET _cluster/health` 클러스터 health 확인  
    `GET _cluster/settings` 클러스터 setting 확인

### ES 플러그인
* 플러그인은 ES 기능을 커스텀 설정에 의해 좀 더 강화하여 사용하는 방법으로 플러그인을 로딩하려면 `클러스터 재시작`이 필요
* Core Plugins - Elasticsearch에서 공식적으로 지원하는 플러그인
* Community Plugins - Elasticsearch에서 공식 지원이 아닌 플러그인

### 주요 플러그인
* HEAD 플러그인 - 한눈에 클러스터를 보기 위한 도구로 접속 포트 9100번 사용
* HQ 플러그인 - 한눈에 클러스터의 사용률을 보기 위한 도구로 접속 포트 5000번 사용

##### HEAD 플러그인 설치 
* ElasticSearch 클러스터의 노드, 인덱스, 샤드 등을 한 눈에 볼 수 있는 플러그인
* 2.x 버전까지는 내부 빌트인 플러그인 형태로 존재했으니 5.x 버전부터 standalone 형태로 변경되어 별도 설치가 필요
* 9100 포트로 실행됨

```bash
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo yum -y install git
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo yum -y install bzip2 epel-release
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo yum -y install npm
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ cd /usr/local/
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo git clone https://github.com/mobz/elasticsearch-head.git
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ cd elasticsearch-head/
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo npm install
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ nohup npm run start &
```

#### HQ Plugin 설치 
* 클러스터의 노드나 상세 상태정보 값을 모니터링 할 수 있는 플러그인
* Head Plugin과 마찬가지로 2.x 버전까지는 내부 빌트인 플러그인 형태로 존재했으니 5.x 버전부터 standalone 형태로 변경되어 별도 설치가 필요
* 5000 포트로 실행됨

```bash
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo yum -y install git
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo yum -y install bzip2 epel-release
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ cd /usr/local/
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo git clone https://github.com/ElasticHQ/elasticsearch-HQ.git
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ cd elasticsearch-HQ/
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo yum -y install python34 python34-pip
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo pip3 install -r requirements.txt
[ec2-user@ip-xxx-xxx-xxx-xxx ~]$ sudo nohup python3 application.py &
```

### 보충
* ES 7.x 이상부터는 일부 명령어에서 type(_doc)을 생략하는 것이 디폴트로 되어 있음  
  `GET twitter/_doc/1/_source` -> `GET twitter/_source/1`
* POST와 PUT의 차이: HTT와 ES에서 PUT과 POST의 차이는 PUT은 식별자가 반드시 존재해야하고 POST는 그렇지 않음(기본적으로 POST는 생성의 의미 PUT은 업데이트의 의미)
