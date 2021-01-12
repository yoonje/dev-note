
# 카프카 컨슈머

<hr>

### 콘솔 컨슈머로 메세지 가져오기
* 컨슈머
  * `컨슈머`: 토픽에서 메세지르 가져오는 애플리케이션과 서버 등을 모두 컨슈머라고 함
  * `하트비트`: 컨슈머가 `poll()`을 호출하여 메시지를 구독할 때 발행하는 비트로 컨슈머가 살아 있다는 신호 
  * `poll()`: 컨슈머에서 호출하는 함수로 poll 호출은 파티션에 할당된 메시지 세트를 리턴
* 콘솔 컨슈머로 메시지 가져오기
  * 메시지를 토픽에서 가져와서 보낸 메시지 확인
  ```bash
  $ /usr/local/kafka/bin/kafka-console-consumer.sh --bootstrap-server {카프카 노드:포트 번호,...} --topic {토픽 이름} --from-beginning
  ```
  * 컨슈머 그룹의 리스트를 확인
  ```bash
  $ /usr/local/kafka/bin/kafka-consumer-groups.sh --bootstrap-server {카프카 노드:포트 번호,...} --list
  ```
  * 컨슈머 그룹을 지정하여 메시지를 토픽에서 가져와서 보낸 메시지 확인
  ```bash
  $ /usr/local/kafka/bin/kafka-console-consumer.sh --bootstrap-server {카프카 노드:포트 번호,...} --topic {토픽 이름} --group {그룹 이름} --from-beginning
  ```
  * 파티션을 지정하여 메시지를 가져와서 확인
  ```bash
  $ /usr/local/kafka/bin/kafka-console-consumer.sh --bootstrap-server {카프카 노드:포트 번호,...} --topic {토픽 이름} --partition {파티션 번호} --from-beginning
  ```

### Python을 이용한 컨슈머
* 일반적인 Python 컨슈머 코드
```py
from kafka import KafkaConsumer

consumer = KafkaConsumer('peter-topic',group_id='peter-consumer',bootstrap_servers='peter-kafka001:9092,peter-kafka002:9092,peter-kafka003:9092', enable_auto_commit=True, auto_offset_reset='latest')
for message in consumer:
    print("Topic: %s, Partition: %d, Offset: %d, Key: %s, Value: %s" % (message.topic, message.partition, message.offset, message.key, message.value.decode('utf-8')))
```

### 컨슈머 주요 옵션
* `boostrap.servers`: 카프카 클러스터에 처음 연결을 하기 위한 호스트와 포트 정보로 구성된 리스트 정보를 나타냄
* `fetch.min.bytes`: 한번에 가져올 수 있는 최소 데이터 사이즈
* `fetch.max.bytes`: 한번에 가져올 수 있는 최대 데이터 사이즈
* `group.id`: 컨슈머가 속한 컨슈머 그룹을 식별하는 식별자
* `enable.auto.commit`: 백그라운드로 주기적으로 오프셋을 커밋
* `auto.offset.reset`: 오프셋에 대한 재설정 옵션
* `request.timeout.ms`: 요청에 대해 응답을 기다리는 최대 시간
* `session.timeout.ms`: 컨슈머와 브로커 사이의 세션 타임 아웃 시간으로 하트비트를 이 타임 아웃 옵션 동안 주지 않을 경우 컨슈머에 문제이 있는 것으로 판단하여 `리벨런스`
* `heartbeat.interval.ms`: 그룹 코디네이터에게 얼마나 자주 하트비트를 보낼지 조정
* `max.poll.records`: 단일 호출 `poll()`에 대한 최대 레코드 수
* `max.poll.interval.ms`: 컨슈머가 하트비트만 보내고 실제로 메시지를 가져가지 않을 때, 즉 주기적으로 poll()을 호출하지 않으면 장애라고 판단하는 타임 아웃 시간
* `auto.commit.interval.ms`: 주기적으로 오프셋을 커밋하는 시간
* `fetch.max.wait.ms`: fetch.min.bytes에 의해 설정된 데이터보다 적은 경우 요청에 응답을 기다리는 최대 시간

### 파티션과 메시지 순서
* 파티션이 1개 있는 경우 동일한 파티션 내에서는 생성한 순서와 동일하게 처리하기 때문에 순서가 보장되나 파티션이 여러 개 있는 경우의 메시지 순서는 보장되지 않음

### 컨슈머 그룹
* 컨슈머 그룹
  * `컨슈머 그룹`: 컨슈머 인스턴스들의 논리적인 그룹 단위
  * `그룹 코디네이터`: 컨슈머 그룹의 상태를 관리할 책임이 있고, 코디네이터의 주된 일은 새 멤버가 오고 갈 때, 그리고 토픽 메타데이터가 변할 때 파티션 할당을 중재하는 브로커
  * 컨슈머 그룹 안에서 컨슈머를 추가하는 것이 아니라 독립적으로 추가하게 되면 기존의 컨슈머의 오프셋 정보를 알 수 없어 메시지들이 뒤죽박죽이 됨
* 컨슈머 그룹의 기능
  * 동일한 컨슈머 그룹 아이디를 식별자로 하여 토픽에 대한 소유권을 공유함
  * 컨슈머가 그룹에 추가되거나 기존의 컨슈머가 다운됐을 때 `그룹 코디네이터`에 의해 `리벨런스`가 진행됨
  * 토픽의 파티션에는 하나의 컨슈머만 연결될 수 있기 때문에 토픽의 파티션의 수보다 컨슈머 그룹 안의 컨슈머가 많아도 소비할 수 없음
  * 컨슈머 그룹 안에서 컨슈머가 재기능을 하고 있는지 없는지는 `하트비트`를 통해 알 수 있음

### 커밋과 오프셋
* 커밋
  * `커밋`: 컨슈머 그룹의 컨슈머들은 각각의 파티션에 자신이 가져간 메세지의 위치 정보인 오프셋을 기록하는 오프셋을 업데이트하는 것을 커밋이라고 명침
  * `자동 커밋`: 카프카에서 메시지를 가져갈 때 자동으로 구독 신청을 호출할 때 마지막 오프셋을 커밋하는 것
  * `수동 커밋`: 컨슈머가 메세지를 저장한 이후에 수동으로 커밋을 하는 것
  * 카프카 내에 별도의 토픽을 생성하고 그 토픽에 오프셋 정보를 저장하여 커밋
* 커밋의 기능
  * 리밸런스 이후에는 컨슈머는 가장 최근에 커밋된 오프셋을 읽고 그 이후부터 메세지를 읽기 시작
