# 인프런 ELK 강의 섹션 1

### 엘라스틱서치
- 확장성이 뛰어난 오픈 소스 `텍스트 검색` 및 `분석 엔진` 기능 제공
- 데이터를 신속하고 거의 실시간으로 저장 그리고 검색 및 분석
- Near Realtime으로 검색 가능할 때까지 약간의 대기 시간 (일반적으로 1 초)이 매우 짧음
- 엘라스틱서치 핵심 개념
  - `클러스터 (Cluster)`
    - 전체 데이터를 함께 보유하고 모든 노드에서 연합 인덱싱 및 검색 기능을 제공하는 하나 이상의 노드 (서버) 모음
    - 클러스터는 기본적으로 고유한 이름으로 식별
    - 이 이름은 노드가 이름으로 클러스터에 참여하도록 설정된 경우 노드가 클러스터의 일부일 수 있기 때문에 중요
  - `노드 (Node)`
    - 노드는 클러스터의 일부이며 데이터를 저장하고 클러스터의 인덱싱 및 검색 기능에 참여하는 단일 서버
    - 단일 클러스터에서 원하는 만큼의 노드를 소유 가능
    - 또한 현재 네트워크에서 실행중인 다른 Elasticsearch 노드가 없는 경우 단일 노드를 시작하면 기본적으로 elasticsearch라는 새로운 단일 노드 클러스터가 형성
  - `인덱스 (Index)` - RDB의 데이터베이스
    - 색인은 다소 유사한 특성을 갖는 문서의 콜렉션
    - 예를 들어, 고객 데이터에 대한 색인, 제품 카탈로그에 대한 또 다른 색인 및 주문 데이터에 대한 또 다른 색인을 가질 수 있음
    - 색인은 이름(모두 소문자 여야 함)로 식별되며 이 이름은 색인 된 문서를 색인 작성, 검색, 갱신 및 삭제할 때 색인을 참조하는 데 사용
  - `Type` - RDB의 테이블
    - 사용자가 하나의 유형, 블로그 게시물을 다른 유형과 같이 여러 Type의 문서를 동일한 색인에 저장할 수 있도록 색인의 논리적 범주 / 파티션으로 사용되는 유형
    - 더 이상 인덱스에 여러 유형을 작성할 수 없으며 `Type이라는 전체 개념이 제거`되어 _doc 으로 고정
  - `Documents` - RDB의 레코드(열)
    - 문서는 색인을 생성 할 수 있는 최소 정보 단위
    - 단일 고객에 대한 문서, 단일 제품에 대한 다른 문서 및 단일 주문에 대한 문서를 보유
    - JSON으로 표현
  - `필드` - RDB의 행
  - `매핑` - RDB의 스키마
  - `RESTFul API`
    - URI를 사용한 동작이 가능
    - HTTP 프로토콜로 JSON 문서의 입출력과 다양한 제어
    - JSON 문서의 입출력과 다양한 제어

### 엘라스틱서치 CRUD
- REST API
  - HTTP 기반으로 리소스, 메서드, 메시지로 API 정의하는 방법
  - Elasticsearch는 클러스터와 통신하는데 사용할 때 REST API 제공
-  API로 수행 할 수 있는 작업
  - 클러스터, 노드 및 색인 상태, 상태 및 통계 확인
  - 클러스터, 노드 및 색인 데이터 및 메타 데이터 관리
  - CRUD (Create, Read, Update, Delete) 및 인덱스에 대한 검색 작업 수행 
  - 페이징, 정렬, 필터링, 스크립팅, 집계 및 기타 여러 고급 검색 작업 실행
- 클러스터 상태 확인
  ```
  GET /_cat/nodes?v
  ```
- 인덱스가 가진 모든 데이터 확인
  ```
  GET /_cat/indices?v
  ```
- `엘라스틱서치 CRUD`
  - 메소드

  |HTTP 메서드|CRUD|SQL|
  |----------|----|----|
  |GET|READ|SELECT|
  |PUT|UPDATE|UPDATE|
  |POST|CREATE|INSERT|
  |DELETE|DELETE|DELETE|

  - 6.X 이상부터는 PUT과 POST를 엄격히 구분하진 않음
- `CRUD 요약`
  - 입력: PUT, http://localhost:9200/index1/type1/1 -d ‘{“num”:1, “name”:”Ilsun Choi”}’
  - 조회: GET, http://localhost:9200/index1/type1/1
  - 삭제: DELETE, http://localhost:9200/index1/type1/1
  - 업데이트: POST, http://localhost:9200/index1/type1/1/_update -d ‘{doc: {“age”:99} }’
