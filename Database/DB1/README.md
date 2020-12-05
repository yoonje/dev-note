# 데이터베이스 기초
하석재 강사님 데이터베이스 기초 정리

## DBMS의 기초
##### DBMS
- DBMS: `데이터베이스를 관리하는 시스템`으로 데이터를 저장하고 유지보수하고 이를 검색하는 것이 목적
- DB: 테이블들이 모여 이루는 데이터 단위
- CRUD / Create, Retrieve, Update, Delete
  - Create: INSERT
  - Retrieve: SELECT
  - Update: UPDATE
  - Delete: DELETE
  - 일반적인 경우 검색이 다른 연산에 비해 압도적으로 많음
- 빅데이터: 일반적인 데이터베이스토 다룰 수 없는 큰 데이터

##### 정렬
- DBMS는 빠른 검색을 위해서 데이터는 `반드시 정렬`이 되어 있어야함
- 퀵정렬/힙정렬(O(NlongN))이 주로 사용됨

##### 인덱스
- 인덱스: `검색을 하기 위해 만들어 놓은 이진 탐색 트리 계열이나 B-Tree 계열의 자료구조(비교값)`
- 데이터 추가/수정/삭제 시에 정렬 또는 인덱스 업데이트가 일어남

##### 이진 탐색 트리
- 데이터가 추가/삭제/변경될 때마다 `한가운데/왼쪽 가운데/오른쪽 가운데`(인덱스) 값등을 미리 계산해 놓음
- 지수가 2인 logN 복잡도
- x -> `x < mid, x > mid` 반복
##### B-트리
- 이진 트리와 유사하지만 한 번에 비교를 2번하여 값들을 미리 계산해 놓음
- 지수가 3인 logN 복잡도
- x -> `x < a, a < x < b, x > b` 반복

##### DBMS의 종류
- 계층형 데이터베이스
- 네트워크형 데이터베이스
- `관계형 데이터베이스(RDBMS)`
- 객체지향 데이터베이스
- 객체관계형 데이터베이스
- `NoSQL(Not Only SQL)`

### RDBMS
##### RDBMS
- RDBMS: 관계형 데이터베이스 시스템
- 테이블 기반의 DBMS
  - 테이블 - `칼럼 형태의 데이터 저장 방식`
  - `테이블 단위로 데이터를 관리`
  - 테이블과 테이블 간의 연관 관계(외래키)를 이용해 필요한 정보를 구하는 방식
- 모델링은 E-R(Entity Relationship) 모델을 사용
- 테이블을 엔티티와 릴레이션십 테이블로 구분
- 테이블끼리의 중복 정보는 최소화시킴(정규화) -> 정규형
- JOIN을 통해서 여러 테이블을 합쳐 큰 테이블을 생성하고 필요한 정보를 찾는 방식

##### 기본 용어
- 스키마: 테이블 이름과 속성 이름의 나열
- SQL: 관계형 DBMS를 사용하는 전용 질의 언어로 대소문자를 구분하지 않는 인터프리터 언어
- 기본키: 테이블에서 `하나의 레코드를 지정`할 수 있는 하나의 컬럼 집합
- 외래키: 테이블의 기본키가 다른 테이블의 칼럼에 들어 있는 경우에 외래키라고 부름
- 테이블(릴레이션): 정보들의 묶음 단위
- 컬럼(열,필드,속성): 테이블을 구성하는 정보
- 레코드(행,로우,튜플): 테이블에 들어 있는 인스턴스 하나
- 도메인 값: 각 컬럼에서 나오는게 가능한 후보 값
- 릴레이션쉽: 릴레이션 간의 관계
- 도메인: 속성들이 가질 수 있는 값의 집합

## RDMBS(MySQL) 기본 사용법
##### 기본 사용법
- `show databases;`: DB들의 리스트를 표시한다
- `use 디비명`: DB를 사용한다
- `show tables`: (DB 안에 있을 때) DB의 테이블 리스트를 표시한다
- `desc 테이블명`: 테이블의 구조를 표시한다
- `select * from 테이블명`: 테이블의 모든 내용을 표시한다

## SQL DML 1

##### SQL 기본
- DML(데이터 조작어): 데이터베이스에 들어 있는 데이터를 `조회하거나 변형을 가하는 명령어`
  - SELECT: 데이터베이스 객에 안의 데이터를 조회
  - INSERT: 데이터베이스 객체에 데이터를 입력
  - UPDATE: 데이터베이스 객체 안의 데이터를 수정
  - DELETE: 데이터베이스 객체에 데이터를 삭제
- DDL(데이터 정의어): 테이블과 같은 데이터 구조를 `정의하는데 사용되는 명령어`
  - CREATE: 데이터베이스 객체를 생성
  - DROP: 데이터베이슷 객체를 삭제
  - ALTER: 기존에 존재하는 데이터베이스 객체를 다시 정의
- DCL(데이터 제어어): 데이터베이스에 접근하고 객체들을 사용하도록 `권한을 주고 회수하는 명령어`
  - GRANT: 데이터베이스 객체에 권한을 부여
  - REVOKE: 데이터베이스 객체에 권한을 취소
- SQL(Structured Query Language): 관계형 데이터베이스에서 필요한 정보를 사용하도록 도와주는 표준 언어
  - 모든 DBMS에서 사용이 가능
  - 인터프리터 언어
  - 대소문자를 구별하지 않음

##### DML
- DML 정리 표

|이름|조작|SQL|
|------|---|---|
|Create|새로운 레코드 추가(생성)|INSERT|
|Read|조건에 만족하는 레코드를 찾아 검색(읽기)|SELECT|
|Update|레코드의 컬럼 값을 수정(갱신)|UPDATE|
|Delete|특정 레코드를 삭제(삭제)|DELETE|

- SELECT
  - `SELECT 컬럼명 FROM 테이블명 WHERE 조건절;`
  - select * from city where CountryCode=‘KOR’;
