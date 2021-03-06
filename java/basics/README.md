# 자바 스터디
[스터디 할래](https://github.com/whiteship/live-study) 정리

Table of contents
=================
<!--ts-->
   * [JVM](#JVM)
   * [데이터 타입 변수 배열](#데이터-타입-변수-배열)
   * [연산자](#연산자)
   * [제어문](#제어문)
   * [클래스](#클래스)
   * [상속](#상속)
   * [패키지](#패키지)
   * [인터페이스](#인터페이스)
   * [예외처리](#예외처리)
   * [멀티쓰레드](#멀티쓰레드)
   * [Enum](#Enum)
   * [애노테이션](#애노테이션)
   * [IO](#IO)
   * [제네릭](#제네릭)
   * [람다식](#람다식)
<!--te-->

JVM
=======
- JVM이란 무엇인가
  - JVM: JAVA Virtial Machine의 약자로 `Java Byte Code를 OS에 맞게 해석해주는 역할을 하는 가상머신`
  > JVM을 통해 OS에 의존없이 바이트 코드를 실행할 수 있지만, OS 별로 JVM은 필요함
  - JVM 활용 순서
    - 자바 컴파일러(javac)는 .java 파일을 .class라는 Java byte code로 변환
    - JVM은 OS가 Byte 코드를 이해할 수 있도록 해석
    - Byte 코드는 JVM 위에서 OS 상관없이 실행

- 컴파일 하는 방법 및 실행하는 방법
  - javac 는 자바 소스코드를 컴파일할 때 사용하는 프로그램이며 컴파일된 바이트 코드를 실행할 때 java 사용하여 실행
  - `$ javac 소스파일명.java`
  - `$ java 소스파일명`

- 컴파일 타임과 런타임
  - 런타임: 컴파일 과정을 마친 응용 프로그램이 사용자에 의해서 실행되는 때
  - 런타임 오류 : 0나누기 오류, 널(Null)참조 오류, 메모리 부족 오류
  - 컴파일타임: 소스코드가 컴파일러에 의해 컴퓨터가 이해할 수 있는 기계어 코드로 변환되는 때
  - 컴파일타임 오류: 신택스 오류, 타입체크 오류

- 바이트코드란 무엇인가
  - Byte 코드: 0과 1로 구성되어 있는 이진 코드이지만 일반적인 바이너리 코드와 다르게 가상 머신이 이해할 수 있는 바이너리 코드

- JIT 컴파일러란 무엇이며 어떻게 동작하는지
  - Java를 실행할 때 사용되는 컴파일러로 바이트코드를 읽어 기계어로 번역하지만 프로그램에는 반복적으로 사용하는 코드가 존재할 때 최초 1회만 번역하여 캐싱한 뒤 추가 참조가 필요할 때마다 불러와서 성능 향상시키는 기능을 가진 인터프리와 동시에 동작하는 컴파일러

- JVM 구성 요소
  - `Class Loader`
    - Runtime 시점에 .class에서 바이트 코드를 읽고 JVM의 메모리에 저장하는 요소
    - 로딩: 클래스를 읽어오는 과정
    - 링크: 레퍼런스를 연결하는 과정
    - 초기화: static 값들을 초기화 및 변수에 할당
  - `Runtime Data Areas`
    - JVM의 메모리 영역
    - Heap 과 Method는 모든 쓰레드가 공유하고 나머지는 쓰레드마다 생성
      - PC Register: CPU가 Instruction을 수행하는 동한 필요한 정보를 저장
      - Stack: Thread가 시작될 때 생성되며 Method와 Method 정보 저장
      - Navtive Method Stack: Java 이외의 언어로 작성된 native 코드를 위한 Stack
      - Method: 모든 쓰레드가 공유하는 메모리 영역(클래스, 인터페이스, 메소드, 필드, Static 변수등의 바이트 코드 등을 보관)
      - Heap: 런타임시 동적으로 할당하여 사용하는 영역 class를 통해 instance를 생성하면 Heap에 저장됨
        - Heap의 경우 명시적으로 만든 class와 암묵적인 static 클래스(.class 파일의 class)가 담긴다.
        - 또한 암묵적인 static 클래스의 경우 클래스 로딩 시 class 타입의 인스턴스를 만들어 힙에 저장한다. 이는 Reflection에 등장한다.
  - `Execution Engine`
    - Class Loader를 통해 JVM 내의 Runtime Data Areas에 배치된 바이트 코드는 Execution Engine에 의해 실행
    - Load된 Class의 ByteCode를 실행하는 Runtime Module로 인터프리터, JIT 컴파일러, GC를 포함
  - `Native Method Interface(JNI)`
    - Java Native Interface(JNI)는 자바 가상 머신(JVM)위에서 실행되고 있는 자바코드가 네이티브 응용 프로그램 그리고 다른 언어들로 작성된 라이브러리들을 호출하거나 반대로 호출되는 것을 가능하게 하는 프로그래밍 프레임워크

- JDK와 JRE의 차이
  - `JRE`: JRE는 자바 실행환경(Java Runtime Environment)의 약자로 JRE는 JVM 이 자바 프로그램을 동작시킬 때 필요한 라이브러리 파일들과 기타 파일들을 가지고 있음
  - `JDK`: JDK는 자바 개발도구(Java Development Kit)의 약자로 JRE에 개발을 위해 필요한 도구(javac, java)를 포함

데이터 타입 변수 배열
=======
- 프리미티브 타입 종류와 값의 범위 그리고 기본 값

  |타입|크기|범위|기본 값| 비고 |
  |---|---|---|----|-----|
  |byte| 1 byte|	-128 ~ 127	|0	|
  |short|	2 bytes|	-32,768 ~ 32,767	|0	|
  |(signed) int| 4 bytes|	-2^{31}  ~  2^{31}-1	|0	|
  |unsigned int| 4 bytes|	0  ~  2^{32}-1	|0|	java 8 이상부터 가능|
  |(signed) long|	8 bytes|	-2^{63}  ~  2^{63}-1	|0L|	
  |unsigned long|	8 bytes|	0  ~  2^{64}-1	|0L	|java 8 이상부터 가능|
  |float|	4 bytes|	single-precision 32-bit	|0.0f|	|
  |double| 8 bytes|	double-precision 64-bit	|0.0d|	|
  |boolean|	1 bit|	true / false	|false|	|
  |char| 2 bytes|	'\u0000' ~ '\uffff'	|'\u0000'|	|

- 프리미티브 타입과 레퍼런스 타입
  - **Primitive type**
    - byte, short, signed/unsigned int, signed/unsigned long, float, double, boolean, char
    - not object
    - 값 저장
    - 스택에 만들어짐
- **Reference type**
    - class, interface, enum, array, String type
    - 주소 저장
    - 힙에 만들어짐(가르키는 변수는 스택에 만들어짐)

- 리터럴
  - 리터럴은 변수나 상수에 저장되는 값 그 자체를 의미
  - 정수 리터럴
    - 정수 리터럴은 기본적으로 int 형이고, long 타입을 표현하려면 l이나 L을 마지막에 붙임
    - 기본적으로 10진법이고 0이 앞에 붙으면 8진법, 0x가 붙으면 16진법, 0b가 붙으면 2진법
    > 숫자가 매우 큰 경우는 리터럴 대신 BigInteger를 사용해야함
  - 실수 리터럴
    - 실수 리터널의 리터럴은 기본적으로 double 타입이고, float 타입으로 표현하려면 f를 명시적으로 붙임
    > 숫자가 매우 큰 경우는 리터럴 대신 BigDecimal를 사용해야함
  - 문자 리터럴
    - 문자는 작은따옴표(')안에 표현
  - 문자열 리터럴
    - 문자열은 큰따옴표(")안에 표현
  - boolean 리터럴
    - true, false 로 표현

- 변수 선언 및 초기화하는 방법
  - 변수 선언: 저장공간을 확보하겠다는 의미
  - 변수 초기화: 변수를 사용하기 전 처음으로 값을 저장하는 것

- 변수의 스코프와 라이프타임
  - `스코프`: 코프란 해당 변수를 사용할 수 있는 영역 범위
  - `라이프 타임`: 해당 변수가 메모리에 언제까지 살아있느지를 의미
  - 변수의 종류 

    |종류|의미|스코프|라이프타임| 비고 |
    |---|---|---|----|-----|
    |인스턴스 변수| 클래스 안에서 선언되어있고, 어떠한 메서드나 블럭 안에서 선언되지 않은 변수|static method를 제외한 클래스 전체|클래스를 인스턴스화한 객체가 메모리에서 사라질 때 까지|
    |클래스 변수(전역변수)| 클래스 안에서 선언되어있고, 어떠한 메서드나 블럭 안에서 선언되지 않았으며 static 키워드가 포함되어 선언된 변수|클래스 전체|프로그램 종료시 까지|
    |지역 변수| 인스턴스 변수, 클래스 변수가 아닌 모든 변수|변수가 선언된 블럭 내부|변수가 선언된 블럭 내부에 있는 동안|

- 타입 변환, 캐스팅 그리고 타입 프로모션
  - 타입 변환: 변수나 리터럴의 타입을 다른 타입으로 변환하는 것
  - 타입 캐스팅: 타입캐스팅이란 크기가 더 큰 자료형을 크기가 더 작은 자료형에 대입하는 것, 데이터 손실이나 변형이 올 수 있음으로 명시적으로 `(자료형)`을 적어야함
  - 타입 프로모션: 기가 더 작은 자료형을 더 큰 자료형에 대입하는 것, 데이터 손실이나 변형이 오지 않음으로 캐스팅할 때 처럼 명시적으로 적지 않아도 자동으로 변환이 가능

- 배열 선언하기
  - 배열 선언: [] 혹은 변수명 뒤에 [] 붙여서 선언하고 new 연산이나 할당 연산을 통해서 초기화
  - 배열은 객체로 Runtime Stack 영역의 힙 영역 주소값을 가지고 값은 힙에 저장되는 방식
  ```java
  int [] arr; // 추천 방법
  int arr [];
  int arr2 [] = new int[10]; 
  int arr2 [][] = new int[10][10]; 
  int[] oneDimensionArrayEx1 = {1, 2, 3, 4, 5};
  int[][] twoDimensionArrayEx1 = {{1, 2}, {3, 4}};
  ```
- 타입 추론, var
  - 타입 추론: 데이터 타입을 소스코드에 명시하지 않아도, `컴파일 단계에서 컴파일러가 타입을 유추`해 정해주는 것
  - Java 5부터 추가된 Generic, Java 10부터 추가된 var가 타입 추론의 대표 기능
  - Generic(primitive type 사용 불가)
    - 제네릭 메소드: `<T> 반환형 매소드 이름(매개변수)` 방식으로 선언하여, 반환형과 매개변수의 데이터 타입을 함수를 호출할 때 결정
    - 제네릭 클래스: `class 클래스이름<T>` 방식으로 선언하여, 클래스 내부에서 사용하는 데이터의 타입을 클래스의 인스턴스를 생성할 때 결정
    > 자바의 모든 객체는 Object 상속하므로 다형성을 통해서 제네릭과 유사한 기능을 활용할 수있지만 형변환을 자주 해야하는 문제가 있음 
  - var
    - Local Variable Type Inference은 로컬 변수 선언을 var를 이용하여 기존의 엄격한 타입 선언방식에서 컴파일러에게 타입추론 책임을 위임하는 기능



연산자
=======
- 산술 연산자
  - 더하기: +는 기본적으로 두 수를 더하는 연산이지만 문자열을 연결시키는데도 사용, +의 피연산자 중 문자열이 있다면 다른 피연산자도 문자열로 변환
  - 빼기: - 연산자는 첫번째 피연산자에서 두번째 피연산자를 빼는 연산
  - 곱하기: * 연산자는 두 피연산자를 곱하는 연산
  - 나누기: / 연산자는 첫번째 피연산자를 두번째 피연산자로 나누는 연산
  - 나머지 연산: % 연산자는 첫번째 피연산자를 두번째 피연산자로 나누고 남은 나머지를 정수로 리턴하는 연산
  - 단항 마이너스 연산: 연산자를 단항 연산자로 사용하면 값의 부정이 수행되는 연산
- 비트 연산자: 비트 연산자(Bitwise Operators) 및 시프트 연산자(Shift Operators)는 개별 비트를 조작하는 저수준 연산자
  - `~`: 비트 반전 또는 비트 NOT 연산자로 각 비트를 반전시켜 1을 0으로, 0을 1로 변환
  - `&`: & 연산자는 두 정수 피연산자를 AND 연산(비트 곱)
  - `|`: | 연산자는 두 정수 피연산자를 OR 연산(비트 합)
  - `^`: ^ 연산자는 두 정수 피연산자를 XOR 연산, 비트가 같으면 0으로 다르면 1을 리턴
  - `<<`: << 연산자는 비트를 왼쪽으로 두번째 피연산자로 제시된 비트 수 만큼 이동, 기존의 가장 왼쪽 비트는 삭제되고 가장 오른쪽 비트는 0
  - `>>`: >> 연산자는 왼쪽 시프트 연산과 반대로 우측으로 두번째 피연산자로 제시된 비트 수 만큼 이동, 기존의 값이 양수인 경우 가장 왼쪽 비트는 0으로 채워지고 음수인 경우는 1

- 관계 연산자
  - `==`: == 연산자는 Primitive Type를 비교할 때 두 피연산자의 값이 같다면 true를 그렇지 않다면 false를 리턴 
  - `!=`: 두 피연산자의 값이 다른지 여부를 체크하여 true/false를 리턴
  - `<`: 첫번째 피연산자가 두번째 피연산자보다 작은지 여부를 리턴
  - `<=`: 첫번째 피연산자가 두번째 피연산자보다 작거나 같은지까지 여부를 리턴
  - `>`: 첫번째 피연산자가 두번째 피연산자보다 큰지 여부를 리턴
  - `>=`: 첫번째 피연산자가 두번째 피연산자보다 크거나 같은지까지 여부를 리턴

- 논리 연산자
  - `&&`: 두 피연산자가 모두 true인지 여부를 평가하며 두 피연산자 중 하나라도 false라면 false를 리턴
  - `||`: 두 피연산자 중 하나라도 true 라면 true를 리턴
  > 단락 회로 평가: &&와 || 연산을 사용할 때 첫 번째 피연산자의 결과에 따라 결과 값이 정해졌을 때 두 번째 피연산자의 평가를 하지 않는 것
  - `!`: 단항 연산자로 해당 값의 결과의 반대를 리턴

- instanceof
  - 객체(Object) 또는 배열(Array) 값을 어떠한 참조 유형에 맞는 값인지를 평가하는 연산자
  - null을 연산한다면 항상 false가 리턴
  ```java
  "Apple" instanceof String // true
  null instanceof String // false
  
  Object o = new int[]{1, 2, 3};
  o instanceof int[] // true
  ```
  > 일반적으로 instanceof를 사용하지 않는 것이 좋음

- 대입 연산자
  - 어떠한 변수에 값을 할당할 때 사용하는 연산자

- 화살표(->) 연산자
  - `->`: 람다 표현식(Lamda Expression) 이라고 하며 메소드 본문에 해당 실행 가능한 자바 코드의 익명 컬렉션
  > 함수형 프로그래밍은 간단히 말하자면 함수의 입력만을 의존해서 출력을 만드는 구조로 외부의 상태를 변경하는 것을 줄여 부작용 발생을 최소화 하는 방법론
  - 반환 타입과 메서드 이름 없이 `(Parameter 매개 변수) -> {Body 함수 몸체}` 형태로, 람다는 익명 함수의 매개변수와 리턴변수를 통해 만들어 짐
  ```java
  Runnable r = () -> {
    System.out.println("1");
    System.out.println("2");
  }

  // 코드가 한 문장이면 중괄호 생략 가능
  Runnable r = () -> System.out.println("1");
  ```

- 3항 연산자
  - `? :`: `조건 ? true일때 결과 : false 일때 결과`, if ~ else 문장을 연산자로 표현할 수 있고 조건에 따라 결과를 반환
  ```java
  public int max(int x, int y) {
    return x > y ? x : y;
  }
  ```

- 연산자 우선 순위

우선 순위 | 연산자 | 설명
| :---: | :---: | :---: |
1 | expr++ expr-- | 후위 증가/감소 연산자
2 | ++expr --expr +expr -expr ~ ! | 전위 증가/감소 연산자, 양/음 부호, 논리/비트 NOT 연산자
3 |	* ㅤ / ㅤ %	 | 곱셈/나눗셈/나머지 연산자
4 |	+ ㅤ -	 | 덧셈/뺄셈 연산자
5 |	<< ㅤ >> ㅤ >>>	 | 비트 왼쪽/오른쪽 Shift 연산자, Unsigned Shift 연산자
6 |	< ㅤ > ㅤ <= ㅤ >= ㅤ instanceof	 | 보다 작은/보다 큰/보다 작거나 같은/보다 크거나 같은 관계 연산자, instanceof
7 |	== ㅤ !=	| 와 같은/와 다른 관계 연산자
8 |	&	| 비트 AND 연산자
9 |	^	|비트 XOR 연산자
10 |	`|`	| 비트 OR 연산자
11 |	&&	| 논리 AND 연산자
12 |	`||`	| 논리 OR 연산자
13 |	? :	| 삼항 조건 연산자
14 |	= ㅤ += ㅤ -= ㅤ *= ㅤ /= ㅤ %= ㅤ &= ㅤ ^= ㅤ `|=` ㅤ <<= ㅤ >>= ㅤ >>>=	| 대입 연산자 및 복합 대입 연산자

제어문
=======
- 선택문
  - switch 문: 값을 입력 받고 그 값의 경우로 분기하여 실행하는 키워드
  ```java
  switch(domain){
    	case 1:
        break;
	    case 2:
		    break;
		    .
		    .
		    .
	    default:
		    break;
  }
  ```
  - if 문: 조건을 판단하고 참이면 if 블럭을 실행하는 키워드
  ```java
  if (expression){
    	statement;
  }
  ```
  - if else 문: 조건을 판단하고 참이면 if 블럭을 실행하고 거짓이면 else 블럭을 실행하는 키워드
  ```java
  if (expression){
    statement;
  } else {
    statement2;
  }
  ```
  - if else if 문: 여러 조건을 판단하고 if, else if 블럭 중에 참이 있으면 실행하고 아니면 else 블럭을 실행하는 키워드
  ```java
  if (expression){
    statement;
  } else if (expression2){
	  statement2;
  } 
  .
	.
	.
  else {
	  statement10;
  }
  ```
- 반복문
  - while: 조건을 검사하고 참이면 반복하는 키워드
  ```java
  while (expression){
    statement;
  }
  ```
  - do while: 명령을 최소 1번은 수행하고 조건을 검사하고 참이면 반복하는 키워드
  ```java
  do {
    statement;
  }
  while (expression)
  ```
  - for: 반복할 횟수를 지정하여 반복하는 키워드
  ```java
  for (변수 초기화; expression; statement) {
    statement;
  }
  ```
  - for each: 반복 가능한 객체가 있을 때 반복할 횟수를 제어하여 반복하는 키워드
  ```java
  for (타입 변수명 : iterable 객체) {
    statement;
  }
  ```
- 제어문
  - break: 반복문 중 반복을 종료할 수 있는 키워드
  - continue: 반복문 중 특정 조건 하에서 명령문 실행을 skip할 수 있는 키워드

클래스
=======
- 클래스: 클래스는 데이터 필드나 메소드의 모음
- 객체: 클래스에 규정된 인스턴스로서, 변수 대신 실제 값을 가짐
- 클래스 정의하는 방법
  - 클래스 구성 멤버
    - `필드(Field)`
      - 객체의 데이터(상태)가 저장되는 곳
      - 생성자와 메소드 전체에서 사용되며 객체가 소멸되기 전까지 객체와 함께 존재
    - `생성자(Constructor)`
      - 객체 생성 시 초기화
      - 생성자는 메소드와 비슷하게 생겼지만 클래스 이름으로 되어있고 리턴 타입이 없음
      - 생성자를 실행시키지 않고 클래스로부터 객체를 만들 수 없음
      - 생성자가 생성되면 Heap Area에 객체가 생성되고 객체의 주소가 리턴
      - 리턴된 객체의 주소는 클래스 타입 변수에 저장되어 객체에 접근 할 때 이용
      - 아무것도 안해도 디폴트 생성자가 만들어짐
    - `메소드(Method)`
      - 객체의 동작에 해당하는 실행 블록
      - 메소드를 호출하게 되면 중괄호 블록에 있는 코드들이 일괄적으로 실행되고 필드 읽기, 수정, 객체간 협력 수단 등 다양한 기능을 수행하기 위해 사용
    - 접근 제어자
      - public: 누구나 접근 할 수 있도록 할 때 사용
      - protected: 같은 패키지 내 그리고 상속 받은 경우에만 사용
      - package private: `기본 접근 지시자`로 같은 패키지 내에 있을 때만 접근 가능
      - private: 해당 클래스 내에서만 접근 가능
    - 클래스 제어자
      - abstract: 추상 클래스를 선언하고자 할때 사용, 이 클래스는 구현이 끝나지 않은 추상적인 형태의 클래스이므로, 객체로 생성될 수 없음
      - final: 상속이 더이상 되지 않는 클래스를 의미
  - 클래스 정의
  ```java
  public class Car{

    // 필드
    int battery;
    String engine;

    // 생성자
    Car() {...} 

    // 메소드
    void run() {...}
    void stop() {...}
  }
  ```
  
- 객체 만드는 방법 (new 키워드 이해하기)
  - 객체 생성
  ```java
  new Car();

  Car car; // 메모리에 참조변수 car를 위한 공간 생성
  car = new Car(); //  인스턴스 생성 및 대입
  Car car = new Car();
  ```
  - nwe 키워드
    - new 연산자로 생성된 객체는 `메모리 힙 영역`에 생성되고 객체의 주소를 리턴하는데 이 주소를 참조 타입인 클래스 변수에 저장
- 메소드 정의하는 방법
  - 메소드 정의
  ```java
  public class Car{
    int battery;
    String engine;

  void charge(){
        System.out.println("no charge");   
  }

  // 매개변수의 수를 모를 경우
  void charge(int... values){
    // int[] values == int...values

    for(int i = 0; i < values.length; i++){
         System.out.println("charge  "+i);   
    }
  }
  ```
  - 메서드 오버라이딩: 만약 자식의 클래스에서 부모 클래스의 메소드를 다른 방식으로 사용 및 구현하는 것
  - 메서드 오버로딩: 같은 함수 이름을 가지고 있으나 매개변수, 리턴타입 등의 특징은 다른 여러의 메소드를 정의하는 것
- 생성자 정의하는 방법
  - 생성자 정의
  ```java
  public class Car {
        int speed;
        String color;
    
    Car(){
      color = getDefaultColor();
      speed =0;
    }
    Car(String color){}
    Car(int speed){}
    Car(String color, int speed){}
    
    String getDefaultColor(){
      return "blue";
    }
  }
  ```
  - 초기화 블록
    - 클래스 초기화 블록: 클래스 변수 초기화에 쓰임
    - 인스턴스 초기화 블록: 인스턴스 변수 초기화에 쓰임
  - 다양한 제어자
    - 접근 제어자(pirvate, public ...)
    - `static`: static이 붙은 변수와 메서드는 객체가 아닌 클래스에 속함
    - `final`: final이 클래스 앞에 붙으면 해당 클래스는 상속될 수 없고 변수 또는 메서드 앞에 붙으면 수정되거나 오버라이딩 될 수 없음
    - abstract: abstract이 클래스 앞에 붙으면 추상 클래스가 되어 객체 생성이 불가하고, 접근을 위해선 상속받아야함
    - transient: 변수 또는 메서드가 포함된 객체를 직렬화할 때 무시하게하게 하는 제어자
    - `synchronized`: 메서드는 한 번에 하나의 쓰레드에 의해서만 접근 가능하게 하는 제어자
    - volatile: 해당 변수의 조작에 CPU 캐시가 쓰이지 않고 항상 메인 메모리로부터 읽게하는 제어자
- this 키워드 이해하기
  - this: 메소드나 생성자에서 현재 객체를 가리키고 있는 특별한 키워드
  - 주로 생성자와 메소드의 매개변수 이름이 필드와 동일한 경우 필드를 명시하기 위해 사용
  - 생성자 내에서 다른 생성자를 호출할 때 클래스 이름 대신 this를 사용해야함
  - 빌더 패턴 등에서 유용하게 사용할 수 있는, 현재 인스턴스의 reference를 반환해줄 때 사용
상속
=======
- 자바 상속의 특징
  - 자바에서 최상위 계층 부모 클래스는 java.lang.Object
  - 자바는 다중 상속을 지원하지 않으므로 extends 뒤에는 하나의 부모 클래스만 올 수 있음
  - 상속을 받은 클래스는 부모의 클래스에 선언되어있는 public및 protected 로 선언돼어있는 모든 변수와 메소드를 내가 가진 것 처럼 사용
- super 키워드
  - super: 부모 클래스를 지징하는 키워드
  - super(): 부모 클래스의 생성자
  - super.함수이름(): 부모 클래스의 메소드 사용 
- 메소드 오버라이딩
  - 자식 클래스에서 부모 클래스에 있는 메소드와 동일하게 선언하는 것
  > 메소드 오버로딩: 같은 함수 이름을 가지고 있으나 매개변수, 리턴타입 등의 특징은 다른 여러의 메소드를 정의하는 것
  - 부모 클래스의 메소드보다 접근 제어자를 더 좁은 범위로 변경 못함
  - 부모 클래스의 메소드보다 더 큰 범위의 예외를 선언할 수 없음
- 추상 클래스
  - 추상 클래스는 클래스를 만들기 위한 일종의 설계도로 인스턴스를 생성할 수 없는 클래스
  - 반드시 하나 이상의 추상 메서드를 포함하고 있고, 생성자와 멤버 변수 그리고 일반 메서드를 가질 수 있음
- 인터페이스
  - 추상 클래스의 일종으로 추상화정도가 높아 일반 메서드나 멤버 변수를 가질 수 없고 오로지 추상 메소드나 상수만을 멤버로 가질 수 있는 클래스를 정의하는 키워드
  - 인터페이스의 모든 멤버 변수와 메소드는 public static final이어야 하며, 이를 생략할 수도 있음
  - 다중 상속이 가능
- final 키워드
  - final 키워드: 엔티티를 한 번만 할당하겠다는 의미의 키워드
  - final 변수: 생성자나 대입연산자를 이용해 한 번만 초기화가 가능한 변수
  - final 메소드: final 메소드는 오버라이드하거나 숨길 수 없음을 의미
  - final 클래스: 해당 클래스는 상속할 수 없음을 의미하여 상속 계층에서 마지막 클래스라는 의미
- Object 클래스
  - java.lang.Object 클래스는 모든 클래스의 최상위 클래스로 기본 함수를 제공
  - clone (native 메소드): Clonable한 객체만 사용 가능한 메소드로 객체를 깊은 복사하는 메소드, `Clonable 인터페이스`의 clone 이라는 메소드를 오버라이딩해야함
  - equals: 객체의 참조값이 같은지만 비교하는 메소드
  - getClass (native 메소드): 객체의 런타임에서의 클래스(타입)을 반환
  - hashcode (native 메소드): 객체에 해당하는 해쉬코드를 만들어 반환
  - toString: toString()은 이 객체를 stirng으로 표현하는 방법을 표현하는 메소드로 기본적으로 객체의 경우 hash값이 출력
  - wait (native 메소드): 스레드를 정지 상태로 바꾸는 메소드 
  - notify (native 메소드): 정지 상태에 있는 다른 스레드를 실행 상태로 바꾸는 메소드
  - notifyAll (native 메소드): 정지 상태의 모든 스레드의 실행을 재개하는 메소드

패키지
=======
- package 키워드
  - 패키지: 클래스와 인터페이스 등의 집합을 의미
    - 파일을 묶음으로써 효율적으로 관리할 수 있으며 이름 충돌 문제도 피할 수 있음
    - 패키지 선언은 `package 패키지명`
    - 어떤 클래스를 패키지에 추가하게 되면 클래스의 이름은 `패키지명.클래스명`
  - 이름 없는 패키지
    - 자바의 모든 클래스는 반드시 하나 이상의 패키지에 포함되어야하는데, 소스 파일에 어떤 패키지 선언도 없다면 기본적은으로 하나의 이름 없는 패키지에 모아서 컴파일
- import 키워드
  - import: 다른 패키지에 접근하기 위해 사용
  ```java
  package c.javapackage;
  
  import c.javapackage.sub.Sub;
  
  public cass Package {
    public static void main(String[] args) {
        Sub.subClassSaticMethod();
        System.out.println(Sub.CLASS_NAME);     
    }
  }
  ```
  - import static: 다른 패키지의 static 한 변수와 메소드에 접근할 때 사용
  ```java
  package c.javapackage;
  
  import static c.javapackage.sub.Sub.subClassStaticMethod;
  import static c.javapackage.sub.Sub.CLASS_NAME;
  
  public cass Package {
    public static void main(String[] args) {     
        subClassSaticMethod();
        System.out.println(CLASS_NAME);
    }
  }
  ```

- 클래스 패스
  - 클래스 패스: 클래스를 찾기 위한 경로로, JVM 프로그램을 실행할 때 읽을 클래스 파일을 찾는 기준이 되는 경로(루트 폴더)
  - 클래스 패스 지정하기
    - java runtime cp/-classpath 플래그 사용
    ```java
    java -cp 폴더위치 패키지명.클래스명;패키지명.클래스명;패키지명.클래스명;...
    ```
    ```java
    java -classpath 폴더위치 패키지명.클래스명;패키지명.클래스명;패키지명.클래스명;...
    ```
    - CLASSPATH 시스템 환경 변수 지정
    ```sh
    // 쉘 커맨드에서 설정
    CLASSPATH=클래스패스경로
    ```
    ```sh
    echo $CLASSPATH
    ```
- 접근지시자
  - public: 누구나 접근 할 수 있도록 할 때 사용
  - protected: 같은 패키지 내 그리고 상속 받은 경우에만 사용
  - package private: `기본 접근 지시자`로 같은 패키지 내에 있을 때만 접근 가능
  - private: 해당 클래스 내에서만 접근 가능

인터페이스
=======
- 인터페이스: 추상클래스보다 더욱 강력한 추상화를 제공하는 도구이고, 그를 통해 다형성을 더욱 강력하게 해주는 도구
- 인터페이스 정의하는 방법
  - 멤버변수는 모두 `상수형`으로 선언되어야함
  - 메서드는 모두 `추상 메서드`로 선언되어야함
  - Java 8부터 인터페이스에 `static 메소드`를 정의할 수 있음
  - Java 8부터 인터페이스에 `default 메소드`를 정의할 수 있음
  - Java 9부터 인터페이스에 `private 메소드`를 정의할 수 있음
  ```java
  public interface [인터페이스 이름] extends [부모 인터페이스명 ...] {

		// 상수 (static final)
		static final String example = "myExample"; 
		/// static final은 생략될 수 있지만 그 의미는 유지됩니다.

		// 추상 메소드 (public abstract)
		public abstract void printExample();
		// public abstract 는 생략될 수 있지만 그 의미는 유지됩니다.
  }
  ```
- 인터페이스 구현하는 방법
  - implements 키워드 사용
  - 인터페이스가 가지고 있는 메소드를 하나라도 구현하지 않으면, 해당 클래스는 추상 클래스가 됨
  ```java
  interface Flyable{
    void fly();
  }

  interface Jumpable {
	 void jump();
  }

  class Bird implements Flyable, Jumpable {
      @Override
      public void fly() {
          System.out.println("Bird's Flying");
      }
      @Override
      public void jump() {
          System.out.println("Bird's Jumping");
      }
  }
  ```

- 인터페이스 레퍼런스를 통해 구현체를 사용하는 방법
  - 참조변수의 타입으로 인터페이스를 사용할 수 있고 이 경우 인터페이스가 가지고 있는 메소드만 사용
  ```java
  // 좋은 예. 인터페이스를 타입으로 사용했다.
  Set<Son> sonSet = new LinkedHashSet<>();

  // 나쁜 예. 클래스를 타입으로 사용했다.
  LinkedHashSet<Son> sonSet = new LinkedHashSet<>();
  ```
- 인터페이스 상속
  - extends 키워드로 (다중) 상속도 가능
  ```java
  interface Drawble {
  	void draw();
  }

  interface Flyable {
	  void perform();
  }

  interface Printable extends Drawble, Flyable {
	  void print();
  }

  class Circle implements Printable {
    
    @Override
    public void draw() {
    }
    
    @Override
    public void print() {
    }

  }
  ```
- 인터페이스의 기본 메소드 (Default Method), 자바 8
  - default 키워드를 사용하여 기본 메소드를 구현할 수 있고 기본 메소드는 구현체에서 필수로 구현할 필요가 없음
  - 이름이 같은 여러 개 디폴트 메소드가 있는 경우 오버라이딩해야함
  - 기본 메소드를 통해서 추상 클래스의 많은 기능을 대체해주었지만 상태 정보를 변수에 저장하는 경우 추상 클래스가 필요
  ```java
  // 인터페이스
  public interface PrintableAnimal extends Animal, Comparable<PrintableAnimal> {
      // 자신의 메소드를 기본 메소드로 구현
      default void print() {
          System.out.println("이름 : " + getName());
          System.out.println("다리개수 : " + getLegs());
      }

      // Comparable 인터페이스의 메소드를 상속하여 기본 메소드 구현
      @Override
      default int compareTo(PrintableAnimal o) {
          return getLegs() - o.getLegs();
      }
  }

  // 구현체
  public class Snake implements PrintableAnimal {

      @Override
      public String getName() {
          return "뱀";
      }

      @Override
      public int getLegs() {
          return 0;
      }

  }

  // 사용하기
  Snake snake = new Snake();
  snake.print(); // PrintableAnimal의 기본 메소드 사용
  ```
- 인터페이스의 static 메소드, 자바 8
  - static 메소드로 추가가 가능하여 디폴트 메소드처럼 사용 가능
  - static 메소드이므로 상속이 불가능
  ```java
  public interface PrintableAnimal extends Animal, Comparable<PrintableAnimal> {

    static String getDescription() {
        return "출력기능이 있는 동물 인터페이스";
    }
  }

  System.out.println(PrintableAnimal.getDescription()); 
  ```
- 인터페이스의 private 메소드, 자바 9
  - private 메소드로 추가가 가능하여 디폴트 메소드처럼 사용이 가능
  - private 메소드이므로 구현체에서 구현할 수 없고 자식 인터페이스에서도 상속이 불가능
  ```java
  public interface PrintableAnimal extends Animal, Comparable<PrintableAnimal> {

    static String getDescription() {
        return "출력기능이 있는 동물 인터페이스";
    }

    // 자신의 메소드를 기본 메소드로 구현
    // private 메소드 사용
    default void print() {
        printName();
        printLegs();
    }
    
    // private 메소드로 기본 메소드에서 사용할 로직 분리 1
    private void printName() {
        System.out.println("이름 : " + getName());
    }
    
    // private 메소드로 기본 메소드에서 사용할 로직 분리 2
    private void printLegs() {
        System.out.println("다리개수 : " + getLegs());
    }

    // Comparable 인터페이스의 메소드를 상속하여 기본 메소드 구현
    @Override
    default int compareTo(PrintableAnimal o) {
        return getLegs() - o.getLegs();
    }

    default void otherDefaultMethod() {
        System.out.println("other default method");
    }
  }
  ```
예외처리
=======
- 자바에서 예외 처리 방법 (try, catch, throw, throws, finally)
  - try-catch: try에서 시도를 하고 catch애서 예상되는 예외를 처리하는 방법
  ```java
  try {
    return dividend % divisor; // 예외가 발생할 가능성이 있는 코드.
  }
  catch (ArithmeticException e) {
    throw new DivideByZeroException(); // 예외 처리
  }
  catch (RunTimeException e) {
    throw new DivideByZeroException(); // 예외 처리
  }
  ```
  > 순서대로 catch문을 순회하기 때문에 만약 객체의 super calss가 먼저 등장하게 되면, 어떤 한 clause는 영영 실행이 안될 수 있어서 compile error를 냄
  - try-catch-finally: try-catch에서 finally는 항상 실행될 코드를 목적으로 사용
  ```java
  try {
    return dividend % divisor; // 예외가 발생할 가능성이 있는 코드.
  }
  catch (ArithmeticException e) {
    throw new DivideByZeroException(); // 예외 처리
  }
  finally {
	  System.out.println("done");
  }
  ```
  - try-with-resoucre: try 구문이 종료되면 해제를 도와주는 기능으로 AutoClosable이라는 인터페이스를 반드시 구현해서, 자바가 try 구문 후에 close() 라는 메소드를 사용
  ```java
  try (
      FileInputStream is = new FileInputStream("file.txt");
      BufferedInputStream bis = new BufferedInputStream(is)
  ) {
      int data = -1;
      while ((data = bis.read()) != -1) {
          System.out.print((char) data);
      }
  } catch (IOException e) {
      e.printStackTrace();
  }
  ```
  - throw: throw 키워드를 사용해 예외를 발생시킬 수 있음
  ```java
  throw new Exception();
  ```
  - throws: throws를 메소드에 붙임으로서, 해당 메소드에서 throw가 발생된다는것을 선언해줄 수 있어 이 메소드를 사용하는 클라이언트에게 어떤 예외를 처리해야하는지 알려줌
  ```java
  static File createFile(String fileName) throws Exception {
    if (fileName == null || fileName.equals("")) {
        throw new Exception("File not found.");
    }

    File f = new File(fileName);
    f.createNewFile();
    return f;
  }
  ```
- 자바가 제공하는 예외 계층 구조
  - 구조
  https://media.geeksforgeeks.org/wp-content/uploads/Exception-in-java1.png
  - Checked Exception: Checked Exception은 확인된 예외로 컴파일 시점에 확인되는 예외로 반드시 예외 처리해야하는 예외(IOException, SQLException...)
  - Unchecked Exception: Checked Exception과 반대로 컴파일 시점에 확인할 수 없는 예외로 RuntimeException을 상속한 예외(NPE, IndexOutOfBoundException, IllegalArgumentException...)
- Exception과 Error의 차이는?
  - Exception: 문제가 발생한다고 하면, 개발자가 대응할 수 있는 문제로 예외 처리가 가능
  - Error: 문제가 발생한다고 하더라도 개발자가 대응할 수 없는 문제로 예외 처리가 불가능
- 커스텀한 예외 만드는 방법
  - Checked Exception 커스텀 만들기: Exception 클래스를 상속
  - Unchecked Exception 커스텀 만들기: RuntimeException 클래스를 상속

멀티쓰레드
=======
- 쓰레드
  - 하나의 프로세스 내에서 더 작은 단위로 독립적으로 실행시키며, 제어가 가능한 흐름
  - 자바에서 쓰레드를 만드는 방법은 크게 Thread 클래스를 상속받는 방법과 Runnable인터페이스를 구현하는 방법이 존재
- Thread 클래스와 Runnable 인터페이스
  - java.lang 패키지의 Thread라는 클래스를 상속하여 스레드를 만들 수 있음, run 이외의 다른 것들을 오버라이딩할 필요가 있으면 이를 사용
  ```java
  class ThreadExample extends Thread {

    @Override
    public void run() {
        System.out.println("thread started");
   }
  }

  public static void main(String[] args) { // 메인 메소드에서 쓰레드 시작.
    Thread th = new ThreadExample(); // 쓰레드 생성.
    th.start(); // 쓰레드 시작.
  }
  ```
  - java.lang 패키지의 Runnable 인터페이스를 구현하여 스레드를 만들 수 있음, 대부분의 경우 run 만 오버라이딩하여 스레드를 만들 수 있으므로 이를 보통 사용
  ```java
  class ThreadExample implements Runnable {

    @Override
    public void run() {
        System.out.println("thread started");
    }
  }

  public static void main(String[] args) { // 메인 메소드에서 쓰레드 시작.
    Thread th = new Thread(new ThreadExample()) // Runnable 객체를 Thread에 주입.
    th.start(); // 쓰레드 시작.
  }
  ```
  > runnable interface에는 run() 메소드가 한개만 존재하므로, java 8의 람다를 이용해 아래와 같이 생성할 수 있음
- 쓰레드의 상태
  - 자바는 스레드 상태를 나타내는 `Thread.State`라는 Enum을 제공
  - `NEW`: 스레드가 생성되었지만 start() 메소드가 호출되지 않은 상태로 모든 스레드는 이 상태에서 시작
  - `RUNNABLE`: 쓰레드가 실행중이거나 운영체제가 예약하여 실행이 가능할 때
  - `BLOCKED`: 동기화된(synchronized) 메소드 또는 블록에 들어갈 수 있도록 락을 얻으려고(aquire) 대기 중이기 때문에 스레드가 샐행중이 아닌 상태
  - `WAITING`: Object.wait(), Thread.join() 메소드가 호출되어 스레드가 실행되고 있지 않는 상태
  - `TIMED_WAITING`: Thread.sleep()를 호출했거나 타임아웃을 사용하여 Object.wait(), Thread.join()을 호출했을 때 스레드가 실행되고 있지 않는 상태
  - `TERMINATED`: run() 메소드가 정상적으로 종료되었거나 예외가 발생하여 스레드가 실행이 완료된 상태
- 쓰레드 상태 제어 메소드
  - sleep(millis): 현재 실행중인 쓰레드를 Sleeping pool로 이동시키고 안에 있는 시간 이후, 다시 Runnable pool로 이동
  - join(): Join메소드가 실행되면 이는 joining pool에 들어가게 되며, 모든 수행이 끝나면, 그 이후에 Runnable pool에 들어갈 수 있음
  - wait(): Object 클래스에 소속되어 있는 메소드, 실행하면 그 쓰레드는 모니터링 락을 반환하고, 객체의 wait pool로 들어감
  - notify(), notifyall(): Object 클래스에 소속되어 있는 메소드, wait pool에 있는 쓰레드는 다른 객체의 notify() 콜로 깨움
  - yield(): 쓰레드 내부에서 yield()를 사용하면, 쓰레드를 점유할 기회를 양보하여 다른 쓰레드가 먼저 선택되도록 할 수 있음
  - start() : 쓰레드를 구동 시킴
  - run() : 쓰레드 수행 코드가 들어가는 메소드
- 쓰레드의 우선순위
  - Thread 클래스의 getPriority(), setPriority() 메소드를 사용하여 스레드의 우선순위를 컨트롤할 수 있음
  - 자바에서 생성된 모든 쓰레드는 기본적으로 5의 우선순위를 가짐
- Main 쓰레드
  - 메인 쓰레드는 java 프로그램이 시작 될 때, JVM에 의해 생성되는 쓰레드
  - 메인 쓰레드를 시작으로 `자식 쓰레드들이 쓰레드를 생성해 나감`
  > 데몬 쓰레드: 데몬(Daemon)이란 보통 리눅스와 같은 유닉스계열의 운영체제에서 백그라운드로 동작하는 프로그램인데, 데몬 쓰레드는 이와 같이 보조적인 역할로 사용되는 쓰레드 thread.setDaemon(true);로 데몬으로 설정 가능
- 동기화
  - 멀티 스레드 프로그램은 여러 스레드가 동일한 리소스에 접근하려고 할 때 예기치 않는 결과를 생성할 수 있어 처리가 필요함
  - 자바는 동기화된 블록을 사용하여 스레드를 생성하고 작업을 동기화하는 방법을 제공하는데 이때 `synchronized` 키워드를 사용
  - 모든 객체에는 고유락/모니터락이 존재하는데, synchronized를 사용하면 쓰레드는 syncronized 범위에 접근 시에 객체에 대한 락을 가져감
  ```java
  /**
  * 출금만 가능한 계좌
  */
  public class Account {

      private int balance;

      public Account(int money) {
          this.balance = money;
      }

      private boolean hasBalance() {
          return balance > 0;
      }

      public synchronized void withdraw(int money) {
          if (!hasBalance()) {
              System.out.println("Insufficient balance");
              return;
          }

          balance -= money;
          System.out.println("balance is : " + balance);
      }
  }

  /**
  * 100원씩 출금하는 스레드
  */
  public class AccountWithdrawThread extends Thread {

      private final Account account;

      public AccountWithdrawThread(Account account) {
          this.account = account;
      }

      @Override
      public void run() {
          account.withdraw(100);
      }
  }

  public class AccountApp {
      public static void main(String[] args) {
          Account account = new Account(1000);

          // 스레드 여러개 만들어서 실행하기
          IntStream.range(0, 15).forEach(i -> new AccountWithdrawThread(account).start());
      }
  }
  ```
- 데드락
  - 데드락(Deadlock) 또는 교착상태란 최소 두개의 스레드가 다른 리소스에 대해 락(lock)을 유지하고 있고 둘 다 다른 리소스가 작업을 완료할 때까지 기다리는 상황
  ```java
  Object lock1 = new Object();
  Object lock2 = new Object();

  Thread t1 = new Thread( () -> {
        while(true){
              synchronized (lock1) {
                  try {
                      Thread.sleep(100);
                  } catch (InterruptedException e) {
                      e.printStackTrace();
                  }
                  synchronized (lock2) {
                      System.out.println("lock1->lock2");
                  }
              }
          }
  });

  Thread t2 = new Thread( () -> {
      while(true){
          synchronized (lock2) {
              synchronized (lock1) {
                  System.out.println("lock2->lock1");
              }
        }
      }
  });

  t1.start();
  t2.start();
  ```
  - 데드락이 발생하는 필수 조건들
    - 상호 배제(Mutual Exclusion): 자원은 한 번에 한 프로세스만이 사용할 수 있어야함
    - 점유 대기(Hold and Wait): 자원을 점유하면서도 다른 프로세스가 사용하고 있는 자원에 대해 대기
    - 비선점(No Preemption): 다른 프로세스에 할당된 자원은 사용이 끝날 때까지 강제로 뺏을 수 없음
    - 순환 대기(Circular Wait): 락 자원 획득이 T1(A -> B), T2(B -> C), T3(C -> D), T4(D -> A) 로 되어 있고, 서로가 물려 있는 상태를 뜻함

Enum
=======
- enum
  - Enum은 제한된 기능을 까지고 허용하는 값이 적은 `클래스`의 변형된 유형
  - `java.lang.Enum 클래스`를 자동으로 상속하는데, Enum 클래스는 name과 ordinal 필드를 갖고 있고 name 필드에는 정의한 열거 상수명이 String이 ordinal에는 열거 상수의 정의 순서가 int로 들어가 있음
ordinal에는 열거 상수의 정의 순서가 int로 있음
  - 타입 세이프티를 보장
- enum 정의하는 방법
  - 열거 상수
  ```java
  public enum {
	  MONDAY,TUESDAY,WEDNSDAY;
  }
  ```
  - 열거 필드와 메소드
  ```java
  public enum Color {
    // 생성자 파라미터 대로 적용
    RED("빨강"), GREEN("초록"), BLUE("파랑");

    // 필드
    private String desc;

    // 메소드
    public String getDesc() {
        return desc;
    }

    // 생성자
    Color(String desc) {
        this.desc = desc;
    }
  }
  ```
- enum이 제공하는 메소드
  - name() 메소드: 필드명을 그대로 가져옴
  - ordinal() 메소드: 거형의 순서를 가져옴
  - values() 메소드: 해당 Enum 클래스의 모든 열거 상수 목록을 리턴
  - valueOf(String key) 메소드: Enum의 기본 필드인 name 필드를 기반으로 동일한 열거 상수를 반환하고 존재하지 않을 때엔 IllegalArgumentException 예외를 던짐
- EnumSet
  - EnumSet은 Enum과 함께 사용할 수 있는 특별한 Set 구현체
  ```java
  public class Text {
    public enum Style { BOLD, ITALIC, UNDERLINE, STRIKETHROUGH }
    
    // 어떤 Set을 넘겨도 되나 EnumSet이 가장 좋다.
    // 이왕이면 Set Interface로 받는게 좋은 습관이다.
    public void applyStyles(Set<Style> styles) {...}
  }
  text.applyStyles(EnumSet.of(Style.BOLD, Style.ITALIC));
  ```
- EnumMap
  - EnumMap은 맵의 키의 타입을 열거형으로 가지는 특수한 Map
  ```java
  EnumMap<Color, String> colorStringEnumMap = new EnumMap<>(Color.class);

  colorStringEnumMap.put(Color.RED, "빨간색");
  colorStringEnumMap.put(Color.BLUE, "파란색");
  colorStringEnumMap.put(Color.GREEN, "초록색");

  colorStringEnumMap.forEach((k, v) -> {
      System.out.println("key: " + k + ", value: " + v);
  });
  ```

애노테이션
=======
- 애노테이션: 자바의 특수한 인터페이스 이며 기본적으로 이름처럼 주석을 다는 역할로 일반적인 주석과는 다르게 추가적인 작업을 덧붙일 수 있으며 IDE에 유용한 힌트를 줌
> 메타 애노테이션: 개발자가 새로운 애노테이션을 만들 때 사용할 위치나 자바 컴파일러나 런타임에서 어떻게 처리될지 정책을 명시하는 애노테이션
- 애노테이션 정의하는 방법
  - @interface 키워드를 사용하여 정의 가능
  ```java
  @Retention(RetentionPolicy.SOURCE)
  @Target(ElementType.METHOD)
  public @interface Logger {
      String value() default "";
  }
  ```
  - 빌트인 어노테이션
    - @Override: 현재 메서드가 슈퍼 클래스의 메서드를 오버라이드한 것임을 컴파일러에게 명시할 때 사용
    - @Deprecated: 다음 버전에서 사용되지 않을 때 명시해서 사용
    - @SupperessWarnings: 경고를 제거하는 어노테이션으로 개발자가 의도를 가지고 설계를 했는데 컴파일은 이를 알지 못하고 컴파일 경고를 띄울 수 있기 때문에 이를 제거할 때 사용
    - @FunctionalInterface: Java 8이상에서 사용가능하고 컴파일러에게 함수형 인터페이스라는 것을 알릴 때 사용
    - @SafeVarargs: Java 7이상에서 사용가능하고 제네릭같은 가변인자 매개변수 사용시 경고를 무시할 때 사용
    - @Native: 네이티브 메소드에서 참조되는 상수 앞에 붙일 때 사용
  - 애노테이션을 선언하기 위한 메타 애노테이션 종류
    - @Target, @Retention, @Documented, @Inherited ...
- @Retention
  - @Retention 애노테이션은 자바 컴파일러와 자바 런타임이 커스텀 애노테이션을 어떻게 처리해야하는지 알려주는 역할
  - RetentionPolicy 종류
    - SOURCE : 소스 상에서만 애노테이션이 보이고 컴파일 되면 사라짐
    - CLASS : 애노테이션이 클래스 파일에 존재하지만 JVM을 통한 자바 런타임이 접근할 수 없음
    - RUNTIME : 자바 런타임이 애노테이션을 접근할 수 있고 그를 통해 무언가 추가적인 작업이 가능함을 의미
  ```java
  @Target(ElementType.METHOD)
  @Retention(RetentionPolicy.RUNTIME)
  public @interface Logger {
      String value() default "";
  }
  ```
- @Target
  - @Target 애노테이션은 자바 컴파일러가 애노테이션이 어디에 적용될 지 결정하기 위해 사용
  - ElemType 요소
    - CONSTRUCTOR: 생성자 선언 시
    - FIELD: enum 상수를 포함한 필드 값 선언 시
    - LOCAL_VARIABLE: 지역변수 선언 시
    - METHOD: 메소드 선언 시
    - PACKAGE: 패키지 선언 시
    - PARAMETER: 매개 변수 선언 시
    - TYPE: 클래스, 인터페이스, Enum 등 선언시
  ```java
  @Target({ElementType.METHOD, ElementType.TYPE}) // 메소드와 타입에 애노테이션 설정 가능
  @Retention(RetentionPolicy.RUNTIME)
  public @interface Logger {
    String value() default "";
  }
  ```
- @Documented
  - @Documented 애노테이션은 Javadoc에 해당 애노테이션 정보를 표시하기 위해 사용
  ```java
  @Target(ElementType.TYPE)
  @Retention(RetentionPolicy.RUNTIME)
  @Documented
  public @interface Logger {
      String value() default "";
  }
  ```
- 애노테이션 프로세서
  - 자바 컴파일러의 컴파일 단계에서, 유저가 정의한 어노테이션의 소스코드를 분석하고 처리하기 위해 사용되는 훅
  - 컴파일 타임에 조작이 완료된 상황이기 때문에 런타임 비용이 없음
  - javax.annotation.processing.Processor 인터페이스를 구현하거나 자바가 제공하는 기본적인 추상 클래스인 AbstractProcessor를 사용하여 등록할 수 있음
  ```java
  public class LoggerProcessor extends AbstractProcessor {

    /**
     * 이 프로세서로 처리할 애노테이션
     */
    @Override
    public Set<String> getSupportedOptions() {
        return Set.of(Logger.class.getName());
    }

    /**
     * 어떤 소스코드 버전을 지원할 것인지 명시 (필요하지 않다면 재정의하지 않아도 됨)
     */
    @Override
    public SourceVersion getSupportedSourceVersion() {
        return SourceVersion.latestSupported();
    }

    /**
     * 애노테이션을 처리하기
     */
    @Override
    public boolean process(Set<? extends TypeElement> annotations, RoundEnvironment roundEnv) {
        Set<? extends Element> elements = roundEnv.getElementsAnnotatedWith(Logger.class);

        elements.forEach(el -> {
            if (el.getKind() != ElementKind.METHOD) {
                processingEnv.getMessager().printMessage(Diagnostic.Kind.ERROR, "Cannot use this annotation!"); // 애노테이션이 메소드에 붙어있지 않다면 에러 발생!
            } else {
                processingEnv.getMessager().printMessage(Diagnostic.Kind.NOTE, "Processing...");
            }
        });

        return true; // 애노테이션이 이 프로세서에 특화되어있다면 true, 다른 프로레서에서도 처리가 가능하다면 false
    }
  }
  ```

IO
=======
- 스트림 (Stream) / 버퍼 (Buffer) / 채널 (Channel) 기반의 I/O
  - 스트림(Stream): I/O 스트림(Stream)은 디스크 또는 기타 소스의 순차적 바이트 스트림을 처리하는 방법으로 스트림은 `단방향 통신`만 가능하고 그 때문에 입출력을 모두 처리하려면 입력 스트림과 출력 스트림 모두 필요
  > 자바8에 추가된 컬렉션 API의 Stream과 다름
  - 버퍼(Buffer): byte, char, int 등 기본 데이터 타입을 저장할 수 있는 저장소로, 배열과 마찬가지로 제한된 크기에 순서대로 데이터를 저장하는데 채널을 통해 소켓, 파일 등에 데이터를 전송할 때나 읽어올 때 버퍼를 사용
  - IO와 NIO
    - IO: `스트림`에서 read() 와 write() 가 호출이 되면, 데이터가 입력되고 데이터가 출력되기 전까지 스레드는 블로킹 상태로 처리
    - NIO: 자바의 1.4버전부터 추가된 API 로 비동기 방식 및 논블로킹 처리가 가능하며, 스트림이 아닌 `채널`을 사용하여 `양방향 입출력`이 가능
- InputStream과 OutputStream
  - InputStream과 OutputStream은 스트림의 핵심적인 API로 이 둘은 모두 데이터를 바이트(byte) 단위로 입출력을 하는 스트림으로 다양한 구현체가 존재
  - InputStream과 핵심 메소드
  ```java
  // 핵심 메소드
  public abstract int read() throws IOException;
  public int read(byte b[]) throws IOException;
  public int read(byte b[], int off, int len) throws IOException;
  ```
  - OutputStream 핵심 메소드
  ```java
  // 핵심 메소드
  public abstract void write(int b) throws IOException;
  public void write(byte b[]) throws IOException;
  public void write(byte b[], int off, int len) throws IOException;
  ```
  - 종류
  |입력 스트림|출력 스트림|종류|
  |------|---|---|
  |FileInputStream|FileOutputStream|파일|
  |ByteArrayInputStream|ByteArrayOutputStream|메모리(바이트 배열)|
  |PipedInputStream|PipedOutputStream|프로세스간 통신|
  |AudioInputStream|AudioOutputStream|오디오 장치|

- Byte와 Character 스트림
  - Byte 스트림: 1바이트 단위로 데이터를 처리하는 스트림으로 일반적인 스트림
  - Character 스트림: 바이트가 아닌 문자(Character) 단위로 처리하는 스트림으로 개발자에게 더 친숙하고 인코딩이나 유니코드 등의 문제를 숨긴 API를 제공하며 Reader, Writer 클래스를 사용
  - 바이트기반과 문자기반 스트림 비교
  |바이트 기반 스트림|문자 기반 스트림|
  |--------|----------|
  |FileInputStream | FileReader |
  |FileOutputStream | FileWriter |
  |ByteArrayInputStream | CharArrayReader |
  |ByteArrayOutputStream | CharArrayWriter |
  |PipedInputStream | PipedReader |
  |PipedOutputStream | PipedWriter |
  |StringBufferInputStream(deprecated) | StringReader |
  |StringBufferOutputStream(deprecated) | StringWriter |

- 표준 스트림 (System.in, System.out, System.err)
  - System.out: 콘솔에 출력하기 위함
  - System.in: 키보드로 입력을 받기 위함
  - System.err: 에러 출력을 위함
- 파일 읽고 쓰기
  - 텍스트 파일의 경우, 문자 스트림 클래스를 사용하면 되고, 바이너리 파일인 경우, 바이트 스트림을 기본적으로 사용
  - 입출력 효율을 위해 Buffered 계열의 보조 스트림을 함께 사용하는게 좋음
  ```java
  // InputStream, OutputStream
  try (InputStream is = new FileInputStream("input.png");
     OutputStream os = new FileOutputStream("output.png")) {
    int line;
    while ((line = is.read()) > -1) {
        os.write(line);
    }
  } catch (IOException e) {
      e.printStackTrace();
  }
  ```
  ```java
  // Reader, Writer 사용
  try (BufferedReader in = new BufferedReader(new FileReader("input.txt"));
     BufferedWriter out = new BufferedWriter(new FileWriter("output.txt"))) {
    String line;
    while ((line = in.readLine()) != null) {
        out.write(line);
    }
  } catch (IOException e) {
      e.printStackTrace();
  }
  ```

제네릭
=======
- 제네릭 사용법
  - 타입(Class, Interface)들을 정의할 때 타입을 파라미터로 쓸수 있게 하는 것으로 컴파일 타임에 타입 의존성을 최대한 늦춰서 여러 타입을 받을 수 있게 하는 기능
  - primitive type은 Object를 상속받지 않으므로 제네릭스 사용 불가
  - 컴파일 타임에 타입 의존성을 체크하므로 static 변수에는 사용 불가
  - List<E>의 raw type이란 List인데, 타입 매개변수를 쓰지 않은 경우를 말하며 raw type은 사용하면 안됨
  ```java
  // 제네릭 클래스 선언
  class MyArray<T>{
    T element;
    void setElement(T element){this.element = element;}
    T getElement(){return element;}
  }
  // <T>는 다양한 타입을 넣어서 사용할 수 있다.
  // T에 값이 들어온 이후에는 그 타입만 쓸 수 있다.
  ```
  ```java
  // 제네릭 클래스 사용
  MyArray<Integer> myArr  = new MyArray<Integer>();    
  ```
  ```java
  // 제네릭 메소드 선언
  public class Test {
    public <T> Person<T> naming(T t) { }
	  }
  }
  // 메소드에서 별도로 제네릭을 쓰고 싶다면 <T>라는것으로 제네릭을 쓴다고 표기해준다. (타입을 먼저 명시)
  // 타입을 파라미터로 받거나 리턴할 때 사용
  ```
  ```java
  Person<String> resultMethod = naming("My Name is...");
  ```
- 제네릭 주요 개념 (바운디드 타입, 와일드 카드)
  - 타입 파라미터: 제네릭에서 타입을 파라미터로 지정하는 것으로 `<T>`를 뜻하며 메소드 파라미터는 값(Value)이고, 타입 파라미터는 타입(Type)
  ```java
  public class Person<T> {
    private T t;
    public void set(T t) {
    	this.t = t;
    }
    public T get() {
    	return t;
    }
  }
  ```
  - 멀티 타입 파라미터: 제네릭에서 두 개 이상의 타입 파라미터를 지정하는 것
  ```java
  public class Person<T, M> { }
  ```
  - 제네릭 타입: 타입 파라미터를 가지는 제네릭 클래스와 제니릭 인터페이스를 의미
  - 바운디드 타입: 메소드의 파라미터로 상위타입 또는 상위타입의 하위 클래스 타입의 인스턴스만 가지게하는 기능으로 상위 타입은 클래스와 인터페이스 모두 가능
  ```java
  public class Wrapper<T> {

      private final T value;

      public Wrapper(T value) {
          this.value = value;
      }
  }

  Wrapper<String> wrapper1 = new Wrapper<>();
  Wrapper<Integer> wrapper2 = new Wrapper<>();
  }
  ```
  ```java
  public class Wrapper<T extends Number> {
    private T value;

    public byte getByteValue() {
        return value.byteValue();
    }
  }

  Wrapper<String> wrapper1 = new Wrapper<>(); // 컴파일 에러 발생
  Wrapper<Integer> wrapper2 = new Wrapper<>();
  ```
  - 와일드 카드: 타입 파라미터에 구체적인 값을 제공하지 않고 모든 타입을 의미하는 값을 넣고 싶을 때 사용하며 와일드카드는 물음표(?)로 나타냄
  ```java
  List<?> list = Arrays.asList("alan", 1, 100L, new User("bsw", "bsw@ss.com"));

  List<?> hobbies = new ArrayList<String>();
  ```
- Erasure
  - 제네릭이 없는 컬렉션과 제네릭이 추가된 버전의 컬렉션이 함께 사용될 때 호환성 문제를 해결하기 위해 만든 기능
  - 제네릭 타입 파라미터는 컴파일이 되면 없어지고 바이트코드에 반영되지 않음

랑다식
=======
- 람다식
  - 람다식은 메서드를 하나의 식으로 표현하는 선언적 프로그래밍의 방법으로 원래의 자바는 익명 클래스를 이용하여 익명 구현 객체를 사용했던 방식을 함수형 프로그래밍을 도입하면서 가단하게 표현하게 만든 방법
  - 보통의 메서드와 달리 이름이 없음
  - 보통의 메서드와 달리 메서드가 아닌 함수이므로 클래스에 종속하지 않으며 어느곳에 종속적이지 않음
  - 매개변수의 인자가 될 수 있고, 반환값이 될 수 있고, 자료구조에 담길 수 있음
  - 익명 클래스는 새로운 scope를 갖지만, 람다는 람다를 감싸고있는 전체 scope를 공유
- 람다식 사용법
  - 기본 : (int num) -> {System.out.println(num);} 
  - 단일 실행문은 중괄호 제거 : (int num) -> System.out.println(num); 
  - 단일 인자는 타입 생략 : (num) -> System.out.println(num); 
  - 단일 인자는 소괄호 제거 : num -> System.out.println(num); 
  - 인자가 없으면 소괄호 필수 : () -> System.out.println("매개변수 없음"); 
  - 인자가 여러개면 소괄호 필수 : (x, y) -> System.out.println(x, y); 
  - 인자가 없고 반환값이 있으면 : () -> {return value;}; 실행코드가 return문 뿐이면 return 키워드 생략 가능 : () -> value; 
  - 매개변수, 리턴타입 둘다 있으면 : (x, y) -> x+y;

- 함수형 인터페이스: 함수형 인터페이스는 default 메소드가 아닌 1개의 추상 메소드만을 갖고 있는 인터페이스
  - @FunctionalInterface를 통해서 커스텀 함수형 인터페이스 정의 및 람다 구현 가능
  ```java
  // 함수형 인터페이스
  @FunctionalInterface
  public interface MyListener {
      void listen(String data);
  }

  // 함수형 인터페이스를 파라미터로 받는 메소드
  public void onAction(MyListener listener) {
      listener.listen("data");
  }

  // 함수형 인터페이스 람다로 구현
  MyListener listener = data -> System.out.println("listening data : " + data);

  // 함수 실행
  onAction(listener);
  ```
  - 기본 함수형 인터페이스의 종류
    - Function<T,R> : T 타입을 받아서 R로 변환하는 함수 인터페이스
      - R apply(T t);
    - BiFunction<T,U,R> : T와 U를 받아 R로 리턴하는 함수 인터페이스
      - R apply(T t, U u);
    - Consumer<T> : T타입을 단순하게 받는 함수 인터페이스
      - void accept(T t);
    - Supplier<T> : T타입을 제공하는 함수 인터페이스
      - T get();
    - Predicate<T> : T타입을 받아서 boolean으로 리턴하는 함수 인터페이스
      - boolean test(T t);
    - UnaryOperator<T> :  동일한 타입의 한개를 받아서, 같은 타입으로 리턴하는 경우 (Function <T,T>를 상속함)
    - BinaryOperator<T>: 동일한 타입의 입력값 두개 받아서, 같은 타입으로 리턴하는 경우 (BiFunction<T,T,T> 상속)

- Variable Capture
  - 람다식에서 내부의 파라미터를 제외한 외부의 변수를 참조하는 것
  - 변수의 제약 조건
    - 지역변수는 final 변수이어야 함
    - 지역변수는 final 변수가 아니라면 값이 재할당 되지 않아야 함(재할당된 값을 람다식에서 사용하고 싶다면 해당 값을 다른 변수로 할당하여 처리 가능)
    - 인스턴스 변수는 final 변수가 아니여도 가능하고 재할당이 되도 상관 없음 
  ```java
  public class LambdaApp {
    
    public void run() {
        final String str = "this is local variable"; // final 변수
        int num = 10; // final은 아니지만 정의 이후 재할당 되지 않는 변수

        onAction(data -> {
            System.out.println("str : " + str);
            System.out.println("num : " + num);
        });
    }

    public void onAction(MyListener listener) {
        listener.listen("data");
    }

    public static void main(String[] args) {
        LambdaApp app = new LambdaApp();
        app.run();
    }
  }
  ```
- 메소드 레퍼런스, 생성자 레퍼런스
  - 람다에서 조금 더 간결한 문법을 사용할 수 있는 방법으로써 기존 메소드를 람다식으로 사용하는 방법
  ```java
  // 함수형 인터페이스
  @FunctionalInterface
  public interface ButtonClickListener {
      void onClick(String data);
  }

  public class Button {
      // 함수형 인터페이스를 받는 메소드
      public void click(ButtonClickListener listener) {
          listener.onClick(data);
      }
  }

  // 람다 형태
  Button button = new Button();
  button.click(data -> data.length()); // data의 메소드 사용
  button.click(data -> System.out.println(data)); // data를 파라미터로 사용
  button.click(data -> Integer.parseInt(data)); // 스태틱 메소드에서 data를 파라미터로 사용  
  ```
  ```java
  // 메소드 레퍼런스 형태
  Button button = new Button();
  // Unbound Method Reference
  button.click(String::length); 
  // Bound Method Reference
  button.click(System.out::println);
  // Static Bound Method Reference
  button.click(Integer::parseInt); 
  ```
  ```java
  // 기존 람다식
  button.click(data -> new StringBuilder(data));
  ```
  ```java
  // 생성자 레퍼런스 형태
  button.click(StringBuilder::new);
  ```
