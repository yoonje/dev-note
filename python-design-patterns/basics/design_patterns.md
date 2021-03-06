# 디자인 패턴
디자인 패턴이란 객체지향 프로그래밍에서 소프트웨어를 설계할 때 자주 발생하는 고질적인 문제들을 해결하기 위해 재사용할 수 있는 소프트웨어 개발 방법이다.

### 생성 패턴
객체가 생성되는 방식에 대한 디자인 설계 방법으로 싱글톤 패턴, 팩토리 패턴이 대표적이다.

### 구조 패턴
클래스 간의 관계와 구조에 대한 디자인 설계 방법으로 어뎁터 패턴, 프록시 패턴, 퍼사드 패턴이 대표적이다.

### 행위 패턴
객체 간의 상호 작용에 대한 디자인 설계 방법으로 옵서버 패턴, 커맨드 패턴, 템플릿 패턴, 상태 패턴이 대표적이다.

### 싱글턴 패턴(생성 패턴)
- 싱글턴 패턴(Singleton pattern)을 따르는 클래스는, 생성자가 여러 차례 호출되더라도 실제로 생성되는 객체는 하나이고 최초 생성 이후에 호출된 생성자는 최초의 생성자가 생성한 객체를 리턴한다. 이와 같은 디자인 유형을 싱글턴 패턴이라고 한다.
- 주로 공통된 객체를 여러 개 생성해서 사용하는 DBCP(DataBase Connection Pool)와 같은 상황에서 메모리 낭비를 방지하는데에 탁월하다.
- 클래스 생성자에서 초기 생성자 호출과 2번째 생성자 호출 이후를 분리한다. 초기 생성일 경우 생성자를 통해서 인스턴스를 만든다. 그러나 2번째 이후부터는 기존 인스턴스가 있는지 확인한 이후에 기존 인스턴스가 있으면 그 인스턴스를 리턴해준다.
- 게으른 초기화: 싱글턴 패턴에서 멀티스레딩을 적용하면 객체가 2개 이상 생기는 경우가 생길 수 있다. 이를 막기 위해서 게으른 초기화 기법을 사용한다. 객체를 꼭 필요한 시점에서 하나만 생성하는 것이다.

### 팩토리 패턴(생성 패턴)
- 팩토리 패턴은 객체를 생성하는 인터페이스를 정의하는데, 어떤 클래스의 인스턴스를 만들지에 대해서는 서브 클래스에서 결정하게 만든다. 즉, 팩토리 패턴을 이용하면 클래스의 인스턴스를 만드는 일을 서브 클래스에서 하게 된다.
- 클래스 생성에 있어서 바뀔 수 있는 부분과 바뀌지 않는 부분을 분리시키는 팩토리 패턴을 사용하면 생성과 구현의 상호 의존도를 줄일 수 있다. 상위 클래스의 코드에 하위 클래스의 이름을 감추기 위한 방법으로도 사용된다.
- 팩토리는 다른 클래스의 객체를 생성하는 클래스를 일컫는다. 팩토리 패턴은 팩토리 메소드 패턴, 추상 팩토리 패턴으로 분류 된다.
- 팩토리 메소드 패턴은 인터페이스를 통해서 객체를 생성하지만 서브 클래스가 객체 생성에 필요한 클래스를 선택하는 패턴이다. 상위 클래스가 바뀌어도 메인 프로그램이 변경되는 것이 최소화 된다.
- 추상 팩토리 패턴은 객체 생성에 필요한 클래스를 노출하지 않고 객체를 생성하는 인터페이스이다. 내부적으로 다른 팩토리 객체를 생성한다.

### 퍼사드 패턴(구조 패턴)
- 어떤 서브 시스템의 일련의 인터페이스에 대한 통합된 인터페이스를 제공한다. 퍼사드에서 고수준 인터페이스를 정의하기 때문에 서브시스템을 쉽게 사용할 수 있다.
- 통합된 단일 인터페이스를 제공하여 클라이언트가 쉽게 서브시스템에 접근하는 경우 설계하기 좋은 구조이다. 클라이언트와 내부 구현을 분리하여 설계한다.
- 통합 단일 인터페이스를 통해서 내부에 접근하기 때문에 클라이언트 입장에서 매우 편리하다.
- 퍼사드: 외부에서 접근할 때 깔끔하게 서브시스템을 감싸는 역할로 어떤 서브시스템이 어떤 요청에 알맞은 것인지 알고 있다.
- 시스템: 전체 시스템을 하나의 복잡한 복합체로 만드는 여러 서브시스템의 집합.
- 클라이언트: 퍼사드를 통해 서브시스템과 통신한다. 복잡한 시스템의 구조를 알지 못한다.