- INSERT
  - `INSERT INTO 테이블명(컬렴명) VALUES (값);`
  - insert into city values (20000, ‘SampleTest’, ‘SPL’, ‘Test’, 2000000);
- UPDATE
  - `UPDATE 테이블명 SET 컬럼명=값,... WHERE 조건절;`
  - update city set name=‘SampleRevised’ where id = 10000;
  - WHERE 절에 매칭되는 레코드가 여러 개일 수 있으므로 주의
- DELETE
  - `DELETE FROM 테이블명 WHERE 조건절;`
  - delete from city where ID = 10000;
  - WHERE 절에 매칭되는 레코드가 여러 개일 수 있으므로 주의

## SQL DML 2
##### DISTINCT 연산자
- DISTINCT
  - SELECT 문의 결과값에서 특정 컬럼만 출력할 경우 중복된 값들이 나오는 경우에 이를 제거해서 표시하는 기능
  - `select distinct 컬럼명1, 컬럼명2, ... from 테이블명 where 조건절`
  - select distinct CountryCode from city where CountryCode=‘KOR’;

##### 논리연산자
- AND, OR, NOT
  - SELECT 문의 조건절에 논리조건 적용해서 적용할 수 있는 연산자
  - `select * from 테이블명 where (not) 조건1 and/or (not) 조건2 ....`
  - select * from city where CountryCode !=‘KOR’ and Population >= 1000000;
- IN, BETWEEN
  - SELECT 문의 조건절에 논리조건에 추가 적용해서 적용할 수 있는 연산자
  - select * from city where CountryCode = ‘KOR’ and (Population between 1000000 and 5000000);

##### 결과값 정렬
- ORDER BY
  - SELECT문의 결과값을 특정한 컬럼을 기준으로 오름차순/내림차순으로 정렬해서 표시하게 해주는 연산자
  - 기본값은 오름차순 정렬이고 여러 개의 컬럼을 나열하면 순서대로 우선순위를 두어 정렬
  - `select * from 테이블명 where 조건절 order by 컬럼명 asc/desc, ...`
  - select CountryCode, Population from city order by CountryCode, Population desc;

## SQL DML 3
##### 결과값 일부 조회
- LIMIT
  - SQL 쿼리 결과 중 상위 몇개만 보여주는 쿼리
  - Order by와 많이 쓰임
  - 오라클에서는 ROWNUM, SQLServer는 TOP이라는 명령으로 쓰임
  - `select 컬럼명1, 컬럼명2, ... from 테이블명 where 조건절 limit 숫자`
  - select * from city where CountryCode=‘KOR’ order by Population desc limit 10;

##### 집합함수(집계함수)
- 집합함수 count(), avg(), sum(), min(), max(), first(), last()
  - SELECT 문에서 테이블의 전체레코드를 대상으로 특정 컬럼을 적용해서 한 개의 값을 리턴하는 함수
  - `select aggregation_function(컬럼명) from 테이블명 where 조건절;`
  - count(): 레코드의 개수를 리턴하는 함수
    - select count(*) from city where CountryCode=‘KOR;
  - sum()/avg(): 컬럼값의 합/평균을 리턴 
    - select sum(Population) from city where CountryCode=‘KOR’;
    - select avg(Population) from city where CountryCode=‘KOR’;
  - min()/max(): 컬럼값의 최소/최대값을 리턴
    - select min(Population) from city where CountryCode=‘KOR’; 
    - select max(Population) from city where CountryCode=‘KOR’;

##### 기타 유용한 함수
- LENGTH(): 레코드의 문자열 컬럼의 글자 수를 리턴
  - select length(Name) from country;
- MID(): 문자열의 중간 부분을 리턴
  - select mid(Name,1,3) from country;
- UPPER()/LOWER(): 문자열을 대문자/소문자로 리턴
  - select Name, upper(mid(Name,1,3)) from country;
- ROUND(): 레코드의 숫자 컬럼 값을 반올림해서 리턴
  - select Name, round(LifeExpentancy,0) from country;


## SQL DML 4
##### JOIN
- INNER JOIN
  - 서로 다른 테이블을 `공통 컬럼을 기준으로 결합하는 테이블 단위의 연산`
  - 조인의 결과는 레코드 개수는 연산되는 레코드의 개수가 많은 테이블의 레코드의 개수와 같음
  - 조인의 결과 테이블은 이전 테이블의 컬럼 수의 합과 같음
  - INNER는 보통 생략
  - 조인 시 NULL 값을 허용하지 않아서 NULL 값을 가진 레코드는 결과에서 빠짐
  - 조인 시 서로 다른 테이블에 같은 컬럼명이 존재하면 구분을 위해 테이블명.컬럼명으로 사용해서 표시
  - `select * from 테이블1 join 테이블2 on 테이블1.컬럼명 = 테이블2.컬럼명 ...`
  - select * from `city join country` on city.CountryCode = country.Code;
- LEFT JOIN(외부조인)
  - INNER JOIN과 기본적인 연산은 동일하나 조인을 할 때 왼쪽 테이블의 NULL 값을 가진 레코드는 결과에서 포함시키는 조인 연산
- RIGHT JOIN(외부조인)
  - INNER JOIN과 기본적인 연산은 동일하나 조인을 할 때 오른쪽 테이블의 NULL 값을 가진 레코드는 결과에서 포함시키는 조인 연산
- FULL JOIN(외부조인)
  - INNER JOIN과 기본적인 연산은 동일하나 조인을 할 때 전체 테이블의 NULL 값을 가진 레코드는 결과에서 포함시키는 조인 연산


##### ALIAS
- SQL 쿼리 결과 생성 시 컬럼 명에 대한 별명을 사용해 표시하는 기능
- 조인할 때 많이 사용됨
- `SELECT 테이블명1.컬럼명1 AS 별명1,테이블명2.컬럼명2 AS 별명2 FROM...`
-  select city.countryCode As Abbr, country.Name As FullName from city where city.CountryCode = ‘KOR’;

