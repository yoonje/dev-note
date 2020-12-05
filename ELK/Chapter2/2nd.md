# Elastic Stack Chapter 2 - Beats

<hr>

### Beats
* Beats - 로그스태시의 스니퍼 역할 대신에 용도에 맞춰 고안된 경량화된 데이터 수집 도구로 `데이터 파이프라인` 중의 하나
* 특징
  * 데이터를 수집할 원격 서버에 에이전트로 설치되어 동작
  * 웹서버의 로그부터 도커나 쿠버네티스와 같은 컨테이너 도구를 모니터링하는 기능까지 갖춤
  * Filebeat, Metricbeat, Packetbeat, Winlogbeat, Audibeat, Heartbeat가 대표적인 비츠

### Filebeat
* 파일로부터 데이터를 수집하는 경량화된 비츠
* 구조
  * `kibana` 디렉토리 - 키바나에서 import하여 시각화할 파일
  * `module` 디렉토리 - 잘 알려진 로그 데이터 형식에 맞춰 데이터 구문 분석과 엘라스틱서치의 인덱싱 방식 정의 파일셋
  * `modules.d` 디렉토리 - 각 모듈의 활성화 관련 파일 모음으로 .disable 파일들은 .disable를 지우면 활용 가능
* Filebeat의 Apache2 모듈로 아파치 웹 로그 수집
  * Filebeat는 로그스태시의 필터 플러그인과 비슷한 역할을 하는 엘라스틱서치의 인제스트 노드를 통해서 엘라스틱서치로 데이터를 전달
  * Filebeat에서 엘라스틱서치로 데이터를 바로 전달하기 보다는 부하를 줄이기 위해 앞에 `Kafka`를 붙이는 경우가 많음
  * Filebeat의 모듈을 활용하여 로그를 수집하고 ES에 인덱싱
  * ES와 Kibana 실행
  ```sh
  $ $ELASTICSTACK_HOME/start.sh elasticsearch 
  ```
  ```sh
  $ $ELASTICSTACK_HOME/start.sh kibana 
  ```
  * ES Filebeat를 위한 필수 플러그인 설치
  ```sh
  $ sudo $ELASTICSTACK_HOME/bin/elasticsearch-plugin install ingest-user-agent 
  ```
  ```sh
  $ sudo $ELASTICSTACK_HOME/bin/elasticsearch-plugin install ingest-geoip 
  ```
  * ES 재시작
  ```sh
  $ $ELASTICSTACK_HOME/restart.sh elasticsearch 
  ```
  * apache2 모듈 활성화
  ```sh
  $ $FILEBEAT_HOME/filebeat -c $FILEBEAT_HOME/filebeat.yml modules enable apache2
  ```
  * apache2 모듈 설정
  ```sh
  $ vi $FILEBEAT_HOME/modules.d/apache2.yml
  ```
  ```yml
  - moudule: apache2
    access:
      enabled: true
      var.path = ["${ELASTIC_STACK_HOME}/pilot02/filebeat-apache-access.log"]
    error:
      enabled: false
  ```
  * apache2 모듈 활성화 체크
  ```sh
  $ $FILEBEAT_HOME/filebeat -c $FILEBEAT_HOME/filebeat.yml modules list
  ```
  * 초기환경 설정
  ```sh
  $ $FILEBEAT_HOME/filebeat -e -c $FILEBEAT_HOME/filebeat.yml setup --modules apache2
  ```
  * 데이터 전송
  ```sh
  $ $FILEBEAT_HOME/filebeat -e -c $FILEBEAT_HOME/filebeat.yml
  ```
* Apache 왭 로그 파일에서 로그 수집 
  * apache 웹 모듈을 사용하지 않고 비츠에서 수동으로 파일을 지정하여 바로 ES로 인덱싱
  * filebeat 설정 파일에서 수동으로 파일을 지정하고 ES에 연결 및 사용자 정의 인덱스에 대한 템플릿 지정
  ```sh
  $ vi $FILEBEAT_HOME/filebeat.yml
  ```
  ```yml
  filebeat.inputs:
  - type: log
    enabled: true
    paths: ${ELASTICSTACK_HOME}/pilot02/filebeat-apache-access.log  
  output.elasticsearch:
    host: ["localhst:9200"]
    index: "filebeat-apache-access-%{yyyy.MM.dd}"
  setup.template:
    name: "filebeat-apache-access"
    pattern: "filebeat-apache-access-*"
    enabled: true
  ```
  * Filebeat 실행
  ```sh
  $ $FILEBEAT_HOME/filebeat -e -c $FILEBEAT_HOME/filebeat.yml
  ```
  * curl 명렁어를 통해 설정한 템플릿 확인
  ```sh
  $ curl -XGET "localhost:9200/_template/filebeat-apache-access?pretty"
  ```
  * Filebeat는 수집한 데이터의 재수집을 방지하기 위해서 registry에 마지막으로 수집한 위치 정보를 적으므로 이를 확인
  ```
  $ cat $FILEBEAT_HOME/data/registry
  ```
  * `setup` 명령을 통한 인덱스 패턴과 시작화 및 대시보드 생성
  ```sh
  $ $FILEBEAT_HOME/filebeat -e -c $FILEBEAT_HOME/filebeat.yml setup --modules apache2
  ```
  * 키바나에서 어려가지 작업이 가능