### 프록시 패턴(구조 패턴)
- 프록시는 대리자, 대변인이라는 뜻으로 다른 누군가를 대신해서 역할을 수행하는 존재라는 의미이다. 즉 프록시에게 어떤 일을 대신 시키는 것이다. 인터페이스를 사용하고 실행시킬 클래스에 대한 객체가 들어갈 자리에 대리자 객체를 대신 투입해서 클라이언트 쪽에서 실제 실행되는 루틴을 모르게 처리한다. 중요한 것은 결과값은 동일하고 흐르제어만 한다는 것이다.
- 웹 관점에서 프록시 서버를 보면 크라이언트가 특정 웹 사이트에 접속하면 프록시 서버가 이에 알맞은 서버에 요청을 보내고 결과를 받아 클라이언트에게 전달한다. 프록시 서버는 요청을 캡슐화하여 안전하 분산 시스템 구조에 적합하다.
- 디자인 패턴 관점에서는 프록시 클래스는 객체의 인터페이스 역할을 한다.
- 복잡한 시스템을 간단히 표현할 수 있고 객체에 대한 보안성을 제공한다. 클라이언트는 객체에 직접 접근할 수 없다. 다른 서버가 존재하는 경우 외부 객체에 대한 로컬 인터페이스를 제공한다.
- 프록시 패턴의 역할은 특정 객체의 대리 객체를 제공해 접근을 제어하고 분산 구조를 지원하기 위한 인터페이스를 제공한다. 또한 객체를 보호한다.
- 프록시 패턴은 퍼사드 패턴과 유사한데, 사용 목적에서 다르다. 프록시는 클라이언트와 객체 사이의 중재자 역할이지만 퍼사드 패턴은 여러 객체에 대한 하나의 통합된 간단한 인터페이스 역할이다.

### 옵서버(리스너) 패턴(행위 패턴)
- 옵서버 패턴은 상태를 가지고 있는 주체 객체와 상태의 변경을 알아야하는 관찰 객체가 존재하여 관찰 객체가 여러개 도는 한 개의 주체 객체의 변경을 조사하는 패턴이다. 객체들의 관계가 복잡할수록 구현하기가 어렵기 때문에 이를 쉽게한다. 데이터의 변경이 발생했을 경우 상대 클래스나 객체에 의존하지 않으면서 데이터 변경을 통보할 수 있다.
- 여러 객체가 존재하고 그것의 데이터 변화에 대해서 알리고 알림 받는 작업이 필요한 상황에서 주로 사용된다.
- 옵서버 패턴은 서브젝트, 옵서버, 구체적 옵서버로 구성된다. 서브젝트는 여러 옵서버를 관리한다. 옵서버는 서브젝트 클래스의 메소드를 통해서 자신을 등록한다.
- 옵서버는 서브젝트 감시하는 객체를 위한 인터페이스를 제공한다. 데이터의 변경을 통보 받는 인터페이스이다.
- 구체적 옵서버는 옵서버와 상속관계로 서브젝트의 변경을 통보 받고 상태를 저장하는 클래스이다. 옵서버 인터페이스 메소드를 통해서 상태를 일관되게 유지한다.
- 구체적 옵서버가 실제 구독자라면 서브젝트가 뉴스가 될 수 있다.
- 서브젝트의 등록/등록 해제 메소드를 통해서 옵서버를 관리한다. 등록/해제 메소드는 옵서버 내부에 서브젝트 객체가 있어서 이를 통해 옵서버가 서브젝트를 등록/해제 한다. 옵서버는 서브젝트를 관리하는 객체로 메소드를 갖고 있고 이를 통해서 서브젝트의 알림 사항을 모든 구체적 옵서버들이 받게 된다.

### 커맨드 패턴(행위 패턴)
- 커맨드 패턴은 객체가 특정 기능을 바로 수행하거나 나중에 트기허라 때 필요한 모든 정보들을 캡슐화하는 행동 패턴이다. 캡슐화하는 정보들은 메소드명, 메소드를 소유하는 객체, 메소드 인자들이다.
- 이벤트가 발생했을 때 실행될 기능이 다양하면서도 변경이 필요한 경우에 이벤트를 발생시키는 클래스를 변경하지 않고 재사용하고자 할 때 유용하다.
- 커맨드 클래스는 실행될 기능에 대한 인터페이스를 담당하며 실행될 기능을 execute 메소드로 선언한다. 구체적 커맨드는 실제로 실행되는 기능을 구현한다. Invoker는 기능의 실행을 요청하는 호출자 클래스이다. Receiver는 구체적 커맨드에서 execute 메소드를 구현할 때 필요한 클래스로 구체적 커맨드의 기능을 실행하기 위해 사용하는 수신자 클래스이다.
- Redo나 Rollback 기능 시 주로 사용하고 비동기 작업 수행 시에도 사용한다. 큐에 커맨드를 순서대로 저장할 수 있고 기존 코드를 수정하지 않고 새로운 커맨드를 쉽게 추가할 수 있어 유용하다.