##### VIEW
- SQL 쿼리의 결과를 `임시 테이블로 저장해서 사용하는 기능`
- 사용이 끝나면 명시적으로 삭제해야함
- `CREATE VIEW 뷰명 AS SELECT ...`
- `DROP VIEW 뷰명`
- create view sampleView as select city.countryCode As Abbr, country.Name As FullName from city join country on city.CountryCode = country.Code where city.CountryCode = ‘KOR’;
- select * from sampleView;


## SQL DML 5
##### SELECT INTO
- `쿼리 결과를 새 테이블로 만듦`
- 기존에 존재하지 않는 테이블이 새로 생성 (뷰와 동일한 효과)
- `MySQL에서는 CREATE TABLE 테이블명 SELECT * FROM 테이블명`
- create table city_new select * from city where CountryCode=‘KOR’;

##### INSERT INTO SELECT
- `쿼리 결과를 기존의 테이블에 추가`
- SELECT의 결과 테이블과 INSERT하는 테이블은 동일한 구조를 가져야 함
- `INSERT INTO 테이블명1 SELECT * FROM 테이블명2 WHERE 조건절 ...`
- insert into city_kor select * from city where CountryCode=‘KOR’;

##### CASE WHE END
- SQL의 조건문(if/switch문)에 해당
- `CASE WHEN 조건값1 THEN ... WHEN 조건값2 THEN ... ELSE ... END`
- select 
    case when length(Name) > 3 then upper(mid(Name, 1,3)) when length(Name) <= 3 then upper(Name) end, 
  Population from city;

## SQL DML 6
##### LIKE 검색
- 정확한 키워드를 모를 경우 `일부만으로 검색하는 방법`
- 와일드카드(%, _)를 사용하여 패턴 매칭
  - %: 0~n글자
  - _: 1글자
- LIKE의 검색은 매칭하기 위해 DBMS에 부담이 많으므로 LIKE에 OR와 같은 논리조건자를 중복해서 사용하지 않는게 좋음
- `select * from 테이블명 where like 컬럼명1 like ... or 컬럼명2 like ... ;`
- select CountryCode from city where CountryCode like ‘%K’;


##### NULL 값
- NULL이란 `해당 컬럼의 값이 없다는 의미`(해당 컬럼이 NULL값을 허용하는 경우) 
- NULL 값을 가지고 있는 컬럼을 검색하려면 is NULL
- NULL이 아닌 값을 가지고 있는 컬럼을 검색하려면 `is not NULL`
- select count(*) from country where LifeExpectancy is NULL; 
- select count(*) from country where LifeExpectancy is not NULL;

##### NULL 함수
- 숫자 컬럼을 연산해야 할때 컬럼에 있는 NULL을 처리해주는 함수로 `NULL값이 나오면 다른 값(주로 0)으로 대체해서 계산에 문제없도록 처리`
- IFNULL(MySQL), ISNULL(SQL Server), NVL(오라클)
- 숫자연산/sum() 함수의 경우는 처리가 내장
- select avg(IFNULL(LifeExpectancy,0)) from country;
- select count(IFNULL(LifeExpectancy, 0)) from country;

##### GROUP BY
- SELECT 문에서 `집합 함수와 같이 사용해 그룹별 연산을 적용하는 함수`
- HAVING은 `그룹 연산에 WHERE 조건절 대체로` 사용
- `select 컬럼명, 집합 함수명(컬럼명) from 테이블명 group by 컬럼명 having 조건절;`
- select CountryCode, count(CountryCode) from city group by CountryCode having count(CountryCode) >= 70;


## SQL DML 7
##### 서브쿼리
- 쿼리문 내에 또 다른 쿼리문이 있는 형태로 `서브 쿼리의 결과를 포함하여 메인 쿼리가 존재하는 구조`
- 서브쿼리에서는 ORDER BY를 사용할 수 없으며 ()를 사용해 감싸야함
- 단일행 서브쿼리: 결과가 레코드 하나인 서브쿼리로 `일반 연산자(<,>,=) 사용`
  - select count(*) from city where CountryCode = (select Code from country where Name=‘South Korea’);
- 다중행 서브쿼리: 결과가 레코드 여러 개인 서브쿼리로 `다중행 연산자(IN,ALL,ANY,EXISTS) 사용`
  - 다중행 연산자
    - ALL: 여러 개의 레코드의 AND 효과
    - ANY: 여러 개의 레코드의 OR 효과
    - IN: 결과값 중에 있는 것 중에서의 의미로 전체 레코드를 스캔
    - EXIST: 결과값 중에 있는 것 중에서의 의미로 존재여부만 확인
  - select CountryCode, count(*) from city where CountryCode IN (select Code from country where Name in ('South Korea','China','Japan')) group by CountryCode; 
- 다중 컬럼 서브쿼리: 결과가 컬럼 여러 개인 서브쿼리
  - select Name, CountryCode, Population from city where (Name, CountryCode) in (select Name, CountryCode from city where Population > 5000000);

##### 집합연산
- UNION(합집합)
  - `두 쿼리의 결과값을 합쳐서 리턴`
  - 기본적으로 distict 옵션이 있으므로 중복을 허용하려면 UNION ALL
  - select * from city where CountryCode=‘KOR’ UNION select * from city where CountryCode=‘CHN’;
- INTERSECT(교집합)
  - `두 쿼리의 결과값 중 공통값을 찾아서 리턴`
  - 기본적으로 distict 옵션이 있음
  - 두 쿼리의 결과의 형식이 동일해야함
  - select Code from country where LifeExpectancy >= 80 INTERSECT select Code from country where Population >= 1000000;
- MINUS(차집합)
  - `쿼리1 결과값에서 쿼리2 결과값을 빼서 리턴`
  - 두 쿼리의 결과의 형식이 동일해야함
  - select CountryCode from city where Population > 5000000 MINUS select CountryCode from city where CountryCode=‘CHN’;