* 로그스태시 결합 및 키바나 활용
  * raw 데이터를 ES에 그대로 인덱싱하는 것보다 중간에 로그스태시를 두어 가공하고 저장하는 것이 합리적인 구조
  * Filebeat에 데이터를 가공할 Logstash를 설정
  ```sh
  $ vi $LOGSTASH_HOME/pipeline/filebeat.yml
  ```
  ```yml
  input {
    beats {
      port => 5044
    }
  }
  filter {
    grok {
      match => { "message" => "%{HTTPD_COMBINEDOG}"}
    }
    mutate {
      remove_field => [ "auth", "ident" ]
      convert => { "bytes" => "integer" }
      convert => { "response" => "integer" }
    }
    date{
      match => ["timestamp", "d/MMM/yyyy:HH:mm:SS Z"]
      target => "timestamp"
    }
    geoip {
      source => "clientip"
    }
  }
  output {
    elasticsearch{
      host => [ "localhost:9200" ]
      index => "filebeat-using-logstash-%{yyyy.MM.dd}"
    }
    stdout{
    }
  }
  ```
  * 로그스태시 실행
  ```sh
  $ $LOGSTASH_HOME/start.sh logstash -f $LOGSTASH_HOME/pipeline/filebeat.yml
  ```
  * Filebeat에서 로그스태시로 데이터를 넘기도록 설정
  ```sh
  $ vi $FILEBEAT_HOME/filebeat.yml
  ```
  ```yml
  output.logstash:
    hosts: ["localhost:5044"]
  ```
  * registry 파일 제거
  ```sh
  $ rm $FILE_HOME/data/*
  ```
  * filebeat 실행
  ```sh
  $ $FILEBEAT_HOME/filebeat -e -c $FILEBEAT_HOME/filebeat.yml
  ```
  * 키바나에서 인덱스 패턴을 만들고 어려가지 작업이 가능

### Metricbeat
* Metricbeat는 설치된 대상 호스트의 리소스 정보를 수집하고 로그스태시나 엘라스틱서치에 전달하는 비츠
  * metricbeat 설정 파일
  ```sh
  $ vi $METICBEAT_HOME/metricbeat.yml
  ```
  ```yml
  metricbeat.config.modules:
    path: ${path.config}/modules.d/*.yml # module.d 디렉토리 안에서 .yml 확장자 glob패턴으로 로드
    reload.enabled: false # 설정 파일을 reload하는 기능의 가능 여부 
    reload.period: 10s # 설정 파일의 reload 주기
  output.elasticsearch: # 아웃풋은 ES로 하여 바로 인덱싱
    hosts: ["localhost:9200"]
  ```
  * metricbeat의 정보 관련 설정 파일인 systeml.yml 파일 설정
  ```sh
  $ vi $METRICBEAT_HOME/modules.d/system.yml
  ```
  ```yml
  - module: system # 호스트의 시스템 리소스를 수집하기 때문에 시스템 모듈로 지정
    period: 10s
    metricsets: # 수집할 데이터 목록
      - cpu
      - load
      - memory
      - network
      - process
      - process_summary
    processes: ['.*']
    process.include._top_n:
      by_cpu: 5
      by_memory: 5
  - module: system # 호스트의 파일 시스템 관련 데이터를 수집하는 모듈
    period: 1m
    metricets:
      - filesystem
      - fsstat
    processors:
      - drop_event.when.regexp:
        system.filesystem.mount_point: '^/(sys|cgroup|proc|dev|etc|host|lib)($|/)'
  - module: system # 15분 주기로 호스트의 OS의 구동 시간을 수집하는 모듈
    period: 10m
    metricsets:
      - uptime
  ```
  * elasticsearch와 kibana 실행
  ```sh
  $ $ELASTICSTACK_HOME/start.sh elasticsearch
  ```
  ```sh
  $ $ELASTICSTACK_HOME/starth.sh kibana
  ```
  * 수집할 대상 확인
  ```sh
  $ $METRICBEAT_HOME/metricbeat -c $METRICBEAT_HOME/metricbeat.yml modules list
  ```
  * 모듈 활성화
  ```sh
  $ $METRICBEAT_HOME/metricbeat -c $METRICBEAT_HOME/metricbeat.yml enable {해당 모듈}
  ```
  해당 모듈에는 `MySQL`같은 모듈 이름이 들어감
  * metricbeat 실행을 통한 데이터 수집
  ```sh
  $ $METRICBEAT_HOME/metricbeat -c $METRICBEAT_HOME/metricbeat.yml
  ```
  * `setup` 명령을 통한 인덱스 패턴과 시작화 및 대시보드 생성
  ```sh
  $ $METRICBEAT_HOME/metricbeat -c $METRICBEAT_HOME/metricbeat.yml setup --dashboards
  ```
  * 키바나에서 여러가지 작업이 가능


