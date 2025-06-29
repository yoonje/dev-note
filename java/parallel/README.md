# 자바 병렬 처리

## 상황별 병렬 처리 방식 추천
| 병렬 처리 프레임 워크                  | 설명                                                                 | 사용에 적합한 경우                                    |
|-------------------------------|----------------------------------------------------------------------|------------------------------------------------------------|
| **ExecutorService (스레드 풀)** | 스레드를 직접 생성하는 대신, 스레드를 재사용하고 관리해주는 스레드 풀(thread pool) 기반의 병렬 처리 프레임워크    | 일반적인 병렬 작업 또는 큐에 쌓아 관리하고 싶을 때 (예: 웹 크롤링, I/O 작업 등) |
| **ForkJoinPool**              | 작업을 분할하고(join), 병렬로 실행한 후(fork) 다시 합치는(divide and conquer) 데 특화된 프레임워크        | 큰 작업을 여러 개의 작은 작업으로 나눌 수 있을 때 (예: 배열 정렬, 계산 작업, 재귀적 작업 등) |

| 병렬 처리 방식                  | 설명                                                                 | 사용에 적합한 경우                                           |
|-------------------------------|----------------------------------------------------------------------|------------------------------------------------------------|
| **CompletableFuture / Future** | 비동기 작업을 체이닝하며 병렬 수행                                    | 병렬 + 논블로킹으로 API 호출, 계산 등을 할 때                     |
| **Parallel Stream**           | 스트림 API에서 `.parallel()` 사용 (ForkJoinPool 기반)  | 데이터 처리량이 많고, 병렬로 처리해도 무방할 때 (주의: 무조건 빠르지 않음) |
| **Reactive Streams (Reactor, RxJava)** | 리액티브 프로그래밍 기반, 논블로킹 + 백프레셔 지원           | I/O가 많고 처리량이 유동적인 환경 (예: API 서버, 데이터 스트리밍 등) |

## 실무 기준 추천

| 목적                         | 추천 방식                              |
|----------------------------|----------------------------------------|
| 병렬로 API 호출, IO, 간단한 병렬 테스크 등      | `CompletableFuture` + `ExecutorService` |
| 계산 집중적인 작업, 특히 재귀적 태스크 분할 등     | `ForkJoinPool` 또는 병렬 스트림               |
| 대용량 컬렉션 처리             | `.parallelStream()` (성능 테스트 필수)        |
| 대기 없는 실시간 처리          | 리액티브 프로그래밍 (Reactor, RxJava 등)     |

	•	단순 병렬 작업 → ExecutorService
	•	계산/분할 작업 → ForkJoinPool
	•	비동기/체이닝 → CompletableFuture + ExecutorService
	•	데이터 스트림 처리 → .parallelStream()

## 병렬 처리 시 주의할 점
- 스레드 수 조절 필요: CPU 코어 수 이상으로 과도하게 만들면 오히려 느려질 수 있음.
- 공유 자원 동기화: 여러 스레드가 공유하는 자원이 있다면 동기화 필요.
- 테스트 중요: 병렬 처리는 환경마다 성능이 다르므로, 반드시 실제 데이터로 테스트.

ExecutorService
=======
- ExecutorService
  - JDK 1.5 부터 생성된 비동기 작업 실행을 도와주는 프레임워크
  - 비동기 모드에서 작업 실행을 단순화하는 JDK API로 일반적으로 ExecutorService는 자동으로 스레드 풀과 작업 할당을 위한 API를 제공
  - 스레드 풀을 만들어두고 작업 요청이 들어오면 새 스레드를 생성한 뒤 사용하고 반납하면서 비용을 줄임
- ExecutorService 예시
```java
@Slf4j
public class ExecutorServiceExample {
    public static void main(String[] args) {
        ExecutorService es = Executors.newCachedThreadPool();
		// ExecutorService es = Executors.newFixedThreadPool(5);

        es.execute(() -> {
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) { }
            log.info("Async");
        });

        log.info("Exit");

        es.shutdown();
    }
}
```

ForkJoinPool
=======
- ForkJoinPool
  - JDK 1.7부터 생성된 작업을 분할하고(join), 병렬로 실행한 후(fork) 다시 합치는(divide and conquer) 데 특화된 프레임워크
- ForkJoinPool 예시
```java
public class ForkJoinPoolExample {
	ForkJoinPool pool = new ForkJoinPool();

	pool.submit(() -> {
		IntStream.range(0, 10).parallel().forEach(i ->
			System.out.println(i + " - " + Thread.currentThread().getName())
		);
	}).join();
}
```

CompletableFuture
=======
- CompletableFuture
  - CompletableFuture 는 JDK 1.8 버전부터 추가되었으며 별도 스레드에서 작업이 되는데 별도 스레드에서 완료된 결과를 받을 수 있는 Future와 기본적으로 동일하나 외부에서 완료 시킬 수 있고 콜백 등록 및 조합이 가능한 클래스
  - 별도 스레드를 설정하지 않으면 ForkJoinPool.commonPool()를 사용하며 ExecutorService를 통해 별도 스레드를 설정할 수 있음
- CompletableFuture 예시 1
```java
CompletableFuture<String> call1 = CompletableFuture.supplyAsync(() -> apiCall("A"));
CompletableFuture<String> call2 = CompletableFuture.supplyAsync(() -> apiCall("B"));

CompletableFuture<Void> combined = CompletableFuture.allOf(call1, call2);

combined.join();

System.out.println(call1.get());
System.out.println(call2.get());
```
- CompletableFuture 예시 2
```java
ExecutorService executorService = Executors.newFixedThreadPool(4);

CompletableFuture<Void> future = CompletableFuture.supplyAsync(() -> {
	System.out.println("Hello" + Thread.currentThread().getName());    
	return "hello";
}, executorService).thenRunAsync(()->{    
	System.out.println(Thread.currentThread().getName());
	}, executorService)
		
future.get();
		
executorService.shutdown();
```
Parallel Stream
=======
- Parallel Stream
  - Java 8부터 추가된 스트림 API의 확장으로 스트림을 병렬로 처리를 도와주는 기능
  - 스트림의 모든 요소가 처리될 때까지 기다려야하므로 I/0 등에서 불리하며 집약적인 계산에서 유리
- Parallel Stream 예시
```java
public void getPriceAllAsyncWithParallelStream() {
	List<String> stores = List.of("storeA", "storeB", "storeC");
	
	stores.parallelStream() 
		.forEach(store -> {
			log.info("Thread Name = {}", Thread.currentThread().getName());
			log.info("price = {}", itemRepository.getPriceByStore(store));
		});
}

```