- MySQL은 INTERSECT와 MINUS는 지원하지 않음


## SQL DDL 1

##### DDL
- DDL: 데이터베이스와 테이블을 CRUD(Create, Retrieve, Update, Delete)하는 명령어

##### 스키마 정의
- 데이터베이스 생성
  - `CREATE DATABASE 데이터베이스명;`
  - create database sampleDB;
- 테이블 생성
  - `CREATE TABLE 테이블명 (컬럼명1 데이터타입(크기), 컬럼명2 …);`
  - create table BusinessCard(Name varchar(255), Address varchar(255), Telephone varchar (255));
- 데이터베이스 삭제
  - `DROP DATABASE 데이터베이스명;`
  - drop database sampleDB;
- 테이블 삭제
  - `DROP TABLE 테이블명`
  - drop table BusinessCard; 

##### 자료형
- 정수형
  - TINYINT(-128 – 127 / 255)
  - INT(-21억 – 21억 / 43억)
  - BIGINT(-9경 – 9경 / 18경)
- 실수형
  - FLOAT(size, d)
  - DOUBLE(size, d)
  - DECIMAL(size, d)
- 문자열
  - CHAR 고정길이 문자열(최대 255자)
  - VARCHAR 가변길이 문자열(최대 255자)
- TEXT 문자열
  - TEXT (최대 65,535자)
  -  MEDIUMTEXT(최대 16,777,215자)
  - LONGTEXT(최대 4,294,967,295자)
- BLOB(Binaryy)
  - BLOB(최대 65,535 바이트)
  - MEDIUMBLOB(최대 16,777,215 바이트)
  - LARGEBLOB(최대 4,294,967,295 바이트) 
- 시간관련 자료형
  - DATE(YYYY-MM-DD)
  - TIME(HH:MI:SS)
  - DATETIME(YYYY-MM-DD HH:MI:SS)
  - TIMESTAMP (YYYY-MM-DD HH:MI:SS)

##### 제약조건
- 제약조건: 입력 데이터에 제약조건을 걸어 해당되지 않는 데이터는 `입력되도록 하지 않는 조건`
- NOT NULL: 데이터가 NULL 값을 받아들이지 않는 제약조건
  - create table BusinessCard(Name varchar(255) `not null`, Address varchar(255), Telephone varchar (255));
- UNIQUE: 테이블에 동일한 값이 입력되어 있을 경우 받아들이지 않는 제약 조건
  - create table BusinessCard(Name varchar(255) `unique`, Address varchar(255), Telephone varchar (255));
- PRIMARY KEY: 기본키 제약조건(UNIQUE, NOT NULL 조건)
  - create table BusinessCard(id int not null, Name varchar(255), Address varchar(255), Telephone varchar (255), `primary key(id)`);
- FOREIGN KEY: 외래키(현재 테이블의 특정 컬럼이 다른 테이블의 기본키) 제약 조건
  - create table Salary(id int not null, salary_amount int, business_card_id int not null, primary_key(id), `foreign key (business_card_id) references BusinessCard(id)`);
- DEFAULT: 컬럼값이 입력되지 않으면 기본값을 입력하는 옵션
  - create table BusinessCard(Name varchar(255), Address varchar(255) `default ‘SEOUL’`, Telephone varchar (255));
- 자동 증가: 레코드가 추가될 때마다 자동 증가시키는 옵션
  - create table BusinessCard(ID int `auto_increment`, Name varchar(255), Address varchar(255), Telephone varchar (255), primary key(id));

## SQL DDL 2

##### 중복정보 제거
- 테이블 간의 정보는 중복되면 데이터 낭비 및 수정 시에 관리가 어려워서 `정규화`를 통해서 중복성을 제거
- 중복성 제거 이후 필요한 정보는 외래키를 통한 조인을 통해 구함

##### 정규형
- 제1정규형: 나눌 수 있을 만큼 다 쪼개라.
- 제2정규형: 제1정규형 + 테이블 칼럼들을 `기본키와 직접 연관되는 칼러만으로` 구성하라.
- 제3정규형: 제2정규형 + 칼럼들 간의 종속 관계가 있으면 쪼개라.

##### 참조무결성
- 참조무결성: 외래키에 적용되는 규칙으로 외래키와 참조되는 원래 테이블의 키와의 관게
- 외래키를 참조하면 참조되고 있는 테이블에 해당 레코드 값이 반드시 존재해야하므로 참조하는 외래키값을 먼저 NULL로 바꾸고 원래 레코드를 삭제해야함 -> 레코드 추가 삭제 시에 `순서`가 발생


## SQL DDL 3

##### 스키마 수정
- 테이블 컬럼 추가/삭제/수정
  - ALTER TABLE 테이블명 ADD 컬럼명 데이터타입
  - ALTER TABLE 테이블명 DROP COLUMN 컬럼명
  - ALTER TABLE 테이블명 CHANGE 컬럼명 new_컬럼명 데이터타입(컬럼명변경)
  - ALTER TABLE 테이블명 MODIFY 컬럼명 데이터타입(컬럼타입변경)
- 기본키 제약 조건 추가/삭제
  - ALTER TABLE 테이블명 ADD PRIMARY KEY (컬럼명)
  - ALTER TABLE 테이블명 DROP PRIMARY KEY
- UNIQUE 제약조건 추가/삭제
  - ALTER TABLE 테이블명 ADD UNIQUE (컬럼명)
  - ALTER TABLE 테이블명 ADD CONSTRAINT 제약명 UNIQUE (컬럼명1, 컬럼명2)
  - ALTER TABLE 테이블명 DROP UNIQUE 제약명
- 외래키 제약조건 추가/삭제
  - ALTER TABLE 테이블명 ADD FOREIGN KEY (컬럼명) REFERENCES 원테이블명(원컬럼명)
  - ALTER TABLE 테이블명 DROP FOREIGN KEY 컬럼명
