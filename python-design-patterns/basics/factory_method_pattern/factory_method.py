from abc import ABCMeta, abstractmethod


class Section(metaclass=ABCMeta):
    
    @abstractmethod
    def describe(self):
        pass


class PersonalSection(Section):
    
    def describe(self):
        print("Personal Section")


class AlbumSection(Section):
    
    def describe(self):
        print("Album Section")


class PatentSection(Section):
    
    def describe(self):
        print("Patent Section")


class PublicationSection(Section):
    
    def describe(self):
        print("Publication Section")


class Profile(metaclass=ABCMeta):
    
    def __init__(self):
        self.sections = []
        self.createProfile()
    
    @abstractmethod
    def createProfile(self):
        pass
    
    def getSections(self):
        return self.sections
    
    def addSections(self, section):
        self.sections.append(section)


class linkedin(Profile):
    
    def createProfile(self):
        self.addSections(PersonalSection())
        self.addSections(PatentSection())
        self.addSections(PublicationSection())


class facebook(Profile):
    
    def createProfile(self):
        self.addSections(PersonalSection())
        self.addSections(AlbumSection())


if __name__ == '__main__': # 위 코드를 import 했을 때 사용하지 않기 위해서 사용함. 위 코드를 직접 실행하는 경우만 실행됨.
    profile_type = input("Which Profile you'd like to create? [LinkedIn or FaceBook]")
    profile = eval(profile_type.lower())() # 문자열을 실행한 값을 돌려준다.
    print("Creating Profile..", type(profile).__name__) # __name__은 함수나 클래스의 이름이 자동적으로 갖고 있는 변수
    print("Profile has sections --", profile.getSections())