### 템플릿 패턴(행위 패턴)
- 어떤 작업을 처리하는 일부분을 서브 클래스로 캡슐화해 전체 일을 수행하는 구조는 바꾸지 않으면서 특정 단계에서 수행하는 내역을 바꾸는 패턴이다. 전체적으로는 동일하면서 부분적으로는 다른 구문으로 구성된 메서드의 코드 중복을 최소화 할 때 유용하다.
- 다른 관점에서 보면 동일한 기능을 상위 클래스에서 정의하고 확장/변화가 필요한 부분만 서브 클래스에서 구현한다. 전체적인 알고리즘은 상위 클래스에서 구현하고 다른 부분은 하위 클래스에서 구현하도록 함으로써 전체적인 알고리즘 코드를 재사용하는데 유용하다.
- 추상 클래스는 알고리즘의 각 단계를 정의하는 추상 메소드로 구성하고 구체 클래스에서 여러 추상 메소드로 구성된 알고리즘의 서브 클래스를 구현한다. 추상 클래스 안에 템플릿 메소드를 활용하여 알고리즘의 뼈대를 정의한다.
- 한꺼번에 구체 클래스를 구현하지 않고 추상클래스의 템플릿 메서드를 구현해 놓으면 구체클래스가 이를 상속받아 자신이 필요한 메소드를 작성해주는 방식이다.

### 상태 패턴(행위 패턴)
- 상태 패턴은 객체가 특정 상태에 따라서 행위를 달리하는 상황에서 자신이 직접 상태를 체크하여 상태에 따라 호출하지 않고 상태를 객체화하여 상태가 행동할 수 있도록 위임하는 패턴을 말한다. 즉, 객체의 특정 상태를 클래스로 선언하고 클래스에서는 해당 상태에서 할 수 있는 행위들을 메서드로 정의한다. 그리고 이러한 상태 클래스들을 인터페이스로 캡슐화하여 클라이언트에서 호출하는 방식이다.
- 상태는 객체의 행위를 캡슐화하는 인터페이스이다. 구체적 상태는 상태 인터페이스를 구현하는 서브클래스로 특정 상태의 객체의 행위를 구현한다. Context는 사용자가 선택한 인터페이스를 정의한다. 특정 상태의 객체를 구현한 구체적 상태 서브 클래스의 인스턴스를 갖고 있다.
- 다형성 구현이 쉬워 새로운 상태를 쉽게 추가할 수 있다. 또한 객체의 행위는 해당 상태의 실행 함수의 결가값이 같게 된다

### 데코레이터 패턴(구조 패턴)
- 객체의 결합 을 통해 기능을 동적으로 유연하게 확장 할 수 있게 해주는 패턴으로 기본 기능에 추가할 수 있는 기능의 종류가 많은 경우에 각 추가 기능을 Decorator 클래스로 정의 한 후 필요한 Decorator 객체를 조합함으로써 추가 기능의 조합을 설계 하는 방식이다.
- 기본 기능에 추가할 수 있는 많은 종류의 부가 기능에서 파생되는 다양한 조합을 동적으로 구현할 수 있다. 구성요소는 기본 기능을 뜻하는 구체적 구성요소와 추가 기능을 뜻하는 데코레이터의 공통 기능을 정의한다. 즉, 클라이언트는 컴포넌트를 통해서 실제 객체를 사용한다. 데코레이터는 많은 수가 존재하는 구체적인 데코레이터의 공통기능을 제공한다. 구체적 데코레이터들을 통해서 하위 클래스로 기본 기능에 추가되는 방식이다.

### MVC 패턴
- MVC 패턴은 MVC는 모델-뷰-컨트롤러라는 의미로 3가지의 형태로 역할을 분리하여 개발하는 방법이다.
- 사용자 인터페이스로부터 비즈니스 로직을 분리하여 애플리케이션의 시각적 요소나 그 이면에서 실행되는 비즈니스 로직을 서로 영향 없이 쉽게 고칠 수 있는 애플리케이션을 만들 수 있다. 이는 UI 디자이너와 개발자 간의 업무 분리에 아주 탁월하다.
- 컨트롤러는 모델과 뷰를 연결하는 부분을 의미한다. 사용자의 요청에 따라 모델에 명령을 보냄으로써 모델의 상태를 변경할 수 있다. 또, 컨트롤러가 관련된 뷰에 명령을 보냄으로써 모델의 표시 방법을 바꿀 수 있다.
- 모델은 데이터(데이터베이스)처리하는 부분을 의미한다. 모델의 상태에 변화가 있을 때 컨트롤러와 뷰에 이를 통보한다. 이와 같은 통보를 통해서 뷰는 최신의 결과를 보여줄 수 있고, 컨트롤러는 모델의 변화에 따른 적용 가능한 명령을 추가·제거·수정할 수 있다.
- 뷰는 화면을 의미한다. 사용자가 볼 결과물을 생성하기 위해 모델로부터 정보를 얻어 온다.