- NOT NULL 제약조건 추가/삭제
  - ALTER TABLE 테이블명 MODIFY 컬럼명 (데이터형) NOT NULL;
  - ALTER TABLE 테이블명 DROP CONSTRAINT 제약명
- CHECK 제약조건 추가/삭제 (MySQL은 지원 안함)
  - ALTER TABLE 테이블명 ADD CHECK 조건
  - ALTER TABLE 테이블명 ADD CONSTRAINT 조건명 CHECK (조건절) 
  - ALTER TABLE 테이블명 DROP CHECK 조건명
- 테이블명 수정
  - ALTER TABLE 테이블명 RENAME new_테이블명
- DEFAULT 제약조건 추가/삭제
  - ALTER TABLE 테이블명 ALTER 컬럼명 SET DEFAULT 기본값
  - ALTER TABLE 테이블명 ALTER 컬럼명 DROP DEFAULT

##### 스키마 삭제
- 데이터베이스(DB) 삭제
  - DROP DATABASE 데이터베이스명
- 테이블 삭제
  - DROP TABLE 테이블명 -> 테이블 삭제, 내용과 테이블 전체 삭제
  - DELETE * FROM 테이블명 -> 레코드를 일일히 하나씩 지움, 테이블 스키마는 유지
  - TRUNCATE TABLE 테이블명 -> 테이블 내용만 지움, 테이블 스키마는 유지 <- DELETE * FROM 테이블명 보다 빠른 방법

## SQL DCL

##### DCL
- DCL: 특정 테이블에 대한 CRUD(Create/Retrieve/Update/Delete)권한 설정어
- DBA(DataBase Administrator)가 설정

##### 디비 사용자 추가 및 삭제
- `use 시스템 디비명`을 통해 디비에 접근하고 내부의 user 테이블을 통해서 권한 설정
- 디비 사용자 추가
  - `Create User 사용자명@호스트 IDENTIFIED BY '비밀번호';`
- 디비 사용자 삭제
  - `DROP User 사용자명@호스트;`
- 사용자 추가 및 삭제 이후에는 `flush privileges;`를 통해서 반영해줘야함

##### 권한 설정 및 권한 회수
- 권한 종류
  - 로컬에서의 접근 권한
  - 로컬 네트워크에서의 접근 권한
  - 인터넷 전체에서의 접근 권한
  - CRUD 별로의 권한
- 권한 확인
  - `show grants for 사용자명;`
  - show grants for sampleUser@localhost;
- 권한 부여(GRANT)
  - `grant 권한 종류 on 디비명.테이블명 to 사용자@호스트 indenified by '비밀번호'`
  - sampleUser에게 로컬 접속에 대한 모든 권한 부여: grant all on world.* to sampleUser@localhost identified by ‘비밀번호’;
  - sampleUser에게 로컬 네트워크 접속에 대한 모든 권한 부여: grant all on *.* to sampleUser@'192.168.0.%' identified by '비밀번호';
  - sampleUser에게 인터넷 전체 접속에 대한 모든 권한 부여: grant all on world.* to sampleUser@% identified by ‘비밀번호’;
  - sampleUser에게 로컬 접속에 대한 select, insert 실행 권한 부여: grant select, insert on world.* to sampleUser@localhost identified by ‘비밀번호’;
  - sampleUser에게 로컬 접속에 대한 name 컬럼의 업데이트 권한 부여: grant update(Name) on world.city to sampleUser@localhost identified by ‘비밀번호’;
- 권한 회수(REVOKE)
  - `revoke 권한 종류 for 사용자명`
  - revoke all on *.* from sampleUser@localhost;

##### 역할 설정
- 개별 테이블에 대한 CRUD권한을 사용자별로 설정하면 경우의 수가 `테이블 수 x 사용자 수의 조합`이 생겨서 복잡해지므로 문제점을 개선하기 위해서 롤(역할)을 정하고 역할 별 권한 설정하고 사용자에게 역할을 부여하는 형태로 사용
- 사용자가 여러 개의 롤을 가지는 것이 가능
- `MySQL에는 ROLE관련 명령이 지원 안 됨`
- 역할 생성
  - `CREATE ROLE 역할명;`
  - CREATE ROLE world_admin;
- 역할에 대해 권한 설정
  - `GRANT CRUD ON 테이블명 TO 역할명;`
  - GRANT INSERT, DELETE ON city TO world_admin;
- 사용자에게 역할 부여
  - `GRANT 역할 TO 사용자명;`
  - GRANT world_admin TO sampleUser;


## 데이터베이스 활용 1

##### INDEX
- 검색을 빠르게하기 위한 B 트리 계열의 자료구조
  - 레코드 추가/수정/삭제 시 해당 칼럼으로 다시 정렬한 후 `검색에 필요한 값들을 미리 계산해 검색 속도가 높아짐`
  - 수정/삭제/추가 시에 정렬이나 자료구조 업데이트 과정이 존재하므로 업데이트가 아닌 검색이 많은 경우에 사용
  - 기본 키는 자동으로 인덱스 설정
  - 조인연산에서 검색이 많이 발생하므로 인덱스가 많이 필요

##### INDEX 추가 삭제
- 인덱스 추가
  - `CREATE INDEX 인덱스명 ON 테이블명(컬럼명)`
  - CREATE INDEX 인덱스명 ON 테이블명(컬럼명1, 컬럼명2, ..)
  - CREATE UNIQUE INDEX 인덱스명 ON 테이블명(컬럼명)
  - create index BusinessCard_Telephone_index on BusinessCard(Telephone);
- 인덱스 삭제
  - `ALTER TABLE 테이블명 DROP INDEX 인덱스명`


##### 메타데이터
- 데이터를 위한 데이터로 DB나 테이블의 스키마에 대한 정보를 저장하는 테이블
- `데이터 사전(Data Dictionary) : Information_schema`
  - 데이터베이스의 정보 저장
  - 읽기 전용 정보
  - USE INFORMATION_SCHEMA; 이후 SHOW TABLES;하면 INFORMATION_SCHEMA를 통해 메타 데이터 테이블들을 확인할 수 있음
