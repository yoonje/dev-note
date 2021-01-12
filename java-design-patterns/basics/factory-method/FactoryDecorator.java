public class FactoryDecorator {
  public static void main(String[] args) {
    FighterFactory factory = new FighterFactory();
    
    factory.getFighter(false, false, false).attack();
    // 탄환 발사

    factory.getFighter(true, false, true).attack();
    // 탄환 발사
    // 레이저 발사
    // 플라즈마 발사

    factory.getFighter(true, true, false).attack();
    // 탄환 발사
    // 레이저 발사
    // 미사일 발사

    factory.getFighter(true, true, true).attack();
    // 탄환 발사
    // 레이저 발사
    // 미사일 발사
    // 플라즈마 발사
  }
}