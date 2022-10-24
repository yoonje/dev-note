# ES 교육 3회차 & 강의 교안 3~4

<hr>

### ES 환경 설정
* Static settings
  * `/etc/elasticsearch/elasticsearch.yml` 파일에 정의
  * 노드 단위로 설정
* Dynamic settings
  * 클러스터에 API로 호출
  * 클러스터 단위로 설정

### Index settings에 대한 필수 설정 요소
* Static index settings
  - number_of_shards(Primary 샤드의 개수)
* Dynamic index settings
  - number_of_replicas(Replica 샤드의 개수)
  - refresh_interval(refresh 주기)
  - index.routing.allocation.enable (인덱스에 대한 샤드 할당 제어)
* other settings..
  - Analysis, Mapping, Slowlog..

### elasticsearch.yml 파일 환경 설정(Static settings)
* `cluster.name`: 클러스터를 고유하게 식별할 수 있는 이름
* `node.name`: 노드를 고유하게 식벽할 수 있는 이름
* `path.data`: index 데이터를 저장할 경로(폴더) 지정
  * 싱글 경로(폴더) 설정을 통해서 복잡도를 줄이는 것이 좋음
* `path.logs`: 로그를 저장할 경로(폴더) 지정
  * 싱글 경로(폴더) 설정을 통해서 복잡도를 줄이는 것이 좋음
* `discovery.zen.ping.unicast.hosts(version 6.x)`
  * 외부 시스템에 설치된 ES 노드와 클러스터링이 필요한 경우 설정하는 아이피 리스트
  * 기본적인 경우 localhost 내의 9300~9305 포트를 스캔하여 클러스팅 진행
  * 7.x에서는 `discovery._seed_hosts`가 이 역할을 대체
* `discovery.zen.minimum_master_nodes(version 6.x)`
  * 마스터 노드 개수 지정
  * 아이피 리스트로 지정할 수도 상수로 지정할 수도 있음
  * 미지정 시에 (마스터 노드 개수/2) + 1 개로 최소 마스터 노드의 수를 계산하고 적용
  * 최소 마스터 노드의 수보다 마스터 노드가 적어지면 클러스터 중지
  * 7.x에서는 `cluster.initial_master_nodes`가 이 역할을 대체
* `discovery._seed_hosts`
  * 데이터 노드는 `discovery._seed_hosts` 설정만으로 Discovery
* `cluster.initial_master_nodes`
  * 마스터 노드는 `discovery._seed_hosts`와 `cluster.initial_master_nodes` 설정으로 Discovery  
* `network.bind_host`: 노드가 수신해야할 인터페이스
* `network.publish_host`: 클러스터 안에서 다른 노드들과 통신하기 위해 식별하기 위해 사용 하는 하나의 IP로 보통 자기 자신의 IP
* `http.port`: ES의 API를 전달할 때 사용할 포트
* `transport.tcp.port`: 클러스터 내의 노드들이 서로 통신할 때 사용할 포트 설정
* `http.cors.enabled`: 웹 브라우저에서 ES에 접근할 수 있도록 하는 설정(true or false)
* `http.cors.allow-origin`: 웹 브라우저로 접근할 수 있는 외부 IP ACL 설정
* 노드 설정
  * 마스터 노드: 마스터 노드 역할을 할 수 있는 노드(node.master: `true` / node.data: false / node.ingest: false)
  * 데이터 노드: 데이터 노드 역할을 할 수 있는 노드(node.master: false / node.data: `true` / node.ingest: false)
  * 인제스트 노드: 문서가 인덱싱 되기 전에 사전처리 할 수 있는 역할이 부여된 노드(node.master: false / node.data: false / node.ingest: `true`)
  * 클라이언트 노드(코디네이팅 노드): 클라이언트의 요청을 받고 라우팅 및 분산 처리만 할 수 있는 역할이 부여된 노드(node.master: false / node.data: false / node.ingest: false)