- `데이터 디렉토리(Data Directory)`
  - DBMS의 모든 데이터가 저장되는 디렉토리(폴더)
  - DB 저장, 상태 및 로그 저장
  - MySQL 설정을 통해서 저장되는 파일의 위치를 지정할 수 있음
- 메타데이터 관련 명령
  - SHOW DATABASES;
  - SHOW TABLES;
  - SHOW TABLE STATUS;
  - SHOW COLUMNS FROM 테이블명; SHOW INDEX FROM 테이블명;
  - SHOW TABLES IN INFORMATION_SCHEMA;
  - DESCRIBE INFORMATION_SHEMA.CHARACTER_SET

##### 캐릭터 셋
- 문자 인코딩 정보/메타데이터의 일종으로 문자열(VARCHAR, CHAR)의 값을 저장할 때 사용되는 기본 정보
- 디비나 테이블 별로 설정 가능

|캐릭터 셋|의미|
|------|---|
|ASCII/ISO-8859-1|아스키 계열|
|EUC-KR/KSC_5601|한글 완성형 계열|
|UTF-8/UNICODE|유니코드계열|
|UTF8|기본 인코딩|

##### 콜레이션
- 데이터를 정렬(문자간의 비교)할 때 사용하는 정보
- 정렬 시에 대소문자를 구분/비구분 여부 설정
  - Case Sensitive: 대소문자 구분 -> utf8-general / utf8-unicode
  - Case Insensitive: 대소문자 구분 안함 -> utf8-general-ci / utf8-unicode-ci
- 한글 데이터의 경우 무의미

##### 케릭터셋과 콜레이션 활용
- 테이블 또는 DB에 캐릭터 셋/콜레이션 변경
  - `alter database 디비명 character set 캐릭터셋 collate 콜레이션`
  - alter database world character set utf8 collate utf8_general_ci; 
  - `alter table 테이블명  character set 캐릭터셋 collate 콜레이션`
  - alter table city character set utf8 collate utf8_general_ci;
- 테이블 또는 DB에 캐릭터 셋/콜레이션 기본 설정
  - `create database 디비명 default character set 캐릭터 셋 collate 콜레이션;`
  - create database sampleTestDB default character set utf8 collate utf8_general_ci;
  - `create table 테이블명 default character set 캐릭터 셋 collate 콜레이션;`
  - create table sampleTestTable default character set utf8 collate utf8_general_ci;

##### 스토리지 엔진
- DBMS가 데이터를 CRUD(Create/Retrieve/Update/Delete)할 때 사용하는 기본 컴포넌트인 `데이터베이스 엔진`
- InnoDB: 트랜잭션 지원/업데이트 위주/줄단위 락/복구 용이/동시 처리 성능 높음 (기본 값, 주로 사용)
- MyISAM: 트랜잭션 지원을 지원하지 않음/상대적으로 높은 성능/읽기 위주/테이블단위 락
- 기본 스토리지 엔진 확인
  - SELECT engine, support FROM information_schema.engines WHERE support='DEFAULT';
- 기본 스트로지 엔진 설정
  - `SET default_storage_engine=엔진이름;`
  - SET default_storage_engine=MyISAM; (리부팅시 리셋)

## 데이터베이스 활용 2

##### 데이터베이스 백업
- 콘솔에서 백업하기
  - 전체 데이터베이스 백업
    - mysqldump –u아이디 –p –-all-databases > 덤프파일명.sql
  - 특정 데이터베이스 백업
    - mysqldump –u아이디 –p –-databases DB명 > 덤프파일명.sql
  - 특정 테이블의 스키마+데이터 백업
    - mysqldump –u아이디 –p DB명 테이블명 > 덤프파일명.sql
  - 스키마만 백업
    - mysqldump –u아이디 –p –-no-data ...
  - 데이터만 백업
    - mysqldump –u아이디 –p –-no-create-info ...
- MySQL Workbench에서 백업하기
  - DataExport->Export Options->Export to Self-Contained File  Tables to Export
  - 테이블 선택
  - Dump Structure and Data/Structure Only/Data Only
  - Export 버튼

##### 데이터베이스 복원
- 콘솔에서 복원하기
  - mysql –u아이디 –p DB명 < 파일명
  - mysql –u아이디 –p < 파일명
  - mysql –u아이디 –p DB명 테이블명 < 파일명
- MySQL Workbench에서 복원하기
  - Data Import->Import from Self-Contained File
  - Default Schema to be imported to DB명
  - Data Stucture and Data/Dump Data only/Dump Structure only
  - Import 버튼
##### 데이터베이스 로그
- MySQL 로그의 종류
  - 에러로그(Error Log): MySQL 구동과 모니터링, Query 에러에 관련된 메시지를 포함
  - 일반로그(General Log): 전체 쿼리에 대하여 General log를 활성화 시켜서 저장 가능
  - 슬로우 쿼리 로그(Slow Query Log): `long_query_time`에 설정된 시간 이상을 소요한 쿼리를 기록
  - 이진 로그(Binary Log)/릴레이 로그(Relay Log): Replication에서 사용하는 바이너리 로그(마스터)/릴레이 로그(슬레이브) 로그로 리플리케이션 쿼리를 수행하면서 쌓는 로그, 시점 복구 등을 로깅
- MySQL 설정을 통해서 로그 파일의 위치를 지정할 수 있음
## 데이터베이스 활용 3

