import java.util.HashMap;
import java.util.Map;

public class Json {
  public Map<String, Object> parse(String str) {
    Map<String, Object> result = new HashMap<>();
    result.put("address", "서울시 개발구 객체동");
    return result;
  }
}