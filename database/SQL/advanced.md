# 데이터 분석을 위한 SQL 고급

#### DML (Data Manipulation Language)
- SELECT: 데이터를 검색하는 명령
  - SELECT 컬럼명 FROM 테이블명;
- INSERT: 데이터를 추가하는 명령
  - `테이블 전체에` 데이터를 추가: INSERT INTO 테이블명 VALUES (값_리스트);
  - `특정 칼럼에` 데이터를 추가: INSERT INTO 테이블명 (칼럼_리스트) VALUES (값_리스트);
- UPDATE: 기존에 있던 값을 갱신하는 명령
  - `칼럼 전체` 데이터를 업데이트: UPDATE 테이블명 SET 컬럼 = 값;
  - `특정 행에만` 데이터를 업데이트: UPDATE 테이블명 SET 컬럼 = 값 WHERE 조건식;
- DELETE: 데이터를 삭제하는 명령
  - 테이블 전체 데이터 삭제: DELETE 테이블명;
  - 특정 행에만 데이터를 삭제: DELETE 테이블명 WHERE 조건식;

#### ERD(Entity Relationship Diagram)
- ERD: Entity(테이블)들 간의 관계를 보는 그림
- ERD 보는 법(Crow`s Foot)
  - 속성
    - PK: Primary Key, 각 행마다 갖는 유일한 키
    - FK: Foriegn Key, 다른 엔티티의 PK를 참조하는 키
  - 관계
    - ![img1 daumcdn](https://user-images.githubusercontent.com/38535571/120035961-5b759200-c03a-11eb-98ba-85ea87349936.gif)
  - 데이터 타입
    - 정수: tinyiny(), smallint(), mediumint(), int(), bigint()
    - 실수: float(), decimal(), double()
    - 문자: varchar(), char()
    - 불린: boolean()
    - 날짜: date, time, datetime, timestamp
    - 이진: binary(), tinyblob(), blob(), mediumblob(), longblob()

#### 서브쿼리

#### 조인 심화

#### 윈도우 함수

#### 정규표현식