##### VLDB
- Very Large DBMS
- 전체 DB가 하나의 DBMS시스템에 다 들어가기 힘들어지는 경우 테이블들을 여러 개의 군으로 나눠 분산 저장
- 하나의 테이블이 방대한 경우에는 사전방식으로 나눠 저장
##### 파티셔닝
- `DBMS 내부에서 분할하는 개념`으로 외부에서는 구별할 필요가 없음
- 제약사항
  - 테이블단위 연산이 어려워져서 조인 연산이 어려움 -> 역정규화(중복허용)를 통해서 보완
  - 외래키의 효용 문제 -> 외래키 제약 조건을 없애서 시스템 부담을 줄여줌
- 이점
  - 데이터 전체 검색시 필요한 부분만 탐색하여 성능 증가
  - 데이터 손실의 가능성이 줄어듦
  - 파티션 별로 백업/복구 가능
  - 파티션 단위로 `I/O 분산 처리 가능하여 쓰기 성능 증가`
- 파티셔닝 방식
  - 범위(range) a-m / n-r / s-z
  - 해시(hash) 해시함수 파티션별로 크기를 비슷하게 나눔 
  - 리스트(list) 특정한 컬럼을 기준
  - 컴포지트(composite) - range-hash / range-list
##### 샤딩
- `DBMS 외부에서 분할하는 개념`으로 외부에서는 구별할 필요가 있음
- 제약사항
  - 테이블단위 연산이 어려워져서 조인 연산이 어려움 -> 역정규화(중복허용)를 통해서 보완
  - 외래키의 효용 문제 -> 외래키 제약 조건을 없애서 시스템 부담을 줄여줌
  - 외부에서 CRUD 시에 `데이터가 저장된 위치를 알야야함`
- 이점
  - 데이터 전체 검색시 필요한 부분만 탐색하여 성능 증가
  - 데이터 손실의 가능성이 줄어듦
  - 샤드 별로 백업/복구 가능
  - 샤드 단위로 `I/O 분산 처리 가능하여 쓰기 성능 증가`

##### 복제
- 두 개 이상의 DBMS 시스템을 마스터/슬레이브로 나눠 DBMS의 내용을 복제해 동일한 DB 내용을 유지하는 것
- 복제 구조
  - 마스터 DBMS -> 슬레이브 DBMS 방향으로 로그기반 복제(Binary Log)로 `SQL쿼리를 복제`
  - 데이터 업데이트(CUD)는 마스터에서 읽기(R)는 슬레이브에서 하는 것이 좋음
- 이점
  - `읽기 성능 향상`
  - 시스템 확장성 향상
- 복제하는 방식
  - Statement Based: SQL 문장 자체를 복제하는 방식으로 시간 값을 이용해서 쓰는 경우에는 사용하기 어려움
  - Row Based: SQL에 따라 변경된 라인만 기록하는 방식으로 데이터가 많이 변경된 경우 데이터가 커짐
  - Mixed: 두 방식 복합


## 데이터베이스 활용 4

##### 전문 검색
- 기본적으로 컬럼 내용 전체를 단순 문자열(Plain Text)로 생각하고 검색하는 방식
- SQL의 LIKE 검색은 여러 개의 검색필터를 동시에 매칭시키는 방식으로 여러 개의 조건문을 AND/OR 시킬 경우 심각한 성능 저하
- MySQL의 Full Text Search 검색
  - 자연어 검색
  - 불린 검색
  - 쿼리 확장 검색  
  ...
- 자연어 검색 방식
  - `where match(컬럼명) against(‘검색어/검색문장’);`
  - 매칭 정확도에 따라 score 기반으로 검색 정확도 확인
  - 검색의 정확도에 대한 내림차순 정렬
- 불린 검색 방식
  - `where match(컬럼명) against('“단어*“ -제외단어 in boolean mode);`
  - 연산자 사용한 구문 검색 가능
  - 필수단어(+), 예외단어(-), 부분단어(*)

##### 벌크 INSERT
- `여러 개의 레코드를 넣어야 하는 경우` 하나의 레코드 입력할 때마다 인덱스를 재구성하는 작업이 작업마다 연속적으로 발생하므로 인덱스를 정지하고 한번에 저장하는 방법
- 인덱스 정지/재설정
  - 인덱스 작업을 정지(ALTER TABLE ’테이블명’ DISABLE KEYS;)
  - 인덱스 작업 재설정(ALTER TABLE ’테이블명’ ENABLE KEYS;)
- 벌크 INSERT 방법
  - INSERT INTO 테이블명 VALUES (...) VALUES (...);
  - SQL을 사용한 방식
  - CSV 파일를 사용한 방식
    - LOAD DATA INFILE ‘파일경로’  
      INTO TABLE 테이블명  
      FIELDS TERMINATED BY ‘구분자’ ENCLOSED BY ‘구분자’ ESCAPED BY ‘구분자’ LINES STARTING BY ‘구분자’ TERMINATED BY ‘구분자’

## 데이터베이스 활용 5

##### 트랜잭션
- 복수의 SQL문을 수행하는 도중에 `장애가 발생했을 때 장애에 대응할 수 있도록 하는 기능`
- `반영(커밋:Commit)`과 `취소(롤백:Rollback)` 두 가지의 결과값만 가져야 함
- 기본적으로 SQL의 수행모드는 AutoCommit모드(줄단위 커밋모드)이므로 트랜잭션을 지원하기 위해서는 AutoCommit모드를 오프시켜야 함
- 트랜잭션 명령
  - 오토커밋 모드 확인: select @@autocommit;
  - 오토커밋 오프: set autocommit = flase
  - 커밋: commit;
  - 롤백: rollback;

##### ACID
- 원자성(Atomicity): All-or-Nothing, Commit/Rollback
- 일관성(Consistency): 트랜잭션 전후에 데이터가 손상을 받으면 안됨 같은 데이터가 다른 값을 가지면 안됨
- 고립성/격리수준(Isolation): 여러 개의 트랜잭션이 수행될 때 성능과 데이터 안정성간의 trade-off
- 지속성(Durability): 트랜잭션이 종료된 이후에도 데이터에 문제가 없어야 됨(장시간)

