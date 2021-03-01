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


연산자
=======


제어문
=======


클래스
=======


상속
=======


패키지
=======


인터페이스
=======


예외처리
=======


멀티쓰레드
=======


Enum
=======


애노테이션
=======


IO
=======


제네릭
=======


랑다식
=======