### Discovery
* 노드가 막 시작되었거나 이전 마스터가 실패한 경우와 같이 마스터를 알 수 없을 때 노드가 서로를 찾는 프로세스, 즉 노드가 클러스터를 찾아가는 과정
* Ping 기반으로 동작

### Split Brain
* 클러스터 구성에서 네트워크 단절로 인해 예비 마스터 노드를 마스터 노드로 승격하게 되는데 이때 클러스터가 복구 되어도 여러 개의 노드가 서로 마스터로 인식되는 증상
* 최소 필수 마스터의 개수를 홀수 개로 두어 과반을 넘지 못할 경우 클러스터를 중지 시켜 Split Brain을 방지
* 4대의 마스터 노드가 존재하는 경우 최소 마스터의 개수(4/2+1=`3`) -> 2대가 내려가는 순간 클러스터 중지

### 마스터 Fault
* 마스터로 정의된 노드들은 각각 작업이 처리될 때마다 값이 하나씩 증가하는 `cluster state version`을 갖음
* 마스터가 내려가게 되면 각 마스터 노드들은 discovery에 정의된 호스트에게 Ping Check를 시작
* 실제 마스터가 내려가게 되면 응답이 오는 호스트 중 cluster state version이 낮은 노드(제일 건강한 노드)를 마스터로 선출

### jvm.options 파일 환경 설정
* JVM
  * JVM은 Heap에 객체를 할당하여 사용하는 구조로 Young / Old Generation으로 Heap을 구성하여 사용
  * Young Generation은 Eden / From survivor / To survivor로 나뉨
  * GC가 수행될 때 Stop the Wolrd가 발생하고 GC는 각 영역의 객체가 이동 또는 삭제될 때 실행
* JVM 동작 방식
  * 가장 처음 객체를 저장하는 곳은 `Eden 영역`으로 GC를 수행할 때마다 age bit가 증가하고 Eden이 차오르면 임계값을 넘고 GC되지 않고 살아남은 객체들은 `from survivor 영역`으로 전달함
  * Eden 영역이 다시 차오르면 from survivor 영역의 객체와 Eden 영역의 객체는 `to survivor 영역`으로 이동
  * to survivor 영역도 가득 차올랐고 from survivor 영역도 가득 찼을 때 from survivor의 객체들은 Old Generation 영역으로 이동
* jvm.options를 통한 힙 사이즈 설정
  * `-Xms{바이트 단위 사이즈}g`: 최소 힙 사이즈 크기 설정
  * `-Xmx{바이트 단위 사이즈}g`: 최대 힙 사이즈 크기 설정
* jvm.options를 통한 기타 설정
  * `XX:+UseConcMarkSweepGC`: 기본으로 CMS GC를 사용
  * `-XX:CMSInitiatingOccupancyFraction={점유 비율}`: Old 영역이 설정 점유 비율(%)을 차오르면 GC 주기를 시작
  * `-XX:+UseCMSInitiatingOccupancyOnly`: GC 통계에 따르지 않고 설정한 CMSInitiatingOccupancyFraction을 기준으로 GC 주기를 시작
  * `-XX:+HeapDumpOnOutOfMemoryErrorOOM`: 에러 발생 시 힙 덤프를 발생시켜주게하는 설정
  * `-XX:HeapDumpPath=/var/lib/elasticsearch`: 힙 덤프를 저장할 경로
  * `-XX:ErrorFile=/var/log/elasticsearch/hs_err_pid%p.log`: JVM Fatal error logs 를 받을 경로
* JVM 운영
  * 초기 힙 사이즈와 최대 힙 사이즈를 동일하게 하는 것이 좋음
  * 힙 사이즈가 크면 클수록 많은 데이터를 힙에서 사용할 수 있어 GC 발생 확률이 적음
  * 페이지 캐시/버퍼 캐시를 두어 디스크 I/O를 줄이는 것은 좋으나 물리메모리의 50%가 넘지 않도록 하는 것이 좋음
