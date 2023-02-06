# 자바 테스트

Table of contents
=================
<!--ts-->
   * [JUnit5](#JUnit5)
   * [Mockito](#Mockito)
<!--te-->

JUnit5
=======
- JUnit5 소개
  - 자바 개발자가 가장 많이 사용하는 테스팅 프레임워크
  - JUnit5의 구성
    - JUnit Platform: 테스트를 실행해주는 런처와 TestEngine API 제공
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
  - `테스트 그룹을 만들고 원하는 테스트 그룹만 테스트를 실행할 수 있는 기능`
  - @Tag: 테스트 메소드에 태그를 추가할 수 있고 하나의 테스트 메소드에 여러 태그를 사용
  ```java
  @Test
  @Tag("fast")
  void test(){

  }
  ```
  - 인텔리제이 제이에서 `Edit Configuration` -> `JUnit`의 테스트 종류에서 테크 표현을 통해서 필터링 가능
- JUnit5 커스텀 태그
  - JUnit5 애노테이션을 조합하여 커스텀 태그를 만들 수 있음
  ```java
  @Target(ElementType.METHOD)
  @Retention(RetentionPolicy.RUNTIME)
  @Tag("fast")
  @Test
  public @interface FastTest {

  }
  ```
  ```java
  @FastTest
  @Tag("fast")
  void test(){

  }
  ```
- JUnit5 테스트 반복하기
  - @RepeatedTest: 반복 횟수와 반복 테스트 이름을 설정할 수 있고 RepetitionInfo 타입의 인자를 받아서 반복에 대한 정보를 전달할 수 있음
    - {displayName}
    - {currentRepetition}
    - {totalRepetitions}
  ```java
  @RepeatedTest(value = 10, name="{displayName}, {currentRepetition}/{totalRepetitions}")
  void test(RepetitionInfo repetitionInfo) {
    System.out.println("Hello" + repetitionInfo.getCurrentRepetition());
  }
  ```

  - @ParameterizedTest: 테스트에 여러 다른 매개변수를 대입해가며 반복 실행
    - {displayName}
    - {index}
    - {arguments}
    - {0}, {1}, ... 
  ```java
  @ParameterizedTest(name = "{index} {displayName} message={0}")
  @ValueSource(strings = {"날씨가", "많이", "추워지고", "있네요."})
  void test(String message) {
    System.out.println(message);    
  }
  ```
  - 인자 값들의 소스
    - @ValueSource
    - @NullSource, @EmptySource, @NullAndEmptySource
    - @EnumSource
    - @MethodSource
    - @CvsSource
    - @CvsFileSource
    - @ArgumentSource
  ```java
  @DisplayName("스터디 만들기")
  @ParameterizedTest(name = "{index} {displayName} message={0}")
  @ValueSource(ints = {10, 20, 40})
  void test(String message) {
    System.out.println(message);    
  }
  ```
  - 인자 값 타입 변환: 1개의 아규먼트일 때 사용
    - 암묵적인 타입 변환: String에서 primitive 타입은 일반적으로 제공
    ```java
    @DisplayName("스터디 만들기")
    @ParameterizedTest(name = "{index} {displayName} message={0}")
    @ValueSource(springs = {10, 20, 40})
    void test(int message) {
      System.out.println(message);    
    }
    ```
    - 명시적인 타입 변환: SimpleArgumentConverter 상속 받은 구현체 제공하여 구현체를 만들고 @ConvertWith로 적용
    ```java
    @DisplayName("스터디 만들기")
    @ParameterizedTest(name = "{index} {displayName} message={0}")
    @ValueSource(ints = {10, 20, 40})
    void test(@ConvertWith(StudyConverter.class) Study study) {
      System.out.println(study.getId());    
    }

    static class StudyConverter extends SimpleArgumentConverter{

        @Override
        protected Object convert(Object source, Class<?> targetType) throws ArgumentConversionException{
            return new Study(Integer.parseInt(source.toString()));
        }
    }
    ```
  - 인자 값 조합: 여러 개의 아규먼트일 때 사용
    - ArgumentsAccessor
    ```java
    @DisplayName("스터디 만들기")
    @ParameterizedTest(name = "{index} {displayName} message={0}")
    @CsvSource({"10, '자바 스터디'","'20, 스프링'"})
    void test(ArgumentsAccessor argumentsAccessor) {
        Study study = new Study(argumentsAccessor.getInteger(0, argumentsAccessor.getString(1)));
        System.out.println(study);
    }
    ```
    - 커스텀 Accessor: ArgumentsAggregator 인터페이스 구현체를 만들고 @AggregateWith로 적용
    ```java
    @DisplayName("스터디 만들기")
    @ParameterizedTest(name = "{index} {displayName} message={0}")
    @CsvSource({"10, '자바 스터디'","'20, 스프링'"})
    void test(@ArggregateWith(StudyAggregator.class) Study study) {
        System.out.println(study);
    }

    static class StudyAggregator implements ArgumentsAggregator {
        @Override
        public Object aggregateArguments(ArgumentsAccessor argumentsAccessor, ParameterContext parameterContext) throws ArgumentsAggregationException {
			return new Study(argumentsAccessor.getInteger(0, argumentsAccessor.getString(1)));
		}
    }
    ```

- JUnit5 테스트 인스턴스
  - JUnit은 기본적으로 테스트 메소드 마다 테스트 인스턴스를 새로 만드는데 이를 변경할 수 있음
  - @TestInstance(Lifecycle.PER_CLASS)
    - 테스트 클래스당 인스턴스를 하나만 만들어 사용
    - 경우에 따라, 테스트 간에 공유하는 모든 상태를 @BeforeEach 또는 @AfterEach에서 초기화 할 필요가 있음
    - @BeforeAll과 @AfterAll을 인스턴스 메소드 또는 인터페이스에 정의한 default 메소드로 정의할 수도 있음
  ```java
  @TestInstance(Lifecycle.PER_CLASS)
  class StudyTest {

  }
  ```

- JUnit5 테스트 순서
  - 실행할 테스트 메소드 특정한 순서에 의해 실행되지만 어떻게 그 순서를 정하는지는 의도적으로 분명히 하지 않아서 특정 순서대로 테스트를 실행하고 싶을 때가 있으므로 그 경우에는 테스트 메소드를 원하는 순서에 따라 실행
  - @TestMethodOrder: MethodOrderer 구현체를 설정
    - 기본 제공 구현체
      - Alphanumeric
      - OrderAnnoation
      - Random
  ```java
  @TestMethodOrder(MethodOrderer.OrderAnnoation.class)
  class StudyTest {
    @Order(1)
    void test() {
    System.out.println("HELLO");
    }    
    
    @Order(2)
    void test2() {
    System.out.println("HELLO");
    }
  }
  ```


- JUnit5 junit-platform
  - JUnit 설정 파일로, 클래스패스 루트 (src/test/resources/)에 넣어두면 적용
  - 테스트 인스턴스 라이프사이클 설정: junit.jupiter.testinstance.lifecycle.default = per_class
  - 확장팩 자동 감지 기능: junit.jupiter.extensions.autodetection.enabled = true
  - @Disabled 무시하고 실행하기: junit.jupiter.conditions.deactivate = org.junit.*DisabledCondition
  - 테스트 이름 표기 전략 설정: junit.jupiter.displayname.generator.default = \org.junit.jupiter.api.DisplayNameGenerator$ReplaceUnderscores
 


- JUnit5 확장 모델
  - 단위 테스트간에 공통적으로 사용할 기능을 구현하여 적용하는 확장 기능
  - JUnit 4의 확장 모델은 @RunWith(Runner), TestRule, MethodRule 이었으나 JUnit 5의 확장 모델은 Extension로 단 하나
  - 스프링의 테스트 어노테이션은 대부분 @ExtendWith이 붙어 있음
  - 확장 팩 등록 방법
    - 선언적인 등록: `@ExtendWith`
    - 프로그래밍 등록: @RegisterExtension
    - 자동 등록: 자바 ServiceLoader 이용
  ```java
  @ExtendWith(SpringExtension.class)
  class MixedPlanBOTest {
  
  }
  ```
  - 확장팩 만드는 방법
    - 테스트 실행 조건
    - 테스트 인스턴스 팩토리
    - 테스트 인스턴스 후-처리기
    - 테스트 매개변수 리졸버
    - 테스트 라이프사이클 콜백
    - 예외 처리

- JUnit4 마이그레이션
  - junit-vintage-engine을 의존성으로 추가하면, JUnit5의 junit-platform으로 JUnit3과 4로 작성된 테스트를 수정 없이 실행이 가능
  - @Rule은 기본적으로 지원하지 않지만, junit-jupiter-migrationsupport 모듈이 제공하는 @EnableRuleMigrationSupport를 사용하면 다음 타입의 Rule을 지원
    - ExternalResource
    - Verifier
    - ExpectedException
  - JUnit4와 JUnit5 어노테이션 비교

    |JUnit4|JUnit5|
    |------|----------|
    |@Category(Class)|@Tag(String)|
    |@RunWith, @Rule, @ClassRule|@ExtendWith, @RegisterExtension|
    |@Ignore|@Disabled|
    |@Before, @After, @BeforeClass, @AfterClass|@BeforeEach, @AfterEach, @BeforeAll, @AfterAll|

Mockito
=======
- Mockito 소개
  - Mock: 진짜 객체와 비슷하게 동작하지만 `프로그래머가 직접 그 객체의 행동을 관리하는 가짜 객체`
  - Mockito: Mock 객체를 쉽게 만들고 관리하고 검증할 수 있는 방법을 제공하는 프레임워크
  - DB 사용, 외부 API, 자바 API를 등등을 사용할 때 그 외부 의존성을 각각 테스트 코드에서 정의하지 않고 동작만 예측하여 편리하게 Mock으로 정의해서 테스트에서 사용

- Mockito 시작하기
  - 2.2+ 버전의 스프링 부트 프로젝트를 만든다면 기본으로 Mockito 의존성 추가
  - Mocking을 활용해서 테스트를 쉽게 작성하려면 알아야하는 방법
    - Mock을 만드는 방법
    - Mock이 어떻게 동작해야 하는지 관리하는 방법
    - Mock의 행동을 검증하는 방법

- Mock 객체 만들기
  - Mockito.mock() 메소드로 만드는 방법
  ```java
  MemberService memberService = Mockio.mock(MemberService.class);
  StudyRepository studyRepository = Mockio.mock(StudyRepository.class);

  @Test
  void createStudyServce(){
      StudyService studyService = new StudyService(memberService, studyRepository);
  }
  ```
  - @Mock 애노테이션으로 Mock 객체 만드는 방법: JUnit 5 extension으로 MockitoExtension을 사용
  ```java
  @ExtendWith(MockitoExtension.class)
  class StudyServiceTest {

    @Mock
    MemberService memberService;

    @Mock
    StudyRepository studyRepository;

    @Test
    void createStudyServce(){
      StudyService studyService = new StudyService(memberService, studyRepository);
    }
    
    @Test
    void createStudyService2(@Mock MemberService memberService2,
                            @Mock StudyRepository studyRepository2) {
        StudyService studyService = new StudyService(memberService, studyRepository);
    }
  }
  ```
- Mock 객체 Stubbing
  - Stubbing: `Mock 객체의 행동을 조작하는 것을 의미`
  - 모든 Mock 객체의 초기 상태의 특징과 해동
    - Null을 리턴(Optional 타입은 Optional.empty 리턴)
    - Primitive 타입은 기본 Primitive 값이 할당
    - 콜렉션은 비어있는 콜렉션이 할당
    - Void 메소드는 예외를 던지지 않고 아무런 일도 발생하지 않음
- Mock 객체 조작
  -	특정한 매개변수를 받은 경우 특정한 값을 리턴하거나 예뢰를 던지도록 만들 수 있음
  - any()와 같은 Argument Matcher를 통해서 파라미터 처리를 할 수 있음
  -	Void 메소드 특정 매개변수를 받거나 호출된 경우 예외를 발생 시킬 수 있음
  -	메소드가 동일한 매개변수로 여러번 호출될 때 각기 다르게 행동하도록 조작할 수도 있음
  ```java
    @Mock
    MemberService memberService;

    @Mock
    StudyRepository studyRepository;

    @Test
    void test(){
      // == given ==
      Member member = new Member();
      member.setId(1);
      member.setEmail("keesun@gmail.com");

      // Stubbing
      when(memberService.findById(1)).thenReturn(Optional.of(member));
      // Argument Matcher 사용
      when(memberService.findById(any())).thenReturn(Optional.of(member));
      // 예외 발생 로직도 추가
      when(memberService.findById(any()))
                    .thenReturn(Optional.of(member))
                    .thenThrow(new RuntimeException())
                    .thenReturn(Optional.empty())

      // == when ==
      Optional<Member> member2 = memberService.findById(1L);

      // == then ==
      assertEquals("keesun@gmail.com", member2.get().getEmail());
      assertThrows(RuntimeException.class, () -> {
          memberService.findById(2);
      });
      assertEquals(Optional.empty(), memberService.findById(3));

    }

    @Test
    void test2(){
        // == given ==
        Study study = new Study(10, "테스트");

        // memberService 객체에 findById 메소드를 1L 값으로 호출하면 Optional.of(member) 객체를 리턴하도록 Stubbing
        when(memberService.findById(1).thenReturn(Optional.of(member)));
        // studyRepository 객체에 save 메소드를 study 객체로 호출하면 study 객체 그대로 리턴하도록 Stubbing
        when(studyRepository.save(study)).threnReturn(study);

        // == when ==
        studyService.createNewStudy(1L, study);

        // == then ==
        assertNotNull(study.getOwner());
        assertEquals(member, study.getOwner());
    }
  }
  ```
- Mock 객체 확인 
  - 특정 메소드가 특정 매개변수로 몇번 호출 되었는지, 최소 한번은 호출 됐는지, 전혀 호출되지 않았는지
    - Verifying exact number of invocations
    ```java
    verify(memberService, times(1)).notify(study));
    ```
  - 어떤 순서대로 호출했는지
    - Verification in order
    ```java
    InOrder inOrder = inOrder(memberService);
    inOrder.verify(memberService).notify(study);
    inOrder.verify(memberService).notify(member);
    ```
  - 특정 시간 이내에 호출됐는지
    - Verification with timeout
  - 특정 시점 이후에 아무 일도 벌어지지 않았는지
    - Finding redundant invocations
 

- BDD 스타일 Mockito API 
  - BDD: `애플리케이션이 어떻게 행동해야 하는지에 대한 공통된 이해를 구성하는 방법`
  - 행동에 대한 스팩
    - Title
    - Narrative
      - As a  / I want / so that
    - Acceptance criteria
      - Given / When / Then
  - Mockito는 BddMockito라는 클래스를 통해 BDD 스타일의 API를 제공
    - When -> Given
    ```java
    given(memberService.findById(1L)).willReturn(Optional.of(member));
    given(studyRepository.save(study)).willReturn(study);
    ```
    - Verify -> Then
    ```java
    then(memberService).should(times(1)).notify(study);
    then(memberService).shouldHaveNoMoreInteractions();
    ```
