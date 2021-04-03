# 자바 테스트
인프런 더 자바 애플리케이션을 테스트하는 다양한 방법

Table of contents
=================
<!--ts-->
   * [JUnit5](#JUnit5)
   * [Mockito](#Mockito)
   * [도커와 테스트](#도커와-테스트)
   * [성능 테스트](#성능-테스트)
   * [운영 이슈 테스트](#운영-이슈-테스트)
   * [아키텍처 테스트](#아키텍처-테스트)
<!--te-->

JUnit5
=======
- JUnit5 소개
  - 자바 개발자가 가장 많이 사용하는 테스팅 프레임워크
  - JUnit5의 구성
    - JUnit Platform:  테스트를 실행해주는 런처 제공. TestEngine API 제공
    - `Jupiter`: JUnit 5를 지원하는 TestEngine API 구현체
    - Vintage: JUnit 4와 3을 지원하는 TestEngine 구현체

- JUnit5 시작하기
  - 2.2+ 버전의 스프링 부트 프로젝트를 만든다면 기본으로 JUnit 5 의존성 추가
  - Junit5 부터는 테스트하는 클래스나 메소드가 public일 필요가 없어졌음
  - 기본 어노테이션
    - `@Test`: 테스트할 메소드를 적용하는 어노테이션
    - `@BeforeAll / @AfterAll`: 모든 테스트가 실행되기 전이나 후에 실행할 코드에 적용하는 어노테이션
    - `@BeforeEach / @AfterEach`: 각각의 Test 메소드가 실행될 때 적용하는 어노테이션으로 각각의 모든 메소드가 실행 전, 실행 후에 호출되어 처리
    - @Disabled: 테스트하지 않을 메소드에 적용하는 어노테이션

- JUnit5 테스트 이름 표시하기
  - 기본적으로 스네이크 케이스를 통해서 메소드 이름에 구분을 줌
  - @DisplayName: 어떤 테스트인지 테스트 이름을 보다 쉽게 표현할 수 있는 방법을 제공하는 애노테이션(권장되는 방법)
  ```java
  @Test
  @DisplayName("스터디 만들기")
  void test(){

  }
  ```
  - @DisplayNameGeneration: Method 이름와 Class 레퍼런스를 사용해서 테스트 이름을 표기하는 방법 설정

- JUnit5 Assertion
  - org.junit.jupiter.api.Assertions.* 의 API에서 제공하고, Assert API 메소드에 supplier message를 활용해서 실패했을 때 메시지를 파라미터로 줄 수 있음
  - `assertEqulas(expected, actual): 실제 값이 기대한 값과 같은지 확인`
  ```java
  @Test
  void test() {
    Study study = new Study();
    assertNotNull(study);
    assertEquals(StudyStatus.DRAFT, study.getStatus());
  }
  ```
  - `assertNotNull(actual): 값이 null이 아닌지 확인`
  ```java
  @Test
  void test() {
    Study study = new Study();
    assertNotNull(study);
  }
  ```
  - `assertTrue(boolean): 다음 조건이 참(true)인지 확인`
  - assertAll(executables...): 모든 Assert 구문을 assertAll안에 넣으면 테스트의 순서에 상관 없이 모두 확인
  - `assertThrows(expectedType, executable): 예외 발생 확인`
  ```java
  @Test
  void test() {
    CustomException exception = assertThrows(CustomException.class, ()-> new CustomClass(-1));
    String message = exception.getMessage();
    assertEquals("CustomException!!!", message);
  }
  ```
  - assertTimeout(duration, executable): 특정 시간 안에 실행이 완료되는지 확인

- JUnit5 조건에 따라 테스트 실행하기
  - 환경 변수, OS, 자바 버전 등등의 특정한 조건을 만족하는 경우에 테스트를 실행하는 방법을 제공
  - assumeTrue(조건)와 assumingThat(조건, 테스트): 특정 조건을 조건식에 넣고 만족하는 경우 테스트시킬 수 있음
  ```java
  @Test
  void test(){
    String test_env = System.getenv("TEST_ENV"); // 시스템의 TEST_ENV 환경 변수 값 읽기
    System.out.println(test_env);
    assumeTrue("LOCAL".equalsIgnoreCase(test_env));
  }
  ```
  - @Enabled___ 와 @Disabled___: OnOS, OnJre, IfSystemProperty, IfEnvironmentVariable, If 등등으로 어노테이션을 통해 특정 조건에 따라 실행 시킬 수 있음
  ```java
  @Test
  @EnabledIfEnviromentVariable(named = "TEST_ENV", matches = "local")
  void test(){

  }
  ```
- JUnit5 태깅과 필터링
  -     

- JUnit5 커스텀 태그
- JUnit5 테스트 반복하기
- JUnit5 테스트 인스턴스
- JUnit5 테스트 순서
- JUnit5 junit-platform
- JUnit5 확장 모델
- JUnit5 마이그레이션
- JUnit5 연습 문제


Mockito
=======