##### 락
- 공유자원(리소스)에 대해 여러 개의 트랜잭션이 접근하려고 경쟁하려고 할 때 제어하는 방법
- 동시성제어(Concurrency Control)라고 하고 보통 Lock으로 해결하는 것을 동기화라고 부름
- 락의 종류
  - 테이블 단위 락: 동일한 테이블을 다른 트랜잭션이 사용하고 있다면 접근 금지 <-> MyISAM
  - 줄 단위 락: 동일한 줄(Row)만 접근 금지(테이블 락에 비해 높은 성능) <-> InnoDB


##### 격리 수준
- 트랜잭션에 `일관성없는 데이터를 허용하는 수준`
- 격리 수준의 종류
  - Read Uncommitted
    - 트랜잭션이 처리되는 도중에 다른 트랜잭션이 해당 데이터를 읽기를 허용(uncommitted data)
  - `Read Committed`
    - 트랜잭션이 끝난 이후에만 접근하도록 허용(committed data)
  - `Repeatable Read`
    - 다른 트랜잭션이 업데이트하는 것은 금지하지만 레코드 추가하는 것은 허용
  - Serializable
    - 트랜잭션이 동시에 수행되는 것이 금지되고 순차적으로 수행
- 격리 수준 명령
  - 트랜잭션 격리수준 확인: select @@tx_isolation;
  - 트랜잭션 격리수준 변경: set tx_isolation = ‘READ-COMMITED’;
  - 커밋: commit;
## 데이터베이스 활용 6

##### 저장 프로시저
- SQL을 리턴 값이 없는 함수 형태로 저장하고 사용하는 방법
- 정의할 때 마침표의 의미인 `DELIMITER`를 먼저 정의해서 구분자로 활용해야함
- 저장 프로시저 정의
  - `CREATE PROCEDURE 프로시저명(인자 인자형, ...) BEGIN SQL 문장들 END`
  - CREATE PROCEDURE InsertLines() BEGIN insert into city values (10000, ‘Sample’,’KOR’, ‘Test’, 1000000); insert into city values (20000, ‘SampleTest’, ‘KOR’, ‘Test’, 2000000); END
- 저장 프로시저 호출
  - `CALL 프로시저명;`
  - CALL InsertLines;
- 저장 프로시저 삭제
  - `DROP PROCEDURE 프로시저명;`
  - DRIO PROCEDURE InsertLines;

##### 저장 함수
- SQL을 리턴이 있는 함수 형태로 저장하고 사용하는 방법
- 정의할 때 마침표의 의미인 `DELIMITER`를 먼저 정의해서 구분자로 활용해야함
- 함수 정의
  - `CREATE FUNCTION 함수명(인자 인자형, ...) RETURNS 타입 BEGIN SQL 문장들 END`
  - CREATE FUNCTION CountLines() RETURNS INTEGER BEGIN DECLARE LINE_COUNT INTEGER; SELECT COUNT(*) INTO LINE_COUNT FROM BusinessCard; RETURN LINE_COUNT; END
- 함수 호출
  - `함수명(인자);`
  - select countLines() from BusinessCard;
- 함수 삭제
  - `DROP FUNCTION 함수명;`
  - select countLines

##### 트리거
- `특정한 조건이 되면 자동으로 호출(콜백:Callback)되는 저장 프로시저`
- 정의할 때 마침표의 의미인 `DELIMITER`를 먼저 정의해서 구분자로 활용해야함
- 트리거 정의
  - `CREATE TRIGGER 트리거명 BEFORE(또는 AFTER) CRUD ON 테이블명 
      FOR EACH ROW 
    BEGIN
      변경 전(OLD.칼럼명) 또는 변경 후(NEW.칼럼명)을 이용한 처리
    END`
  - create trigger InsertBusinessCard2 after insert on BusinessCard
      for each row 
    begin
      insert into BusinessCard2 values ('zzz', 'zzzz','000-0000');
    end
- 트리거 삭제
  - `DROP PROCEDURE 트리거명;`

## 대형 데이터 베이스

##### 스케일 업
- 보통 말하는 업그레이드를 말함
- CPU 클럭속도 증가, 코어 수 증가, 메모리 증가
- 보통 성능증가에 비해 가격증가가 더 빠름
- 비용부담 

##### 스케일 아웃
- 동일한 서버/DBMS를 병렬로 구축
- 스케일 업에 비해 상대적으로 저렴
- 노드 수 추가하여 계속 성능 향상 가능

##### NoSQL
- Not Only SQL
- 스키마 기반이 아니라 필요하면 새로운 컬럼을 추가하면 가능하고 전체적으로 동일한 구조가 아닐 수 있음
- RDBMS와 NoSQL의 차이
  - 일반적으로 `RDBMS는 주로 읽기 성능`에 최적화되어 있고 `NoSQL은 쓰기 성능`에 최적화 되어 있음
  - RDBMS은 정규형 데이터이고 NoSQL은 반정규형 데이터
  - NoSQL은 칼럼 기반의 저장방식인데 비해 RDBMS는 행 기반의 저장 방식
  - 외래키 연결 구조가 아니며 당연히 조인도 안됨
- CAP 이론을 이용한 NoSQL 시스템 분류
  - C(일관성:Consistency): 어떤 노드를 접근하더라도 데이터값이 동일
  - A(가용성:Availability): 노드 일부가 Fail되더라도 서비스가 중단이 되면 안됨
  - P(파티션 내성:Partition Tolerance): 노드간 통신에 장애가 생겨도 문제가 없어야함
  - CP(Hbase, MongoDB, Redis) / AP(Cassandra)
- 저장형태에 대한 분류
  - 키/밸류(Key/Value): 키값을 주면 밸류를 리턴하는 형태
  - 정렬된 키/밸류(Ordered Key/Value): 값을 주면 밸류를 리턴하는데 키값으로 정렬되는 형태
  - 도큐먼트 형태(Document based): 밸류 값이 JSON/XML 문서인 형태
  