- 인덱스 생성
  ```
  PUT /customer
  ```
- 인덱스에 데이터 넣기(덮어씀)
  ```
  POST /customer/_doc/1
  {
    "name": "yoonje"
  }
  ```
- 데이터 확인
  ```
  GET /customer/_doc/1
  ```
- 데이터 삭제
  ```
  DELETE /customer/_doc/1
  ```
- 데이터 업데이트
  - update API의 두 개의 매개 변수인 doc와 script를 이용해서 데이터를 제어
  - doc : 도큐먼트에 새로운 필드를 추가하거나 기존 필드 값을 변경하는 데 사용
  - script : 프로그래밍 기법을 사용. 입력된 내용에 따라 필드의 값을 변경하는 등의 처리
  ```
  POST /customer/_doc/1/_update
  {
    "doc": {
      "name": "yoonje2"
    }
  }
  ```
  ```
  POST /customer/_doc/1/_update
  {
    "script": {
      "inline": "if(ctx._source.age==123) {ctx._source.age++}"
    }
  }
  ```

### 엘라스틱서치 Batch
- 배치 프로세스
  - `_bulk API`를 사용하여 적은 네트워크 왕복으로 작업을 일괄적으로 수행 할 수 있는 기능
- 배치 입력
```
POST /customer/_doc/_bulk
{"index":{"_id":"1"}}
{"name": "John"}
{"index":{"_id":"2"}}
{"name": "Doe"}
```
- 다양한 연산
```
POST /customer/_doc/_bulk?pretty 
{"update":{"_id":"1"}}
{"doc": { "name": "John Doe becomes Jane Doe" } } 
{"delete":{"_id":"2"}}
```
- 데이터 셋 로드

### 다양한 검색
- 검색
  - `_search API`를 사용하여 검색
  - 인덱스 단위로 수행
  - _source를 지정하여 검색 결과를 반환할 수 있음
- 검색 항목
  - took: Elasticsearch가 검색을 실행하 는 데 걸린 시간 (밀리 초)
  - timed_out: 검색 시간이 초과되었는지 여부 를 알림
  - _shards: 검색된 파편의 수와 성공 / 실패 한 파편의 수를 알림
  - hits: 검색 결과
  - hits.total: 검색 조건과 일치하는 총 문서 수
  - hits.hits: 검색 결과의 실제 배열 (기본값 은 처음 10 개)
  - hits.sort: 결과 정렬 키 (점수 순 정렬시 누락)
- `JSON을 이용한 검색`
  - JSON을 전달해서 제공
  ```
  POST /bank/_search
  {
    "query": { "match_all": {} }, 
    "sort": [
       { "account_number": "asc" }
    ] 
  }
  ```
- `URI을 이용한 검색`
  - 질의는 q 매개변수의 요청 본문 값으로 입력 ex) /_search?q=title:time
  ```
  GET /bank/_search?q=*&sort=account_number:asc&pretty
  ```
  ``` 
  GET /bank/_search?q=title:time&_source=title,author,category
  ```
- `QueryDSL`
  - JSON 스타일을 활용한 도메인 관련 언어를 제공
  - 다양한 쿼리 옵션 제공
  ```
  GET /bank/_search
  {
    "query": { "match": { "account_number": 20 } }
  }
  ```
  ```
  POST /bank/_search
  {
    "query": { "match": { "address": "mill lane" } }
  }
  ```
  ```
  GET /bank/_search {
    "query": {
      "bool": {
        "must": [
          { "match": { "age": "40" } }
        ],
        "must_not" : [
          { "match": { "state": "ID" } }
        ]
      }
    }
  }
  ```

### 집계
- 반환하는 검색에서 통계 정보를 그룹화하고 추출 할 수 있는 기능을 제공
- 질의와 다중 집계를 실행하고 간결하고 단순화 된 API를 사용하여 네트워크 라운드 트립을 피하면서 한 번의 작업으로 결과를 모두 얻을 수 있다는 점에서 매우 강력
```
GET /bank/_search 
{
  "size": 0, "aggs": {
    "group_by_state": {
    "terms": { "field": "state.keyword" }
    } 
  }
}
```
```
GET /bank/_search {
  "size": 0, 
  "aggs": {
    "group_by_state": {
      "terms": { "field": "state.keyword" },
      "aggs": {
        "average_balance": {
          "avg": { "field": "balance" }
        }
      }
    }
  }
}
```
