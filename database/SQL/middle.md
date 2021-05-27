# 데이터 분석을 위한 SQL 중급

#### 보고 싶은 데이터 요약하기 - 집계함수와 GROUP BY
- COUNT, SUM, AVG, MIN, MAX 
  - COUNT(): SELECT 절에 와서 행의 개수를 계산, NULL은 제외하고 DISTINCT 와 결합 가능
  - SUM(열): SELECT 절에 와서 숫자 데이터인 경우 합을 계산, NULL은 계산에서 제외하므로 0으로 취급되지 않음
  - AVG(열): SELECT 절에 와서 숫자 데이터인 경우 평균을 계산, NULL은 계산에서 제외하므로 0으로 취급되지 않음
  - MIN(열): SELECT 절에 와서 숫자 데이터인 경우 최소 값을 계산, NULL은 계산에서 제외하므로 0으로 취급되지 않음
  - MAX(열): SELECT 절에 와서 숫자 데이터인 경우 최대 값을 계산, NULL은 계산에서 제외하므로 0으로 취급되지 않음
- GROUP BY, HAVING
  - SELECT 쿼리 안에서 주어진 키 외에 `다른 값으로 카테고리를 나누기 위해` GROUP BY를 사용
  - GROUP BY: 다음에 오는 컬럼으로 그룹핑하고, 이 칼럼은 SELECT 절에 반드시 나와야며 여러가지 구분을 넣어주려면 칼럼을 더 추가하면 됨 
  - HAVING: WHERE 절이 GROUP BY 이전에 수행되므로, GROUP BY의 결과물에 조건을 다는 절

#### 조건문 - CASE
- CASE ~ END: SELECT 앞에서 CASE END 안에 WHEN 조건, THEN 값, 그 외의는 ELSE을 지정하는 구조를 통해서 조건식별로 값을 지정할 수 있음

#### 옆으로 데이터 이어붙이기(두 개 이상 테이블 결합하기) - JOIN
- 중복 저장, NULL 저장을 피하기 위해서 테이블을 여러 개 쪼개서 저장하는데, 테이블을 두개 합치기 위해서 JOIN을 사용 -> 칼럼의 수가 늘어남
- INNER JOIN: `여러 개의 테이블에 조건에 해당하는 키 값이 양 쪽 테이블에 다 있을 때` 양 테이블을 연결해주고 SELECT 할 때 사용 
- OUTER JOIN: `여러 개의 테이블에 조건에 해당하는 키 값이 양 쪽 테이블에 다 없어도` 기준 테이블의 데이터는 누락되지 않게 하며 양 테이블을 연결해주고 없으면 NULL을 넣어주고 SELECT 할 때 사용 
  - LEFT JOIN(LEFT OUTER JOIN)
  - RIGHT JOIN(RIGHT OUTER JOIN)
  - LEFT JOIN과 RIGHT JOIN의 결과를 UNION(FULL OUTER JOIN)
- 정규화가 잘 되어 있지 않은 테이블인 경우 자기 자신을 JOIN하여 값을 추출해야하는 경우도 있음
- MySQL 시간 더하기, 빼기
  - DATE_ADD(기준 날짜, INTERVAL 시간 SECOND/MINUTE/HOUR/DAY/MONTH/YEAR)
  - DATE_SUB기준 날짜, INTERVAL 시간 SECOND/MINUTE/HOUR/DAY/MONTH/YEAR)
  
#### 위 아래로 데이터 이어붙이기 - UNION
- 동일한 칼럼을 SELECT하는 구문이 여러 개 있을 때 여러 개의 결과를 결합하기 위해서 UNION을 사용 -> 행의 수가 늘어남
- UNION: 중복 값을 제거하며 여러 개의 결과를 결합
- UNION ALL: 중복 값을 포함하여 여러 개의 결과를 결합
