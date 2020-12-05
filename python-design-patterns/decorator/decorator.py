# Python 에서 추상 클래스와 메소드를 만들기 위해 추가
from abc import ABCMeta, abstractmethod


# 음료 클래스
class Beverage(object):
    __metaclass__ = ABCMeta  # 추상 클래스로 선언

    def __init__(self):
        self.description = "Null"

    def get_description(self):
        return self.description

    @abstractmethod
    # 추상 메소드 선언
    def cost(self):
        pass


# 음료를 상속받은 아메리카노 객체 선언
class Americano(Beverage):
    # 아메리카노 객체 생성
    def __init__(self):
        self.description = "Americano"

    # 가격을 리턴하는 함수
    def cost(self):
        return 1.99


# 데코레이터 클래스 선언
class CondimentDecorator(Beverage):
    __metaclass__ = ABCMeta

    @abstractmethod
    def get_description(self):
        pass


# 소이밀크를 추가하는 클래스 선언 - 데코레이터 상속
class Soy(CondimentDecorator):
    def __init__(self, beverage):
        self.beverage = beverage

    # 기존 음료에 소이밀크 추가
    def get_description(self):
        return self.beverage.get_description() + ", Soy"

    # 기존 음료수 가격에 소이밀크 가격 추가
    def cost(self):
        return self.beverage.cost() + 0.5


a = Americano()
a_soy = Soy(a)
print(a_soy.get_description(), a_soy.cost())