### Packetbeat
* Packetbeat는 설치된 대상 호스트의 네트워크 리소스 정보를 수집하고 로그스태시나 엘라스틱서치에 전달하는 비츠
  * packetbeat 설정 파일
  ```sh
  $vi $PACKETBEAT_HOME/packetbeat.yml
  ```
  ```yml
  packetbeat.interfaces.device: any # 기록할 네트워크 인터페이스 설정
  packetbeat.flows: # 타임 아웃 설정과 수집한 데이터를 기록하는 주기
    timeout: 30s
    period: 10s
  packetbeat.protocols: # 지원하는 다양한 프로토콜에 대한 설정에 대해 데이터를 수집하고 output 섹션에 정의한 대상에게 전달
  - type: icmp
    enabled: true
  - type: amqp
    ports: [5672]
  - type: cassandra
    prots: [9042]
  - type: dns
    ports: [53]
    include_authorities: true
    include_addithinals: true
  - type: http
    ports: [80, 8080, 8000, 5000, 8002]
  - type: memcache
    ports: [11211]
    ....
  output.elasticsearch:
    hosts: ["localhost:9200"]
  ```
  * elasticsearch와 kibana 실행
  ```sh
  $ $ELASTICSTACK_HOME/start.sh elasticsearch
  ```
  ```sh
  $ $ELASTICSTACK_HOME/start.sh kibana
  ```
  * 호스트 내부적으로 root 권한 획득을 위해 퍼미션 부여
  ```sh
  $ sudo chown root:root $PACKETBEAT_HOME/packetbeat.yml
  ```
  * root 권한으로 packetbeat 실행
  ```sh
  $ sudo $PACKETBEAT_HOME/packetbeat -e -c $PACKETBEAT_HOME/packetbeat.yml 
  ```
  * `setup` 명령을 통한 인덱스 패턴과 시작화 및 대시보드 생성
  ```sh
  $ $PACKETBEAT_HOME/packetbeat -c $PACKETBEAT_HOME/packetbeat.yml setup --dashboards
  ```
  * 키바나에서 여러가지 작업이 가능

### Heartbeat
* 서버의 상태를 주기적 알리는 것을 `Heartbeat`라고 하여 Heartbeat는 서버 상태를 체크하는 비츠
* ICMP, HTTP, TCP에 대해서 체크 가능
  * Heatbeat 설정 파일
  ```sh
  $ vi $HEARTBEAT_HOME/heartbeat.yml
  ```
  ```yml
  heartbeat.monitors: # 모니터링할 대상의 유형
    - type: http
      urls: ["http://localhost:9200"]
      schedule: '@every 10s' # 모니터링 주기
  output.elasticsearch: # 수집한 데이터를 보내는 곳
    hosts: ["localhost:9200"]
  ```
  * 엘라스틱서치와 키바나 실행
  ```sh
  $ $ELASTICSTACK_HOME/start.sh elasticsearch
  ```
  ```sh
  $ $ELASTICSTACK_HOME/start.sh kibana
  ```
  * Heatbeat 실행
  ```sh
  $ sudo $HEARTBEAT_HOME/heartbeat -e -c $HEARTBEAT_HOME/heartbeat.yml 
  ```
  * `setup` 명령을 통한 인덱스 패턴과 시작화 및 대시보드 생성
  ```sh
  $ sudo $HEARTBEAT_HOME/heartbeat -e -c $HEARTBEAT_HOME/heartbeat.yml setup --dashboards
  ```
  * 키바나에서 여러가지 작업이 가능

  ### Auditbeat
  * 시스템 상의 사용자와 프로세스의 활동을 감시하는 경량 비츠
    * Auditbeat 설정 파일
  ```sh
  $ vi $AUDITBEAT_HOME/auditbeat.yml
  ```
  ```yml
  # 리눅스 커널을 감시하는 모듈인 auditd
  - module: auditd
    audit_rule_files: ['${path.config}/audit.rules.d/*.conf']
    audit_rules: |
  # 파일이 변경되면 이벤트를 감지하는 모듈인 file_integrity
  - module: file_integrity
    path:
    - ${elasticstack_home}
  output.elasticsearch:
    hosts: ["localhost:9200"]
  ```
  * 엘라스틱서치와 키바나 실행
  ```sh
  $ $ELASTICSTACK_HOME/start.sh elasticsearch
  ```
  ```sh
  $ $ELASTICSTACK_HOME/start.sh kibana
  ```
  * 호스트 내부적으로 root 권한 획득을 위해 퍼미션 부여
  ```sh
  $ sudo chown root:root $AUDITBEAT_HOME/auditbeat.yml
  ```
  * root 권한으로 Auditbeat 실행
  ```sh
  $ sudo $AUDITBEAT_HOME/auditbeat -e -c $AUDITBEAT_HOME/auditbeat.yml -E elasticstack_home=${ELASTICSTACK_HOME}
  ```
  * `setup` 명령을 통한 인덱스 패턴과 시작화 및 대시보드 생성
  ```sh
  $ sudo $AUDITBEAT_HOME/auditbeat -e -c $AUDITBEAT_HOME/auditbeat.yml setup --dashboards
  ```
  * 키바나에서 여러가지 작업이 가능
