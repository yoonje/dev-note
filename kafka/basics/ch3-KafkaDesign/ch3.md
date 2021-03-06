
# 카프카 디자인

<hr>


### 카프카 디자인의 특징
* 분산 시스템
  * 단일 시스템을 통해 더 높은 성능을 얻을 수 있음
  * 분산 시스템 중 하나의 서버나 노드에 장애가 발생하면 다른 서버나 노드가 대신 처리할 수 있음
  * 시스템 확장에 용이함
* JVM 힙 사이즈와 페이지 캐시를 통한 카프카 디자인
  * 잔여 메모리를 이용해 디스크 활용을 최소로 해주는 페이지 캐시 설정을 통해서 카프카의 활용성을 더 높일 수 있음
  * JVM 힙 사이즈 설정인 `KAFKA_HEAP_OPTS`을 변경하여 충분한 메모리 할당 영역으로 활용하면 성능을 높일 수 있음
* 배치 전송 처리
  * 카프카에서는 작은 I/0들을 묶어서 처리할 수 있는 배치 전송을 지원

### 카프카 데이터 모델
* 토픽
  * `토픽`: 메시지를 받을 수 있도록 데이터를 논리적으로 구분하여 묶은 개념
  * 서버 자체를 Target으로 하지 않고 토픽만으로 메시지를 보내서 메시지의 송수신을 간단하게 함
* 파티션
  * `파티션`: 토픽을 분할한 개념
  * 메시지 전송의 병렬성을 높이기 위해서 파티션을 늘리면 프로듀서는 메시지를 토픽의 파티션으로 보내게 됨
  * 분산 시스템이면 일반적으로 N개의 파티션을 만들면 N배의 성능 향상이 보장되지만 메시징 큐 시스템에선 메시지의 순서가 느슨하게 보장되는 약간의 기능이 있어 N배의 성능이 보장되지는 않음(파티션이 1개이면 순서가 완전 보장)
  * 파티션 수를 늘리면 성능이 향상되지만 파티션의 수가 많을 수록 파일 핸들 수도 많아지고 파티션마다 리플리케이션이 동작하게 되어 성능이 떨어질 수 있음
  * 각각의 관계를 파악하여 적절하게 파티션 수를 설정해야함
  * 파티션 수를 줄이고 싶은 상황에서는 토픽을 삭제하는 방법밖에 존재하지 않으므로 적저한 파티션 수를 책정하기 위해선 적은 파티션 수로 운영해보고 이후에 병목이 발생하면 조금씩 파티션 수를 늘리는 접근이 좋음
* 오프셋
  * `오프셋`: 각 파티션마다 메시지가 저장되는 위치로 순차적으로 증가하는 숫자 형태
  * 카프카에서는 오프셋을 이용해 메시지의 순서를 보장
  * 오프셋 순서가 바뀐 상태로는 컨슈머가 가져갈 수 없음

### 리플리케이션
* 리플리케이션
  * `리플리케이션`: 장애 상황에 대응하기 위해 만든 복제 기능
  * 토픽 자체를 리플리케이션하는 것이 아닌 `파티션을 리플리케이션하는 것`이므로 리플리케이션은 파티션
  * Replication이 많아도 브로커가 적으면 하나의 브로커에 Replication이 여러개가 속하게 되는 경우가 발생하여 무의미하므로 브로커의 개수로 Replication의 개수가 제한
  * 카프카 환경 설정 파일에서 리플리케이션 설정
  ```bash
  $ vi /usr/local/kafka/config/server.properties
  ```
  ```yml
  # 리더(원본)을 포함한 전체 리플리케이션의 개수
  default.replication.facotr = 2
  ```
  * 카프카 로그 파일을 통해 변경된 리플리케이션 설정 확인
  ```bash
  $ cat /usr/local/kafka/logs/server.log
  ```
  * `리더(원본)`: 리플리케이션 중에서 읽기와 쓰기가 일어나는 리플리케이션
  * `팔로워(복제본)`: 리플리케이션 중에서 읽기와 쓰기에는 관여하지 않고 리더를 복사하고 있는 리플리케이션
  * 카프카는 파티션 단위로 리플리케이션 하기 때문에 `파티션이 N개인 경우 리플리케이션하게 되면 파티션 리더도 N개 존재` 
  * 리플레키이션을 늘리면 안정성은 커지지만 복사본에 대한 추가 저장소 증가 및 브로커들의 리소스 사용량이 증가함
* 리더와 팔로워
  * 리더에 장애가 생기면 팔로워가 이를 대신하는 것으로 서비스의 안정성을 유지함
  * 아직 리더로부터 데이터를 완전히 가져오지 못한 리플리케이션과 데이터를 완전히 가져 온 리플리케이션을 구분하여 완전히 가져온 리플리케이션은 `ISR`에 속하게 하고 `ISR`에 속해 있는 구성원만이 리더의 자격을 부여
* 브로커가 모두 다운된 상황에서의 장애 처리 방식 비교
  * 마지막 리더가 살아날 때까지 기다리기  
  장점: 메세지 손실이 없음  
  단점: 장애 시간이 길어짐
  * ISR에서 추방된 상태이지만 먼저 살아나면 자동으로 리더로 승격하기  
  장점: 장애 시간이 짧음  
  단점: 메세지 손실이 있음

### 주키퍼 지노드의 역할
* 주키퍼 지노드를 이용한 카프카 정보 확인
  * 주키퍼 CLI를 실행
  ```bash
  $ /usr/local/zookeeper/bin/zkCli.sh
  ```
  * 주키퍼 지노드 확인
  ```bash
  [zk: localhost:2181(CONNECTED)] ls /
  ```
  * 카프카가 사용하는 지노드들을 확인
  ```bash
  [zk: localhost:2181(CONNECTED)] ls /{지노드 이름}
  ```
  /{지노드 이름}/controller: 실패한 브로커들에 영향을 받는 파티션의 리더 변경을 책임지는 현재 카프카 클러스터의 `컨트롤러 정보`  
  /{지노드 이름}/brokers: `broker.id`  
  /{지노드 이름}/consumers: 컨슈머가 각각의 파티션들에 어디까지 읽었는지에 대한 `오프셋` 정보  
  /{지노드 이름}/config: 토픽의 상세 설정 정보  

### 보충
* 주키퍼에 오프셋을 저장하는 방식은 향후 종료될 예정이므로 오프셋 저장을 카프카의 하나의 토픽으로 하는 것이 좋음
