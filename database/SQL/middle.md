# 데이터 분석을 위한 SQL 중급

#### 보고 싶은 데이터 요약하기 - 집계함수와 GROUP BY
- COUNT, SUM, AVG, MIN, MAX 
  - COUNT(): SELECT 절에 와서 행의 개수를 계산, NULL은 제외하고 DISTINCT 와 결합 가능
  - SUM(열): SELECT 절에 와서 숫자 데이터인 경우 합을 계산, NULL은 계산에서 제외하므로 0으로 취급되지 않음
  - AVG(열): SELECT 절에 와서 숫자 데이터인 경우 평균을 계산, NULL은 계산에서 제외하므로 0으로 취급되지 않음
  - MIN(열): SELECT 절에 와서 숫자 데이터인 경우 최소 값을 계산, NULL은 계산에서 제외하므로 0으로 취급되지 않음
  - MAX(열): SELECT 절에 와서 숫자 데이터인 경우 최대 값을 계산, NULL은 계산에서 제외하므로 0으로 취급되지 않음
- GROUP BY, HAVING
  - GROUP BY: 다음에 오는 컬럼으로 카테고리를 나눔, 이 칼럼은 SELECT 절에 반드시 나와야며 그룹화가 된 상태이기 때문에 칼럼 자체로는 이 칼럼만 단독으로 올 수 있음 (여러 가지 구분을 넣어주려면 GROUP BY 다음에 칼럼을 더 추가하면 됨)
  - HAVING: WHERE 절이 GROUP BY 이전에 수행되므로, GROUP BY의 결과물에 조건을 다는 절

#### 조건문 - CASE
- CASE ~ END: SELECT 앞에서 CASE END 안에 WHEN 조건, THEN 값, 그 외의는 ELSE을 지정하는 구조를 통해서 조건식별로 값을 지정할 수 있음

#### 두 개 이상 테입르 결합하기 - JOIN

#### 위 아래로 데이터 이어붙이기 - UNION
