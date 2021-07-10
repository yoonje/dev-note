# 인프런 ELK 강의 섹션 2

### 키바나
- Kibana는 Elasticsearch와 함께 작동하도록 설계된 오픈 소스 분석 및 시각화 플랫폼
- Elasticsearch 색인에 저장된 데이터를 검색,보기 및 상호 작용
- 인덱스 패턴 정의하면 Elasticsearch의 인덱스를 키바나에서 활용 가능
- 키바나 메뉴
  - `Discover`: 결과를 탐색하고 Visualize에서 저장된 검색의 시각화
  - `Visualize`: 여러 가지 방법으로 데이터를 시각화
  - `Dashboard`: 각종 시각화자리를 커스터마이징할 수 있는 대시보드
  - `Timelion`: 데이터 발생량 타임 라인
  - `Management`: 인덱스, 오브젝트, 및 각종 기능 관리 탭
  - `Dev Tools`: curl과 같이 쓸 수 있는 기능


### Discover
- Elasticsearch의 결과를 탐색
- 쿼리 바에서 key value 형태의 KQL를 통해서 Elasticsearch query를 입력하여 데이터를 검색
  - 관심있는 필드 이름과 값을 사용하여 검색을 구성
  - 숫자 필드에서는 큼 (>), 작음 (<) 또는 같음 (=)과 같은 비교 연산자 지원
  - 논리 연산자 AND, OR 및 NOT 등 지원

### Visualize
- Visualize에서 저장된 검색의 시각화

### Dashboard
- Visualize에서 저장한 그래프들을 불러와서 대시보드를 만들 수 있음
