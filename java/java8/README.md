# 자바 8
인프런 더 자바 자바8 정리

Table of contents
=================
<!--ts-->
   * [함수형 인터페이스와 람다 표현식 소개](#함수형-인터페이스와-람다-표현식-소개)
   * [인터페이스의 변화](#인터페이스의-변화)
   * [Stream](#Stream)
   * [Optional](#Optional)
   * [Date와 Time](#Date와-Time)
   * [CompletableFuture](#CompletableFuture)
<!--te-->

함수형 인터페이스와 람다 표현식 소개
=======
- 함수형 인터페이스(Functional Interface)
  - `추상 메소드`를 딱 하나만 가지고 있는 인터페이스
  - @FuncationInterface 애노테이션을 가지고 있는 인터페이스
  > 인터페이스 안에 static 메소드와 default 메소드 기능을 통해 메소드를 `정의` 할 수 있음

- 람다 표현식(Lambda Expressions)
  - 람다 표현식을 통해 함수형 인터페이스의 인스턴스를 만드는 방법으로 쓰일 수 있음
  - 기존 익명 클래스를 통한 함수형 인터페이스 구현
  ```java
  RunSomething runSomething = new RunSomething() {
      @Override
      public void doIt(){
          System.out.println("Hello");
      }
  };
  runSomething.doIt()
  ```
  - 람다 표현식을 통한 함수형 인터페이스 구현
  ```java
  RunSomething runSomething = () -> System.out.println("Hello");
  runSomething.doIt()
  ```

- 자바에서 함수형 프로그래밍
  - 함수형 인터페이스와 람다 표현식을 통해서 함수형 프로그래밍을 할 수 있음
  - 함수를 First class `object`로 사용할 수 있음
  - `순수 함수`(Pure function)
      - 사이드 이팩트가 없음 (`오버라이딩하는 함수 밖에 있는 값을 변경하지 않는다.`)
      - 상태가 없음 (`오버라이딩하는 함수 밖에 있는 값을 사용하지 않는다.`)
  - 고차 함수 (Higher-Order Function)
    - 함수가 함수를 매개변수로 받을 수 있고 함수를 리턴할 수도 있음
  - 불변성

- Java가 기본으로 제공하는 함수형 인터페이스
  - java.util.function 패키지
  - Function<T, R>: T 타입을 받아서 R 타입을 리턴하는 함수 인터페이스
  ```java
  public class Plus10 implements Function<Integer, Integer>{
      @Override
      public Integer apply(Integer integer){
          return integer + 10;
      }
  }
  Plus10 puls10 = new Plus10();
  System.out.println(puls10(1));
  ```

  ```java
  Funtion<Integer, Integer> plus10 = (i) -> i + 10;
  System.out.println(puls10(1));
  ```
  - Function<T, R>의 함수 조합용 메소드
    - andThen: 뒤에다가 함수를 조합하는 메소드
    ```java
    Funtion<Integer, Integer> plus10 = (i) -> i + 10;
    Funtion<Integer, Integer> multiply2 = (i) -> i * 2;

    Funtion<Integer, Integer> multiply2AndPlus10 = plus10.andThen(multiply2);
    System.out.println(multiply2AndPlus10(2)); // 24
    ```
    - compose: 앞에다가 함수를 조합하는 메소드
    ```java
    Funtion<Integer, Integer> plus10 = (i) -> i + 10;
    Funtion<Integer, Integer> multiply2 = (i) -> i * 2;

    Funtion<Integer, Integer> multiply2AndPlus10 = plus10.compose(multiply2);
    System.out.println(multiply2AndPlus10.apply(2)); // 14
    ```

  - BiFunction<T, U, R>: 두 개의 값(T, U)를 받아서 R 타입을 리턴하는 함수 인터페이스
  - Consumer<T>: T 타입을 받아서 아무값도 리턴하지 않는 함수 인터페이스
  ```java
  Consumer<Integer> printT = (i) -> System.out.println(i);
  printT.accpet(10); // 10
  ```
  - Supplier<T>: T 타입의 값을 제공하는 함수 인터페이스
  ```java
  Supplier<Integer> get10 = () -> 10;
  System.out.println(get10.get()); // 10
  ```
  - Predicate<T>: T 타입을 받아서 boolean을 리턴하는 함수 인터페이스
  ```java
  Predicate<String> startWithKeesun = (s) -> s.startsWith("keesun");
  Predicate<Integer> isEven = (i) -> i%2 == 0;
  System.out.println(startWithKeesun.test("keesun2"));
  System.out.println(isEven.test(2));
  ```
  - Predicate<T>의 함수 조합용 메소드
    - And
    ```java
    Predicate<String> startWithKeesun = (s) -> s.startsWith("keesun");
    Predicate<String> endsWithKeesun = (s) -> s.endsWith("keesun");
    System.out.println(startWithKeesun.and(endsWithKeesun).test("keesun2"));
    ```
    - Or
    ```java
    Predicate<String> startWithKeesun = (s) -> s.startsWith("keesun");
    Predicate<String> endsWithKeesun = (s) -> s.endsWith("keesun");
    System.out.println(startWithKeesun.or(endsWithKeesun).test("keesun2"));
    ```
    - Negate
    ```java
    Predicate<String> startWithKeesun = (s) -> s.startsWith("keesun");
    Predicate<String> endsWithKeesun = (s) -> s.endsWith("keesun");
    System.out.println(startWithKeesun.or(endsWithKeesun).negate().test("keesun2"));
    ```
  - UnaryOperator<T>: Function<T, R>의 특수한 형태로, 입력값 하나를 받아서 동일한 타입을 리턴하는 함수 인터페이스
  - BinaryOperator<T>: BiFunction<T, U, R>의 특수한 형태로, 동일한 타입의 입렵값 두개를 받아 리턴하는 함수 인터페이스
- 람다 표현식
  - (인자 리스트) -> {바디}
  - 인자 리스트
    - 인자가 없을 때: ()
    - 인자가 한개일 때: (one) 또는 one
    - 인자가 여러개 일 때: (one, two)
    - 인자의 타입은 생략 가능, 컴파일러가 추론(infer)하지만 명시할 수도 있다. (Integer one, Integer two)
  - 바디
    - 화상표 오른쪽에 함수 본문을 정의
    - 여러 줄인 경우에 { }를 사용해서 묶음
    - 한 줄인 경우에 생략 가능, return도 생략 가능
    ```java
    Supplier<Integer> get10 = () -> 10;
    BinaryOperator<Integer> sum = (a, b) -> a + b;
    ```
  - 변수 캡쳐
    - 로컬 변수 캡처
      - `final이거나 effective final인` 경우에만 참조할 수 있음
    - effective final(final 키워드 사용하지 않은 변수)
      - 자바 8부터 지원하는 기능으로 변경이 가해지지 않아서 사실상 final인 변수
      - final 키워드 사용하지 않은 변수를 익명 클래스 구현체 또는 람다에서 참조할 수 있음
    - 익명 클래스 구현체와 달리 `쉐도윙`하지 않음
      - 익명 클래스는 새로 스콥을 만들지만, 람다는 람다를 감싸고 있는 스콥과 같음
      ```java
      // 익명클래스
      int baseNumber = 10;
      Consumer<Integer> integerConsumer = new Consumer<Integer>() {
          @Override
          public void accept(Integer baseNumber){
              System.out.println(baseNumber); // 스콥이 다르므로 다른 변수로 가능
          }
      }
      integerConsumer.accept(12);
      ```
      ```java
      // 람다
      int baseNumber = 10;
      IntConsumer printInt = (i) -> {
          System.out.println(i + baseNumber); // 스콥이 똑같으므로 같은 변수로 불가능
      };
      printInt.accept(12);
      ```
- 메소드 레퍼런스
  - 람다 표현식이 단 하나의 메소드만을 호출하는 경우에 해당 람다 표현식에서 불필요한 매개변수를 제거하고 사용이 가능
  - 메소드를 참조하는 방법

  |스태틱 메소드 참조|타입::스태틱 메소드|
  |특정 객체의 인스턴스 메소드 참조|객체 레퍼런스::인스턴스 메소드|
  |임의 객체의 인스턴스 메소드 참조|타입::인스턴스 메소드|
  |생성자 참조|타입::new|

  - 메소드 또는 생성자의 매개변수로 람다의 입력값을 받음
  - 리턴값 또는 생성한 객체는 람다의 리턴값
  ```java
  // 스태틱 메소드 참조
  Greeting greeting = new Greeting();
  UnaryOperator<String> hello = greeting::hello;
  System.out.println(hello.apply("keesun"));

  // 생성자 참조
  Supplier<Greeting> newGreeting = Greeting::new;
  newGreeting.get();

  // 특정 객체의 인스턴스 메소드 참조
  Function<String, Greeting> keesunGreeting = Greeting::new;
  Greeting keesun = keesunGreeting.apply("keesun");
  System.out.println(keesun.getName());
  ```

인터페이스의 변화
=======
- 인터페이스의 기본 메소드
  - 인터페이스에 메소드 선언 뿐만 아니라 `구현체를 제공하는 방법`
  - 해당 인터페이스를 구현한 클래스를 깨트리지 않고 새 기능을 추가가 가능
  - 인터페이스를 상속받는 인터페이스에서 다시 추상 메소드로 변경 가능
  - 인터페이스 구현체가 `재정의 할 수도 있음`
  - Object가 제공하는 기능 (equals, hasCode)는 기본 메소드로 제공할 수 없어 구현체가 재정의 해야함
  ```java
  default void printNameUpperCase(){
      System.out.println("Hi");
  } 
  ```
- 인터페이스의 스태틱 메소드
  - 해당 타입 관련 헬퍼 또는 유틸리티 메소드를 제공할 때 `인터페이스에 스태틱 메소드를 제공할 수 있음`
  ```java
  static void printAnything() {
      System.out.println("Foo");
  }
  ```

- 자바 8 API의 기본 메소드와 스태틱 메소드
  - Iterable의 기본 메소드
    - forEach(): 순회하는데 사용되는 메소드
    ```java
    List<String> name = new ArrayList<>();
    name.add("keesun");
    name.add("keesun2");

    name.forEach(System.out:println);
    ```
    - spliterator(): 쪼갤 수 있는 기능을 가진 iterator
    ```java
    List<String> name = new ArrayList<>();
    name.add("keesun");
    name.add("keesun2");

    Spliterator<String> spliterator = name.spliterator();
    Spliterator<String> spliterator2 = spliterator.trySplit();
    while (spliterator.tryAdvance(System.out:println));
    while (spliterator2.tryAdvance(System.out:println));
    ```
  - Collection의 기본 메소드
    - stream()
    ```java
    List<String> name = new ArrayList<>();
    name.add("keesun");
    name.add("keesun2");

    long cnt = name.stream().map(String::toUpperCase).filter(s -> s.startswith("K")).count();
    ```
    - removeIf(Predicate)
    ```java
    List<String> name = new ArrayList<>();
    name.add("keesun");
    name.add("keesun2");

    name.removeIf(s -> s,startsWith("k"));
    ```
  - Comparator의 기본 메소드 및 스태틱 메소드
    - reversed()
    ```java
    List<String> name = new ArrayList<>();
    name.add("keesun");
    name.add("keesun2");

    Comparator<String> compareToIgnoreCase = String::compareToIgnoreCase;
    name.sort(compareToIgnoreCase.reversed());
    ```
    - thenComparing()
    ```java
    List<String> name = new ArrayList<>();
    name.add("keesun");
    name.add("keesun2");

    Comparator<String> compareToIgnoreCase = String::compareToIgnoreCase;
    name.sort(compareToIgnoreCase.reversed().thenComparing());
    ```
    - static reverseOrder() / naturalOrder()
    - static nullsFirst() / nullsLast()
    - static comparing()


Stream
=======
- 스트림
  - 데이터를 담고 있는 저장소가 아니며 `연속된 데이터를 처리하는 연산들의 모음`
  - 스트림이 처리하는 `데이터 소스를 변경하지 않음`
  - 처리하는 데이터는 오직 한번만 처리
  - 중개 오퍼레이션은 근본적으로 lazy하며 `손쉽게 병렬 처리가 가능함`
  ```java
  List<String> name = new ArrayList<>();
  name.add("keesun");
  name.add("keesun2");

  Stream<String> stringStream = names.stream().map(String::toUpperCase);
  ```
  ```java
  List<String> name = new ArrayList<>();
  name.add("keesun");
  name.add("keesun2");

  List<String> collect = names.parallelStream().map(String::toUpperCase).collect(Collectors.toList());
  ```
- 스트림 파이프라인
  - 0 또는 다수의 중개 오퍼레이션과 한개의 종료 오퍼레이션 1개로 구성
  - 스트림의 데이터 소스는 오직 종료 오퍼네이션을 실행할 때에만 처리
- 중개 오퍼레이션
  - 스트림을 리턴
  - filter, map, limit, skip, sorted, ...
- 종료 오퍼레이션
  - 스트림을 리턴하지 않음
  - collect, allMatch, count, forEach, min, max 등등

- 스트림 API
  - 걸러내기: Filter(Predicate)
  ```java
  List<OnlineClass> springClasses = new ArrayList<>();
  springClasses.add(new OnlineClass(1, "spring boot", true));
  springClasses.add(new OnlineClass(2, "spring data jpa", true));
  springClasses.add(new OnlineClass(3, "spring mvc", false));
  springClasses.add(new OnlineClass(4, "spring rest api", true));
  springClasses.add(new OnlineClass(5, "spring test", true));

  // spring으로 시작하는 수업
  springClasses.stream()
          .filter(oc -> oc.getTitle().startsWith("spring"))
          .forEach(oc -> System.out.println(oc.getId()));
      
  // close 되지 않은 수업
  springClasses.stream()
          .filter(oc -> !oc.isClosed())
          .forEach(oc -> System.out.println(oc.getId()));
  ```
  
  - 변경하기: Map(Function) 또는 FlatMap(Function)
  ```java
  // 수업 이름만 모아서 스트림 만들기
  springClasses.stream()
          .map(oc -> oc.getTitle())
          .forEach(System.out::println);
  ```
  - 생성하기: generate(Supplier) 또는 Iterate(T seed, UnaryOperator) 
  - 제한하기: limit(long) 또는 skip(long)
  ```java
  // 10부터 1씩 증가하는 무제한 숫자 스트림 중에서 앞에 10개 빼고 최대 10개 까지만
  Stream.iterate(10, i -> i + 1)
      .skip(10)
      .limit(10)
      .forEach(System.out::println);
  ```

  - 스트림에 있는 데이터가 특정 조건을 만족하는지 확인: anyMatch(), allMatch(), nonMatch()
  ```java
  // 스프링 수업 중에 Test가 들어 있는 수업이 있는지 확인
  boolean result = springClasses.stream().anyMatch(oc -> oc.getTitle().contains("Test"));
  System.out.println(result);
  ```

  - 개수 세기: count()
  - 스트림을 데이터 하나로 뭉치기: reduce(identity, BiFunction), collect(), sum(), max()
  ```java
  // 스프링 수업 중에 제목에 spring이 들어간 제목만 모아서 List 만들기
  List<String> spring = springClasses.stream()
                .filter(oc -> oc.getTitle().contains("spring"))
                .map(OnlineClass::getTitle)
                .collect(Collectors.toList());
  spring.forEach(System.out::println);
  ```


Optional
=======
- 옵셔널
  - `오직 값 한 개가 들어있을 수도 없을 수도 있는 인스턴스의 컨테이너 타입`
  - null을 리턴이나 null 체크를 깜빡했을 때 `NullPointerException이 나는 경우를 처리하기 쉽게 해줌`
  - null을 처리하는 방법
    - 예외를 던짐 -> 스택트레이스 때문에 비용이 비쌈
    - null을 리턴 -> 클리어인트 코드에 주의가 매우 많이 필요함
    - Optional을 리턴 -> 클라이언트에 코드에게 명시적으로 빈 값일 수도 있다는 걸 알려주고, 빈 값인 경우에 대한 처리를 강제하여 안전함
  - `리턴 값으로만` 쓰기를 권장
  - 프리미티브 타입 용 Optional을 따로 존재(OptionalInt, OptionalLong, OptionalDouble)
  - Collection, Map, Stream Array, Optional 같은 컨테이너 성격의 인스턴스들은 그 자체로 null체크가 가능하므로 Opiontal로 감싸지 말 것
  ```java
  Optional<Progress> progress = onlineClass.getProgress();
  progress.ifPresent(p -> System.out.println(p.getId));
  ```

- 옵셔널 API
  - Optional 만들기: Optional.of(), Optional.ofNullable(), Optional.empty()
  - Optional에 값이 있는지 없는지 확인하기: isPresent(), isEmpty()
  ```java
  Optional<OnlineClass> optional = springClasses.stream()
              .filter(oc -> oc.getTitle().startsWith("spring"))
              .findFirst();
  
  optional.ifPresent(oc -> System.out.println(oc.getTitle()));
  ```
  - Optional에 있는 값 가져오기: get()
  ```java
  Optional<OnlineClass> optional = springClasses.stream()
              .filter(oc -> oc.getTitle().startsWith("spring"))
              .findFirst();

  // 값이 없을 경우 NoSuchElementException이 발생
  Onlineclass onlineClasses = optional.get();
  ```
  - Optional에 값이 있는 경우 ~~를 하라: ifPresent(Consumer)
  - Optional에 값이 있으면 가져오고 없는 경우에 특정 값 리턴하기:orElse(T)
  ```java
  Optional<OnlineClass> optional = springClasses.stream()
              .filter(oc -> oc.getTitle().startsWith("spring"))
              .findFirst();
  
  Onlineclass onlineClasses = optional.orElse(createNewClass());
  ```
  - Optional에 값이 있으면 가져오고 없는 경우에 ~~를 하라: orElseGet(Supplier)
  ```java
  Optional<OnlineClass> optional = springClasses.stream()
              .filter(oc -> oc.getTitle().startsWith("spring"))
              .findFirst();
  
  Onlineclass onlineClasses = optional.orElseGet(App::createNweClass);
  ```
  - Optional에 값이 있으면 가졍고 없는 경우 에러를 던지기: orElseThrow()
  ```java
  Optional<OnlineClass> optional = springClasses.stream()
              .filter(oc -> oc.getTitle().startsWith("spring"))
              .findFirst();
  
  Onlineclass onlineClasses = optional.orElseThrow(() ->{
    return new IllegalArgumentException();
  });
  ```
  - Optional에 들어있는 값 걸러내기: Optional filter(Predicate)
  ```java
  Optional<OnlineClass> optional = springClasses.stream()
              .filter(oc -> oc.getTitle().startsWith("spring"))
              .findFirst();
  
  Optional<Onlineclass> onlineClasses = optional.filter(oc -> !oc.isClosed());
  ```
  - Optional에 들어있는 값 변환하기: Optional map(Function), Optional flatMap(Function)
  ```java
  Optional<OnlineClass> optional = springClasses.stream()
              .filter(oc -> oc.getTitle().startsWith("spring"))
              .findFirst();
  
  Optional<Onlineclass> onlineClasses = optional.map(OnlineClass::getId);
  System.out.println(integer.ispRresent());
  ```

Date와 Time
=======
- Date와 Time
  - java.util 시간 라이브러리의 문제점
    - `mutable 하기 때문에 thead safe하지 않음`
    - `타입 안정성이 없음`
    - 클래스 이름이 명확하지 않음
  - Java8 부터는 java.time 시간 라이브러리를 사용
  - 기계용 시간과 인류용 시간으로 나눠져서 기계용 시간은 EPOCK(1970년 1월 1일 0시 0분 0초)부터 현재까지의 타임스탬프로 표현하고 인류용 시간은 우리가 흔히 사용하는 연,월,일,시,분,초 등을 표현
  - 기계용 시간은 타임스탬프는 Instant를 사용
  - 인류용 특정 날짜(LocalDate), 시간(LocalTime), 일시(LocalDateTime)를 등등을 사용
  - 기간을 표현할 때는 Duration(시간 기반,기계용)과 Period(날짜 기반,인류용)를 사용
  - DateTimeFormatter를 사용해서 일시를 특정한 문자열로 포매팅이 가능

- Date와 Time API
  - 기계용 시간을 표현하는 방법
  ```java
  Instant now = Instant.now(); 
  System.out.println(now); // UTC, GMT 출력 
  System.out.println(now.atZone(ZoneId.systemDefault())); // 시스템의 기준시로 출력
  ```
  - 인류용 시간을 표현하는 방법
  ```java
  LocalDateTime now = LocalDateTime.now();
  System.out.println(now);
  LocalDateTime birthday = LocalDateTime.of(1982, Month.JULY, 15, 0, 0, 0);
  ZonedDateTime nowInKorea = ZonedDateTime.now(ZoneId.of("Aisa/Seoul"));
  ```
  - 기계 시간과 인류 시간을 변환하는 방법
  ```java
  Istant now = Instant.now();
  ZonedDateTime zonedDateTime = now.ztZone(ZoneId.of("Asia/Seoul"));
  Istant now2 = zonedDateTime.toInsant();
  ```
  - 기간을 표현하는 방법
  ```java
  // Period
  LocalDate today = localDate.now();
  LocalDate birthDay = LocalDate.of(2020, Month.JULY, 15);

  Period between = Period.between(today, birthDay);
  System.out.println(between.getDays());
  System.out.println(between.get(ChronoUnit.DAYS));
  ```
  ```java
  // Duration
  Instant now = Instant.now();
  Instant plus = now.plus(10, ChronoUnit.SECONDS);
  Duration between = Duration.between(now, plus);
  System.out.println(between.getSeconds());
  ```
  - 파싱 또는 포매팅
  ```java
  // 포매팅
  DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MM/dd/yyyy");
  LocalDate today = localDate.now();
  System.out.println(today.format(formatter));
  ```
  ```java
  // 파싱
  DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MM/dd/yyyy");
  LocalDate date = LocalDate.parse("07/15/1982", formatter);
  System.out.println(date);
  ```
