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
  - `람다가 하는 일이 기존 메소드 또는 생성자를 호출하는 거라면`, 메소드 레퍼런스를 사용해서 매우 간결하게 표현 가능
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
    List<String> name = nwe ArrayList<>();
    name.add("keesun");
    name.add("keesun2");

    name.forEach(System.out:println);
    ```
    - spliterator(): 쪼갤 수 있는 기능을 가진 iterator
    ```java
    List<String> name = nwe ArrayList<>();
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
    List<String> name = nwe ArrayList<>();
    name.add("keesun");
    name.add("keesun2");

    long cnt = name.stream().map(String::toUpperCase).filter(s -> s.startswith("K")).count();
    ```
    - removeIf(Predicate)
    ```java
    List<String> name = nwe ArrayList<>();
    name.add("keesun");
    name.add("keesun2");

    name.removeIf(s -> s,startsWith("k"));
    ```
  - Comparator의 기본 메소드 및 스태틱 메소드
    - reversed()
    ```java
    List<String> name = nwe ArrayList<>();
    name.add("keesun");
    name.add("keesun2");

    Comparator<String> compareToIgnoreCase = String::compareToIgnoreCase;
    name.sort(compareToIgnoreCase.reversed());
    ```
    - thenComparing()
    ```java
    List<String> name = nwe ArrayList<>();
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

Optional
=======

Date와 Time
=======

CompletableFuture
=======
