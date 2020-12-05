class Singleton(object):
    def __new__(cls): # cls는 self와 비슷한 기능을 한다.
                      # 다만 클래스 메소드일 경우 반드시 cls를 사용한다.
                      # 클래스 메소드와 정적 메소드는 둘다 클래스에서 접근이 가능하다.(상속했을 경우 차이가 남.)
                      # 인스턴스 메소드는 객체를 메모리 상에 로드해야 사용가능하다.
        if not hasattr(cls, 'instance'):
            cls.instance = super().__new__(cls)
        return cls.instance

s = Singleton()
print("Object created", s)

s1 = Singleton()
print("Object created", s1)

print("Object created", Singleton())