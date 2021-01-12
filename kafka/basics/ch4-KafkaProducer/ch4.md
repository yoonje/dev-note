
# 카프카 프로듀서

<hr>

### 콘솔 프로듀서 메세지 보내기
* 프로듀서
  * `프로듀서`: 메세지를 생선해서 카프카의 토픽으로 메시지를 보내는 역할을 하는 애플리케이션과 서버 등을 모두 프로듀서라고 함
  * 프로듀서는 각각의 메시지를 토픽에 파티션에 매핑하고 파티션의 리더에게 요청을 보내는 역할을 함
* 콘솔 프로듀서로 메시지 보내기
  * 존재하지 않는 토픽으로 메시지를 보낼 경우 자동으로 토픽을 생성하도록 설정
  ```bash
  $ vi /usr/local/kafka/config/server.properties
  ```
  ```yml
  # 오토 토픽 설정 추가
  auto.create.topics.enable=true
  ```
  * 카프카 제공 명령을 통한 토픽 생성
  ```bash
  $ /usr/local/kafka/bin/kafka-topics.sh --zookpeer {주키퍼 노드:포트 번호 리스트} --topic {만들 토픽 이름} --partitions {파티션 개수} --replication-factor {리플리케이션 팩터 개수} --create 
  ```
  * 카프카 제공 명령을 통한 토픽의 상세 정보 출력
  ```bash
  $ /usr/local/kafka/bin/kafka-topics.sh --zookpeer {주키퍼 노드:포트 번호,...} --topic {토픽 이름} --describe 
  ```
  * 카프카 제공 명령을 통한 메세지 전송
  ```bash
  $ /usr/local/kafka/bin/kafka-topics.sh --broker-list {카프카 노드:포트 번호,...} --topic {토픽 이름}
  ```
  ```bash
  > {전달한 메시지}
  ```
  * 메시지를 토픽에서 가져와서 보낸 메시지 확인
  ```bash
  $ /usr/local/kafka/bin/kafka-console-consumer.sh --bootstrap-server {카프카 노드:포트 번호,...} --topic {토픽 이름} --from-beginning
  ```

### Python을 이용한 프로듀서
* 메세지를 전송하는 방법
  * 메시지를 보내고 확인하지 않기: 카프카가 살아 있는 상태에선 대체적으로 성공적으로 전송되고 프로듀서가 자동을 재전송하지만 일부 메시지가 손실될 수 있음
  * `동기 전송`: 브로커에게 전송한 메시지가 성공했는지 실패했는지 확인하므로 신뢰성있는 전송임
  * `비동기 전송`: 메시지를 전송하고 브로커에서 응답을 받으면 콜백하여 처리하므로 빠른 전송이 가능
* 일반적인 Python 프로듀서 코드
```py
from kafka import KafkaProducer

producer = KafkaProducer(bootstrap_servers='peter-kafka001:9092,peter-kafka002:9092,peter-kafka003:9092')

producer.send('peter-topic', 'Apache Kafka is a distributed streaming platform')
```
* `acks`와 압축 옵션을 추가한 Python 프로듀서 코드
```py
from kafka import KafkaProducer

producer = KafkaProducer(acks=1, compression_type='gzip', bootstrap_servers='peter-kafka001:9092,peter-kafka002:9092,peter-kafka003:9092')

producer.send('peter-topic', 'Apache Kafka is a distributed streaming platform')
```
* for loop를 추가한 Python 프로듀서 코드
```py
from kafka import KafkaProducer
from kafka.errors import KafkaError

producer = KafkaProducer(acks=1,retries=1,bootstrap_servers='peter-kafka001:9092,peter-kafka002:9092,peter-kafka003:9092')

for i in range(1, 1001):
    producer.send('peter-topic', b'Apache Kafka is a distributed streaming platform - %d' % i)
```
* key를 지정하여 특정 파티션으로만 메시지를 보내는 Python 프로듀서 코드
```py
from kafka import KafkaProducer

producer = KafkaProducer(acks=1, compression_type='gzip', bootstrap_servers='peter-kafka001:9092,peter-kafka002:9092,peter-kafka003:9092')
for i in range(1, 11):
    if i % 2 == 1:
		    producer.send('peter-topic2', key='1', value='%d - Apache Kafka is a distributed streaming platform - key=1' % i)
    else:
		    producer.send('peter-topic2', key='2', value='%d - Apache Kafka is a distributed streaming platform - key=2' % i)
```
### 프로듀서의 주요 옵션
* `boostrap.servers`: 카프카 클러스터에 처음 연결을 하기 위한 호스트와 포트 정보로 구성된 리스트 정보를 나타냄
* `acks`: 프로듀서가 카프카 토픽의 리더에게 메시지를 보낸 후 요청을 완료하기 전 승인하는 횟수
* `buffer.memory`: 프로듀서가 카프카 서버로 데이터를 보내기 위해 잠시 대기할 수 있는 전체 메모리 바이트
* `retries`: 전송에 실패한 데이터를 다시 보내는 횟수
* `batch.size`: 파티션으로 보내는 여러 데이터를 배치로 함께 보낼 때 배치의 크기 사이즈
* `linger.ms`:배치 사이즈에 도달하지 못한 상황에서도 제한 시간에 메시지를 전송할 때 사용하는 제한 시간
* `max.request.size`: 프로듀서가 보낼 수 있는 최대 메시지 바이트 사이즈