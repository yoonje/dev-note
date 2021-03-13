# ES 교육 6회차 & 강의 교안 

<hr>

### ES 색인 성능 최적화 - static mapping
* static mapping
    * 어떤 방식으로 색인하는지가 I/O 빈도와 부하를 결정하므로 인덱스 mapping 스키마를 미리 정의하는 것만으로도 성능이 향상
    * mapping 스키마를 미리 정의하지 않고 문서를 인덱싱하면 dynamic mapping이 진행되고 그렇게 되면 ES가 자동으로 대략적인 스키마를 만들어서 비효율적인 I/O가 발생
* mapping과 관련 성능 향상 포인트
    * mapping - 문서의 필드 데이터를 어떤 타입으로 저장할지 결정하는 과정으로 기본적으로 static mapping이 좋음
    * field의 datatype은 text, keyword, date, long, short, double, boolean이 존재
    * mapping 관련 성능 향상 포인트
        1. 문자열 데이터에 대해서 `text field`를 쓸지 `keyword`를 쓸지
        2. 숫자 데이터에 대해서 `short field`를 쓸지 `long field`를 쓸지
        3. date type은 어떻게 정의할지
        4. `refresh interval`을 어떻게 결정할지
        5. `properties` 서브 필드 확장
        6. `nested type` mapping을 이용하여 적용하기
        7. `_all` 필드 사용의 오버헤드와 그 대안
* static mapping 정의하는 방법
    * 매핑 이름을 적지 않고 인덱스 이름에 `mapping`의 `properties` 속성에 값을 넣고 PUT  
    ```json
    PUT {인덱스 이름} 
    {
        "mappings": { 
            "properties": {
                "{필드 이름}": { "type": "text"}
            }
        } 
    }
    ```
* text field와 keyword field 선택을 통한 성능 최적화
    * text field: 전문 검색(full-text)로 색인되는 필드 타입으로 `sorting` 및 `aggregation`에 사용되지 않고 `analyzer`를 통해 생성된 `토큰으로 검색 가능`
    * keyword field: 구조화된 내용으로 색인되는 필드 타입으로 `sorting` 및 `aggregation`이 지원되며 `analyze`되지 않은 하나의 토큰 정확한 값으로만 검색 가능
    * dynamic mapping으로 문자열을 입력하면 text와 keyword 둘다 셋팅 되고 text는 색인될 때 `analyer`를 거치게 되어 낭비가 됨 -> static mapping을 통해서 멀티 셋팅 오버헤드를 줄이고 특히 keyword로 사용할 의도였다면 keyword type으로 매핑하여 analyzer 기능을 거치지 않아야함  
    cf) `aggregation`은 _search API를 통해서 수집된 데이터를 키바나에서 집계/통계를 할때 주로 사용하는 프레임워크인데 full-text로 사용하긴 어렵고 `keyword` 필드로 정의된 데이터 대해서만 집계해야 효율적
    ```json
    PUT {인덱스 이름} 
    {
        "mappings": { 
            "properties": {
                "{필드 이름}": { "type": "keyword"}
            }
        } 
    }
    ```