* GC 튜닝
  * Young 영역을 구성하는 Eden, Survivor0,1이 작아 잦은 young GC가 발생 -> age bit 도달 전에 old GC에 의해 Old 영역으로 이동시키고 Young 영역을 더 확보하여 young GC 빈도를 줄이는게 성능 확보에 좋음
  * `-XX:NewRatio`: New Old 튜닝  
  ex) -XX:NewRatio=2 -> New:Old = 1:2 로 튜닝  
  * `-XX:SurvivorRatio`: Survivor0 Survivor1 Eden 튜닝  
  ex) -XX:SurvivorRatio=6 -> Survivor0:Survivor1:Eden = 1:1:6 로 튜닝

### log4j2.properties 파일 환경 설정
- `${sys:es.logs.base_path}`: Log 설정 디렉토리
- `${sys:es.logs.cluster_name}`: 클러스터 이름  
- `${sys:es.logs.node_name}`: 노드 이름
- `${sys:es.logs.base_path}${sys:file.separator}${sys:es.logs.cluster_name}.log`: 클러스터 운영 로그 설정  
- `${sys:es.logs.base_path}${sys:file.separator}${sys:es.logs.cluster_name}_deprecation.log`: Elasticsearch에서 수행되고 있는 Deprecated 된 기능 정보  
- `${sys:es.logs.base_path}${sys:file.separator}${sys:es.logs.cluster_name}_index_search_slowlog.log`: 인덱스 검색 슬로우 로그 정보  
- `${sys:es.logs.base_path}${sys:file.separator}${sys:es.logs.cluster_name}_index_indexing_slowlog.log`: 인덱스 인덱싱 슬로우 로그 정보  
- `${sys:es.logs.base_path}${sys:file.separator}${sys:es.logs.cluster_name}_access.log`: X-Pack auditing 로그 정보  

### ES와 파일 관련 메모리 설정
* ES는 인덱스를 파일시스템에 쓸 때 mmap을 사용하는데 ES가 열 수 있는 File Descriptor가 부족하면 데이터 손실이 날 수 있어 스왑 메모리를 활용하여 많은 파일 디스크립터가 수용될 수 있도록 설정
* 설정 과정
  * `/etc/security/limits.conf`의 vm.max_map_count 수정
  * `$ sudo sysctl -p`을 통해 파일에서 읽고 커널 매개변수 값 변경
  * `$ sudo swapoff -a`: 스왑 메모리 비활성화
  * `/etc/sysctl.conf`의 vm.swappiness 수정
    cf) vm.swappiness = 0	스왑 사용안함, vm.swappiness = 1	스왑 사용 최소화, vm.swappiness = 60	기본값, vm.swappiness = 100	적극적으로 스왑 사용
  * `$ sudo sysctl -p`: 커널 설정 파일에서 데이터를 읽고 커널 매개변수 값 변경


### 개념 보충
* 0.0.0.0: 로컬 시스템의 모든 IP 주소
* ACL: Access Control List의 약자로, 다른 호스트들이 네트워크에 접근 여부를 허용할지 말지를 결정하는 리스트
* 스왑 영역: 리눅스에서 물리적 메모리(RAM)의 용량이 가득 차게될 경우 사용되는 디스크 상의 여유 공간을 말합니다. 즉, 시스템이 처리하고 있는 데이터를 저장할 RAM이 충분하지 않을 때 스왑 공간
* index.routing.allocation.enable은 인덱스에 샤드를 할당하는 제어할 수 있게 하는 옵션으로 `all(기본값)`-모든 샤드에 샤드 할당을 허용, `primaries`-원본 샤드에 대해서만 샤드 할당을 허용, `new_primaries`-새로 작성된 기본 샤드에 대해서만 샤드 할당을 허용, `none`-샤드 할당이 허용하지 않음
