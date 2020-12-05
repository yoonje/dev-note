# Elastic Stack Chapter 1 - Logstash

<hr>

### Logstash
* Logstash - 데이터를 수집 및 가공하고 다른 저장소로 전송하는 `데이터 파이프라인` 중의 하나
* 특징
    * 입력, 필터, 출력으로 구성되며 각자의 역할이 명확하게 구분됨
    * 각각의 역활 부분에 플러그인을 붙여서 확장하여 사용함
    * 각각의 플러그인은 파이프라인의 일부가 됨

### Logstash와 파이프라인
* 파이프라인 만들기
  * 파이프라인 설정 디렉토리 만들기
  ```sh
  $ mkdir $LOGSTASH_HOME/{파이프라인 이름}
  ```
  * 파이프라인 설정 파일 만들기
  ```sh
  $ mkdir $LOGSTASH_HOME/{파이프라인 이름}.conf
  ```
  ```conf
  input{

  }
  
  filter{

  }

  output{

  }
  ```
* `config` 설정으로 파이프라인 구성하기
  * 파이프라인 설정 파일을 로그스태시가 인지할 수 있게 지정하고 파이프라인은 로그스태시의 홈 디렉토리의 config 디렉토리 안에 있는 설정 파일로 지정
  * 파이프라인 디렉토리 경로 지정
  ```sh
  $ vi $LOGSTASH_HOME/config/logstash.yml
  ```
  ```yml
  path.config = '$LOGSTASH_HOME/{파이프라인 이름}'
  ```
  * 로그스태시 재시작
  ```sh
  $ $LOGSTASH_HOME/bin/logstash
  ``` 
* 옵션을 통해 파이프라인 구성하기
  ```sh
  $ $LOGSTASH_HOME/bin/logstash -f   $LOGSTASH_HOME/{파이프라인 이름}/{파이프라인 이름}.conf
  ```

### 입력 플러그인 - 파이프라인의 시작으로 데이터 소스에서 데이터를 수집하는 역할
* 파일 플러그인
  * 입력 플러그 중에서 로그스태시가 설치된 호스트의 특정 경로에 위치한 파일에서 데이터를 수집하는 플러그인으로 `tail` 명령어처럼 데이터가 추가되면 이벤트를 감지하여 데이터를 수집
  * 파일 플러그인 사용 시 conf 파일 설정
    ```conf
    input{
      file{
        path => "{$LOGSTASH_HOME}/{수집할 파일 이름}"
        start_position => "beginning or end"
      }
    }
    filter{

    }

    output{

    }
    ```
  path는 수집할 파일의 경로 start_position은 파일 읽기를 하는 처음 지점으로 beginning은 앞에서부터 읽는 것이고 end는 뒤에서부터 읽음 -> 항상 새로운 데이터를 받으려면 end(default)
* sincedb
  * 로그스태시는 파일로부터 데이터를 수집할 때마다 어떤 파일의 어느 내용까지 읽었는지를 .sincedb 파일에 기록
  * `config/logstash.yml` 파일의 `path.data` 설정에서 생성 위치를 지정할 수 있고 지정하지 않으면 `$LOGSTASH_HOME/data/plugins/inputs/file` 디렉토리에 생성
  * sincedb 파일에 있는 정보 - inode 번호, 파일시스템의 메이저 디바이스 번호, 파일시스템의 마이너 디바이스 정보, 파일 내의 현재 바이트 오프셋, 최근 수정한 시점의 타임스탬프, 해당 파일의 경로가 공백 구분자로 기록
  * 파일 플러그인의 conf 파일에 `sincedv_path`를 수정하면 자동 생성 기능을 제거 가능
  ```conf
      input{
        file{
          path => "{$LOGSTASH_HOME}/{수집할 파일 이름}"
          start_position => "beginning or end"
          sincedb_path => "/dev/null"
        }
      }
  ```
### 필터 플러그인 - 입력 플러그인을 통해 수집된 데이터에서 불필요한 데이터를 제거하거나 데이터 타입을 변경하는 역할
* grok 필터 플러그인
  * 필터 플러그인 중의 가장 대표적인 플러그인으로 사전 정의되어 있는 정규식 패턴이 정의되어 있어 이용하면 되고 범용적이지 않은 패턴은 grok 패턴을 직접 조합하여 구문 분석에 사용
  * `Grok Debugger`같은 사이트를 이용해서 패턴에 오류가 없는지 체크하고 적용
* Mutate 필터 플러그인
  * 불필요한 필드 삭제나 데이터 타입 변경 시에 사용
  * Mutate 플러그인의 conf 파일 설정
    ```conf
    filter{
      mutate {
        옵션명 => ["대상 필드명" => "값"]
      }
    }
    ```
  * Mutate 필터 플러그인의 옵션
  ```
  convert: 해당 필드의 타입을 다른 타입으로 변환한다.
  copy: 기존에 있는 필드를 다른 필드로 복사한다.
  gsub: 정규표현식을 사용해 일치하는 모든 항목을 해당 문자열로 치환한다.
  Join: 대상 필드가 배열인 경우 구분 문자를 이용해 배열 요소를 결합한다.
  lowercase: 대상 필드를 소문자로 변환한다.
  uppercase: 대상 필드를 대문자로 변환한다.
  merge: 배열 또는 해시로 된 두 필드를 병합한다.
  rename: 필드 이름을 변경한다.
  split: 구분 문자를 사용해 필드의 문자열을 배열로 나눈다.
  strip: 필드 값에서 공백을 제거한다.
  update: 기존 필드를 새 값으로 갱신한다.
  add_field: 필드를 추가한다.
  add_tag: 태그를 추가한다.
  remove_field: 필드를 삭제한다.
  remove_tag: 태그를 삭제한다.
  ```
* date 필터 플러그인
  * date 타입을 처리하기 위해 사용, 주로 string 타입으로 수집해 date 타입으로 변환할 때 사용
  * date 필터 플러그인의 conf 파일 설정
    ```conf
    filter{
      date {
        옵션명 => "옵션에 맞는 설정 값"
      }
    }
    ```
  * date 필터 플러그인의 옵션
  ```
  locale: 날짜 구문 분석에 사용할 지역 설정 옵션
  match: 수집된 데이터의 날짜 형식에 맞는 포맷으로 지정하는 옵션
  tag_on_failure: 일치하는 항목이 없으면 필드에 값을 추가하는 옵션
  target: 타입을 변환할 대상 필드를 지정하는 옵션
  timezone: 날짜 구문 분석에 사용할 시간대의 표준 ID
  ```

### 출력 플러그인 - 수집 후 가공된 데이터를 ES나 다른 플랫폼에 저장하는 역할
* 엘라스틱서치 출력 플러그인
  * 엘라스틱서치로 데이터를 출력할 때 사용하는 플러그인
  * 엘라스틱 서치 출력 플러그인 사용 시 conf 파일 설정
    ```conf
    input{
        ....
    }

    filter{
      ....
    }

    output{
      elasticsearch {
        host => ["localhost:9200"]
        index => {자동 매핑을 피하기 위해 지정할 인덱스 이름}
      }
      stdout {
      }
    }
    ```
    IP와 Port만을 설정하면 호스트가 설정