* date field 정의 방식을 통한 최적화
    * date: 형식이 지정된 날짜가 포함된 문자열이나 밀리초로 저장
    * dynamic mapping으로 입력하면 처음에 입력되는 형태로 인식하여 밀리초로 인식하면 `long type`으로 매핑되고 `date type`는 색인되지 않음
    일반적인 매핑으로 date 필드 정의
    ```json
    PUT {인덱스 이름} 
    {
    "mappings": {
        "properties": {
        "date": {
            "type": "date"
        }
        }
    }
    }
    ```
    timestamp 형태의 date 지정
    ```json
    POST {인덱스 이름}/_doc
    { 
        "date": "2015-01-01T12:10:30Z" 
    }
    밀리초 형태의 date 지정
    ```json
    POST {인덱스 이름}/_doc
    { 
        "date": 1420070400001 
    }
    ```
    사용자가 정의한 format으로만 색인되도록 매핑 설정
    ```json
    PUT {인덱스 이름}
    {
    "mappings": {
        "properties": {
        "date": {
            "type": "date",
            "format": "yyyy-MM-dd HH:mm:ss||yyyy-MM-dd||epoch_millis"
        }
        }
    }
    }
    ```
* short field와 long field 선택을 통한 성능 최적화
    * short에 비해 long은 표현 범위가 넓은데 dynamic mapping 시에 `long type`으로 매핑되므로 적절하게 조절하여 사용하되 통일하는 것이 권고됨
* `properties` 서브 필드 확장
    * `properties`는 매핑을 만들 때나 계층 구조의 데이터(object,list)를 이용할 때 사용하는데 계층 구조의 데이터를 사용할 때 이용하면 효율적
    * object의 .을 이용하여 필드에 접근하여 쿼리를 요청할 수 있음   
    ```json
    PUT {인덱스 이름} 
    {
    "mappings": {
        "properties": {
        "region": {
            "type": "keyword"
        },
        "manager": {
            "properties": {
            "age": {
                "type": "integer"
            },
            "name": {
                "properties": {
                "first": {
                    "type": "keyword"
                },
                "last": {
                    "type": "keyword"
                }
                }
            }
            }
        }
        }
    }
    }
    ```
* `nested type` mapping을 이용하여 정의하기
    * nested type으로 정의한 매핑은 색인이 되는 순간 다시 dynamic mapping으로 색인되어 가변적인 길이의 데이터를 입력받을 때 유용
    * nested type에 대한 쿼리는 nested 서브 쿼리로 검색  
    * nested type의 Parent와 Child는 같은 샤드에 배치되므로 분배 문제가 있어 스키마 설계 시 고려가 필요  
    ```json
    PUT {인덱스 이름}/_doc/1 
    {
    "user": [
        {
        "first": "John",
        "last": "Smith"
        },
        {
        "first": "Alice",
        "last": "White"
        }
    ]
    }
    ```

### ES 색인 성능 최적화 - 기타
* `_all` 필드 사용의 오버헤드와 대안
    * `_all` 필드는 문서의 검색 요청 시에 모든 필드의 값들을 합쳐 힙 영역에 올리는 필드로 전체를 검색할 때 사용하나 성능이 매우 떨어지기 때문에 사용하면 안되는 필드(6.x버전 이상에서는 deprecated)
    * text field 로 analyze 되는 필드
    * 여러 개의 필드를 동시에 검색할 여지가 있을 때는 `copy_to` 기능을 사용  
    copy_to 기능을 활용하여 문서의 모든 필드 값에 대해 요청
    ```json
    PUT {인덱스 이름} 
    {
    "mappings": {
        "properties": {
        "first_name": {
            "type": "text",
            "copy_to": "full_name"
        },
        "last_name": {
            "type": "text",
            "copy_to": "full_name"
        },
        "full_name": {
            "type": "text"
        }
        }
    }
    }
    ```
* `refresh interval`을 설정
    * `refresh interval`는 메모리 캐시 버퍼 영역으로부터 `세그먼트에 도큐먼트를 저장하는 주기`
    ```json
    PUT refresh/_settings 
    {
    "index" : { 
        "refresh_interval" : "1s"
        } 
    }
    ```
    * refresh가 되야만 검색이 가능한 상태가 되지만 검색하기 전에는 interval을 길게 가져갈 수록 I/O 빈도가 낮아져 성능이 향상
    * `refresh interval`를 -1 로 설정하면 disabled, null 로 설정하면 1s로 초기화
    ```json 
    PUT refresh/_settings 
    {
    "index" : { 
        "refresh_interval" : -1
        } 
    }
    ```
    * `refresh interval`를 disalbed하고 refresh=true 로 설정한 문서만 세그먼트로 내려서 직접 제어도 가능
    ```json
    PUT refresh/_doc/1?refresh=true 
    { 
        "msg": "first doc" 
    }
    ```
* 기타 유용한 성능 향상 팁
    * `Document ID 없이 POST로 색인` 권고 - PUT을 통해 doc id 를 설정한 채로 색인을 할 때 ES는 해당 id 의 문서가 있는지를 먼저 체크하므로 인덱스의 크기가 커지면 부담
    * Bulk Indexing 활용 권고 - 가능하면 단일 색인 요청보다는 한번에 많은 문서를 `Bulk Indexing` 하는 것이 더 효율적
    * 상황에 따라서 Replica shard 를 0으로 설정 - 한 번에 많은 데이터를 적재해야하는 상황에서는 replica를 0 으로 두고 색인하고 완료된 이후에 리플리카를 추가하는 형태로 작업
    * Heap에 남은 메모리가 버퍼 캐시로 활용될 수 있도록 충분히 확보하고 `Index Buffer Size`를 상황에 맞게 설정 권고

### ES 검색 성능 최적화 - 쿼리 튜닝
* multi field로 검색을 해야할 때에는 가능한 적은 필드로 검색
    * `copy_to`를 이용하면 두 개의 필드를 하나로 줄여 검색 가능  
    ```json
    PUT copy_index 
    {
    "mappings": {
        "properties": {
        "first_name": {
            "type": "text",
            "copy_to": "full_name"
        },
        "last_name": {
            "type": "text",
            "copy_to": "full_name"
        },
        "full_name": {
            "type": "text"
        }
        }
    }
    }
    ```
* numeric field에 대해서 keyword field로 색인 고려
    * keyword type에서 집계 등의 수치 계산은 안됨 
    매핑하기
    ```json
    PUT {인덱스 이름}
    { 
        "mappings": { 
            "_doc": { 
                "properties": { 
                    "account_no": {
                        "type": "keyword" 
                        } 
                } 
            } 
        } 
    }
    ```
    인덱싱 하기
    ```json
    POST {인덱스 이름}/_doc
    {
         "account_no": "12345" 
    }
    ```
* `wildcard`는 꼭 써야하는지 검토
    * wildcard는 성능을 떨어뜨리므로 token으로 분리되는 용어는 match를 써도 충분히 검색 가능
* exact match 검색을 할 때에는 match 대신 term 쿼리 사용
    * term 쿼리를 사용하면 불필요한 `analyze`를 제외하여 성능 향상
* filter conetxt와 query context를 적절히 활용
    * filter context는 스코어가 의미 없는 쿼리이므로 스코어 계산을 단계가 없는 term을 이용하면 성능 향상
    * bool의 filter 쿼리를 사용하면 must 쿼리에 비해 스코어 계산 단계가 사라짐
    * filter 쿼리는 쿼리된 문서들이 `캐싱`됨
* bool 쿼리는 각 쿼리들이 interleave 하게 실행되어 쿼리의 순서는 크게 상관 없음
* 서비스 전 쿼리 캐시 `warmup`
    * 처음 로딩되는 데이터가 Heap에 올라와 있지 않다면 버퍼 캐시에 데이터가 있는지 확인하고 버퍼 캐시에도 없다면 디스크에 저장된 segment를 찾아서 메모리에 warmup이 필요
    * Heap에도 버퍼 캐시에도 데이터가 없다면 디스크에 저장된 segment 를 찾아
    1. query context에서 사용되었다면 Heap에 데이터를 올리고 리턴
    2. filter context에서 사용된 쿼리에 대해 버퍼 캐시에 캐싱
    3. 자주 사용되는 쿼리로 서비스 전에 `filter context`를 사용해 미리 쿼리를 날려 버퍼 캐시에 캐싱
    4. 캐시 사이즈가 크다면 filter context에 와일드 카드 쿼리로 전체 데이터를 로딩     
* 지양해야할 검색 구조
    1. Parent/Child 구조로 joint job이 들어가는 구조 - parent와 child가 동일한 샤드에 저장되어 샤드 크기 분배 문제 발생
    2. nested datatype field를 사용한 매핑을 사용하는 구조 - nested가 동일한 샤드에 저장되어 샤드 크기 분배 문제 발생
    3. ES에서 제공하는 `script` 속성을 사용하여 색인하고 검색하는 구조 - 스크립트는 업데이트 방식이 아니라 스크립트 수행 후 reindex 방식이므로 오버헤드가 큼
    4. range 쿼리에서 date를 기준으로 범위를 정할 때 분 단위까지 범위를 잡는 것 - 반올림 하는 구조가 좋음

### ES 검색 성능 최적화 - 샤드배치 결정하기
* 샤드 개수를 결정할 때 고려해야할 점 - 한번 설정한 샤드의 개수는 변경할 수 없음
    * 인덱스가 생성될 때 전체 노드가 색인과 검색에 참여할 수 있는가?
        1. 분산 처리를 위해 샤드가 노드에 골고루 분배되어야함 
        2. `노드 개수의 배수`가 샤드 개수가 되면 골고루 분배 
        3. 데이터 노드 증설 시 증설된 노드가 샤드를 받을 수 있어야함
    * 하나의 데이터 노드에 적정 샤드 개수가 저장되도록 설계되었는가? - `데이터 노드`에 의존적인 고려사항
        1. 데이터 노드에 샤드가 너무 많이 들어가 있으면 검색에서 성능이 떨어짐
        2. Heap Size와 고려하여 샤드 개수를 산정해야함
    * 하나의 샤드가 적절한 용량만 저장되도록 설계되었는가?
        1. 샤드의 크기는 적을수록 좋지만 너무 적으면 샤드의 개수가 많아져 검색 성능이 떨어짐
        2. 인덱스 전체 크기를 보고 하나의 샤드 크기를 산정해야함
    * 클러스터의 전체 샤드 개수는 적절한가? - `마스터 노드`에 의존적인 고려사항
        1. 샤드 개수가 늘어나면 클러스터 내 마스터 노드가 알아야할 사항이 너무 많아져 성능이 감소하여 클러스터 사이즈를 보고 적절하게 샤드 개수는 적절히 분배 되어야함
        2. 응용 서비스와 클러스터는 1대1이 좋음
    * 꼭 실시간으로 replica sharding이 필요한가?
        1. replica가 많으면 안정성은 높지만 디스크 볼륨의 2배가 되는 단점이 존재
        2. 원본이 별도로 있다면 색인될 때 replica를 없애면 성능 향상

### ES 검색 성능 최적화 - 기타
* `_forcemerge` API
    * segment를 강제로 병합하는 API
    * 색인이 끝난 인덱스는 하나의 segment로 merge를 추천
    * I/O 비용이 크기 때문에 색인이나 검색이 없는 시간대에 수행  
    `POST shakespeare/_forcemerge?max_num_segments=1`
* Routing
    * `routing key`를 통해서 특정 샤드로 색인하는 방법으로 색인 샤드 할당 알고리즘으로 할당하여 검색을 하는 것이 아닌 문서 가져오기 과정을 거치게 되어 성능이 향상
    * 특정 샤드로 색인하기 때문에 문서가 쏠릴 수 있음
    ```json
    POST rindex/_doc?routing=user1 
    {
        "title": "This is a document" 
    }
     ```
* Rollover API
    * 라우팅으로 커진 샤드를 케어하는 방법으로 특정 조건이 맞으면 `새로운 인덱스를 생성하고 alias를 옮겨주는 기능`
    * 이미 샤드에 배치된 문서 자체는 옮겨지지 않아서 사전 문서에 대해서는 read alias를 2개에 걸쳐 확장해야함
    * `dry_run`을 실행하면 모의 실행 가능
    alias 생성
    ```json
    POST {alias 이름}/_rollover 
    {
        "conditions": { "max_age": "7d", "max_docs": 2, "max_size": "5gb"} 
    }
    ```
    특정 이름을 지정하여 생성 가능
    ```json  
    POST {alias 이름}/_rollover/{인덱스 이름}
    {
        "conditions": { "max_age": "7d", "max_docs": 2, "max_size": "5gb"} 
    }
    ```
* Thread Pool Size
    * 헤비한 색인과 검색을 같이 해야하는 경우 색인에 Thread Pool이 과하게 할당되어 검색 성능이 떨어지므로 Bulk job에 할당되는 thread pool size를 조절하여 성능 보장
    * elasticsearch.yml 파일에 `thread.bulk_size` 값을 변경하여 설정 가능

### ES 모니터링
* rejected
    * 노드 내에서 스레드의 메모리 사용을 관리하기 위해 여러 개의 스레드 풀을 사용하고 각각의 스레드 풀은 대기열 큐를 두어 대기 중인 요청을 보관
    `GET _nodes/thread_pool`
    * 대기열 큐가 꽉차면 그 이후부터는 요청이 reject되어 stats를 통해서 모니터링
    `GET _nodes/stats`
    * _cat/thread_pool?v를 통해서 thread_pool 정보만 실시간 조회 가능
    `GET _cat/thread_pool/search?v`
    * elasticsearch.yml 파일에 `thread_pool.bulk_size`와 `thread_pool_search.queue_size`를 조절하여 파일 큐 사이즈 조절 가능

* cat API
    * GET Method를 통해 클러스터, 노드, 인덱스 등의 상태를 확인해볼 수 있는 API
    * `GET _cat/nodes`: 클러스터에 속한 node들의 상태를 확인할 수 있는 명령
    * `GET _cat/nodes?v`: 클러스터에 속한 node들의 상태를 확인할 수 있는 명령에서 ?v 옵션을 통해 항목의 필드 이름 확인 추가
    * `GET _cat/nodes?v&h=ip,node.role`: 클러스터에 속한 node들의 상태를 확인할 수 있는 명령에서 &h= 를 통해 필요한 항목만 발췌하는 명령
    * `GET _cat/nodes?v&h=ip,node.role&s=ip:asc&format=json`: 클러스터에 속한 node들의 상태를 확인할 수 있는 명령에서 항목의 필드만 발췌하고 &s=ip:asc 를 통해 정렬 및 json 포맷으로 변경
    * `GET _cat/allocation?v`: 샤드 및 디스크 용량 관련 사항 조회
    * `GET _cat/shards?v`: 샤드 정보 조회
    * `GET _cat/indices?v`: 인덱스 정보 조회
    * `GET _cat/health?v`: 클러스터 헬스체크 
    * `GET _cat/templates?v`: 세팅된 템플릿 조회

* stats API
    * GET Method를 통해 전체 클러스터, 인덱스 별 프라이머리 샤드와 전체 샤드의 각종 지표를 확인하는 API로 클러스터 모니터링 지표로 활용
    * `search.(query/fetch)_total` - search에서 (query/fetch)를 요청한 횟수
    * `(query/fetch)_time_in_millis` - (query/fetch)에 소요된 milliseconds
    * A = 1초 전 search.query_total - 현재 search.query_total = 1초 간 search query total 건수-> 초당 search query 의 rate
    * B = 1초 전 search.query_time_in_millis - 현재 search.query_time_in_millis = 1초 간 query time_in_millis-> 초당 search query 의 latency

* nodes API
    * 각 노드의 uuid를 key로 하여 `elasticsearch.yml`, `jvm.options`, `plugin` 정보 등을 제공
    * 노드 이름, IP 정보, ES 버전, 노드 역할 정보 조회 가능
    * elasticserach.yml에 셋팅된 정보 외 추가정보
    * jvm.options에 셋팅된 정보
    * 노드의 시스템 지표도 함께 확인 가능
    * GC에 대한 항목 확인 가능
    * 파일시스템 사용량 확인 가능
