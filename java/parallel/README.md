# 자바 병렬 처리

## 상황별 병렬 처리 방식 추천

| 병렬 처리 방식                  | 설명                                                                 | 사용에 적합한 경우                                           |
|-------------------------------|----------------------------------------------------------------------|------------------------------------------------------------|
| **ExecutorService (스레드 풀)** | 스레드 수를 제한하고 안정적으로 병렬 처리 가능                         | 병렬 작업을 큐에 쌓아 관리하고 싶을 때 (예: 웹 크롤링, I/O 작업 등) |
| **ForkJoinPool**              | 작업을 재귀적으로 나누고 병렬 처리 (Divide & Conquer)                 | 큰 작업을 여러 개의 작은 작업으로 나눌 수 있을 때 (예: 배열 정렬, 계산 작업 등) |
| **CompletableFuture / Future** | 비동기 작업을 체이닝하며 병렬 수행                                    | 병렬 + 논블로킹으로 API 호출, 계산 등을 할 때                     |
| **Parallel Stream**           | Java 8 이상의 스트림 API에서 `.parallel()` 사용                         | 데이터 처리량이 많고, 병렬로 처리해도 무방할 때 (주의: 무조건 빠르지 않음) |
| **Reactive Streams (Reactor, RxJava)** | 리액티브 프로그래밍 기반, 논블로킹 + 백프레셔 지원           | I/O가 많고 처리량이 유동적인 환경 (예: API 서버, 데이터 스트리밍 등) |

## 실무 기준 추천

| 목적                         | 추천 방식                              |
|----------------------------|----------------------------------------|
| 병렬로 API 호출, 파일 읽기 등      | `CompletableFuture` + `ExecutorService` |
| 많은 계산을 나눠 병렬로 처리     | `ForkJoinPool` 또는 병렬 스트림               |
| 대용량 컬렉션 처리             | `.parallelStream()` (성능 테스트 필수)        |
| 커스텀 컨트롤이 필요할 경우       | `ExecutorService` 직접 구성                  |
| 대기 없는 실시간 처리          | 리액티브 프로그래밍 (Reactor, RxJava 등)     |

	•	단순 병렬 작업 → ExecutorService
	•	계산/분할 작업 → ForkJoinPool
	•	비동기/체이닝 → CompletableFuture
	•	데이터 스트림 처리 → .parallelStream()

## 병렬 처리 시 주의할 점
- 스레드 수 조절 필요: CPU 코어 수 이상으로 과도하게 만들면 오히려 느려질 수 있음.
- 공유 자원 동기화: 여러 스레드가 공유하는 자원이 있다면 동기화 필요.
- 테스트 중요: 병렬 처리는 환경마다 성능이 다르므로, 반드시 실제 데이터로 테스트.

#### CompletableFuture

```java
CompletableFuture<String> call1 = CompletableFuture.supplyAsync(() -> apiCall("A"));
CompletableFuture<String> call2 = CompletableFuture.supplyAsync(() -> apiCall("B"));

CompletableFuture<Void> combined = CompletableFuture.allOf(call1, call2);

combined.join();

System.out.println(call1.get());
System.out.println(call2.get());
```
